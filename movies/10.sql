SELECT name FROM directors
JOIN movies ON directors.movie_id = movies.id
JOIN ratings ON ratings.movie_id = movies.id
JOIN people ON people.id = directors.person_id
WHERE rating >= 9;
