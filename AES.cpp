//
// AES.cpp
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
// Login: xxxxxxxx
// ID: xxxxxxxx
// Email: xxxxxxx@mix.wvu.edu

// Inlclude the header file, that contains variables and in turn loads the support file and other needed libraries.
#include "AES.h"

int main(int argc, const char * argv[]) {

	// Try and open the file, if it fails, quit the program.
	// Else load the file content into an string (message).
	cout << "Loading input.txt";
	if (myMessage.fail()) {
		cout << "...........Failed" << endl;;
		return 0;
	} else {
		cout << ".............";
		while (getline(myMessage, tempMessage)) {
			message+=tempMessage;
		}
		myMessage.close();
		cout << "Done" << endl;
	}

	// Try and open the file, if it fails, quit the program.
	// Else load the file content into an string (key).
	cout << "Loading key.txt";
	if (myKey.fail()) {
		cout << ".............Failed" << endl;
		return 0;
	} else {
		cout << "...............";
		while (!myKey.eof()) {
			getline(myKey, key);
		}
		myKey.close();
		cout << "Done" << endl;
	}

	// Print out the message
	//cout << "Message to encrypt: \n" << message << endl;

	// Print out the key
	//cout << "Key to use for encryption: \n" << key << endl;

	// Perform preprocessing to remove punctuation.
	cout << "Performing preprocessing";
	message = preprocessing(message);

	// Perform polyalphabetic substitution using the Vigenere cipher
	cout << "Creating Cipher...";
	cipher = substitution(message, key);
	cout << "Done" << endl;

	// Save the output of step 2.2.
	cout << "Saving Substitution...........";
	myOutput.open ("output.txt", fstream::app|fstream::out);
	myOutput << "Substitution: \n";
	myOutput << cipher << endl << endl;
	myOutput.close();
	cout << "Done" << endl;

	// Calculate the matrix size based on the string length of the message.
	matrixSize = ceil(double(cipher.length())/16);

	// After we have defined our matrixSize, we can create the necessary vector.
	// Holds the original character cipher. Using unsigned char for lowest memory use.
	// Vector type is used since an array cannot be declared with a non-constant length. A pointer-pointer-pointer array could be used, but to keep it simple, and avoid messing with the memory, a vector is used.
	vector<vector<vector<unsigned char> > > AES (4,vector<vector<unsigned char> >(4, vector<unsigned char>(matrixSize)));

	// Holds the hex character cipher. String is needed since the cipher contains 2 characters of both char and int.
	vector<vector<vector<string> > > AESstring (4,vector<vector<string> >(4, vector<string>(matrixSize)));

	// Holds the hex character cipher after the MixColumns.
	vector<vector<vector<string> > > AESMix (4,vector<vector<string> >(4, vector<string>(matrixSize)));

	// Initialize a temp value to use for creating the matrix
	int temp;

	// Create the matrix by using three for-loops.
	cout << "Creating matrix of cipher.....";
	for (int y = 0; y < matrixSize; y++) {
		for (int x = 0; x < 4; x++) {
			for (int z = 0; z < 4; z++) {
				// Get the index using (y*width+x)*height+z.
				// This is the same thing used for image processing of RGB images and other types of structures that needs to go from a 1D array to a 3D array.
				temp = (y*4+x)*4+z;
				// If the temp value is >= the length of the cipher, then we add 'A' as padding.
				if (temp >= cipher.length()) {
					AES[z][x][y] = 'A';
				} else {
					AES[z][x][y] = cipher[temp];
				}
			}
		}
	}
	cout << "Done" << endl;

	// Save the output of step 2.3.
	cout << "Saving Padding................";
	myOutput.open ("output.txt", fstream::app|fstream::out);
	myOutput << "Padding: \n";
	for (int y = 0; y < matrixSize; y++) {
		for (int x = 0; x < 4; x++) {
			for (int z = 0; z < 4; z++) {
				myOutput << AES[z][x][y];
			}
			myOutput << endl;
		}
		myOutput << endl;
	}
	myOutput.close();
	cout << "Done" << endl;

	// Shifts the rows. This is not the optimal way of doing it, but it works.
	// Use a double for-loop to run through the rows and sections.
	// Use an additional for-loop to shift the columns.
	// This is done by swapping the numbers.
	// Since some lines (3+4) needs multiple swaps we have an additional condition for these.
	cout << "Performing ShiftRows..........";
	for (int i = 0; i < matrixSize; i++) {
		for (int k = 1; k < 4; k++) {
			for (int j = 1; j < 4; j++) {
				swap(AES[j%4][k][i], AES[(j+1)%4][k][i]);
			}

			if (k==2 || k==3) {
				for (int j = 1; j < 4; j++) {
					swap(AES[j%4][k][i], AES[(j+1)%4][k][i]);
				}
			}

			if (k==3) {
				for (int j = 1; j < 4; j++) {
					swap(AES[j%4][k][i], AES[(j+1)%4][k][i]);
				}
			}
		}
	}
	cout << "Done" << endl;

	// Save the output of step 2.4.
	cout << "Saving ShiftRows..............";
	myOutput.open ("output.txt", fstream::app|fstream::out);
	myOutput << "ShiftRows: \n";
	for (int y = 0; y < matrixSize; y++) {
		for (int x = 0; x < 4; x++) {
			for (int z = 0; z < 4; z++) {
				myOutput << AES[z][x][y];
			}
			myOutput << endl;
		}
		myOutput << endl;
	}
	myOutput.close();
	cout << "Done" << endl;

	// Create the parity bit for each number in the shifted AES array and convert the result to hex.
	// The result is stored in a string array, since the hex values contain multiple characters and integers.
	cout << "Creating parity bit...........";
	for (int y = 0; y < matrixSize; y++) {
		for (int x = 0; x < 4; x++) {
			for (int z = 0; z < 4; z++) {
				AESstring[z][x][y] = convertToHex(parityBit(AES[z][x][y]));
			}
		}
	}
	cout << "Done" << endl;

	// Save the output of step 2.5.
	cout << "Saving Parity.................";
	myOutput.open ("output.txt", fstream::app|fstream::out);
	myOutput << "Parity: \n";
	for (int y = 0; y < matrixSize; y++) {
		for (int x = 0; x < 4; x++) {
			for (int z = 0; z < 4; z++) {
				myOutput << AESstring[z][x][y] << " ";
			}
			myOutput << endl;
		}
		myOutput << endl;
	}
	myOutput.close();
	cout << "Done" << endl;

	// Performs the MixColumn calculation.
	cout << "Performing MixColumns.........";
	for (int h = 0; h < matrixSize; h++) {
		for (int k = 0; k < 4; k++) {
			for (int j = 0; j < 4; j++) {
				for (int i = 0; i < 4; i++) {
					// Based on the number in the matrix (m) either multiply with 1, 2 or 3.
					// Since we are using the original shifted AES array (not the hex array), we need to do the parityBit again.
					// This is probably counterintuitive when thinking of speed and memory, but it is the easiest, this way we don't have to convert hex to binary.
					switch(m[j][i]) {
						case 1:
							r[i] = multiplyOne(parityBit(AES[k][i][h]));
							break;
						case 2:
							r[i] = multiplyTwo(parityBit(AES[k][i][h]));
							break;
						case 3:
							r[i] = multiplyThree(parityBit(AES[k][i][h]));
							break;
					}
				}
				// Save the XOR'ed value as hex in the new AESMix array.
				AESMix[k][j][h] = convertToHex(XOR(XOR(XOR(r[0],r[1]),r[2]),r[3]));
			}
		}
	}
	cout << "Done" << endl;

	// Save the output of step 2.6.
	cout << "Saving MixColumns.............";
	myOutput.open ("output.txt", fstream::app|fstream::out);
	myOutput << "MixColumns: \n";
	for (int y = 0; y < matrixSize; y++) {
		for (int x = 0; x < 4; x++) {
			for (int z = 0; z < 4; z++) {
				myOutput << AESMix[z][x][y] << " ";
			}
			myOutput << endl;
		}
		myOutput << endl;
	}
	myOutput.close();
	cout << "Done" << endl;

	cout << "_______________Done_______________" << endl;

	// Return 0, as our program has completed without problems.
	return 0;
}

// Polyalphabetic substitution using the Vigenere cipher.
// For the length of the message, we substitute the char with a new char for the cipher based on the key. The key is repeated for the length of the message.
// The new cipher string is returned.
string substitution(string message, string key) {
	string cipher;
	cout << "............";
	for (int i = 0; i < message.length(); i++) {
		cipher += char((message[i]+key[(i+key.length())%key.length()])%26+'A');
	}
	return cipher;
}

// For each char in the string message check if it is a character between A and Z. This can be done by checking the integer value of the char and make sure it is between 65 and 90 (both included).
// Return the new message wihtout the punctuation.
string preprocessing(string message) {
	cout << "......";

	string temp;
	for (int i = 0; i < message.length(); i++) {
		if (!(int(message[i]) > 90 || int(message[i] < 65))) {
			temp+=(message[i]);
		}
	}
	message = temp;
	cout << "Done" << endl;

	// Save the output of step 2.1.
	myOutput.open ("output.txt");
	cout << "Saving Preprocessing result.";
	myOutput << "Preprocessing: \n";
	cout << ".";
	myOutput << message << endl << endl;
	cout << ".";
	myOutput.close();
	cout << "Done" << endl;

	return message;
}
