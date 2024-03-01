#pragma once
#include "FileUserList.h"
class HtmlUserList :
    public FileUserList
{
public:
    HtmlUserList(const std::string& filename) : FileUserList{ filename } {};

    void save_to_file();
    void open_file();
};

