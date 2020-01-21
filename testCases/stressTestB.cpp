#include <string>
#include <iostream>

using namespace std;

//testing
/* testing again
 *
*
    */class myClass
{
    public:
	int value;
};

int
main
(
)
{



char
i =
'\0'
;
string l = "hi"
;
int e=1;		  				         /**/
//				*/ " ' <>#

int p = 6. ; // 6. should be ONE token
int t = .6 ; // .6 should be ONE token
int f = 6.6; // 6.6 should be ONE token

int y =
-.6e-2;  //This one should be three tokens: "-" and ".6e-2" and ";"
-.6*e-2; //This one should be seven tokens: "-" and ".6" and "*" and "e" and "-" and "2" and ";"	(e is a variable name)
-.6E-2;	 //E works the same as e, this should be three tokens: "-" and ".6E-2" and ";"

//*/THIS SHOULD BE A COMMENT
myClass name6;
name6. value = 6;	//For each of these, you should get |name6| |.| |value| |=| |6| |;|
name6 . value = 6;
name6 .value = 6;
name6.value = 6;

name6. value<<= name6.value?e:3;	// ? e : and 3 should be separate tokens
name6. value >>= name6.value;		// <<= and >>= are both 3-character tokens

name6.	value =e?:5;	// ?: should be one token, name6 and . need to be separate tokens
/*



a
aa
*/string z = "TEST"
;

y=z.length(); //This should be eight tokens, not including this comment

if(true&&true||false&&(1<5.2-e||e<=1)){ // 5.2-e should be 3 tokens, watch for double operators
}
return 0;
}

