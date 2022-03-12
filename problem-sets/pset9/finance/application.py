import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # get all holdings as row
    holdings = db.execute(
        "SELECT stock, SUM(shares) as shares FROM transactions WHERE user_id=? GROUP BY stock HAVING SUM(shares)>0", session["user_id"])
    # variable for total value
    totalHoldingsValue = 0
    # loop through rows to get current price and add it up.
    for holding in holdings:
        # lookup stock
        quote = lookup(holding["stock"])
        # get stock name
        holding["name"] = quote["name"]
        # get current price
        holding["price"] = usd(quote["price"])
        # price times shares
        holding["total"] = holding["shares"] * quote["price"]
        holding["totalusd"] = usd(holding["total"])
        # add up totals
        totalHoldingsValue = totalHoldingsValue+holding["total"]
    # get user cash
    cash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
    # add stock values and cash
    totalValue = totalHoldingsValue+cash[0]["cash"]
    return render_template("index.html", holdings=holdings, cash=usd(cash[0]["cash"]), total=usd(totalValue))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # check for missing stock name
        if not request.form.get("symbol"):
            return apology("Missing stock name", 400)
        # check for valid stock name
        quote = lookup(request.form.get("symbol"))
        if quote is None:
            return apology("Invalid stock", 400)
        # check for input in shares
        if not request.form.get("shares"):
            return apology("Missing number of shares", 400)
        # check for valid share number
        shares = int(request.form.get("shares"))
        if shares < 1:
            return apology("No shares to buy", 400)
        # else if stock found
        else:
            # fill variables
            name = quote["name"]
            stock = quote["symbol"]
            price = quote["price"]
            # obtain user balance
            rows = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
            balance = rows[0]["cash"]
            # calculate cost of purchase
            cost = float(price) * int(shares)
            # check for sufficient funds
            if cost <= balance:
                # TODO process purchase
                # update user's cash balance
                remaining_balance = balance - cost
                db.execute("UPDATE users SET cash = ? WHERE id = ?", remaining_balance, session["user_id"])
                # insert transaction into transaction table
                db.execute("INSERT INTO transactions (user_id, stock, shares, price, operation, transTotal) VALUES (?,?,?,?,?,?)",
                            session["user_id"],
                            stock.upper(),
                            shares,
                            price,
                            "buy",
                            cost,
                           )
                # indicate successfull purchase
                flash("Purchase successful")
                # redirect to index
                return redirect("/")
            # if insufficient balance
            elif cost > balance:
                return apology("Insufficient funds", 403)
    elif request.method == "GET":
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT * FROM transactions WHERE user_id=? ORDER BY timestamp DESC", session["user_id"])
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""
    # Forget any user_id
    session.clear()
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)
        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)
        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)
        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        # Redirect user to home page
        flash("Logged in")
        return redirect("/")
    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""
    # Forget any user_id
    session.clear()
    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():

    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Missing stock name", 400)
        quote = lookup(request.form.get("symbol"))
        if quote is None:
            return apology("Invalid stock", 400)
        else:
            name = quote["name"]
            symbol = quote["symbol"]
            price = quote["price"]
            flash("Stock found!")
            return render_template("price.html", name=name, symbol=symbol, price=price)

    elif request.method == "GET":
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        pass_str = request.form.get("password")
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Check passwords match
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords don't match", 400)

        # check if password over 6 characters
        elif len(pass_str) < 6:
            return apology("passwords too short (min 6 characters)", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Check if username already exists
        if len(rows) == 0:
            username = request.form.get("username")
            # Hash the password for insertion
            passhash = generate_password_hash(pass_str)
            # insert username and password into username table
            db.execute("INSERT INTO users (username, hash) VALUES(?,?)", username, passhash)
            # Go to index
            flash("Registration successful")
            return redirect("/")
        elif len(rows) > 0:
            return apology("username already exists, ented different username", 400)

    # For GET requests
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        # if no stocks selected
        if not request.form.get("symbol"):
            return apology("stock not selected", 400)
        # if shares amount not entered
        if not request.form.get("shares"):
            return apology("missing number of shares", 400)
        # fill variables from form
        sellstock = request.form.get("symbol")
        sellshares = int(request.form.get("shares"))
        # if sharel less than 1
        if sellshares < 1:
            return apology("invalid share amount", 400)
        # check how many actually owned
        owned = db.execute("SELECT SUM(shares) AS shares FROM transactions WHERE user_id=? AND stock=?",
                            session["user_id"], sellstock)
        # if trying to sell more than own
        ownedshares = int(owned[0]["shares"])
        if ownedshares < sellshares:
            return apology("Trying to sell more than you own", 400)
        # if enough to sell
        elif ownedshares >= sellshares:
            # lookup current price
            currentinfo = lookup(sellstock)
            currentprice = currentinfo["price"]
            sellamount = currentprice * sellshares
            # insert into transactions
            db.execute("INSERT INTO transactions (user_id, stock, shares, price, operation, transTotal) VALUES (?,?,?,?,?,?)",
                        session["user_id"],
                        sellstock,
                        -sellshares,
                        currentprice,
                        "sell",
                        sellamount,
                        )
            # update user cash
            db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", sellamount, session["user_id"])
            flash("Sale Completed!")
            return redirect("/")

    elif request.method == "GET":
        # get shares that user owns
        holdings = db.execute(
            "SELECT stock, SUM(shares) as shares FROM transactions WHERE user_id=? GROUP BY stock HAVING SUM(shares)>0", session["user_id"])
        return render_template("sell.html", holdings=holdings)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
