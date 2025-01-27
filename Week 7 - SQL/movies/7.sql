SELECT title, rating
FROM ratings
JOIN movies on movies.id = ratings.movie_id
WHERE year = 2010
ORDER BY rating DESC, title;
