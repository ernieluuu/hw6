#include "hash.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

/*

for testing sake, change main function to not have argc, argv
just create an input string within main and pass it in.

*/

/*
int main()
{

	string k = "abc123";

	// use debug r values so we get repeated results
	MyStringHash h1(true);

	// key to hash
	//string k(argv[1]);
	size_t hk = h1(k);
	// Test the hash
	cout << "h(" << k << ")=" << hk << endl;
	return 0;
}
*/


int main(int argc, char* argv[])
{
    if(argc < 2){
        cout << "Please provide a string to hash" << endl;
        return 1;
    }

    // use debug r values so we get repeated results
    MyStringHash h1(true);

    // key to hash
    string k(argv[1]);
    size_t hk = h1(k);
    // Test the hash
    cout << "h(" << k << ")=" << hk << endl;
    return 0;
}
