#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here

		/*
		Next you will translate a(sub)string of 6 letters a1 a2 a3 a4 a5 a6 into 
		an(unsigned long long) 64 - bit integer w[i]
		(essentially converting from base - 36 to decimal), 
		via the following mathematical formula 

		If an input word is longer than 6 letters, then you should first do the above 
		process for the last 6 letters in the word, then repeat the process for each
		previous group of 6 letters. Recall, you will never receive a word longer 
		than 28 characters. 
		The last group may not have 6 letters in which case you would treat it as a 
		substring of less than 6 characters as described above. Since we have at 
		most 28 characters this process should result in a sequence of no more than 
		5 integers: w[0] w[1] w[2] w[3] w[4], where w[4] was produced by the last 
		6 letters of the word.
		
		Store these values in an array (of unsigned long long). 
		Place zeros in the leading positions of w[i] if the string does not 
		contain enough characters to make use of those values. So for a string of 
		12 letters, w[0], w[1], and w[2] would all be 0 and only w[3] and w[4] 
		would be (potentially) non-zero.

		helloworld
		-->
		oworld
		__hell

		*/
		int str_len = k.length();
		unsigned long long vals[28]; // we know that we cannot have more than 28 chars
		// initializes the vals array
		for (int i = 0; i < 28; ++i)
		{
			vals[i] = 0;
		}
		// vector to store the 0-35 digit numbers, you can just push it back into the vector
		vector<int> numericVals; // can later change this to unsigned 4 bit integers if needed
		// also could use an unsigned long long numericVals[str_len];

		for (int i = 0; i < str_len; ++i)
		{
			numericVals.push_back(letterDigitToNumber(k[i]));
		}

		int curr_idx = str_len - 1;// start at the last character of the string
		int curr_arr_idx = 28 - 1; // start at the 27th idx, the last one in the vals array
									  // if we can't finish the string, the leading values will all be 0.

		int wIdx = 4; // w[i] starts at index 4
		// 'helloworld' --> (--hell) + (oworld)
		while (curr_idx >= 0)
		{
			// where i stands for the digit of the word
			for (int i = 6; i > 0; --i)
			{
				if (i == 6) // a6
				{
					vals[curr_arr_idx] = numericVals[curr_idx];
				}

				if (i == 5) // 36 * a5
				{
					vals[curr_arr_idx] = 36 * numericVals[curr_idx];
				}

				if (i == 4) // 36^2 * a4
				{
					vals[curr_arr_idx] = pow(36.0, 2) * numericVals[curr_idx];
				}

				if (i == 3) // 36^3 * a3
				{
					vals[curr_arr_idx] = pow(36.0, 3) * numericVals[curr_idx];
				}

				if (i == 2) // 36^4 * a2
				{
					vals[curr_arr_idx] = pow(36.0, 4) * numericVals[curr_idx];
				}

				if (i == 1) // 36^5 * a4
				{
					vals[curr_arr_idx] = pow(36.0, 5) * numericVals[curr_idx];
				} 

				--curr_arr_idx;
				--curr_idx;
				// if longer than string length, break
				if (curr_idx < 0)
				{
					break;
				}
			}
		}

		// HASH_INDEX_T to store the end result


		// for loop to pass each value in k into letterToDigitNumber
		// and store the returned HASH_INDEX_T into a ____ data structure.

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it

		if (isalpha(letter)) // is an alphabetical letter
		{
			// Convert uppercase letter to lowercase
			char lowercaseLetter = tolower(letter);

			// Map lowercase letter to a value between 0 and 25
			return static_cast<HASH_INDEX_T>(lowercaseLetter - 'a');
		}
		else if (isdigit(letter)) // the char is a number
		{
			// Map digit to a value between 26 and 35
			// '0' == 48 so we have to subtract it
			return static_cast<HASH_INDEX_T>(letter - '0' + 26);
		}
		else
		{
			// Return a default value for non-alphanumeric characters
			return -1;
		}
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
