#include <iostream>
#include "PlaneFactory.h"

using namespace std;

int main()
{
	try
	{
		const string fileName = "PlanesDb.txt";
		PlaneFactory factory(fileName);

		string input;
		getline(cin, input);

		while (input != "exit")
		{
			int firstSpaceIndex = input.find(' ');
			string command = input.substr(0, firstSpaceIndex);
			
			if (command == "create")
			{

			}
			else if (command == "delete")
			{
				string idString = input.substr(firstSpaceIndex);
				int id = stoi(idString);
				factory.Delete(id);
			}
			else if (command == "update")
			{

			}
			else if (command == "show")
			{

			}
			else if (command == "optimize")
			{
				factory.Optimize();
			}
			else if (command == "search")
			{
				string idString = input.substr(firstSpaceIndex);
				int id = stoi(idString);
				factory.Search(id);
			}
			else if (command == "print")
			{
				factory.Print();
			}

			getline(cin, input);
		}
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}

	while (true) {}
	return 0;
}