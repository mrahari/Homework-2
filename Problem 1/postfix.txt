//***********************************************************
// Author: D.S. Malik
//
// Program: Postfix Calculator  
// This program evaluates postfix expressions.
//***********************************************************
  
#include <iostream>  
#include <iomanip>
#include <fstream>
#include "mystack.h"
 
using namespace std; 

void evaluateExpression(ifstream& inpF, ofstream& outF, 
                        stackType<double>& stack,
                        char& ch, bool& isExpOk);
void evaluateOpr(ofstream& out, stackType<double>& stack,
                 char& ch, bool& isExpOk);
void discardExp(ifstream& in, ofstream& out, char& ch);
void printResult(ofstream& outF, stackType<double>& stack,
                 bool isExpOk);

int main()
{
    bool expressionOk;
    char ch;
    stackType<double> stack(100);
    ifstream infile;
    ofstream outfile;
    
    //open the file
    infile.open("RpnData.txt");
    
    //if the file is currently not open, terminate the program
    if (!infile)
    {
        cout << "Cannot open the input file. "
             << "Program terminates!" << endl;
        return 1;
    }
    
    //open the file the output will be printed in
    outfile.open("RpnOutput.txt");

    outfile << fixed << showpoint;
    outfile << setprecision(2); 
    
    //read in the characters from the file
    infile >> ch;
    
    //while the file is open evalutate the expression and print the results
    while (infile)
    {
        stack.initializeStack();
        expressionOk = true;
        outfile << ch;

        evaluateExpression(infile, outfile, stack, ch, 
                           expressionOk);
        printResult(outfile, stack, expressionOk);
        infile >> ch; //begin processing the next expression
    } //end while 

    // close both the input and output files
    infile.close();
    outfile.close();

    return 0;

} //end main

//function that evaluates the expression
void evaluateExpression(ifstream& inpF, ofstream& outF, stackType<double>& stack,char& ch, bool& isExpOk)
{
    double num;
    
    //read each character until the character '=' is read
    while (ch != '=')
    {
        switch (ch)
        {
        //in the case that the character is a number
        case '#': 
            //read the number from the file and write it into a new file
            inpF >> num;
            outF << num << " ";
            //push that number into the stack if the stack is not full
            if (!stack.isFullStack())
                stack.push(num);
            //else terminate the program   
            else
            {
                cout << "Stack overflow. "
                     << "Program terminates!" << endl;
                exit(0);  //terminate the program
            }

            break;
        //the evaluateOpr function does the calculations
        default: 
            evaluateOpr(outF, stack, ch, isExpOk);
        }//end switch

        if (isExpOk) //if no error
        {
        //read the character and write it in a file
            inpF >> ch;
            outF << ch;
        //if the character is not a number write in a space else discard the expression
            if (ch != '#')
                outF << " ";
        }
        else
            discardExp(inpF, outF, ch);
    } //end while (!= '=')
} //end evaluateExpression

// function that does the operations
void evaluateOpr(ofstream& out, stackType<double>& stack,
              char& ch, bool& isExpOk)
{
    double op1, op2;
    
    //if the stack is empty set isExpOk to false 
    if (stack.isEmptyStack())
    {
        out << " (Not enough operands)";
        isExpOk = false;
    }
    //else proceed
    else
    {
        //set op2 to the top value of the stack and pop the stack
        op2 = stack.top();
        stack.pop();
        //if the stack is empty set isExpOk to false
        if (stack.isEmptyStack())
        {
            out << " (Not enough operands)";
            isExpOk = false;
        }
        /else begin the calculation
        else
        {
            //set op1 to the top value of the stack and pop the stack
            op1 = stack.top();
            stack.pop();
            
            //define the cases for each operations
            switch (ch)
            {
            case '+': 
                stack.push(op1 + op2);
                break;
            case '-': 
                stack.push(op1 - op2);
                break;
            case '*': 
                stack.push(op1 * op2);
                break;
            case '/': 
                if (op2 != 0)
                    stack.push(op1 / op2);
                else
                {
                    out << " (Division by 0)";
                    isExpOk = false;
                }
                break;
            //if the character is not a valid operator, set isExpOk to false   
            default:  
                out << " (Illegal operator)";
                isExpOk = false;
            }//end switch
        } //end else
    } //end else
} //end evaluateOpr

//function that discards the expression
void discardExp(ifstream& in, ofstream& out, char& ch)
{
    // discard all characters until '=' is reached
    while (ch != '=')
    {
        in.get(ch);
        out << ch;
    }
} //end discardExp

//print the result
void printResult(ofstream& outF, stackType<double>& stack,
                 bool isExpOk)
{
    double result;

    if (isExpOk) //if no error, print the result
    {
        if (!stack.isEmptyStack())
        {
            result = stack.top();
            stack.pop();

            if (stack.isEmptyStack())
                outF << result << endl;
            else
                outF << " (Error: Too many operands)" << endl;
        } //end if
        else
            outF << " (Error in the expression)" << endl;
    }
    else
        outF << " (Error in the expression)" << endl;

    outF << "_________________________________" 
         << endl << endl;
} //end printResult
