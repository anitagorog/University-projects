use Kaufland_database_l1;
-- LAB 5

--Ta(aid, a2, …)
CREATE TABLE Suppliers(
	supplier_id INT PRIMARY KEY,
	supplier_code INT UNIQUE,
	supplier_name VARCHAR(30)
);
--DROP TABLE Suppliers

--Tb(bid, b2, …)
CREATE TABLE Products(
	product_id INT PRIMARY KEY,
	product_code INT,
	product_type_id INT
);
--DROP TABLE Products

--Tc(cid, aid, bid, …)
CREATE TABLE Purchases(
	purchase_id INT PRIMARY KEY,
	supplier_id INT,
	product_id INT,
	FOREIGN KEY (supplier_id) REFERENCES Suppliers(supplier_id),
	FOREIGN KEY (product_id) REFERENCES Products(product_id)
);
--DROP TABLE Purchases

--aid, bid, cid, a2, b2 are integers;
--the primary keys are underlined; aid bid cid
--a2 is UNIQUE in Ta;
--aid and bid are foreign keys in Tc, referencing the primary keys in Ta and Tb, respectively.

-- 
INSERT INTO Suppliers (supplier_id, supplier_code, supplier_name)
VALUES
    (1, 1001, 'NAME1'),
    (2, 1002, 'NAME2'),
    (3, 1003, 'NAME3');

INSERT INTO Products (product_id, product_code, product_type_id)
VALUES
	(104, 5004, 14),
    (105, 5005, 15),
    (106, 5006, 16),
	(107, 5007, 17),
    (108, 5008, 18),
    (109, 5009, 19),
    (101, 5001, 11),
    (102, 5002, 12),
    (103, 5003, 13);

INSERT INTO Purchases (purchase_id, supplier_id, product_id)
VALUES
    (201, 1, 101),
    (202, 1, 102),
    (203, 2, 103),
    (204, 3, 101),
    (205, 3, 103);
SELECT * FROM Suppliers
SELECT * FROM Products
SELECT * FROM Purchases
--DELETE FROM Purchases
--DELETE FROM Suppliers
--DELETE FROM Products

GO
CREATE PROCEDURE FillTables AS
BEGIN
	DECLARE @I INT = 0
	WHILE @I < 500
	BEGIN 
		INSERT INTO Suppliers(supplier_id, supplier_code, supplier_name)
		VALUES (@I, @I+1000, 'Name'+convert(varchar, @I))                           -- ! CONVERT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		SET @I = @I + 1
	END

	SET @I = 4
	WHILE @I < 800
	BEGIN
		INSERT INTO Products (product_id, product_code, product_type_id)
		VALUES (@I+100, @I+5000, @I+10)
		SET @I = @I + 1
	END

	SET @I = 1
	DECLARE @sid INT = (SELECT MAX(supplier_id)                                   -- max / min
						FROM Suppliers)
	DECLARE @pid INT = (SELECT MIN(product_id)
						FROM Products)
	WHILE @I < 100
	BEGIN
		INSERT INTO Purchases (purchase_id, supplier_id, product_id)
		VALUES (@I+200, @sid, @pid)
		SET @I = @I + 1
	END

	SET @sid = (SELECT MIN(supplier_id)
						FROM Suppliers)
	SET @pid = (SELECT MAX(product_id)
						FROM Products)
	WHILE @I < 200
	BEGIN
		INSERT INTO Purchases (purchase_id, supplier_id, product_id)
		VALUES (@I+200, @sid, @pid)
		SET @I = @I + 1
	END

	SET @sid = (SELECT MIN(supplier_id)
						FROM Suppliers WHERE supplier_id > (SELECT MIN(supplier_id) FROM Suppliers))
	SET @pid = (SELECT MAX(product_id)
						FROM Products WHERE product_id < (SELECT MAX(product_id) FROM Products))
	WHILE @I < 300
	BEGIN
		INSERT INTO Purchases (purchase_id, supplier_id, product_id)
		VALUES (@I+200, @sid, @pid)
		SET @I = @I + 1
	END
END
GO
--DROP PROCEDURE FillTables

EXEC FillTables


-- a) Write queries on Ta (Suppliers) such that their execution plans contain the following operators:
-- clustered index in Suppliers: supplier_id (because PRIMARY KEY -> by default a clustered index)
-- nonclustered index in Suppliers: supplier_code (because of UNIQUE -> by default unique nonclustered index)

-- clustered index scan; 
SELECT max(supplier_id) AS max_id FROM Suppliers

--clustered index seek;
SELECT * FROM Suppliers
WHERE supplier_id = 1 OR supplier_id >=3

--nonclustered index scan;
SELECT supplier_code FROM Suppliers

--nonclustered index seek;
SELECT supplier_code FROM Suppliers
WHERE supplier_code > 1001

--key lookup
SELECT * FROM Suppliers WHERE supplier_code = 1002 


-- b) Write a query on table Tb (Products) with a WHERE clause of the form WHERE b2 (product_code) = value and analyze its execution plan. 
-- Create a nonclustered index that can speed up the query. Examine the execution plan again.
SELECT product_code FROM Products
WHERE product_code = 5006

CREATE NONCLUSTERED INDEX IX_ProductCode
ON Products (product_code);

--DROP INDEX IX_ProductCode ON Products


-- c) Create a view that joins at least 2 tables. Check whether existing indexes are helpful;
-- if not, reassess existing indexes / examine the cardinality of the tables.

GO
CREATE VIEW ProductPurchaseView AS
    SELECT
		PU.purchase_id, 
        PR.product_id,
        PR.product_code
    FROM
        Products PR
    JOIN
        Purchases PU 
	ON PR.product_id = PU.product_id;
GO

SELECT * FROM ProductPurchaseView

CREATE NONCLUSTERED INDEX IX_PurchaseProductId
ON Purchases (product_id);

--DROP INDEX IX_PurchaseProductId ON Purchases
