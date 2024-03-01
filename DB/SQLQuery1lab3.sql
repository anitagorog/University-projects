-- lab3

DROP PROCEDURE TestProc
GO
CREATE PROCEDURE TestProc
AS
	SELECT * FROM CosmeticProductsBrands;
GO

use Kaufland_database_l1

EXEC TestProc
GO



SELECT * FROM Chocolate
GO

-- a. modify the type of a column                                  ! MODIFY WITH ALTER TABLE/COLUMN
CREATE PROCEDURE ChangeChocNameToNvarchar
AS
	ALTER TABLE Chocolate
	ALTER COLUMN name_choc nvarchar(100);
GO

CREATE PROCEDURE ChangeChocNameToVarchar
AS
	ALTER TABLE Chocolate
	ALTER COLUMN name_choc varchar(100);
GO

EXEC ChangeChocNameToNvarchar;
EXEC ChangeChocNameToVarchar;
GO


-- b. add / remove a column;
-- add quantity to Chocolate
CREATE PROCEDURE AddNewColumnQuantity                              -- ALTER TABLE; ADD !  
AS
	ALTER TABLE Chocolate
	ADD quantity varchar
GO

CREATE PROCEDURE RemoveNewColumn
AS
	ALTER TABLE Chocolate
	DROP COLUMN quantity
GO

EXEC AddNewColumnQuantity;
EXEC RemoveNewColumn;
GO


-- c. add / remove a DEFAULT constraint;                           -- DEFAULT CONSTRAINT
CREATE PROCEDURE AddDefaultConstraintToPriceChoc
AS
	ALTER TABLE Chocolate
	ADD CONSTRAINT price
	DEFAULT 20 FOR price
GO

CREATE PROCEDURE RemoveDefaultConstraintFromPriceChoc
AS
	ALTER TABLE Chocolate
	DROP CONSTRAINT price;
GO

EXEC AddDefaultConstraintToPriceChoc;
EXEC RemoveDefaultConstraintFromPriceChoc;
GO


-- d. add / remove a primary key;
CREATE PROCEDURE AddPrimaryKey
AS
	ALTER TABLE Chocolate
	ADD CONSTRAINT pk_Chocolate PRIMARY KEY(id);
GO

CREATE PROCEDURE RemovePrimaryKey
AS
	ALTER TABLE Chocolate
	DROP CONSTRAINT pk_Chocolate;
GO

EXEC AddPrimaryKey;
EXEC RemovePrimaryKey;
GO


-- e. add / remove a candidate key;
CREATE PROCEDURE AddCandidateKey
AS
	ALTER TABLE Chocolate
	ADD CONSTRAINT ck_Chocolate UNIQUE(id);
GO

CREATE PROCEDURE RemoveCandidateKey
AS
	ALTER TABLE Chocolate
	DROP CONSTRAINT ck_Chocolate;
GO

EXEC AddCandidateKey;
EXEC RemoveCandidateKey;
GO


-- f. add / remove a foreign key;
CREATE PROCEDURE AddForeignKey
AS
	ALTER TABLE Orders
	ADD CONSTRAINT fk_ord_choc FOREIGN KEY(id) REFERENCES Chocolate(id) 
GO

CREATE PROCEDURE RemoveForeignKey
AS
	ALTER TABLE Orders
	DROP CONSTRAINT fk_ord_choc;
GO

EXEC AddForeignKey;
EXEC RemoveForeignKey;
GO


-- g. create / drop a table.
CREATE PROCEDURE CreateNewTable
AS
BEGIN
	CREATE TABLE Sweets(
	id INT NOT NULL PRIMARY KEY,
	type_of varchar(30) NOT NULL,
	price INT NOT NULL 
	);
END
GO

CREATE PROCEDURE DropNewTable
AS
BEGIN
	DROP TABLE Sweets;
END
GO

EXEC CreateNewTable;
EXEC DropNewTable;
SELECT * FROM Sweets 
GO


