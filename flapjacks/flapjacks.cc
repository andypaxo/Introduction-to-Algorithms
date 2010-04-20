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
	// List of pancake sizes, top first
	list<int> pancakes;
	// Target list
	list<int> sorted;
	bool initialised;
	
	int position;
	
	void initialise();
	
	public:
		void add(int);
		bool flipOne(int*);
};

void flapstack::add(int size) {
	pancakes.push_back(size);
}

void flapstack::initialise() {
	initialised = true;
	
	sorted = list<int>(pancakes);
	sorted.sort();
	
	position = pancakes.size() - 1;
}

bool flapstack::flipOne(int* nextFlip) {
	if (!initialised)
		initialise();
	
	// TODO : Watch out that we don't try to flip only one pancake - they're already cooked

	return false;
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
