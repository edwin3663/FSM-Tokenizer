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
Nov 5, 2016
*/


#ifndef PARSERCLASSES_H_
#define PARSERCLASSES_H_

#include <string>
#define START 0 

using namespace std;

/*
  A Token is a string of input characters that represent a specific class of C++ grammar.
  For example a token can be an identifier, keyword, digit, symbol, or etc.
*/
class Token {
private:
	Token *next; 			// ptr to next token in the list
	Token *prev; 			// ptr to prev token in the list
	string stringRep; // the sequence of characters that form the token
	
	friend class TokenList;
public:
	/*
	  Default constructor creates a Token without a next or previous token and an empty string value
	*/
	Token() : next(NULL), prev(NULL) { }
		
  /*
    Constructor creates a Token with a string value
    @param stringRep the sequence of characters that form the token
  */
	Token(const string& stringRep) : next(NULL), prev(NULL), stringRep(stringRep) { }

	/*
	  Returns the next token in the list. A NULL value represents the end of the list
	*/
	Token* getNext() { return next; }

	/*
		Use the given Token ptr for the next Token in the list
	  @param next - the next token in the list, a NULL value represents the end of the list
  */
	void setNext(Token* next ) { this->next = next; }

  /*
    Returns the previous token in the list.  A NULL value represents the beginning of the list
  */
	Token* getPrev() const { return prev; }

	/*
    Use the given Token ptr for the previous Token in the list
	  @param prev the previous token in the list, A NULL value represents the beginning of the list
	*/
	void setPrev(Token* prev ){ this->prev = prev; }

	/*
    Returns a reference to the Token's data
	*/
	const string& getStringRep() const { return stringRep; }

	/*
    Uses the given string for the Token's data
	  @param stringRep the sequence of characters that represent the Token
	*/
	void setStringRep(const string& stringRep ) { this->stringRep = stringRep; }
};

/*
  TokenList is a double-linked list using a Token for each node.
*/
class TokenList {
private:
	Token *head;				// head of the list of Tokens
	Token *tail;				// tail of the list of Tokens
	Token *nextToken;		// next Token in the list
	
public:
	/*
	  Default Constructor
	*/
	TokenList() : head(NULL), tail(NULL), nextToken(NULL) { }
	
	/*
	  Returns a pointer to the fisrt token in the list. A NULL value represents an empty list.
	*/
	Token* getFirst() const { return head; }

	/*
	  Returns a pointer to the last token in the list. A NULL value represents an empty list.
	*/
	Token* getLast() const { return tail; }
	
	/*
	    Returns the next token to be read from the list. A NULL value represents an empty list or end of list
	*/
	Token* getNextInList()
	{
	    Token *curToken = nextToken;
	    nextToken = nextToken->next;
	    return curToken;
	}

	/*
	  Creates a Token from the given string and appends it to the end of the list.
	  @param str the string to set as the value of the token. Allowed to be NULL.
	*/
	void append(const string& str);

	/*
		Appends the given Token to the end of the list
	  @param token string to set as the value of the token. Allowed to be NULL.
	*/
	void append(Token *token);

	/*
		Removes the given Token from the list of Tokens
	  @param token the token to remove. Not allowed to be NULL.
	*/
	void deleteToken(Token *token);
	
	/*
	  Deletes the entire list of tokens
	*/
	void deleteList() 
	{
    while (head != NULL) {
	    Token *temp = head;
	    deleteToken(head);     	        
	    head = temp->next;
    }
	}
};

/*
  The Tokenizer class takes a string of well-formed C++ and splits it into
  its tokens according it's BNF grammar.
*/
class Tokenizer {
private:

