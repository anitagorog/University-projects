use Kaufland_database_l1;

CREATE TABLE Milk(
	id int NOT NULL,
	name_milk varchar(30) NOT NULL,
	type_milk varchar(30) NOT NULL,
	PRIMARY KEY(name_milk)
);

CREATE TABLE MullerMilk(
	id int NOT NULL,
	ingredients varchar(100),
	expiring_date datetime,
	price float NOT NULL,
	name_milk varchar(30) NOT NULL,
	PRIMARY KEY(id),
	FOREIGN KEY(name_milk)
		REFERENCES Milk(name_milk)
		ON DELETE CASCADE
);

CREATE TABLE NapolactMilk(
	id int NOT NULL,
	ingredients varchar(100),
	expiring_date datetime,
	price float NOT NULL,
	name_milk varchar(30) NOT NULL,
	PRIMARY KEY(id),
	FOREIGN KEY(name_milk)
		REFERENCES Milk(name_milk)
		ON DELETE CASCADE
);

CREATE TABLE Vegetables(
	id int NOT NULL,
	name_veg varchar(30) NOT NULL,
	--color varchar(30) NOT NULL,
	PRIMARY KEY(name_veg)
);

CREATE TABLE Carrots(
	id int NOT NULL,
	name_veg varchar(30) NOT NULL,
	color varchar(30) NOT NULL,
	price float NOT NULL,
	PRIMARY KEY(id),
	FOREIGN KEY(name_veg)
		REFERENCES Vegetables(name_veg)
		ON DELETE CASCADE
);

CREATE TABLE Tomatoes(
	id int NOT NULL,
	name_veg varchar(30) NOT NULL,
	color varchar(30) NOT NULL,
	price float NOT NULL,
	PRIMARY KEY(id),
	FOREIGN KEY(name_veg)
		REFERENCES Vegetables(name_veg)
		ON DELETE CASCADE
);

CREATE TABLE Cellery(
	id int NOT NULL,
	name_veg varchar(30) NOT NULL,
	color varchar(30) NOT NULL,
	price float NOT NULL,
	PRIMARY KEY(id),
	FOREIGN KEY(name_veg)
		REFERENCES Vegetables(name_veg)
		ON DELETE CASCADE
);

CREATE TABLE CosmeticProductsBrands(
	id int NOT NULL,
	name_of varchar(30) NOT NULL,
	PRIMARY KEY(name_of)
);

CREATE TABLE CosmeticProductsTypes(
	id int NOT NULL,
	type_of varchar(30) NOT NULL,
	PRIMARY KEY(type_of)
);

CREATE TABLE Cosmetics(
	id int NOT NULL,
	type_of varchar(30) NOT NULL,
	name_of varchar(30) NOT NULL,
	price float NOT NULL,
	-- PRIMARY KEY(type_of,name_of),  --'two' primary keys
	PRIMARY KEY(id),
	FOREIGN KEY(name_of)
		REFERENCES CosmeticProductsBrands(name_of)
		ON DELETE CASCADE,
	FOREIGN KEY(type_of)
		REFERENCES CosmeticProductsTypes(type_of)
		ON DELETE CASCADE
);

SELECT * FROM Cosmetics
union all
SELECT * FROM Cosmetics
select * from CosmeticProductsBrands 

insert into Cosmetics values (999,null,null,-1)

SELECT * FROM Cosmetics

select count(price) 
from Cosmetics

select * from Cosmetics
where name_of like 'Nive%'

select name_of, price
from Cosmetics
where name_of = 'Nivea'
group by name_of, price


select distinct type_of, name_of
from Cosmetics

SELECT t.type_of, COUNT(*), COUNT(t.type_of) FROM                         ---- check nr appearance of a column
-- SELECT * FROM
(SELECT * FROM Cosmetics
WHERE name_of LIKE '%nivea%') t
INNER JOIN
(SELECT * FROM Cosmetics
WHERE type_of = 'shampoo' or type_of = 'hand cream') t2
ON t.id = t2.id
GROUP BY t.type_of
-- until here every type and how many for each
HAVING COUNT(*) = 2

CREATE TABLE SoyMilk(
	name_milk VARCHAR(30) FOREIGN KEY REFERENCES Milk(name_milk),
	PRIMARY KEY(name_milk),
	expiring_date TIME
);
--DROP TABLE SoyMilk
INSERT INTO MILK
VALUES (1, 'soymilk', 'plant-based')
SELECT * FROM MILK
INSERT INTO SoyMilk
VALUES ('soymilk', GETDATE())
SELECT * FROM SoyMilk
--DELETE FROM SoyMilk

SELECT COUNT(*)                   -- to check if already there or count how many are
FROM SoyMilk
WHERE name_milk = 'soymilk'

-- OR @TableId NOT IN (SELECT TableId FROM Tables)   !!!!!!!!!!
-- or DECLARE @_ INT = 0 and SELECT @_= id FROM ...

GO

CREATE FUNCTION uf_myfunc(@I int)
RETURNS TABLE
AS
RETURN 
	SELECT t.type_of, COUNT(*) AS count_star, COUNT(t.type_of) AS count_type FROM                       ---- check nr appearance of a column
-- SELECT * FROM
(SELECT * FROM Cosmetics
WHERE name_of LIKE '%nivea%') t
INNER JOIN
(SELECT * FROM Cosmetics
WHERE type_of = 'shampoo' or type_of = 'hand cream') t2
ON t.id = t2.id
GROUP BY t.type_of
-- until here every type and how many for each
HAVING COUNT(*) >= @I

GO
--DROP FUNCTION uf_myfunc

SELECT * FROM uf_myfunc(2)