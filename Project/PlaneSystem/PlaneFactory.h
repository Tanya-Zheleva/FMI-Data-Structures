#include <fstream>
#include <unordered_map>
#include <vector>
#include <regex>
#include "Plane.h"
#pragma once

using namespace std;

class PlaneFactory
{
private:
	unordered_map<int, Plane> planes;
	vector<int> idsOrder;

	bool HasId(int) const;
	void AddPlane(string);
	int GetIdIndex(int);

public:
	PlaneFactory();

	void Create(int, const string&, const string&, int);
	void Delete(int);
	void Update(int, const string&, const string&);

	void ExtractFromFile(const string&);
	void SaveToFile(const string&);

	void Show(int, int);
	void Optimize();
	void Search(int);

	void Print();
};

PlaneFactory::PlaneFactory()
{
	//	idsOrder.resize(32);
}

bool PlaneFactory::HasId(int id) const
{
	return planes.count(id) > 0;
}

void PlaneFactory::Create(int id, const string& name, const string& type, int flights)
{
	if (HasId(id))
	{
		throw invalid_argument("Plane id must be unique!");
	}

	Plane plane(id, name, type, flights);
	planes[id] = plane;
}

void PlaneFactory::Delete(int id)
{
	if (!HasId(id))
	{
		throw invalid_argument("Plane id not found!");
	}

	planes.erase(id);
}

void PlaneFactory::Search(int id)
{
	if (!HasId(id))
	{
		throw invalid_argument("Plane id not found!");
	}

	planes[id].Print();
}

int PlaneFactory::GetIdIndex(int id)
{
	int index = 0;
	vector<int>::iterator it = idsOrder.begin();

	for (; it != idsOrder.end(); it++)
	{
		int current = *it;

		if (current == id)
		{
			return index;
		}

		index++;
	}

	return -1;
}

/*
TODO:
if an element in the file is updated, add a flag to it
when saving to file -> if there is a flag, update the record
at the end append the new reords
*/
void PlaneFactory::Update(int id, const string& attribute, const string& valueToString)
{
	if (!HasId(id))
	{
		throw invalid_argument("Plane id not found!");
	}

	if (attribute == "Id")
	{
		int newId = stoi(valueToString);

		if (HasId(newId))
		{
			throw invalid_argument("Plane id must be unique!");
		}

		int idIndex = GetIdIndex(id);
		planes[id].SetId(newId);
		unordered_map<int, Plane>::iterator it = planes.find(id);

		swap(planes[newId], it->second);
		planes.erase(it);

		idsOrder.erase(idsOrder.begin() + idIndex);
		idsOrder.insert(idsOrder.begin() + idIndex, newId);
	}
	else if (attribute == "Plane")
	{
		planes[id].SetName(valueToString);
	}
	else if (attribute == "Type")
	{
		planes[id].SetType(valueToString);
	}
	else if (attribute == "Flights")
	{
		int flights = stoi(valueToString);
		planes[id].SetFlights(flights);
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

	unordered_map<int, Plane>::iterator it = planes.begin();

	for (int i = 0; i < offset; i++) it++;

	for (int i = offset; i < end; i++)
	{
		it->second.Print();
		it++;
	}
}

void PlaneFactory::Print()
{
	unordered_map<int, Plane>::iterator it = planes.begin();

	for (; it != planes.end(); it++)
	{
		it->second.Print();
	}
}

void PlaneFactory::AddPlane(string record)
{
	regex planeRegex("^(\\d+)\\s+((?:[A-Za-z]+\\s*\\d*)+)\\s+((?:[A-Za-z]+\\s*\\d*)+)\\s+(\\d+)$");
	smatch matches;

	if (regex_search(record, matches, planeRegex)) {

		int id = stoi(matches[1].str());
		string name = matches[2].str();
		string type = matches[3].str();
		int flights = stoi(matches[4].str());

		Plane plane(id, name, type, flights);
		planes[id] = plane;
		idsOrder.push_back(id);
	}
}

void PlaneFactory::ExtractFromFile(const string& fileName)
{
	ifstream reader(fileName);

	if (!reader)
	{
		throw ios_base::failure("Cannot open file");
	}

	string record;

	while (getline(reader, record))
	{
		AddPlane(record);
	}

	reader.close();
}

/*
TODO
Update old records
Append new records to the end
*/
void PlaneFactory::SaveToFile(const string& fileName)
{
	ofstream writer(fileName);

	if (!writer)
	{
		throw ios_base::failure("Cannot open file");
	}

	unordered_map<int, Plane>::iterator it = planes.begin();

	for (; it != planes.end(); it++)
	{
		writer << it->second;
	}

	writer.close();
}