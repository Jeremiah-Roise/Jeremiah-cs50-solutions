-- Keep a log of any SQL queries you execute as you solve the mystery.
.schema on -- enable headers.

.schema -- get a general overview of the database.

SELECT * FROM crime_scene_reports; -- see what this table is about.

SELECT * FROM crime_scene_reports 
    WHERE street LIKE "Humphrey Street%"; -- narrow search down to Humphrey street only.

SELECT * FROM crime_scene_reports WHERE id == 295; -- get only the report of the duck robbery.

SELECT * FROM bakery_security_logs; -- get the general feel of the table

SELECT id, hour, minute, license_plate FROM bakery_security_logs
WHERE year == 2021 AND month == 7 and day == 28; -- select logs from day of robbery.

SELECT id, hour, minute, license_plate FROM bakery_security_logs
WHERE year == 2021 AND month == 7 and day == 28 AND hour == 10 ; -- further refine search

SELECT id, hour, minute, license_plate FROM bakery_security_logs
WHERE year == 2021 AND month == 7 and day == 28 AND hour == 10 AND minute == 15; -- further refine search

.schema -- get a general overview of the database.

SELECT * FROM bakery_security_logs
JOIN people ON people.license_plate = bakery_security_logs.license_plate
WHERE year == 2021 AND month == 7 and day == 28 AND hour == 10; -- cross reference bakery license plate log with people.

SELECT name, activity FROM bakery_security_logs
JOIN people ON people.license_plate = bakery_security_logs.license_plate
WHERE year == 2021 AND month == 7 and day == 28 AND hour == 10; -- refine query.

SELECT name, flight_id FROM bakery_security_logs
JOIN people ON people.license_plate = bakery_security_logs.license_plate
JOIN passengers ON passengers.passport_number = people.passport_number
WHERE year == 2021 AND month == 7 and day == 28 AND hour == 10; -- cross reference with airplane passenger lists.

SELECT name, city FROM bakery_security_logs
JOIN people ON people.license_plate = bakery_security_logs.license_plate
JOIN passengers ON passengers.passport_number = people.passport_number
JOIN flights ON flights.id = passengers.flight_id
JOIN airports ON origin_airport_id
WHERE bakery_security_logs.year == 2021 AND bakery_security_logs.month == 7 and bakery_security_logs.day == 28 AND bakery_security_logs.hour == 10; -- get origin city of flights

SELECT name, city FROM bakery_security_logs
JOIN people ON people.license_plate = bakery_security_logs.license_plate
JOIN passengers ON passengers.passport_number = people.passport_number
JOIN flights ON flights.id = passengers.flight_id
JOIN airports ON origin_airport_id
WHERE bakery_security_logs.year == 2021 AND bakery_security_logs.month == 7 and bakery_security_logs.day == 28 AND bakery_security_logs.hour == 10 AND city LIKE "fiftyville"; -- retrieve only those with flights from fiftyville.

SELECT name, city FROM bakery_security_logs
JOIN people ON people.license_plate = bakery_security_logs.license_plate
JOIN passengers ON passengers.passport_number = people.passport_number
JOIN flights ON flights.id = passengers.flight_id
JOIN airports ON airports.id = flights.origin_airport_id
WHERE flights.year == 2021
    AND flights.month == 7
    AND flights.day == 28
    AND bakery_security_logs.year == 2021
    AND bakery_security_logs.month == 7
    AND bakery_security_logs.day == 28
    AND bakery_security_logs.hour == 10 
    AND city LIKE "fiftyville"; -- retrieve people that were in the bakery and had flights from fiftyville on the same day.

SELECT * FROM interviews; -- get the feel of the interviews table.

SELECT * FROM interviews WHERE year == 2021 AND month == 7 AND day == 28; -- get the feel of the interviews table.


