#include "Service.h"

void Service::add_doc(Doctor d)
{
	this->docs.push_back(d);
}

void Service::read_f()
{
	std::ifstream f("doc.txt");
	if (f.is_open())
	{
		std::string line, com, name, spec;
		int count;
		while (std::getline(f, line))
		{
			
			count = 0;
			std::stringstream ss(line);
			while (std::getline(ss, com, ','))
			{
				if (count == 0)
					name = com;
				else
					spec = com;
				count++;
			}
			docs.push_back(Doctor(name, spec));
		}

		f.close();
	}
}

void Service::read_p()
{
	std::ifstream f("pat.txt");
	if (f.is_open())
	{
		std::string line, com, name, diag, spec, doc, date;
		int count;
		while (std::getline(f, line))
		{

			count = 0;
			std::stringstream ss(line);
			while (std::getline(ss, com, ','))
			{
				if (count == 0)
					name = com;
				else if (count == 1)
					diag = com;
				else if (count == 2)
					spec = com;
				else if (count == 3)
					doc = com;
				else
					date = com;
				count++;
			}
			pats.push_back(Patient(name, diag, spec, doc, stoi(date)));
		}

		f.close();
	}
	this->sort();
}

void Service::sort()
{
	std::sort(this->pats.begin(), this->pats.end(), [](Patient p1, Patient p2) {return p1.get_date() < p2.get_date(); });

}

void Service::save()
{
	std::ofstream f("pat.txt");
	if (f.is_open())
	{
		for (auto a : this->pats)
			f << a.to_str() << "\n";
		f.close();
	}
}

void Service::update_pat(std::string diag, std::string spec, std::string name, std::string doc)
{
	for (auto& o : pats)
	{
		if (o.get_na() == name && (o.get_diag() == "undiagnosed" || o.get_doc() == doc) && diag!="undiagnosed")
		{
			o.set_diag(diag);
			o.set_spec(spec);
		}
	}
	this->notify();
	this->save();
}
