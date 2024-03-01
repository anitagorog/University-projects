use Kaufland_database_l1;

-- a table with a single-column primary key and no foreign keys
CREATE TABLE Soda(
	brandId int ,
	typeId int ,
	quantity int ,
	PRIMARY KEY(brandId)
);

--DROP TABLE Soda;

-- a table with a single-column primary key and at least one foreign key
CREATE TABLE Cola(
	id int ,
	brandId int ,
	flavour varchar(30) ,
	price int ,
	PRIMARY KEY(id) ,
	FOREIGN KEY(brandId) REFERENCES Soda(brandId)
);

--DROP TABLE Cola;

-- a table with a multicolumn primary key
CREATE TABLE Drinks(
	brandId int ,
	typeId int ,
	PRIMARY KEY(brandId, typeId)
);

--DROP TABLE Drinks;

GO

-- adding the tables
CREATE PROCEDURE AddTable 
@TableName VARCHAR(30)
AS
BEGIN 
	IF @TableName IN (SELECT Name FROM Tables)
	BEGIN 
		PRINT 'Table already added'
		RETURN
	END

	IF @TableName NOT IN (SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES)
	BEGIN
		PRINT 'Table does not exist'
		RETURN
	END

	INSERT INTO Tables
	VALUES (@TableName)
END

--DROP PROCEDURE AddTable;

EXEC AddTable 'Soda'
EXEC AddTable 'Cola'
EXEC AddTable 'Drinks'
EXEC AddTable 'Ho'

SELECT * FROM Tables;
GO


-- creating views
-- a view with a SELECT statement operating on one table
CREATE VIEW ColaFlavours AS
	SELECT DISTINCT flavour
	FROM Cola
GO

--DROP VIEW ColaFlavours
GO

-- a view with a SELECT statement that operates on at least 2 different tables and contains at least one JOIN operator
CREATE VIEW SodaCola AS
SELECT
    s.brandId,
    s.typeId,
    s.quantity,
    c.flavour,
    c.price
FROM
    Soda s JOIN Cola c ON s.brandId = c.brandId;

--DROP VIEW SodaCola
GO

--
INSERT INTO Soda (brandId, typeId, quantity)
VALUES
    (1, 101, 50),
    (2, 101, 30),
    (3, 101, 20);
INSERT INTO Cola (id, brandId, flavour, price)  -- typeId = 101 -> sugary soda/any type of cola
VALUES
    (1, 1, 'Cola Classic', 2),
    (2, 2, 'Cherry Cola', 3),
    (3, 3, 'Vanilla Cola', 4),
    (4, 1, 'Cola Classic', 2);
SELECT * FROM ColaFlavours 
SELECT * FROM SodaCola
--SELECT * FROM TotalColaQuantityByFlavour
DELETE FROM Cola
DELETE FROM Soda
--
GO

-- a view with a SELECT statement that has a GROUP BY clause, operates on at least 2 different tables and contains at least one
--  JOIN operator
GO

CREATE VIEW TotalColaQuantityByFlavour AS
SELECT
    c.flavour,
    SUM(s.quantity) AS total_quantity
FROM
    Cola c
JOIN
    Soda s ON c.brandId = s.brandId
GROUP BY
    c.flavour;

--DROP VIEW TotalColaQuantityByFlavour
GO


-- adding the views
CREATE PROCEDURE AddView
@ViewName VARCHAR(30)
AS
BEGIN 
	IF @ViewName IN (SELECT Name FROM Views)
	BEGIN 
		PRINT 'View already added'
		RETURN
	END

	IF @ViewName NOT IN (SELECT TABLE_NAME FROM INFORMATION_SCHEMA.VIEWS)
	BEGIN
		PRINT 'View does not exist'
		RETURN
	END

	INSERT INTO Views
	VALUES (@ViewName)
END

--DROP PROCEDURE AddView;

EXEC AddView 'ColaFlavours'
EXEC AddView 'SodaCola'
EXEC AddView 'TotalColaQuantityByFlavour'
EXEC AddView 'Ho'

SELECT * FROM Views;
GO


-- add to Tests
INSERT INTO Tests
VALUES ('delete'),
	('insert'),
	('select')

SELECT * FROM Tests
SELECT * FROM Tables

-- connection between Tests and Tables
INSERT INTO TestTables (TestID, TableID, NoOfRows, Position) VALUES
	-- delete cola
	(1, 2, 10, 1) ,
	-- delete soda
	(1, 1, 20, 2) ,
	-- delete drinks
	(1, 3, 30, 0) ,
	-- add drinks
	(2, 3, 30, 0) ,
	-- add soda
	(2, 1, 20, 1) ,
	-- add cola
	(2, 2, 10, 2)

