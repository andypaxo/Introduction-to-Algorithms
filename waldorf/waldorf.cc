#include <string>
#include <iostream>
#include <list>
using namespace std;

// Util ////////////////////////////////////////////////////////////////////////

char lower(char c) {
	return c >= 'a' ? c : c + ('a' - 'A');
}

string lower(string word) {
	string output;
	string::iterator i;
	
	for (i = word.begin(); i != word.end(); i++)
		output.push_back(lower(*i));

	return output;
}

// Quiz class //////////////////////////////////////////////////////////////////

class quiz {
	int width, height;
	list<string> words;
	list<string>::iterator cWord;
	char letters[50][50];
	bool gettingWords;
	
	bool getNextWord(string*);
	bool findInRow(int, string, int*);
	bool wordIsAtPoint(int, int, string);
	bool wordSearch(int, int, int, int, string);
	bool charIsAt(char, int, int);
	
	public:
		quiz(int, int);
		~quiz();
		
		void setRow(int, string);
		void addWord(string);
		bool solve (int*,int*);
		void print();
};

quiz::quiz (int w, int h) {
	width = w;
	height = h;
	gettingWords = false;
}

quiz::~quiz () {
	delete [] letters;
}

// Quiz class - diagnostic /////////////////////////////////////////////////////

void quiz::print() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++)
			cout << letters[i][j];
		cout << endl;
	}
	
	list<string>::iterator w;
	for  (w = words.begin(); w != words.end(); w++)
		cout << *w << endl;
	
}

// Quiz class - setup //////////////////////////////////////////////////////////

void quiz::setRow (int rowN, string text) {
	for (int i = 0; i < width; i++)
		letters[rowN][i] = lower(text.at(i));
}

void quiz::addWord (string word) {
	words.push_back(lower(word));
}

// Quiz class - logic //////////////////////////////////////////////////////////

bool quiz::charIsAt(char c, int x, int y) {
	return
		x >= 0 && y >= 0 &&
		x < width && y < height &&
		letters[y][x] == c;
}

bool quiz::wordSearch(int dirX, int dirY, int startX, int startY, string word) {
	string::iterator i;
	int cX = startX, cY = startY;
	for (i = word.begin(); i != word.end(); i++) {
		if (!charIsAt(*i, cX, cY))
			return false;
		cX += dirX;
		cY += dirY;
	}
	
	return true;
}

bool quiz::wordIsAtPoint(int cX, int cY, string word) {
	return
		charIsAt(word.at(0), cX, cY) && (
		wordSearch(-1, -1, cX, cY, word) ||
		wordSearch( 0, -1, cX, cY, word) ||
		wordSearch( 1, -1, cX, cY, word) ||
		wordSearch( 1,  0, cX, cY, word) ||
		wordSearch( 1,  1, cX, cY, word) ||
		wordSearch( 0,  1, cX, cY, word) ||
		wordSearch(-1,  1, cX, cY, word) ||
		wordSearch(-1,  0, cX, cY, word));
}

bool quiz::findInRow(int cY, string word, int* x) {
	for (int cX = 0; cX < width; cX++) {
		if (wordIsAtPoint(cX, cY, word)) {
			*x = cX + 1;
			return true;
		}
	}
	
	return false;
}

bool quiz::getNextWord(string* word) {
	if (cWord == words.end())
		return false;
	if (!gettingWords) {
		cWord = words.begin();
		gettingWords = true;
	}
		
	*word = *cWord;
	cWord++;
	
	return true;
}

bool quiz::solve (int* x, int* y) {
	string word;
	if (!getNextWord(&word))
		return false;
	
	for (int cY = 0; cY < height; cY++) {
		if (findInRow(cY, word, x)) {
			*y = cY + 1;
			return true;
		}
	}
	
	return true;
}

// Input ///////////////////////////////////////////////////////////////////////

quiz readQuiz() {
	int width, height;
	cin >> height >> width;
	quiz q(width, height);
	
	string row;
	for (int i = 0; i < height; i++) {
		cin >> row;
		q.setRow(i, row); 
	}
	
	int numWords;
	cin >> numWords;
	
	for (int i = 0; i < numWords; i++) {
		cin >> row;
		q.addWord(row);
	}
	
	return q;
}

list<quiz> readQuizzes() {
	int numQuizzes;
	cin >> numQuizzes;
	
	list<quiz> quizzes;
	
	for (int i = 0; i < numQuizzes; i++)
		quizzes.push_back(readQuiz());
		
	return quizzes;
}

// Logic ///////////////////////////////////////////////////////////////////////

void solve(quiz q) {
	int x, y;
	while (q.solve(&x, &y))
		cout << y << ' ' << x << endl;
	cout << endl;
}

// Main ////////////////////////////////////////////////////////////////////////

int main() {
	list<quiz> quizzes = readQuizzes();
	
	list<quiz>::iterator i;
	for (i = quizzes.begin(); i != quizzes.end(); i++)
		solve(*i);
	
	return 0;
}