CREATE PROCEDURE CreateNewTableOrder
AS
BEGIN
	CREATE TABLE Orders(
	o_id INT NOT NULL PRIMARY KEY,
	id INT NOT NULL,
	name_of varchar(30) NOT NULL,
	quantity INT NOT NULL,
	price INT NOT NULL 
	);
END
GO

CREATE PROCEDURE DropNewTableOrder
AS
BEGIN
	DROP TABLE Orders;
END
GO

EXEC CreateNewTableOrder;
EXEC DropNewTableOrder;



CREATE TABLE DataBaseVersions(
	NrVersion INT default 0
);

INSERT INTO DataBaseVersions
VALUES(0);

SELECT * FROM DataBaseVersions;
DELETE FROM DataBaseVersions;


CREATE TABLE ProcedureListVersions(
	id INT PRIMARY KEY,
	procedureName varchar(100)
);

INSERT INTO ProcedureListVersions
VALUES
(0,'ChangeChocNameToNvarchar'),
(1,'AddNewColumnQuantity'),
(2,'AddDefaultConstraintToPriceChoc'),
(3,'AddPrimaryKey'),
(4,'AddCandidateKey'),
(5,'CreateNewTableOrder'),
(6,'AddForeignKey');

CREATE TABLE RevertProcedureListVersions(
	id INT PRIMARY KEY,
	procedureName varchar(100)
);

INSERT INTO RevertProcedureListVersions
VALUES
(0,'ChangeChocNameToVarchar'),
(1,'RemoveNewColumn'),
(2,'RemoveDefaultConstraintFromPriceChoc'),
(3,'RemovePrimaryKey'),
(4,'RemoveCandidateKey'),
(5,'DropNewTableOrder'),
(6,'RemoveForeignKey');

SELECT * FROM ProcedureListVersions;
SELECT * FROM RevertProcedureListVersions;

GO

-- main
CREATE PROCEDURE Main
@Version int
AS
BEGIN
	IF @Version > 7 OR @Version < 0
	BEGIN 
		PRINT 'The versions are in between 0 and 7';
		RETURN;
	END

	DECLARE @ActualVersion AS INT
	SELECT @ActualVersion = NrVersion
	FROM DataBaseVersions;

	PRINT 'Actual version is: ';
	PRINT @ActualVersion;
	PRINT 'And we change to version: ';
	PRINT @Version;

	IF @Version = @ActualVersion
	BEGIN
		PRINT 'We are in the required version';
		RETURN;
	END

	DECLARE @Function AS varchar(100);

	IF @Version > @ActualVersion
	BEGIN
		WHILE @Version != @ActualVersion
		BEGIN
			SELECT @Function = procedureName
			FROM ProcedureListVersions
			WHERE id = @ActualVersion;

			EXECUTE @Function;

			SET @ActualVersion = @ActualVersion+1;
		END

		UPDATE DataBaseVersions
		SET NrVersion = @Version;

		RETURN;
	END

	--IF @Version < @ActualVersion
	WHILE @Version != @ActualVersion
	BEGIN
		SET @ActualVersion = @ActualVersion - 1;

		SELECT @Function = ProcedureName 
		FROM RevertProcedureListVersions
		WHERE id  = @ActualVersion;

		EXECUTE @Function;
	END

	UPDATE DataBaseVersions
	SET NrVersion = @Version;
	RETURN;
END
GO

EXEC Main 0;

DROP PROCEDURE Main;
--




INSERT INTO Chocolate
--VALUES (1, 'Milka', 'milk', DEFAULT)
VALUES (1, 'Milka', 'milk', 15)

DELETE FROM Chocolate

SELECT * FROM Chocolate
SELECT * FROM Orders

CREATE TABLE Chocolate(
	id int NOT NULL,
	name_choc varchar(30) NOT NULL,
	type_choc varchar(30) NOT NULL,
	price float NOT NULL,
);