SELECT * FROM TestTables
DELETE FROM TestTables

SELECT * FROM Tests
SELECT * FROM Views


-- connection between Tests and Views
INSERT INTO TestViews (TestID, ViewID) VALUES
	(3, 1),
	(3, 2),
	(3, 3)

SELECT * FROM TestViews
DELETE FROM TestViews
GO


--delete from tables
CREATE PROCEDURE DeleteDrinks AS
BEGIN
	DELETE FROM Drinks;
END
GO

CREATE PROCEDURE DeleteSoda AS
BEGIN
	DELETE FROM Soda;
END
GO

CREATE PROCEDURE DeleteCola AS
BEGIN
	DELETE FROM Cola;
END
GO

EXEC DeleteCola;
EXEC DeleteSoda; -- when delete soda delete cola before
EXEC DeleteDrinks;

--DROP PROCEDURE DeleteDrinks;
--DROP PROCEDURE DeleteSoda;
--DROP PROCEDURE DeleteCola;

SELECT * FROM Cola
SELECT * FROM Soda
SELECT * FROM Drinks
GO


--insert to tables
CREATE PROCEDURE InsertDrinks AS --------------------------------------------------------------------------
BEGIN
	DECLARE @I INT = 0
	DECLARE @NoRows INT =
	(SELECT T.NoOfRows
		FROM TestTables T
		WHERE T.TestID = 2 AND T.TableID = (SELECT t.TableID
							FROM Tables t
							WHERE t.Name = 'Drinks'))
	WHILE @I < @NoRows
	BEGIN
		INSERT INTO Drinks (brandId, typeId) VALUES
			(@I+1, (@I % 5)+100)
		SET @I = @I+1
	END
END

EXEC InsertDrinks
SELECT * FROM Drinks

--DROP PROCEDURE InsertDrinks
GO

CREATE PROCEDURE InsertSoda AS
BEGIN
	DECLARE @I INT = 0
	DECLARE @NoRows INT =
	(SELECT T.NoOfRows
		FROM TestTables T
		WHERE T.TestID = 2 AND T.TableID = (SELECT t.TableID
							FROM Tables t
							WHERE t.Name = 'Soda'))
	WHILE @I < @NoRows
	BEGIN
		INSERT INTO Soda (brandId, typeId, quantity) VALUES
			(@I+1, 101, ((@I+7)%5)+20)
		SET @I = @I+1
	END
END

EXEC InsertSoda
SELECT * FROM Soda

--DROP PROCEDURE InsertSoda
GO

CREATE PROCEDURE InsertCola AS
BEGIN
	DECLARE @I INT = 0
	DECLARE @BRANDID INT = 
	(SELECT MIN(s.brandId)                                      -- MIN
		FROM Soda s)
	DECLARE @NoRows INT =
	(SELECT T.NoOfRows
		FROM TestTables T
		WHERE T.TestID = 2 AND T.TableID = (SELECT t.TableID
							FROM Tables t
							WHERE t.Name = 'Cola'))
	WHILE @I < @NoRows/2
	BEGIN
		INSERT INTO Cola (id, brandId, flavour, price) VALUES
			(@I+11, @BRANDID, 'Cola Classic', ((@I+7)%5)+23)
		SET @I = @I+1
	END

	SET @BRANDID = 
	(SELECT MAX(s.brandId)
		FROM Soda s)
	WHILE @I < @NoRows
	BEGIN
		INSERT INTO Cola (id, brandId, flavour, price) VALUES
			(@I+11, @BRANDID, 'Cherry Cola', ((@I+7)%5)+27)
		SET @I = @I+1
	END
END

EXEC InsertCola
SELECT * FROM Cola

--DROP PROCEDURE InsertCola
GO


--select views
CREATE PROCEDURE SelectView1 AS
BEGIN
	SELECT * FROM ColaFlavours
END
GO

CREATE PROCEDURE SelectView2 AS
BEGIN
	SELECT * FROM SodaCola
END
GO

CREATE PROCEDURE SelectView3 AS
BEGIN
	SELECT * FROM TotalColaQuantityByFlavour
END
GO

EXEC SelectView1 
EXEC SelectView2 
EXEC SelectView3 

--DROP PROCEDURE SelectView1
--DROP PROCEDURE SelectView2
--DROP PROCEDURE SelectView3
GO


