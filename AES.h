//
// AES.h
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

// Include our support file that contains most of the basic functions.
#include "Support.cpp"

// cout and other basic stuff
#include <iostream>

// File use
#include <fstream>

// To avoid using char arrays
#include <string>

// For use in the 3D arrays. It is easier to use a vector than a *** array.
#include <vector>

//For ceil
#include <math.h>

// To avoid writing std:: all the time.
using namespace std;

// Variables to load our message and key.
ifstream myMessage ("input.txt");
ifstream myKey ("key.txt");

// Variable to save our output to a file.
ofstream myOutput;

// Variable to store the temperary message, while loading multiple lines.
string tempMessage;

// Variables to store out message, key and cipher.
string message;
string key;
string cipher;

// Variable for the size of the matrix.
int matrixSize;

// Stores the value of the MixColumn matrix that is doing to be multiplied with the AES hex cipher.
int m[4][4] = { {2,3,1,1},
				{1,2,3,1},
				{1,1,2,3},
				{3,1,1,2}};

// Stores the binary value pre-XOR.
string r[4] = {};

// Simple polyalphabetic substitution using the Vigenere cipher, given message and key.
string substitution(string message, string key);

// Preprocessing to remove punctuation.
string preprocessing(string message);
