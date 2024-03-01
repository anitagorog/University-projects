#pragma once
#include "Repository.h"
#include <fstream>
#include <sstream>

class FileRepository :
	public Repository
{
private:
	std::string file_name;
	void load_from_file();

public:
	FileRepository() {}
	FileRepository(const std::string& filename) : Repository() { this->file_name = filename; load_from_file(); }

	void save_to_file();
};

