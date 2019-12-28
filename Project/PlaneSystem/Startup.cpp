#include "PlaneFactory.h"

using namespace std;

void Create(string& input, PlaneFactory& factory)
{
	regex createRegex("^create\\s+(\\d+)\\s+(.*?)\\s+([A-Za-z]+)\\s+(\\d+)$");
	smatch matches;
	regex_search(input, matches, createRegex);

	int id = stoi(matches[1].str());
	string name = matches[2].str();
	string type = matches[3].str();
	int flights = stoi(matches[4].str());

	factory.Create(id, name, type, flights);
}

void Delete(string& input, int firstSpaceIndex, PlaneFactory& factory)
{
	string idString = input.substr(firstSpaceIndex);
	int id = stoi(idString);
	factory.Delete(id);
}

void Update(string& input, PlaneFactory& factory)
{
	regex updateRegex("^update\\s+(\\d+)\\s+([A-Za-z]+)\\s(.*?)$");

	smatch matches;
	regex_search(input, matches, updateRegex);

	int id = stoi(matches[1].str());
	string attribute = matches[2].str();
	string value = matches[3].str();

	factory.Update(id, attribute, value);
}

void Show(string& input, PlaneFactory& factory)
{
	regex showRegex("^show\\s+(\\d+)\\s+(\\d+)$");
	smatch matches;
	regex_search(input, matches, showRegex);

	int offset = stoi(matches[1].str());
	int limit = stoi(matches[2].str());
	factory.Show(offset, limit);
}

void Search(string& input, int firstSpaceIndex, PlaneFactory& factory)
{
	string idString = input.substr(firstSpaceIndex);
	int id = stoi(idString);
	factory.Search(id);
}

int main()
{
	const string fileName = "PlanesDb.txt";
	PlaneFactory factory(fileName);

	string input;
	getline(cin, input);

	while (input != "exit")
	{
		try
		{
			int firstSpaceIndex = input.find(' ');
			string command = input.substr(0, firstSpaceIndex);

			if (command == "create")
			{
				Create(input, factory);
			}
			else if (command == "delete")
			{
				Delete(input, firstSpaceIndex, factory);
			}
			else if (command == "update")
			{
				Update(input, factory);
			}
			else if (command == "show")
			{
				Show(input, factory);
			}
			else if (command == "optimize")
			{
				factory.Optimize();
			}
			else if (command == "search")
			{
				Search(input, firstSpaceIndex, factory);
			}
			else if (command == "print")
			{
				factory.Print();
			}
		}
		catch (const exception& e)
		{
			cout << e.what() << endl;
		}

		getline(cin, input);
	}

	factory.SaveToFile();

	while (true) {}
	return 0;
}