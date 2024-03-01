#pragma once
#include <exception>
#include <string>

class FileException : public std::exception
{
protected:
	std::string error_message;

public:
	FileException(const std::string& the_message);
	virtual const char* what();
};

class RepositoryException : public std::exception
{
protected:
	std::string error_message;

public:
	RepositoryException();
	RepositoryException(const std::string& the_message);
	virtual const char* what();
};

class DuplicateException : public RepositoryException
{
public:
	const char* what();
};

class InexistentException : public RepositoryException
{
public:
	const char* what();
};
