#pragma once
#include <iostream>
#include <string>

using namespace std;

class Plane
{
private:
	int id;
	string name;
	string type;
	int flights;

public:
	Plane();
	Plane(int, const string&, const string&, int);

	int GetId() const;
	string GetName() const;
	string GetType() const;
	int GetFlights() const;

	void SetId(int);
	void SetName(const string&);
	void SetType(const string&);
	void SetFlights(int);

	void Print() const;

	friend ostream& operator<<(ostream&, const Plane&);
};

Plane::Plane() { }

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
	if (id < 0)
	{
		throw invalid_argument("Id cannot be negative!");
	}

	this->id = id;
}

void Plane::SetName(const string& name)
{
	if (name == "")
	{
		throw invalid_argument("Plane name cannot be an empty string!");
	}

	this->name = name;
}

void Plane::SetType(const string& type)
{
	if (type == "")
	{
		throw invalid_argument("Plane type cannot be an empty string!");
	}

	this->type = type;
}

void Plane::SetFlights(int flights)
{
	if (flights < 0)
	{
		throw invalid_argument("Plane flights cannot be negative!");
	}

	this->flights = flights;
}

void Plane::Print() const
{
	cout << "Plane: " << id << ", name: " << name << ", type: " << type << ", flights: " << flights << endl;
}

ostream& operator<<(ostream& out, const Plane& plane)
{
	out << plane.id << " / " << plane.name << " / "  << plane.type << " / " << plane.flights << endl;

	return out;
}