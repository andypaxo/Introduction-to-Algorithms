#include <iostream>
#include <vector>
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
	vector<int> pancakes;
	bool findNext(vector<int>, int*, int*);
	void recordFlip(int, vector<int>);
	
	public:
		void add(int);
		vector<int> makeFlips();
};

void flapstack::add(int size) {
	pancakes.push_back(size);
}

bool flapstack::findNext(vector<int> sorted, int* nextPosition, int* positionOfTarget) {
	int cPos = *nextPosition - 1;
	
	// TODO : Make sure that this can't overrun the length of the list
	// Find first mismatch
	while (sorted[cPos] == pancakes[cPos] && cPos >= 0)
		cPos--;
		
	*nextPosition = cPos;
	
	if (cPos <= 0)
		return false;
	
	// Find position of target
	int targetValue = sorted[cPos];
	while (sorted[cPos] != targetValue && cPos < pancakes.size())
		cPos++;
		
	*positionOfTarget = cPos;
	
	return true;
}

void flapstack::recordFlip(int position, vector<int> flips) {
	if (position == 0)
		return;

	// TODO : IMPLEMENT flip
	
	int outputPos = pancakes.size() - position;
	flips.push_back(outputPos);	
	cout << outputPos << " ";
}

vector<int> flapstack::makeFlips() {
	// The list we want to construct via flips
	// At the end of the method, both the pancakes and sorted lists should be identical
	list<int> sortedList = list<int>(pancakes.begin(), pancakes.end());
	sortedList.sort();
	vector<int>sorted = vector<int>(sortedList.begin(), sortedList.end());
	
	// List of flip manuvers to make, this will be output
	vector<int> flips;
	
	// The first position that contains a pancake of the wrong size
	int nextPosition = pancakes.size();
	int positionOfTarget;
	
	// Find the lowest position in the stack that doesn't contain the right pancake
	// Find the position of pancake that should be there
	// (If we reach the top without finding any, STOP)
	while (findNext(sorted, &nextPosition, &positionOfTarget)) {		
		// Flip at the position of the right pancake to get it to the top (+output)
		// (If the right one is already at the top, skip this step)
		recordFlip(positionOfTarget, flips);
		
		// Flip at the out of sequence position to get the right pancake there (+output)
		recordFlip(nextPosition + 1, flips);
	}

	return flips;
}

void writeFlips(flapstack stack) {
	vector<int> flips = stack.makeFlips();
	cout << "0" << endl;
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
		cout << line << " - ";
		flapstack current = readStack(line);
		writeFlips(current);
	}

	return 0;
}
