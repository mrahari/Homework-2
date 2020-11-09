#include <iostream>
#include <string>
#include <fstream>
#include "myStack.h"
using namespace std;

int main() {

	stackType<int> stack(100);
	
	stack.push(1); // 1st value
	stack.push(2); // 2nd value
	stack.push(3); // 3rd value
	stack.push(4); // 4th value

	stack.changeThirdValue(10); // change the third value to 10 by iterating through the stack
	stack.listElements(); // list all elements of the stack
	
	//cout << stack.top() << endl;
  
}
