/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Contact: Peter Saffold, pgsaffold@hotmail.com
Nov 5, 2014
*/

#include "parserClasses.h"
#include <fstream>
#include <iostream>

/*
	Demonstrates how the Tokenizer takes well-formed C++ code from an input file.
	A numbered list of all the Tokens found is printed to the screen.
*/
int main(int argc, char *argv[]) {
  ifstream sourceFile;
  TokenList tokens;
  Tokenizer tokenizer;
  Token *t = nullptr;
  int c_count = 0;

  // Open the input file
  if (argc > 1) {
  	sourceFile.open(argv[1]);
  	std::cout << "Opening input file: " << argv[1] << std::endl;
		if (!sourceFile.is_open()) {
		  std::cout << "Failed to open file" << endl;
		  return 1;
		}
	}

	// Tokenizes the input file line-by-line
  while (!sourceFile.eof()) {
    string lineA, lineB;
    getline(sourceFile, lineA);

    // while the current line ends with a line-continuation \ append the next
    // line to the current line
    while (lineA.length() && lineA[lineA.length() - 1] == '\\') {
      lineA.erase(lineA.length() - 1, 1);
      getline(sourceFile, lineB);
      lineA += lineB;
    }
    tokenizer.setString(&lineA);
    while (!tokenizer.isComplete()) {
      string token = tokenizer.getNextToken();
      tokens.append(token);
    }

    // Re-insert newline that was removed by the getline function
    tokens.append("\n");
  }

	// Outputs the list of tokens found in source file
  t = tokens.getFirst();
  while (t) {
    std::cout << "Token " << ++c_count << ": ";

    if (t->getStringRep().compare("\n") == 0) {
      std::cout << "\\n";
    } else {
      std::cout << t->getStringRep();
    }
    std::cout << std::endl;
    t = t->getNext();
  }

  std::cout << "Number of tokens processed: " << c_count << std::endl;
  return 0;
}