--run tabels

SELECT * FROM Tables
GO

CREATE PROCEDURE RunTabel
@TableId INT, @TestId INT AS
BEGIN
	IF @TableId NOT IN (SELECT TableId FROM Tables)                  -- CHECK IF EXISTS !!!!!!!!!!!!!
	BEGIN
		PRINT 'Table does not exist'
	END
	IF @TestId NOT IN (SELECT TestID FROM Tests)
	BEGIN
		PRINT 'Test does not exist'
	END

	DECLARE @Pos INT = (                                            -- !!!
		SELECT T.Position
		FROM TestTables T
		WHERE T.TestID = @TestId AND T.TableID = @TableID)

	IF @Pos <> 0 AND @Pos <> 1
	BEGIN
		DECLARE @P INT = @Pos-1
		DECLARE @Tab INT = (SELECT T.TableID
							FROM TestTables T
							WHERE T.Position = @P AND T.TestID = @TestId)
		IF @TestId = 1
		BEGIN
		EXEC RunTabel @Tab, @TestId 
		END
	END
	IF @TableId = 3 AND @TestId = 1
	BEGIN
		EXEC DeleteDrinks
	END
	IF @TableId = 3 AND @TestId = 2
	BEGIN
		EXEC InsertDrinks
	END
	IF @TableId = 2 AND @TestId = 1
	BEGIN
		EXEC DeleteCola
	END
	IF @TableId = 2 AND @TestId = 2
	BEGIN
		EXEC InsertCola
	END
	IF @TableId = 1 AND @TestId = 1
	BEGIN
		EXEC DeleteSoda
	END
	IF @TableId = 1 AND @TestId = 2
	BEGIN
		EXEC InsertSoda
	END
END

EXEC RunTabel 3, 1
EXEC RunTabel 2, 1
EXEC RunTabel 1, 1
EXEC RunTabel 1, 2
EXEC RunTabel 2, 2
EXEC RunTabel 3, 2

--DROP PROCEDURE RunTabel

SELECT * FROM Drinks -- table 3
SELECT * FROM Cola -- table 2
SELECT * FROM Soda -- table 1
SELECT * FROM TestTables
GO


--run views

SELECT * FROM Views
GO

CREATE PROCEDURE RunView
@ViewId INT AS 
BEGIN
	IF @ViewId NOT IN (SELECT V.ViewID FROM Views V)
	BEGIN
		PRINT 'View does not exist'
		RETURN
	END
	IF @ViewId = 1
	BEGIN 
		SELECT * FROM ColaFlavours
	END 
	IF @ViewId = 2
	BEGIN 
		SELECT * FROM SodaCola
	END 
	IF @ViewId = 3
	BEGIN 
		SELECT * FROM TotalColaQuantityByFlavour
	END 
END

EXEC RunView 1
GO


--fill TestRun
CREATE PROCEDURE TestRun              ---------------------------------------------------------------------------------------
@ID INT, @testName VARCHAR(30) AS
BEGIN
	DECLARE @startTime DATETIME
	DECLARE @midTime DATETIME
	DECLARE @endtime DATETIME

	SET @startTime = GETDATE()
	EXEC RunTabel @ID, 1 
	PRINT 'Deleted'
	EXEC RunTabel @ID, 2
	PRINT 'Inserted'
	SET @midTime = GETDATE()
	EXEC RunView @ID 
	SET @endtime = GETDATE()

	INSERT INTO TestRuns VALUES (@testName, @startTime, @endTime);

	DECLARE @TID INT = (SELECT T.TestRunID FROM TestRuns T WHERE T.Description = @testName AND T.StartAt = @startTime)

	INSERT INTO TestRunTables (TestRunID, TableID, StartAt, EndAt)
	VALUES (@TID, @ID, @startTime, @midTime)

	INSERT INTO TestRunViews (TestRunID, ViewID, StartAt, EndAt)
	VALUES (@TID, @ID, @midTime, @endtime)
END

--DROP PROCEDURE TestRun

EXEC TestRun 1, 'Test1'
EXEC TestRun 2, 'Test2'
EXEC TestRun 3, 'Test3'

SELECT * FROM Cola
SELECT * FROM Soda
SELECT * FROM Drinks

SELECT * FROM TestRuns
SELECT * FROM TestRunTables
SELECT * FROM TestRunViews

DELETE FROM TestRuns
DELETE FROM TestRunTables
DELETE FROM TestRunViews