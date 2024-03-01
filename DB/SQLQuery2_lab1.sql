use Lab1;

CREATE TABLE Users(
	id int NOT NULL,
	first_name varchar(30) NOT NULL,
	last_name varchar(30) NOT NULL,
	address varchar(100),
	PRIMARY KEY(id)
);

CREATE TABLE Books(
	id int NOT NULL,
	title varchar(30) NOT NULL,
	author varchar(50) NOT NULL,
	published_date datetime,
	PRIMARY KEY(id)
);

CREATE TABLE Reviews(
	id int NOT NULL,
	book_id int NOT NULL,
	reviewer_name varchar(100),
	content varchar(255),
	rating int,
	published_date datetime,
	PRIMARY KEY(id),
	FOREIGN KEY(book_id)
		REFERENCES Books(id)
		ON DELETE CASCADE
);

CREATE TABLE Checkouts(
	user_id int NOT NULL,
	book_id int NOT NULL,
	checkout_date datetime,
	return_date datetime,
	FOREIGN KEY(user_id)
		REFERENCES Users(id)
		ON DELETE CASCADE,
	FOREIGN KEY(book_id)
		REFERENCES Books(id)
		ON DELETE CASCADE
);

