// file: studio2.h
//
// author: Chris Gill cdgill@wustl.edu
//
// purpose: Declarations for a simple prefix adder program, which
//          takes the command line arguments as a prefix addition
//          expression and computes an integer result.

#pragma once

// Function prototypes
void usage (char * program_name);
int parse_and_compute (int & current_index, int last_index, char *argv[]);
