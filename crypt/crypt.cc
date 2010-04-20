#include <iostream>
#include <list>
#include <string>
#include <sstream>
using namespace std;
list<string> dictionary;

class cypher
{
	char values[27];
	void init();
	
	public:
		bool isValid;
		
		cypher();
		cypher(const cypher&);
		cypher(string, string);
		void set(char, char);
		char get(char);
		cypher merge(cypher);
		bool equals(cypher);
};

void cypher::init() {
	memset(values, '-', 26);
	values[26] = 0; // Just so we can print the thing out as a string
	isValid = true;
}

cypher::cypher () {
	init();
}

cypher::cypher (string word, string dfn) {
	isValid = true;
	if (word.size() != dfn.size()) {
		isValid = false;
		return;
	}

	init();
	
	for (int i = 0; i < word.length(); i++) {
		set(word.at(i), dfn.at(i));
		if (!isValid)
			return;
	}
}

cypher::cypher (const cypher& other) {
	isValid = other.isValid;
	memcpy(values, other.values, 27);
}

void cypher::set(char code, char decode) {
	int index = code - 'a';
	if (values[index] != '-' && values[index] != decode) {
		isValid = false;
		return;
	}
	
	if (isValid && code != 'a' && memchr(values, decode, index) != NULL)
		isValid = false;
		
	if (isValid && code != 'z' && memchr(values + index + 1, decode, 25 - index) != NULL)
		isValid = false;
	
	values[index] = decode;
}

char cypher::get(char key) {
	return values[key - 'a'];
}

cypher cypher::merge(cypher other) {
	cypher output(*this);
	
	for (char i = 'a'; i <= 'z'; i++) {
		char value = other.values[i - 'a'];
		if (value != '-')
			output.set(i, value);
		if (!output.isValid)
			break;
	}
	
	return output;
}

bool cypher::equals(cypher other) {
	return memcmp(values, other.values, 26) == 0;
}

void read_dictionary(int size) {
	// Extract words, expect up to 16 mixed case characters
	for (int i = 0; i < size; i++)
	{
		string nextWord;
		cin >> nextWord;
		// TODO: Make lowercase
		dictionary.push_back(nextWord);
	}
}

list<cypher> getAllCyphersFor(string word) {
	list<cypher> cyphers;
	
	list<string>::iterator dfn;
	for (dfn = dictionary.begin(); dfn != dictionary.end(); dfn++)
	{
		cypher currCypher(word, *dfn);
		if (currCypher.isValid)
			cyphers.push_back(currCypher);
	}
	
	return cyphers;
}

string decode(string line, cypher decoder) {
	string output = "";
	for (int i = 0; i < line.length(); i++) {
		char value = line.at(i);
		output.append(1, value == ' ' ? ' ' : decoder.get(value));
	}
	return output;
}

string star(string line) {
	string output = "";
	for (int i = 0; i < line.length(); i++)
		output.append(1, line.at(i) == ' ' ? ' ' : '*');
	return output;
}

bool contains(list<cypher> cyphers, cypher subject) {
	list<cypher>::iterator cCypher;
	
	for (cCypher = cyphers.begin(); cCypher != cyphers.end(); cCypher++)
		if (subject.equals(*cCypher))
			return true;
	return false;
}

string decode(string line) {
	// Extract sentence, expect up to 80 lowercase characters
	istringstream lineReader (line, ios_base::in);
	
	// Create list of cyphers, initialised with a single blank
	list<cypher> candidates;
	cypher blankCypher;
	candidates.push_back(blankCypher);
	
	while (!lineReader.eof()) {
		string word;
		lineReader >> word;
		
		list<cypher> newCyphers = getAllCyphersFor(word);
		list<cypher> currentCyphers;
		
		list<cypher>::iterator oldCypher;
		list<cypher>::iterator newCypher;
		
		int mergeRejects = 0;
		int dupeRejects = 0;
		
		for (oldCypher = candidates.begin() ; oldCypher != candidates.end(); oldCypher++ ) {
			for (newCypher = newCyphers.begin() ; newCypher != newCyphers.end(); newCypher++ ) {
				
				cypher merged = (*oldCypher).merge(*newCypher);
				
				if (!merged.isValid)
					mergeRejects++;
				else if (contains(currentCyphers, merged))
					dupeRejects++;
				else
					currentCyphers.push_back(merged);
			}
		}
		
		candidates = currentCyphers;
	}
	
	if (candidates.size() > 0)
		return decode(line, candidates.front());
	else
		return star(line);
}

int main() {
	int dictionarySize;
	cin >> dictionarySize;
	read_dictionary(dictionarySize);
	
	while (!cin.eof())
	{
		string line;
		getline(cin, line);
		
		cout << decode(line) << endl;
	}
	
	return 0;
}