SELECT name, city FROM bakery_security_logs
JOIN people ON people.license_plate = bakery_security_logs.license_plate
JOIN passengers ON passengers.passport_number = people.passport_number
JOIN flights ON flights.id = passengers.flight_id
JOIN airports ON airports.id = flights.origin_airport_id
WHERE flights.year == 2021
    AND flights.month == 7
    AND flights.day == 29
    AND bakery_security_logs.year == 2021
    AND bakery_security_logs.month == 7
    AND bakery_security_logs.day == 28
    AND bakery_security_logs.hour == 10 
    AND city LIKE "fiftyville"; -- modify query based on the info from transcripts.

SELECT * FROM phone_calls;

SELECT call_maker.name, call_receiver.name FROM phone_calls calls
JOIN people call_maker ON call_maker.phone_number = calls.caller
JOIN people call_receiver ON call_receiver.phone_number = calls.receiver
    AND calls.year == 2021
    AND calls.month == 7
    AND calls.day == 28; -- cross check with phones as well.

SELECT name, city FROM bakery_security_logs
JOIN people ON people.license_plate = bakery_security_logs.license_plate
JOIN passengers ON passengers.passport_number = people.passport_number
JOIN flights ON flights.id = passengers.flight_id
JOIN airports ON airports.id = flights.origin_airport_id
JOIN phone_calls ON phone_calls.caller = people.phone_number
WHERE flights.year == 2021
    AND flights.month == 7
    AND flights.day == 29
    AND bakery_security_logs.year == 2021
    AND bakery_security_logs.month == 7
    AND bakery_security_logs.day == 28
    AND bakery_security_logs.hour == 10 
    AND city LIKE "fiftyville"
    AND phone_calls.year == 2021
    AND phone_calls.month == 7
    AND phone_calls.day == 28
    AND name in (
        SELECT call_maker.name FROM phone_calls calls
        JOIN people call_maker ON call_maker.phone_number = calls.caller
        JOIN people call_receiver ON call_receiver.phone_number = calls.receiver
            AND calls.year == 2021
            AND calls.month == 7
            AND calls.day == 28
    ); -- checks for people who were in the bakery, had flights the next day, and made a call on the same day as the bakery robbery

SELECT name FROM bakery_security_logs
JOIN people ON people.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.year == 2021
    AND bakery_security_logs.month == 7
    AND bakery_security_logs.day == 28
    AND bakery_security_logs.hour == 10 

    and passport_number in (
        SELECT passport_number FROM passengers
        JOIN flights ON flights.id = passengers.flight_id
        JOIN airports ON airports.id = flights.origin_airport_id
        WHERE
            airports.city LIKE "fiftyville"
            AND flights.day == 29
            AND flights.month == 7
            AND flights.year == 2021
    )

    and phone_number in (
        SELECT phone_number FROM phone_calls
        WHERE
            phone_calls.year == 2021
            AND phone_calls.month == 7
            AND phone_calls.day == 28
    ); -- refactoring.

SELECT name FROM bakery_security_logs
JOIN people ON people.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.year == 2021
    AND bakery_security_logs.month == 7
    AND bakery_security_logs.day == 28
    AND bakery_security_logs.hour == 10 
    AND bakery_security_logs.minute > 10
    AND bakery_security_logs.minute > 30

    and passport_number in (
        SELECT passport_number FROM passengers
        JOIN flights ON flights.id = passengers.flight_id
        JOIN airports ON airports.id = flights.origin_airport_id
        WHERE
            airports.city LIKE "fiftyville"
            AND flights.day == 29
            AND flights.month == 7
            AND flights.year == 2021
    )

    and phone_number in (
        SELECT phone_number FROM phone_calls
        WHERE
            phone_calls.year == 2021
            AND phone_calls.month == 7
            AND phone_calls.day == 28
    )

    -- check bank transcations.
    AND people.id in (
        SELECT person_id FROM atm_transactions
        JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number
        WHERE
            day = 28
            AND month = 7
            AND year = 2021
    )

    AND name in (
        SELECT call_maker.name FROM phone_calls calls
        JOIN people call_maker ON call_maker.phone_number = calls.caller
        JOIN people call_receiver ON call_receiver.phone_number = calls.receiver
        WHERE
            calls.year == 2021
            AND calls.month == 7
            AND calls.day == 28
    ); -- checks for people who were in the bakery, had flights the next day, made an atm transaction the same day, and made a call on the same day as the bakery robbery








