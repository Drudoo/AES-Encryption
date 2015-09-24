//
// Support.cpp
//
// The MIT License (MIT)
//
// Copyright (c) 2015 Frederik Vanggaard Berentsen
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//  Created by Frederik Vanggaard Berentsen on 15/09/15.
//
//
// CS 465 Introduction to Computer Security:Programming Assignment #1
// Due on September 23rd, 2015
// Frederik Berentsen
// Login: fsberentsen
// ID: 800153924
// Email: fsberentsen@mix.wvu.edu

// Include the header file
#include "Support.h"

// Print array using a triple for-loop to loop through and print out each number from the array.
void printArray(vector<vector<vector<unsigned char> > > &myArray, int matrixSize) {
	for (int y = 0; y < matrixSize; y++) {
		for (int x = 0; x < 4; x++) {
			for (int z = 0; z < 4; z++) {
				cout << myArray[z][x][y];
			}
			cout << endl;
		}
		cout << endl;
	}
}

// Print array using a triple for-loop but pad the left side with a space.
void printArraySpace(vector<vector<vector<string> > > &myArray) {
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			for (int z = 0; z < 4; z++) {
				cout << myArray[z][x][y] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
}

// Since to_string() is not available by default on the LCSEE virtual machines (can be compiled using C++11, but let's keep it simple).
// Converts an integer to a string and returns it.
string int_to_string(int number) {
   stringstream ss;
   ss << number;
   return ss.str();
}

// XOR (Exclusive OR) two string numbers in the format of an 8 bit binary number and return the result.
string XOR(string a, string b) {
	string result;
	int c;
	for (int i = 0; i < a.length(); i++) {
		c = a[i]^b[i];
		result.append(int_to_string(c));
	}
	return result;
}

// Shift a string to the left given a number of times. Pads the result with a '0' to keep the string length.
string shiftLeft(string str, int number) {
	str.append(str.substr(0,number));
	str=str.substr(number,str.length());
	str[7] = '0';
	return str;
}

// MixColumns multiplication using 1. This is just returning the original number.
string multiplyOne(string number) {
	return number;
}

// MixColumns multiplication using 2. Check if the number starts with '1' or '0' to see if it needs to be XOR.
// Shift the number one spot and then XOR it or not, before returning the number.
string multiplyTwo(string number) {
	bool isXOR = false;
	string firstXOR = "00011011";
	if(number[0] == '1') isXOR = true;
	string shifted = shiftLeft(number,1);
	if(isXOR) {
		string xored = XOR(shifted,firstXOR);
		return xored;
	} else {
		return shifted;
	}
}

// MixColumns multiplication using 3. Do a multiplication using 2 and then XOR with the original number.
string multiplyThree(string number) {
	return XOR(multiplyTwo(number),number);
}

// Count the instances of a char in a string and return the number.
int countLetter(string message, char letter) {
	return count(message.begin(), message.end(), letter);
}

// Swap two char.
void swap(char &a, char &b) {
    char temp;
    temp = a;
    a = b;
    b = temp;
}

// Convert an integer to binary and return it as a string.
string convertToBinary(int number) {
	if(number==0) return "0";
	if(number==1) return "1";
	if(number%2 == 0) {
		return convertToBinary(number/2)+"0";
	} else {
		return convertToBinary(number/2)+"1";
	}
}

// Create parity bit on a number. First convert the number to binary and then based on the instances of '1' either pad with '1' or '0'.
// Return the new number.
string parityBit(int number) {
	string binary = convertToBinary(number);
	if(countLetter(binary, '1')%2!=0) {
		binary.insert(0,"1");
	} else {
		binary.insert(0,"0");
	}
	return binary;
}

// Convert a binary string to hex.
// This is NOT a good way or doing it.
// This is a hacked together function that works, but SHOULD NOT be used normally.
string convertToHex(string number) {
	string a, b;
	string r,l;
	for (int i = 0; i < 4; i++) {
		a.append(1,number[i]);
		b.append(1,number[i+4]);
	}

	if(a =="0000") r= "0";
	if(a =="0001") r= "1";
	if(a =="0010") r= "2";
	if(a =="0011") r= "3";
	if(a =="0100") r= "4";
	if(a =="0101") r= "5";
	if(a =="0110") r= "6";
	if(a =="0111") r= "7";
	if(a =="1000") r= "8";
	if(a =="1001") r= "9";
	if(a =="1010") r= "a";
	if(a =="1011") r= "b";
	if(a =="1100") r= "c";
	if(a =="1101") r= "d";
	if(a =="1110") r= "e";
	if(a =="1111") r= "f";

	if(b =="0000") l= "0";
	if(b =="0001") l= "1";
	if(b =="0010") l= "2";
	if(b =="0011") l= "3";
	if(b =="0100") l= "4";
	if(b =="0101") l= "5";
	if(b =="0110") l= "6";
	if(b =="0111") l= "7";
	if(b =="1000") l= "8";
	if(b =="1001") l= "9";
	if(b =="1010") l= "a";
	if(b =="1011") l= "b";
	if(b =="1100") l= "c";
	if(b =="1101") l= "d";
	if(b =="1110") l= "e";
	if(b =="1111") l= "f";

	return r+l;
}
