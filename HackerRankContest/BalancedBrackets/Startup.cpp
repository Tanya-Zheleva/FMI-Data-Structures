#include <iostream>
#include <stack>
#include <string>

using namespace std;

string isBalanced(string s) {
	int len = s.size();
	stack<char> brackets;

	for (int i = 0; i < len; i++)
	{
		char current = s[i];

		if (current == '(' || current == '[' || current == '{')
		{
			brackets.push(current);
		}
		else
		{
			if (brackets.empty()) return "NO";

			char lastAdded = brackets.top();
			brackets.pop();

			if (current == ')' && lastAdded != '(') return "NO";

			if (current == ']' && lastAdded != '[') return "NO";

			if (current == '}' && lastAdded != '{') return "NO";
		}
	}

	return brackets.empty() ? "YES" : "NO";
}

int main()
{
	int t = 0;
	cin >> t;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int i = 0; i < t; i++) {
		string s;
		getline(cin, s);

		string result = isBalanced(s);
		cout << result << endl;
	}

	while (true) { }
	return 0;
}
