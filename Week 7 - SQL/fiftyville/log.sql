SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28
AND street = 'Humphrey Street';

SELECT transcript
FROM interviews
WHERE year = 2023 AND month = 7 AND day = 28
AND transcript LIKE '%bakery%';

SELECT bakery_security_logs.activity, bakery_security_logs.license_plate, people.name
FROM people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE bakery_security_logs.year = 2023
AND bakery_security_logs.month = 7
AND bakery_security_logs.day = 28
AND bakery_security_logs.hour = 10
AND bakery_security_logs.minute >= 15
AND bakery_security_logs.minute <= 25;

SELECT people.name, atm_transactions.transaction_type
FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE atm_transactions.year = 2023
AND atm_transactions.month = 7
AND atm_transactions.day = 25
AND atm_location = 'Leggett Street'
AND atm_transactions.transaction_type = 'withdraw';

SELECT caller , receiver
FROM phone_calls
WHERE year = 2023
AND month = 7
AND day = 28
AND duration < 60;

UPDATE phone_calls
SET receiver = people.name
FROM people
WHERE phone_calls.receiver  = people.phone_number;

SELECT *
FROM flights
WHERE year = 2023
AND month = 7
AND day = 28
ORDER BY hour ASC;

SELECT *
FROM airports
WHERE id = 4;

SELECT flights.destination_airport_id, name, phone_number, license_plate
FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON flights.id = passengers.flight_id
WHERE flights.id = 36
ORDER BY flights.hour ASC;

SELECT name
FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON flights.id = passengers.flight_id
WHERE ( flights.year = 2023 AND flights.month = 7 AND flights.day = 29 AND flights.id = 36 )
AND name IN
(
    SELECT phone_calls.caller FROM phone_calls
    JOIN bank_accounts ON bank_accounts.person_id = people.id
    JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
    WHERE atm_transactions.year = 2023
    AND atm_transactions.month = 7
    AND atm_transactions.day = 28
    AND atm_location = 'Leggett Street'
    AND atm_transactions.transaction_type = 'withdraw'
)
AND name IN
(
    SELECT bakery_security_logs.activity, bakery_security_logs.license_plate, people.name
    FROM people
    JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
    WHERE bakery_security_logs.year = 2023
    AND bakery_security_logs.month = 7
    AND bakery_security_logs.day = 28
    AND bakery_security_logs.hour = 10
    AND bakery_security_logs.minute >= 15
    AND bakery_security_logs.minute <= 25
);

SELECT caller , receiver
FROM phone_calls
WHERE year = 2023
AND month = 7
AND day = 28
AND duration < 60;

