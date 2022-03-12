-- Keep a log of any SQL queries you execute as you solve the mystery.

/*To see all reports*/
SELECT * FROM crime_scene_reports;

/*To see specific date*/
SELECT * FROM crime_scene_reports WHERE day=28 AND month=7;

/*Report of interest
id | year | month | day | street | description
295 | 2020 | 7 | 28 | Chamberlin Street |
Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
Interviews were conducted today with three witnesses who were present at the time —
each of their interview transcripts mentions the courthouse.*/

/*To see all logs*/
SELECT * FROM courthouse_security_logs WHERE day=28 AND month=7;

/*names of people by license plate on the court log*/
SELECT name FROM courthouse_security_logs
JOIN people ON courthouse_security_logs.license_plate=people.license_plate
WHERE day=28 AND month=7 AND hour=10 AND minute >15 AND minute<25;

/*To see intervies on the day*/
SELECT * FROM interviews WHERE day = 28 AND month = 7;

/*info obtained
161 | Ruth | 2020 | 7 | 28 | Sometime within ten minutes of the theft, I saw the thief get into
a car in the courthouse parking lot and drive away. If you have security footage from the courthouse
parking lot, you might want to look for cars that left the parking lot in that time frame.

162 | Eugene | 2020 | 7 | 28 | I don't know the thief's name, but it was someone I recognized.
Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street
and saw the thief there withdrawing some money.

163 | Raymond | 2020 | 7 | 28 | As the thief was leaving the courthouse, they called someone who
talked to them for less than a minute. In the call, I heard the thief say that they were planning
to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the
other end of the phone to purchase the flight ticket.*/

/*Obtain ATM records from same day Join with Bank Accounts and Join with people*/
SELECT * FROM atm_transactions

SELECT name FROM people JOIN bank_accounts ON people.id=bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number=atm_transactions.account_number
WHERE month=7 AND day=28 AND atm_location='Fifer Street' AND transaction_type='withdraw';


/* check flights*/
SELECT * FROM airports;
/*
1 | ORD | O'Hare International Airport | Chicago
2 | PEK | Beijing Capital International Airport | Beijing
3 | LAX | Los Angeles International Airport | Los Angeles
4 | LHR | Heathrow Airport | London
5 | DFS | Dallas/Fort Worth International Airport | Dallas
6 | BOS | Logan International Airport | Boston
7 | DXB | Dubai International Airport | Dubai
8 | CSF | Fiftyville Regional Airport | Fiftyville
9 | HND | Tokyo International Airport | Tokyo
10 | CDG | Charles de Gaulle Airport | Paris
11 | SFO | San Francisco International Airport | San Francisco
12 | DEL | Indira Gandhi International Airport | Delhi
*/

SELECT * FROM flights WHERE month=7 AND day=29 AND origin_airport_id=8;
/*
all flights out of  Fiftyville on 07/29
id | origin_airport_id | destination_airport_id | year | month | day | hour | minute
18 | 8 | 6 | 2020 | 7 | 29 | 16 | 0 - to Boston
23 | 8 | 11 | 2020 | 7 | 29 | 12 | 15 - to San Francisco
36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20 - to London
43 | 8 | 1 | 2020 | 7 | 29 | 9 | 30 - to Chicago
53 | 8 | 9 | 2020 | 7 | 29 | 15 | 20 - to Tokyo
*/
SELECT name FROM people
JOIN passengers ON people.passport_number=passengers.passport_number
JOIN flights ON passengers.flight_id=flights.id
WHERE month=7 AND day=29 AND origin_airport_id=8 AND flight_id=36;


/*check flight seats for accomplice*/

/*check call logs for accomplice*/
SELECT * FROM phone_calls

/*list of callers that made calls on 07/28 less than 60 secs*/
SELECT name FROM people
JOIN phone_calls ON people.phone_number=phone_calls.caller
WHERE month=7 AND day=28 and duration<60;




/*summerize queries using INTERSECT to find thief*/
SELECT name FROM people
JOIN passengers ON people.passport_number=passengers.passport_number
JOIN flights ON passengers.flight_id=flights.id
WHERE month=7 AND day=29 AND origin_airport_id=8 AND flight_id=36
INTERSECT
SELECT name FROM people
JOIN phone_calls ON people.phone_number=phone_calls.caller
WHERE month=7 AND day=28 and duration<60
INTERSECT
SELECT name FROM people JOIN bank_accounts ON people.id=bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number=atm_transactions.account_number
WHERE month=7 AND day=28 AND atm_location='Fifer Street' AND transaction_type='withdraw'
INTERSECT
SELECT name FROM courthouse_security_logs
JOIN people ON courthouse_security_logs.license_plate=people.license_plate
WHERE day=28 AND month=7 AND hour=10 AND minute >15 AND minute<25;

/*find accomplice*/
SELECT name FROM people WHERE phone_number='(375) 555-8161'

SELECT name, receiver FROM people
JOIN phone_calls ON people.phone_number=phone_calls.caller
WHERE month=7 AND day=28 AND duration<60 AND caller IN (SELECT phone_number FROM phone_calls WHERE
caller IN (SELECT phone_number FROM people WHERE name='Ernest'));