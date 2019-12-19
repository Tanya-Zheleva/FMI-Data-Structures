#include <fstream>
#include <map>
#include <vector>
#include <utility>
#include <regex>
#include "Plane.h"

using namespace std;

class PlaneFactory
{
private:
	map<int, Plane> planesOptimized;
	vector<Plane> planes;
	string fileName;
	bool isOptimizeUsed;

	bool HasIdOptimized(int) const;
	int GetIdIndex(int) const;

	void DeleteOptimized(int);
	void SearchOptimized(int);
	void UpdateOptimized(int, const string&, const string&);

	void CreateFilePlane(string);
	void ExtractFromFile();

public:
	PlaneFactory(const string&);

	void Create(int, const string&, const string&, int);
	void Delete(int);
	void Update(int, const string&, const string&);

	void SaveToFile();

	void Show(int, int);
	void Optimize();
	void Search(int);

	void Print();
};

PlaneFactory::PlaneFactory(const string& fileName)
{
	this->fileName = fileName;
	isOptimizeUsed = false;
	ExtractFromFile();
}

bool PlaneFactory::HasIdOptimized(int id) const
{
	return planesOptimized.count(id) > 0;
}

int PlaneFactory::GetIdIndex(int id) const
{
	for (int i = 0; i < planes.size(); i++)
	{
		if (planes[i].GetId() == id) return i;
	}

	return -1;
}

void PlaneFactory::Create(int id, const string& name, const string& type, int flights)
{
	if (GetIdIndex(id) < 0)
	{
		throw invalid_argument("Plane id must be unique!");
	}

	Plane plane(id, name, type, flights);
	planes.push_back(plane);
	isOptimizeUsed = false;
	planesOptimized.clear();
}

void PlaneFactory::DeleteOptimized(int id)
{
	if (!HasIdOptimized(id))
	{
		throw invalid_argument("Plane id not found!");
	}

	planesOptimized.erase(id);
}

void PlaneFactory::Delete(int id)
{
	if (isOptimizeUsed)
	{
		DeleteOptimized(id);

		return;
	}

	int idIndex = GetIdIndex(id);

	if (idIndex < 0)
	{
		throw invalid_argument("Plane id not found!");
	}

	planes.erase(planes.begin() + idIndex);
}

void PlaneFactory::SearchOptimized(int id)
{
	if (!HasIdOptimized(id))
	{
		throw invalid_argument("Plane id not found!");
	}

	planesOptimized[id].Print();
}

void PlaneFactory::Search(int id)
{
	if (isOptimizeUsed)
	{
		SearchOptimized(id);
		
		return;
	}

	int idIndex = GetIdIndex(id);

	if (idIndex < 0)
	{
		throw invalid_argument("Plane id not found!");
	}

	planes[idIndex].Print();
}

void PlaneFactory::UpdateOptimized(int id, const string& attribute, const string& valueToString)
{
	if (!HasIdOptimized(id))
	{
		throw invalid_argument("Plane id not found!");
	}

	if (attribute == "Id")
	{
		int newId = stoi(valueToString);

		if (HasIdOptimized(newId))
		{
			throw invalid_argument("Plane id must be unique!");
		}

		planesOptimized[id].SetId(newId);
		map<int, Plane>::iterator it = planesOptimized.find(id);

		swap(planesOptimized[newId], it->second);
		planesOptimized.erase(it);
	}
	else if (attribute == "Plane")
	{
		planesOptimized[id].SetName(valueToString);
	}
	else if (attribute == "Type")
	{
		planesOptimized[id].SetType(valueToString);
	}
	else if (attribute == "Flights")
	{
		int flights = stoi(valueToString);
		planesOptimized[id].SetFlights(flights);
	}
	else
	{
		throw invalid_argument("Invalid attribute!");
	}
}

void PlaneFactory::Update(int id, const string& attribute, const string& valueToString)
{
	if (isOptimizeUsed)
	{
		UpdateOptimized(id, attribute, valueToString);

		return;
	}

	int idIndex = GetIdIndex(id);

	if (idIndex < 0)
	{
		throw invalid_argument("Plane id not found!");
	}

	if (attribute == "Id")
	{
		int newId = stoi(valueToString);
		int newIdIndex = GetIdIndex(newId);

		if (newIdIndex > -1)
		{
			throw invalid_argument("Plane id must be unique!");
		}

		planes[idIndex].SetId(newId);
	}
	else if (attribute == "Plane")
	{
		planes[idIndex].SetName(valueToString);
	}
	else if (attribute == "Type")
	{
		planes[idIndex].SetType(valueToString);
	}
	else if (attribute == "Flights")
	{
		int flights = stoi(valueToString);
		planes[idIndex].SetFlights(flights);
	}
	else
	{
		throw invalid_argument("Invalid attribute!");
	}
}

void PlaneFactory::Show(int offset, int limit)
{
	int end = offset + limit;

	if (end > planes.size())
	{
		throw out_of_range("Cannot read amount of elements!");
	}

	for (int i = offset; i < end; i++)
	{
		planes[i].Print();
	}
}

void PlaneFactory::Optimize()
{
	isOptimizeUsed = true;

	for (size_t i = 0; i < planes.size(); i++)
	{
		planesOptimized[planes[i].GetId()] = planes[i];
	}
}

void PlaneFactory::Print()
{
	for (int i = 0; i < planes.size(); i++)
	{
		planes[i].Print();
	}
}

void PlaneFactory::CreateFilePlane(string record)
{
	regex planeRegex("^(\\d+)\\s+((?:[A-Za-z]+\\s*\\d*)+)\\s+((?:[A-Za-z]+\\s*\\d*)+)\\s+(\\d+)$");
	smatch matches;

	if (regex_search(record, matches, planeRegex)) {

		int id = stoi(matches[1].str());
		string name = matches[2].str();
		string type = matches[3].str();
		int flights = stoi(matches[4].str());

		Plane plane(id, name, type, flights);
		planes.push_back(plane);
	}
}

void PlaneFactory::ExtractFromFile()
{
	ifstream reader(fileName);

	if (!reader)
	{
		throw ios_base::failure("Cannot open file");
	}

	string record;

	while (getline(reader, record))
	{
		CreateFilePlane(record);
	}

	reader.close();
}

void PlaneFactory::SaveToFile()
{
	ofstream writer(fileName);

	if (!writer)
	{
		throw ios_base::failure("Cannot open file");
	}

	vector<Plane>::iterator it = planes.begin();

	for (; it != planes.end(); it++)
	{
		writer << *it;
	}

	writer.close();
}