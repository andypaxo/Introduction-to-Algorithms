#include <iostream>
#include <list>
#include <string>
#include <sstream>
using namespace std;

/*
Solution for 'stacks of flapjacks'

NOTE: A flapjack is a sweet snack made from oats and syrup.
It is not the same as a pancake.
*/

class flapstack {
	// List of pancake sizes, bottom first
	list<int> pancakes;
	
	public:
		void add(int);
};

void flapstack::add(int size) {
	pancakes.push_front(size);
}

void writeFlips(flapstack stack) {
	int nextFlip;
	while (stack.flipOne(&nextFlip))
		cout << nextFlip << ' ';
	cout << '0' << endl;
}

flapstack readStack(string line) {
	// Consume pancakes
	stringstream stackReader(line, stringstream::in);
	
	flapstack stack;
	int nextSize;
	
	while (!stackReader.eof()) {
		stackReader >> nextSize;
		stack.add(nextSize);
	}
	
	return stack;
}

int main() {
	string line;
	while (getline(cin, line))
	{
		flapstack current = readStack(line);
		writeFlips(current);
	}

	return 0;
}
