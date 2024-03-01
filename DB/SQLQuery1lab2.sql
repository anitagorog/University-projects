use Kaufland_database_l1;
-- lab2


--insert
INSERT INTO Cosmetics
	(id, type_of, name_of, price)
VALUES
	(44, 'shampoo', 'Head&S', 23),
	(1, 'hand cream', 'Nivea', 25),
	(2, 'shampoo', 'Head&S', 18),
	(3, 'shampoo', 'Nivea', 21),
	(4, 'hand cream', 'Nivea', 22),
	(12, 'shaving gel', 'Nivea', 23);

INSERT INTO CosmeticProductsBrands
	(id, name_of)
VALUES 
	(9, 'Nivea'),
	(8, 'Head&S'),
	(20, 'Cerave');

INSERT INTO CosmeticProductsTypes
	(id, type_of)
VALUES 
	(7, 'hand cream'),
	(6, 'shampoo'),
	(5, 'body cream');

INSERT INTO Vegetables
	(id, name_veg)
VALUES
	(11, 'carrot'),
	(12, 'cellery'),
	(13, 'tomato');

SELECT * FROM CosmeticProductsBrands;
SELECT * FROM CosmeticProductsTypes;
SELECT * FROM Cosmetics;
SELECT * FROM Vegetables;


--update
UPDATE Cosmetics
	SET price = 20;

UPDATE Cosmetics
	SET price = 21
WHERE name_of = 'Nivea' OR name_of = 'Head&S';

UPDATE Cosmetics
	SET price = 20
WHERE price IS NULL;

UPDATE Vegetables
	SET id = 10
WHERE name_veg = 'carrot' AND id <> 10;

UPDATE CosmeticProductsBrands
	SET id = 5
WHERE name_of = 'Head&S';

UPDATE Cosmetics
	SET price = 10
WHERE type_of IN ( SELECT T.type_of
					FROM CosmeticProductsTypes T
					WHERE T.id = 6 )


--delete
DELETE FROM Vegetables;
DELETE FROM CosmeticProductsBrands;
DELETE FROM Cosmetics;
DELETE FROM CosmeticProductsTypes;

DELETE FROM Vegetables
WHERE id = 12;

DELETE FROM Cosmetics
WHERE NOT id = 2;

DELETE FROM Cosmetics
WHERE price < 20;

DELETE FROM Cosmetics
WHERE price <= 21;

DELETE FROM Cosmetics
WHERE price > 21;

DELETE FROM Cosmetics
WHERE price >= 18;

DELETE FROM Cosmetics
WHERE price IS NOT NULL;

DELETE FROM Cosmetics 
WHERE price BETWEEN 18 AND 21;

DELETE FROM Cosmetics
WHERE name_of LIKE '%a';


--a) union
SELECT B.name_of 
FROM CosmeticProductsBrands B
UNION
SELECT T.type_of
FROM CosmeticProductsTypes T

SELECT B.id 
FROM CosmeticProductsBrands B
UNION ALL --(needed?)
SELECT T.id
FROM CosmeticProductsTypes T

SELECT TOP 2 C.price               -- TOP
FROM Cosmetics C
WHERE C.id = 1 OR C.id = 2;

SELECT C.price
FROM Cosmetics C
WHERE C.id = 1
UNION 
SELECT C.price
FROM Cosmetics C
WHERE C.id = 2

SELECT * FROM CosmeticProductsBrands;
SELECT * FROM CosmeticProductsTypes;
SELECT * FROM Cosmetics;
SELECT * FROM Vegetables;


--b) intersection
SELECT C.id
FROM Cosmetics C
WHERE C.price < 25
INTERSECT
SELECT C.id
FROM Cosmetics C
WHERE C.name_of = 'Nivea'

SELECT C.id
FROM Cosmetics C
WHERE C.price < 25 AND C.price IN (SELECT C2.price
									FROM Cosmetics C2
									WHERE C2.name_of = 'Nivea')


