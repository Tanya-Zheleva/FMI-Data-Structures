#include "PlaneFactory.h"

using namespace std;

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
				regex createRegex("^create\\s+(\\d+)\\s+(.*?)\\s+([A-Za-z]+)\\s+(\\d+)$");
				smatch matches;
				regex_search(input, matches, createRegex);

				int id = stoi(matches[1].str());
				string name = matches[2].str();
				string type = matches[3].str();
				int flights = stoi(matches[4].str());

				factory.Create(id, name, type, flights);
			}
			else if (command == "delete")
			{
				string idString = input.substr(firstSpaceIndex);
				int id = stoi(idString);
				factory.Delete(id);
			}
			else if (command == "update")
			{
				regex updateRegex("^update\\s+(\\d+)\\s+([A-Za-z]+)\\s(.*?)$");

				smatch matches;
				regex_search(input, matches, updateRegex);

				int id = stoi(matches[1].str());
				string attribute = matches[2].str();
				string value = matches[3].str();

				factory.Update(id, attribute, value);
			}
			else if (command == "show")
			{
				regex showRegex("^show\\s+(\\d+)\\s+(\\d+)$");
				smatch matches;
				regex_search(input, matches, showRegex);

				int offset = stoi(matches[1].str());
				int limit = stoi(matches[2].str());
				factory.Show(offset, limit);
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
		}
		catch (const exception& e)
		{
			cout << e.what() << endl;
		}

		getline(cin, input);
	}

	while (true) {}
	return 0;
}