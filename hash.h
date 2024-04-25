#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
	HASH_INDEX_T rValues[5]{ 983132572, 1468777056, 552714139, 984953261, 261934300 };
	MyStringHash(bool debug = true)
	{
		if (false == debug) {
			generateRValues();
		}
	}
	// hash function entry point (i.e. this is h(k))
	HASH_INDEX_T operator()(const std::string& k) const
	{
		// Add your code here
		int str_len = k.length();
		unsigned long long wVals[5] = { 0,0,0,0,0 }; // initializes wVals array

		// vector to store the 0-35 digit numbers, you can just push it back into the vector
		std::vector<unsigned long long> numericVals(str_len, 0); // switched to vector because using array generates C2131 in Visual Studio
		// also could use an unsigned long long numericVals[str_len];
		//unsigned long long numericVals[str_len];

		// initializes it to all 0
		for (int i = 0; i < str_len; ++i)
		{
			numericVals[i] = 0;
		}

		for (int i = 0; i < k.length(); i++)
		{
			numericVals[i] = letterDigitToNumber(k[i]);
		}

		int curr_idx = str_len - 1;// start at the last character of the string
		//int curr_arr_idx = 28 - 1; // start at the 27th idx, the last one in the vals array
									  // if we can't finish the string, the leading values will all be 0.

		int wIdx = 4; // w[i] starts at index 4
		// 'helloworld' --> (--hell) + (oworld)
		while (curr_idx >= 0)
		{
			unsigned long long result = 0;
			// where i stands for the digit of the word
			for (int i = 6; i > 0; --i)
			{
				if (i == 6) // a6
				{
					result += numericVals[curr_idx];
				}

				if (i == 5) // 36 * a5
				{
					result += 36 * numericVals[curr_idx];
				}

				if (i == 4) // 36^2 * a4
				{
					result += pow(36, 2) * numericVals[curr_idx];
				}

				if (i == 3) // 36^3 * a3
				{
					result += pow(36, 3) * numericVals[curr_idx];
				}

				if (i == 2) // 36^4 * a2
				{
					result += pow(36, 4) * numericVals[curr_idx];
				}

				if (i == 1) // 36^5 * a4
				{
					result += pow(36, 5) * numericVals[curr_idx];
				}

				--curr_idx;

				if (curr_idx < 0)
				{
					wVals[wIdx] = result;
					break;
				}
			}
			//wVals[wIdx] = 0; // stores result in the current index
			wVals[wIdx] = result;
			--wIdx; // moves on to the new index
		}

		// conditional statement

		return rValues[0] * wVals[0] + rValues[1] * wVals[1] +
			rValues[2] * wVals[2] + rValues[3] * wVals[3] +
			rValues[4] * wVals[4];

	}

	// A likely helper function is to convert a-z,0-9 to an integral value 0-35
	HASH_INDEX_T letterDigitToNumber(char letter) const
	{
		// Add code here or delete this helper function if you do not want it
		char c = tolower(letter);
		/*
		switch (c)
		{
		case 'a': return 0;
		case 'b': return 1;
		case 'c': return 2;
		case 'd': return 3;
		case 'e': return 4;
		case 'f': return 5;
		case 'g': return 6;
		case 'h': return 7;
		case 'i': return 8;
		case 'j': return 9;
		case 'k': return 10;
		case 'l': return 11;
		case 'm': return 12;
		case 'n': return 13;
		case 'o': return 14;
		case 'p': return 15;
		case 'q': return 16;
		case 'r': return 17;
		case 's': return 18;
		case 't': return 19;
		case 'u': return 20;
		case 'v': return 21;
		case 'w': return 22;
		case 'x': return 23;
		case 'y': return 24;
		case 'z': return 25;
		case '0': return 26;
		case '1': return 27;
		case '2': return 28;
		case '3': return 29;
		case '4': return 30;
		case '5': return 31;
		case '6': return 32;
		case '7': return 33;
		case '8': return 34;
		case '9': return 35;
		default: return -1;
		}*/
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
		std::mt19937 generator(seed);  // mt19937 is a standard random number generator

		// Simply call generator() [it has an operator()] to get another random number
		for (int i{ 0 }; i < 5; ++i)
		{
			rValues[i] = generator();
		}
	}
};

#endif
