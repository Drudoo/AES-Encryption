//
// Support.h
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

#include <string> // For string support
#include <iostream> // For cout support
#include <sstream> // For stringstream (when converting integers to strings)
#include <vector> //For std::vector
#include <algorithm> //For std::count

using namespace std;

// Print 3D array of unsigned char
void printArray(vector<vector<vector<unsigned char> > > &myArray, int matrixSize);

// Print 3D array of strings with separators
void printArraySpace(vector<vector<vector<string> > > &myArray);

// XOR two strings (should be in 8 bit binary format)
string XOR(string a, string b);

// Shift a string to the left
string shiftLeft(string str, int number);

// Make MixColumns multiplication using 1, 2 or 3
string multiplyOne(string number);
string multiplyTwo(string number);
string multiplyThree(string number);

// Remove spaces from a string
string removeSpaces(string message);

// Remove dots from a string
string removeDot(string message);

// Remove commas from a string
string removeComma(string message);

// Remove ; from a strings
string removeChar(string message, char key);

// Count instances of a char in a string
int countLetter(string message, char letter);

// Swap two chars
void swap(char &a, char &b);

// Convert an integer number to a binary number
string convertToBinary(int number);

// Parity bit
string parityBit(int number);

// Convert a decimal number to a hex number
string convertToHex(string number);

// Converts an integer to a string and returns it.
string int_to_string(int number);
