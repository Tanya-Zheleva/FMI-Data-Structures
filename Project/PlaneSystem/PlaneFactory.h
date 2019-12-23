#include <fstream>
#include <vector>
#include <regex>
#include "PlaneSearchTree.h"

using namespace std;

class PlaneFactory
{
private:
	PlaneSearchTree planesOptimized;
	vector<Plane> planes;
	string fileName;
	bool isOptimizeUsed;

	void RemoveOptimized();
	int GetIdIndex(int) const;
	void SearchOptimized(int);

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


int PlaneFactory::GetIdIndex(int id) const
{
	for (int i = 0; i < planes.size(); i++)
	{
		if (planes[i].GetId() == id) return i;
	}

	return -1;
}

void PlaneFactory::RemoveOptimized()
{
	if (isOptimizeUsed)
	{
		isOptimizeUsed = false;
		planesOptimized.Clear();
		planesOptimized.Reset();
	}
}

void PlaneFactory::Create(int id, const string& name, const string& type, int flights)
{
	if (GetIdIndex(id) >= 0)
	{
		throw invalid_argument("Plane id must be unique!");
	}

	Plane plane(id, name, type, flights);
	planes.push_back(plane);

	RemoveOptimized();
}

void PlaneFactory::Delete(int id)
{
	int idIndex = GetIdIndex(id);

	if (idIndex < 0)
	{
		throw invalid_argument("Plane id not found!");
	}

	planes.erase(planes.begin() + idIndex);

	RemoveOptimized();
}

void PlaneFactory::SearchOptimized(int id)
{
	if (!planesOptimized.Contains(id))
	{
		throw invalid_argument("Plane id not found!");
	}

	cout << planesOptimized.Find(id);
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

	cout << planes[idIndex];
}

void PlaneFactory::Update(int id, const string& attribute, const string& valueToString)
{
	int idIndex = GetIdIndex(id);

	if (idIndex < 0)
	{
		throw invalid_argument("Plane id not found!");
	}

	if (attribute == "Id" || attribute == "id")
	{
		int newId = stoi(valueToString);
		int newIdIndex = GetIdIndex(newId);

		if (newIdIndex > -1)
		{
			throw invalid_argument("Plane id must be unique!");
		}

		planes[idIndex].SetId(newId);
	}
	else if (attribute == "Plane" || attribute == "plane")
	{
		planes[idIndex].SetName(valueToString);
	}
	else if (attribute == "Type" || attribute == "type")
	{
		planes[idIndex].SetType(valueToString);
	}
	else if (attribute == "Flights" || attribute == "flights")
	{
		int flights = stoi(valueToString);
		planes[idIndex].SetFlights(flights);
	}
	else
	{
		throw invalid_argument("Invalid attribute!");
	}

	RemoveOptimized();
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
		cout << planes[i];
	}
}

void PlaneFactory::Optimize()
{
	isOptimizeUsed = true;

	for (size_t i = 0; i < planes.size(); i++)
	{
		planesOptimized.Insert(planes[i]);
	}
}

void PlaneFactory::Print()
{
	for (int i = 0; i < planes.size(); i++)
	{
		cout << planes[i];
	}
}

void PlaneFactory::CreateFilePlane(string record)
{
	regex planeRegex("^(\\d+)\\s+(.*?)\\s+([A-Za-z]+)\\s+(\\d+)$");
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

	for (int i = 0; i < planes.size(); i++)
	{
		writer << planes[i];
	}

	writer.close();

	if (isOptimizeUsed)
	{
		isOptimizeUsed = false;
		planesOptimized.Clear();
	}
}