#include <string>
#include <sstream>
#include <iostream>
#include <list>
#include <vector>
#include <math.h>

using namespace std;

list<int> makeIntList(string inputLine)
{
	istringstream input (inputLine,istringstream::in);
	int inputSize;
	input >> inputSize;	
	list<int> output = list<int>();
	
	int next;
	for (int n = 0; n < inputSize; n++)
	{
		input >> next;
		output.push_back(next);
	}
	
	return output;
}

bool isJolly(list<int> sequence)
{
	vector<bool> flags (sequence.size());
	int last;
	for (list<int>::iterator itr = sequence.begin(); itr != sequence.end(); itr++ )
	{
		if (itr != sequence.begin())
		{
			int diff = abs(last - *itr);
			if (diff >= flags.size() || flags[diff])
				return false;
			flags[diff] = true;
		}
		last = *itr;
	}
	
	return true;
}

int main()
{
	string inputLine;
	while (!cin.eof())
	{
		getline(cin, inputLine);
		if (inputLine.length() > 0)
		{
			list<int> sequence = makeIntList(inputLine);
			cout << (isJolly(sequence) ? "Jolly" : "Not jolly") << endl;
		}
	}
	
	return 0;
}
