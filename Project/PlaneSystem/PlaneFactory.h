#include <map>
#include "Plane.h"
#pragma once

using namespace std;

class PlaneFactory
{
private:
	map<int, Plane> planes;

	bool HasId(int) const;

public:
	PlaneFactory();

	void Create(int, const string&, const string&, int);
	void Delete(int);
	void Update(int, const string&);
	void Show(int, int) const;
	void Optimize();
	void Search(int) const;
};