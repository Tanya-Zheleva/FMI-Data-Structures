#include <string>
#pragma once

using namespace std;

class Plane
{
private:
	int id;
	string name;
	string type;
	int flights;

	void SetId(int);
	void SetName(const string&);
	void SetType(const string&);
	void SetFlights(int);

public:
	Plane(int, const string&, const string&, int);

	int GetId() const;
	string GetName() const;
	string GetType() const;
	int GetFlights() const;

	void Print();
};

Plane::Plane(int id, const string& name, const string& type, int flights)
{
	SetId(id);
	SetName(name);
	SetType(type);
	SetFlights(flights);
}

int Plane::GetId() const
{
	return id;
}

string Plane::GetName() const
{
	return name;
}

string Plane::GetType() const
{
	return type;
}

int Plane::GetFlights() const
{
	return flights;
}

void Plane::SetId(int id)
{
	if (id <= 0)
	{
		throw invalid_argument("Id cannot be zero or negative!");
	}

	this->id = id;
}