SELECT name, city FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
JOIN flights ON flights.id = passengers.flight_id
JOIN airports ON airports.id = flights.destination_airport_id
WHERE name LIKE "taylor"; -- find where thief escaped too.


SELECT call_receiver.name, calls.duration FROM phone_calls calls
JOIN people call_maker ON call_maker.phone_number = calls.caller
JOIN people call_receiver ON call_receiver.phone_number = calls.receiver
WHERE
    calls.year == 2021
    AND calls.month == 7
    AND calls.day == 28
    AND call_maker.name LIKE "taylor"





SELECT name FROM bakery_security_logs
JOIN people ON people.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.year == 2021
    AND bakery_security_logs.month == 7
    AND bakery_security_logs.day == 28
    AND bakery_security_logs.hour == 10 
    AND bakery_security_logs.minute > 10
    AND bakery_security_logs.minute < 30

    and passport_number in (
        SELECT passport_number FROM passengers
        JOIN flights ON flights.id = passengers.flight_id
        JOIN airports ON airports.id = flights.origin_airport_id
        WHERE
            airports.city LIKE "fiftyville"
            AND flights.day == 29
            AND flights.month == 7
            AND flights.year == 2021
    )

    and phone_number in (
        SELECT phone_number FROM phone_calls
        WHERE
            phone_calls.year == 2021
            AND phone_calls.month == 7
            AND phone_calls.day == 28
    )

    -- check bank transcations.
    AND people.id in (
        SELECT person_id FROM atm_transactions
        JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number
        WHERE
            day = 28
            AND month = 7
            AND year = 2021
    )

    AND name in (
        SELECT call_maker.name FROM phone_calls calls
        JOIN people call_maker ON call_maker.phone_number = calls.caller
        JOIN people call_receiver ON call_receiver.phone_number = calls.receiver
        WHERE
            calls.year == 2021
            AND calls.month == 7
            AND calls.day == 28
    ); -- checks for people who were in the bakery, had flights the next day, made an atm transaction the same day, and made a call on the same day as the bakery robbery


SELECT name FROM bakery_security_logs
JOIN people ON people.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.year == 2021
    AND bakery_security_logs.month == 7
    AND bakery_security_logs.day == 28
    AND bakery_security_logs.hour == 10 
    AND bakery_security_logs.minute > 5
    AND bakery_security_logs.minute < 30

    and passport_number in (
        SELECT passport_number FROM passengers
        JOIN flights ON flights.id = passengers.flight_id
        JOIN airports ON airports.id = flights.origin_airport_id
        WHERE
            airports.city LIKE 'fiftyville'
            AND flights.day == 29
            AND flights.month == 7
            AND flights.year == 2021
    )

    and phone_number in (
        SELECT phone_number FROM phone_calls
        WHERE
            phone_calls.year == 2021
            AND phone_calls.month == 7
            AND phone_calls.day == 28
    )

    -- check bank transcations.
    AND people.id in (
        SELECT person_id FROM atm_transactions
        JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number
        WHERE
            day = 28
            AND month = 7
            AND year = 2021
    )

    AND name in (
        SELECT call_maker.name FROM phone_calls calls
        JOIN people call_maker ON call_maker.phone_number = calls.caller
        JOIN people call_receiver ON call_receiver.phone_number = calls.receiver
        WHERE
            calls.year == 2021
            AND calls.month == 7
            AND calls.day == 28
    ); -- checks for people who were in the bakery, had flights the next day, made an atm transaction the same day, and made a call on the same day as the bakery robbery

-- 2023/04/5
SELECT name FROM people WHERE

    name in (
        SELECT call_receiver.name FROM phone_calls calls
        JOIN people call_maker ON call_maker.phone_number = calls.caller
        JOIN people call_receiver ON call_receiver.phone_number = calls.receiver
        WHERE
            calls.year == 2021
            AND calls.month == 7
            AND calls.day == 28
            AND duration < 60
            AND call_maker.name LIKE 'bruce'
    )
