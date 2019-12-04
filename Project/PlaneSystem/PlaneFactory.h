#include <unordered_map>
#include "Plane.h"
#pragma once

using namespace std;

class PlaneFactory
{
private:
	unordered_map<int, Plane> planes;

	bool HasId(int) const;

public:
	PlaneFactory();

	void Create(int, const string&, const string&, int);
	void Delete(int);
	void Update(int, const string&, const string&);
	void ExtractFromFile(const string&);

	void Show(int, int);
	void Optimize();
	void Search(int);

	void Print();
};

PlaneFactory::PlaneFactory() { }

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
		planes[id].SetId(newId);
		unordered_map<int, Plane>::iterator it = planes.find(id);

		swap(planes[newId], it->second);
		planes.erase(it);
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

//Test
void PlaneFactory::Print()
{
	unordered_map<int, Plane>::iterator it = planes.begin();

	for (; it != planes.end(); it++)
	{
		it->second.Print();
	}
}