--c) difference
SELECT C.id, C.name_of
FROM Cosmetics C
WHERE C.id < 3
EXCEPT
SELECT C.id, C.name_of
FROM Cosmetics C
WHERE C.name_of = 'Head&S';

SELECT C.id, C.name_of, C.price, C.price/4 AS in_euro
FROM Cosmetics C
WHERE C.id < 3 AND C.id NOT IN (SELECT C2.id
								FROM Cosmetics C2
								WHERE C2.name_of = 'Head&S')

SELECT * FROM CosmeticProductsBrands
SELECT * FROM CosmeticProductsTypes
SELECT * FROM Cosmetics
--d) JOIN operations
-- many to many - INNER
SELECT B.name_of, T.type_of
FROM CosmeticProductsBrands B
INNER JOIN CosmeticProductsTypes T ON B.id <> T.id;

-- 3 tables - FULL OUTER
SELECT B.name_of, T.type_of
FROM CosmeticProductsBrands B
FULL OUTER JOIN Cosmetics C ON B.name_of = C.name_of
FULL OUTER JOIN CosmeticProductsTypes T ON C.type_of = T.type_of

-- LEFT OUTER
SELECT B.name_of, C.type_of
FROM CosmeticProductsBrands B
LEFT OUTER JOIN Cosmetics C ON C.name_of = B.name_of;

-- RIGHT OUTER
--SELECT C.name_of, T.type_of
SELECT *
FROM Cosmetics C
RIGHT OUTER JOIN CosmeticProductsTypes T ON C.type_of = T.type_of;


--e) with the IN operator and a subquery in the WHERE clause
-- the subquery must include a subquery in its own WHERE clause, in at least one case
SELECT DISTINCT C.id, C.name_of                                                               -- DISTINCT
FROM Cosmetics C
WHERE C.id IN (SELECT C2.id
				FROM Cosmetics C2
				WHERE C2.name_of IN (SELECT B.name_of
										FROM CosmeticProductsBrands B
										WHERE B.name_of LIKE '%a'))

SELECT DISTINCT C.id, C.name_of
FROM Cosmetics C
WHERE (C.price < 25) AND C.price IN (SELECT C2.price
									FROM Cosmetics C2
									WHERE C2.name_of = 'Nivea')


--f)  with the EXISTS operator and a subquery in the WHERE clause          -- EXISTS !
SELECT DISTINCT B.id, B.name_of
FROM CosmeticProductsBrands B
WHERE EXISTS (SELECT C.name_of
				FROM Cosmetics C
				WHERE C.name_of = B.name_of)

SELECT TOP 1 B.id, B.name_of
FROM CosmeticProductsBrands B
WHERE NOT EXISTS (SELECT C.name_of
				FROM Cosmetics C
				WHERE C.name_of = B.name_of)


--g) with a subquery in the FROM clause
SELECT DISTINCT T.type_of
FROM (SELECT C.type_of
		FROM Cosmetics C) T
WHERE T.type_of LIKE 's%'

SELECT TOP 1 *
FROM (SELECT B.name_of
		FROM CosmeticProductsBrands B
		WHERE B.name_of LIKE 'C%' OR B.name_of LIKE 'N%')  N

SELECT * FROM Cosmetics
--h) 4 queries with the GROUP BY clause, 3 of which also contain the HAVING clause; 
--2 of the latter will also have a subquery in the HAVING clause; use the aggregation operators: COUNT, SUM, AVG, MIN, MAX

SELECT C.name_of, AVG(C.price) AS average_price, MIN(C.price) AS min_price, MAX(C.price) AS max_price, COUNT(*)
FROM Cosmetics C
GROUP BY C.name_of
HAVING COUNT(C.name_of) > 1 
ORDER BY C.name_of
-- !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

SELECT B.name_of
FROM CosmeticProductsBrands B
GROUP BY B.name_of
HAVING B.name_of IN (SELECT C.name_of
						FROM Cosmetics C)
ORDER BY B.name_of DESC                     -- DESC 