		/*
			These are the commands that the Tokenizer can perform each character
			
  	  STORE = store current character to buffer
	    ACCEPT = copy the buffer to a token, and increase offset 1
  	  ACCEPT_BACK1 = copy the buffer to a token
	    ACCEPT_BACK2 = copy the buffer to a token, and decresse offset 2
      START_BLOCK_COMMENT = processes block comments
      START_INLINE_COMMENT = processes inline comments
      START_INCLUDE = treats the < > characters as "
      STOP_BLOCK_COMMENT = never used
      IGNORE = skips the current character
      ERROR = report an error in lexeme (ununsed)
    */
    enum commands_t { STORE = 0, ACCEPT, ACCEPT_BACK1, ACCEPT_BACK2, 
                      START_BLOCK_COMMENT, START_INLINE_COMMENT,
                      START_INCLUDE, STOP_BLOCK_COMMENT, IGNORE, ERROR };

                    
    commands_t stateCommands[78] = {
                IGNORE,
                STORE,
                ACCEPT,
                ACCEPT,
                ACCEPT_BACK1,
                STORE,
                ACCEPT,
                ACCEPT,
                STORE,
                ACCEPT,
                ACCEPT_BACK1,
                ACCEPT_BACK1,
                STORE,
                STORE,
                ACCEPT,
                ACCEPT_BACK1,
                ACCEPT,
                ACCEPT_BACK1,
                STORE,
                STORE,
                ACCEPT,
                ACCEPT_BACK1,
                ACCEPT,
                ACCEPT_BACK1,
                STORE,
                ACCEPT,
                ACCEPT_BACK1,
                ACCEPT,
                STORE,
                ACCEPT,
                ACCEPT_BACK1,
                ACCEPT,
                ACCEPT,
                STORE,
                ACCEPT_BACK1,
                ACCEPT,
                ACCEPT,
                STORE,
                ACCEPT_BACK1,
                ACCEPT,
                START_INLINE_COMMENT,
                START_BLOCK_COMMENT,
                STORE,
                ACCEPT,
                ACCEPT_BACK1,
                STORE,
                ACCEPT,
                ACCEPT_BACK1,
                STORE,
                ACCEPT_BACK1,
                STORE,
                ACCEPT,
                ACCEPT_BACK1,
                STORE,
                STORE,
                STORE,
                ACCEPT,
                STORE,
                STORE,
                STORE,
                ACCEPT,
                STORE,
                ACCEPT_BACK1,
                ACCEPT,
                STORE,
                STORE,
                STORE,
                STORE,
                ACCEPT,
                STORE,
                STORE,
                ACCEPT_BACK1,
                STORE,
                STORE,
                ACCEPT,
                ACCEPT_BACK1,
                START_INCLUDE,
                STORE
                };                  

	/* State tracking variables for processing a single string */
	bool processingInlineComment; //True if processing an In-line comment //
	bool processingBlockComment;  //True if processing a Block Comment /* */
	bool processingIncludeStatement; //True if processing an include statement <> ""
	bool complete; //True if finished processing the current string
	
	size_t offset; // current position in string
	string *str;   // the current line being processed
	int state;
	TokenList tokens;
	
	int cur_char; // the character we are looking at now

  string buffer; // buffer characters until we decide it is the end of the token

  // processes a command at each stage of the tokenizing process    
  void processStateCommand(commands_t command);
  
  /*
    Takes the buffer of characters adds it to the list of tokens.  Then increases the offset one position 
  */    
  void addToken();
    
public:

	/*
		Default constructor
	*/
	Tokenizer() 
	{
	    processingInlineComment = false;
	    processingBlockComment = false;
	    processingIncludeStatement = false;
	    complete = false;
	    offset = 0;
	    state = 0;
    }

  /*
    My setString implementation takes a string and tokenizes it.  Each token is first added to a list inside the Tokenizer class.
    When all tokens are added from a line they can be retrieved by the getNextToken function one-by-one.
    @param str the string to be tokenized.  Not allowed to be NULL.
  */
	void setString(string *str);

	/*
	 Returns true if all possible tokens have been extracted from the internal token list
	*/
	bool isComplete() const { return complete; }

  /*
   Returns the next token from the internal list of tokens.
  */
	string getNextToken();
};

#endif /* PARSERCLASSES_H_ */
