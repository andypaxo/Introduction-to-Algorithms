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
	
	public:
		void add(int);
		list<int> makeFlips(int*);
};

void flapstack::add(int size) {
	pancakes.push_back(size);
}

list<int> flapstack::makeFlips(int* nextFlip) {
	// The list we want to construct via flips
	// At the end of the method, both the pancakes and sorted lists should be identical
	list<int>sorted = list<int>(pancakes);
	sorted.sort();
	
	// List of flip manuvers to make, this will be output
	list<int> flips;
	
	// The first position that contains a pancake of the wrong size
	int nextPosition -1;
	int positionOfTarget;
	
	// Find the lowest position in the stack that doesn't contain the right pancake
	// Find the position of pancake that should be there
	// (If we reach the top without finding any, STOP)
	while (findNext(sorted, *nextPosition, *positionOfTarget)) {
	
		int positionOfTarget = 
		
		// Flip at the position of the right pancake to get it to the top (+output)
		// (If the right one is already at the top, skip this step)
		
		// Flip at the out of sequence position to get the right pancake there (+output)
			
	}

	return flips;
}

void writeFlips(flapstack stack) {
	
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
