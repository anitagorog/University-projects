#pragma once
#include "FileUserList.h"
class CsvUserList :
    public FileUserList
{
public:
    CsvUserList(const std::string& filename) : FileUserList{ filename } {};

    void save_to_file();
    void open_file();
};

