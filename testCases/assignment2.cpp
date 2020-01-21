//Use only the following three libraries:
#include "parserClasses.h"
#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <sys/resource.h>

using namespace std;

//Removes all inline comments from the tokenList including the // marker
//Returns the number of comments removed
int removeInlineComments(TokenList &tokenList) { 
	int count = 0;
	Token *t = tokenList.getFirst();
	while(t) {
		Token *c1, *c2;
		if (t->getStringRep() == "//") {
			c1 = t;
			c2 = t->getNext();
			if (c2->getStringRep() != "\n") {
				t = c2->getNext();
				tokenList.deleteToken(c2);
				tokenList.deleteToken(c1);
				count++;
			}
			else {
				t = c2;
				tokenList.deleteToken(c1);
				count++;
			}
		}
		else {
			t= t->getNext();
		}
	}
	return count;
}

//Remove all block comments from the tokenList including /* and */ markers
//Returns the number of block comments removed (where each pair of /* and */ count as one comment)
int removeBlockComments(TokenList &tokenList) {
	int count = 0;
	Token *t = tokenList.getFirst();
	Token *prev;
	bool deleteNext = false;

	while(t) {
		if (t->getStringRep() == "/*") {
			deleteNext = true;
		}

		prev = t;
		t= t->getNext();

		if (prev->getStringRep() == "*/") {
			tokenList.deleteToken(prev);
			deleteNext = false;
			count++;
		}

		if (deleteNext) {
			tokenList.deleteToken(prev);
		}
	}
	return count;
}

//Example Test code for interacting with your Token, TokenList, and Tokenizer classes
//Add your own code to further test the operation of your Token, TokenList, and Tokenizer classes
int main(int argc, char *argv[]) {
	ifstream sourceFile;
	TokenList tokens;
	Tokenizer tokenizer;
	string lineA, lineB;

	//Read in a file line-by-line and tokenize each line
	if (argc > 1) {
		sourceFile.open(argv[1]);
		if (!sourceFile.is_open()) {
			cout << "Failed to open file" << endl;
			return 1;
		}
	}

	//Set Memory limit
	struct rlimit rlim;
	rlim.rlim_cur = 134217728; //128MB
	rlim.rlim_max = 268435456; //256MB
	setrlimit(RLIMIT_AS, &rlim);

	string runTokenizer = argv[2];
	if (argc > 2 && runTokenizer == "true") {
		getline(sourceFile, lineA);
		while(!sourceFile.eof()) {

			//while the current line ends with a line-continuation \ append the next line to the current line
			while(lineA.length() && lineA[lineA.length()-1] == '\\') {
				lineA.erase(lineA.length()-1, 1);
				getline(sourceFile, lineB);
				lineA += lineB;
			}

			tokenizer.setString(&lineA);
			while(!tokenizer.isComplete()) {
				tokens.append(tokenizer.getNextToken());
			}
			//Re-insert newline that was removed by the getline function
			tokens.append("\n");
			getline(sourceFile, lineA);
		}
	}
	else {
		string testNULL = argv[4];
		if (argc > 4 && testNULL == "true") {
			tokens.append(NULL);
			tokens.deleteToken(NULL);
		}
		tokens.append("test");
		tokens.append("token");
		tokens.append("//");
		tokens.append("comment1");
		tokens.append("\n");
		tokens.append("//");
		tokens.append("comment2");
		tokens.append("\n");
		tokens.append("test");

		/*Output should be 9 tokens, 5 if comments removed */
	}

	string processComments = argv[3];
	if (argc > 3 &&processComments == "true") {
		removeInlineComments(tokens);
		removeBlockComments(tokens);
	}

	/*Test your tokenization of the file by traversing the tokens list and printing out the tokens*/
	int length = 0;
	Token *t = tokens.getFirst();
	while(t) {
		cout << t->getStringRep() << " ";
		length++;
		t = t->getNext();
	}
	cout << "Final Token Count: " << length << endl;
	return 0;
}
