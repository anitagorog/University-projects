#pragma once
#include <string>

class Doctor
{
private:
	std::string name;
	std::string specialis;
public:
	Doctor(std::string n, std::string s) : name(n), specialis(s) {}

	std::string get_name() { return this->name; }
	std::string get_spec() { return this->specialis; }
};

