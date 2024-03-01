#pragma once
#include <vector>
#include "Doctor.h"
#include <sstream>
#include <fstream>
#include "Patient.h"
#include <algorithm>
#include "Observer.h"

class Service : public Subject
{
private:
	std::vector<Doctor> docs = { Doctor{"adam", "b"}};
	std::vector<Patient> pats;
public:
	Service s() { 
		this->read_f();
	}

	void add_doc(Doctor d);
	void add_p(Patient p) { this->pats.push_back(p); this->sort(); this->save(); }
	std::vector<Doctor> get_docs() { return docs; }
	std::vector<Patient> get_pats() { return pats; }
	void read_f();
	void read_p();
	void sort();
	void save();
	void update_pat(std::string diag, std::string spec, std::string name, std::string doc);
};

