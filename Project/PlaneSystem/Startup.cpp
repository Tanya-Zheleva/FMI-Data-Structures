#include <iostream>
#include "PlaneFactory.h"

using namespace std;

int main()
{
	try
	{
		PlaneFactory factory;
		const string fileName = "PlanesDb.txt";

		factory.ExtractFromFile(fileName);

		//factory.Create(99, "Plane 7", "737 Max", 5);
		//factory.Update(5, "Id", "9");
		factory.Print();

		/*factory.Create(5, "Plane 1", "AirBus", 7);
		factory.Create(1234, "Plane 2", "AirBus 737", 77);
		factory.Create(5555555, "Plane 33", "Concordia", 12);
		factory.Create(2, "Plane 4444", "AirBus Max", 0);
		factory.Print();

		factory.SaveToFile(fileName);*/
		/*
		cout << endl;
		factory.Print();*/
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}

	while (true) {}
	return 0;
}