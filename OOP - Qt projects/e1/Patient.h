#pragma once
#include <string>

class Patient
{
private:
	std::string na;
	std::string diag;
	std::string spec;
	std::string doc;
	int date;

public:
	Patient(std::string na, std::string di, std::string spec, std::string doc, int da) : na(na), diag(di), spec(spec), doc(doc), date(da) {}

	std::string to_str() { return na + "," + diag + "," + spec + "," + doc + "," + std::to_string(date); }
	std::string get_diag() { return diag; }
	std::string get_doc() { return doc; }
	std::string get_spec() { return spec; }
	std::string get_na() { return na; }
	int get_date() { return date; }

	void set_diag(std::string ne) { diag = ne; }
	void set_spec(std::string ne) { spec = ne; }
};

