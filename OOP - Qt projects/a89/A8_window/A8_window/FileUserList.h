#pragma once
#include "UserList.h"
class FileUserList :
    public UserList
{
protected:
    std::string file_name;

public:
    FileUserList(const std::string& filename) : file_name(filename) {};

    virtual void save_to_file() = 0;
    virtual void open_file() = 0;
};

