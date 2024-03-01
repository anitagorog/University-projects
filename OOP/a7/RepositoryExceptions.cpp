#include "RepositoryExceptions.h"

FileException::FileException(const std::string& the_message)
{
}

const char* FileException::what()
{
    return error_message.c_str();
}

RepositoryException::RepositoryException()
{
}

RepositoryException::RepositoryException(const std::string& the_message)
{
}

const char* RepositoryException::what()
{
    return error_message.c_str();
}

const char* DuplicateException::what()
{
    return "The event has been already added";
}

const char* InexistentException::what()
{
    return "The event does not exist";
}