SELECT T.type_of
FROM CosmeticProductsTypes T
GROUP BY T.type_of
HAVING T.type_of IN (SELECT C.type_of
						FROM Cosmetics C)

SELECT C.name_of, SUM(C.price) AS sum_of_prices
FROM Cosmetics C
GROUP BY C.name_of
ORDER BY SUM(C.price) DESC


SELECT * FROM CosmeticProductsBrands;
SELECT * FROM CosmeticProductsTypes;
SELECT * FROM Cosmetics;


--i) 4 queries using ANY and ALL to introduce a subquery in the WHERE clause (2 queries per operator); 
--rewrite 2 of them with aggregation operators, and the other 2 with IN / [NOT] IN.
SELECT *
FROM Cosmetics C
WHERE C.price > ANY (SELECT C.price
						FROM Cosmetics C
						WHERE NOT C.name_of = 'Head&S')
SELECT *
FROM Cosmetics C
WHERE C.price IN (SELECT C2.price
					FROM Cosmetics C2
					WHERE C2.price > (SELECT TOP 1 C3.price
										FROM Cosmetics C3
										WHERE NOT C3.name_of = 'Head&S'
										ORDER BY C3.price))

--trial
SELECT *
FROM Cosmetics C
WHERE C.price IN (SELECT C2.price
					FROM Cosmetics C2
					WHERE C2.price > 21)



SELECT C.name_of, C.price
FROM Cosmetics C
WHERE C.price >= ALL (SELECT C.price
						FROM Cosmetics C
						WHERE NOT C.name_of = 'Head&S')
SELECT C.name_of, C.price
FROM Cosmetics C
WHERE C.price IN (SELECT C2.price
					FROM Cosmetics C2
					WHERE C2.price >= (SELECT TOP 1 MAX(C3.price)
										FROM Cosmetics C3
										GROUP BY C3.name_of
										HAVING NOT C3.name_of = 'Head&S'
										ORDER BY MAX(C3.price) DESC))

--trial
SELECT C.name_of, MAX(C.price) AS price
FROM Cosmetics C
GROUP BY C.name_of
HAVING NOT C.name_of = 'Head&S'



SELECT *
FROM Cosmetics C
WHERE C.price > ANY (SELECT C.price
						FROM Cosmetics C
						WHERE NOT C.name_of = 'Nivea')
SELECT *
FROM Cosmetics C
WHERE C.price IN (SELECT C2.price
					FROM Cosmetics C2
					WHERE C2.price > (SELECT TOP 1 C3.price
										FROM Cosmetics C3
										WHERE NOT C3.name_of = 'Nivea'
										ORDER BY C3.price))

--trial
SELECT *
FROM Cosmetics C
WHERE C.price IN (SELECT C2.price
					FROM Cosmetics C2
					WHERE C2.price > 18)


SELECT * FROM Cosmetics;



SELECT C.name_of, C.price
FROM Cosmetics C
WHERE C.price > ALL (SELECT C.price
						FROM Cosmetics C
						WHERE NOT C.name_of = 'Nivea')
SELECT C2.name_of, C2.price
FROM Cosmetics C2
WHERE C2.price > (SELECT TOP 1 MAX(C3.price)
					FROM Cosmetics C3
					GROUP BY C3.name_of
					HAVING NOT C3.name_of = 'Nivea'
					ORDER BY MAX(C3.price) DESC)

--just a few trials
SELECT C.name_of, MAX(C.price) AS price
FROM Cosmetics C
GROUP BY C.name_of
HAVING C.name_of = 'Nivea'
--
SELECT C.name_of, C.price
FROM Cosmetics C
WHERE C.price IN (SELECT C2.price
					FROM Cosmetics C2
					WHERE C2.price > (SELECT TOP 1 MAX(C3.price)
										FROM Cosmetics C3
										GROUP BY C3.name_of
										HAVING NOT C3.name_of = 'Nivea'
										ORDER BY MAX(C3.price) DESC))

