// file: studio2.cpp
//
// author: Chris Gill cdgill@wustl.edu
//
// purpose: definitions for a simple prefix adder program, which
// takes the command line arguments as a prefix addition
// expression and computes an integer result.

// include declarations the program uses
#include "studio2.h"

#include <iostream> // For standard output stream and manipulators.
#include <string>   // For standard C++ strings.
#include <sstream>  // For standard string streams.
#include <cstring>  // For C-style string functions

// Access symbols from the standard namespace directly.
using namespace std;

enum class Result_Code {success, bad_command_line,
                        unexpected_end_of_expression,
                        bad_arg, unknown_exception};

int main (int argc, char *argv[])
{
  // A few useful constants for argument positions  
  const int minimum_arguments = 2;         
  const int starting_index = 1;   
  const int program_name_index = 0;
       
  if (argc < minimum_arguments || 
      strcmp (argv[starting_index], "--help") == 0 || 
      strcmp (argv[starting_index], "-?") == 0) {        
       
    usage (argv[program_name_index]);      
    return static_cast<int>(Result_Code::bad_command_line);   
  }    
       
  try {         
       
    // Pass the current and last index to use, and the array, to the  
    // expression parsing function, and store the result.    
       
    int current_position = starting_index; 
    int arguments = argc - 1;
    int value = parse_and_compute (current_position, arguments, argv); 
       
    // Print out the result, and return success value.       
       
    cout << "The value calculated is " << value << endl;     
    return static_cast<int>(Result_Code::success);   
  }    
  catch (Result_Code rc)  {         
       
    cout << "caught ";
    switch (rc) {
    case Result_Code::unexpected_end_of_expression:
      cout << "exception for unexpected end of expression.";
      break;
    case Result_Code::bad_arg:
      cout << "exception for badly formed command line argument.";
      break;
    default:
      cout << "unknown exception.";
      break;
    }

    cout << endl;    

    return static_cast<int>(rc);  
  }    
  catch (...)  {         
       
    cout << "caught exception" << endl;    
    return static_cast<int>(Result_Code::unknown_exception);  
  }    
}      
  
// Helper function to print out the program's usage message. 
void usage (char * program_name) {         
       
  cout << "Usage: " << program_name << " <argument> [<argument>]..." << endl   
       << "Purpose: computes program arguments as prefix addition expression"  
       << endl; 
       
}      
       
       
// Helper function to parse the input symbols and compute a value.    
int parse_and_compute (int & current_index, int last_index, char *argv[]) {    
       
  // make sure we're still in the argument range    
  if (current_index > last_index) {        
    throw Result_Code::unexpected_end_of_expression;
  }         
       
       
  // look for a single-symbol addition operator     
  if (strlen (argv[current_index]) == 1 && 
      *(argv[current_index]) == '+') {     
       
        int first_operand =       
  parse_and_compute (++current_index,      
   last_index, argv);    
       
        int second_operand =      
  parse_and_compute (current_index,        
   last_index, argv);    
       
        return first_operand + second_operand;      
  }    
       
  // look for an integer at the current position in the command line
  else {        
       
      // make sure the command line argument is a well formed unsigned integer
    for (unsigned int i = 0; i < strlen(argv[current_index]); ++i) {        
	if (!isdigit(argv[current_index][i])) {
            throw Result_Code::bad_arg;
	  }
    }         
       
    int result; 
    istringstream iss (argv[current_index++]);        
    iss >> result;         
    return result;       
       
  }  
}