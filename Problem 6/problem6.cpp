#include <iostream>
#include <string>
#include <fstream>
#include "myStack.h"
using namespace std;

void reverse(string& str, int n)
{
	// create stack
	stackType<char> stack;
	
	// push all the characters from the string in the stack
	for (int i = 0; i < n; i++)
		stack.push(str[i]);

	// start from index 0
	int k = 0;

	// pop the stack until the stack is empty
	while (!stack.isEmptyStack())
	{
		// replace the each character of the strings with the elements of the stack
		str[k++] = stack.top();
		stack.pop();
	}
}



int main() {
	
		fstream file;
		string word, filename;

		// set the file name
		filename = "jokes.txt";

		// opening file 
		file.open(filename.c_str());

		// reads the words in the file
		while (file >> word)
		{
			//reverse each words
			reverse(word, word.length());
			cout << word << " ";
		}

		file.close();
}
