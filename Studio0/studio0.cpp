/* A C++ Program in the spirit of the classic example from page 6
      of Kernighan and Ritchie's The C Programming Language, 2nd. Ed. */

#include <iostream> // for cout ostream and endl manipulator
#include <fstream>  // for ifstream and ofstream

using namespace std; // optional, could say std::cout and std::endl below instead

const int SUCCESS = 0; // by convention, where non-zero results are error codes
const int WRONG_ARGUMENTS = 1; //  Fail code: wrong number of arguments
const int FILE_NOT_FOUND = 2; //  Fail code: file not found

const int expectedArgs = 2; // Expected Input Argument

int main(int argc, char* argv[]) { // argc and argv not used, but their types are specified

    // Check for correct number of arguments
	const char* program = argv[0];
	if(argc < expectedArgs){
		cout << "usage: " << program << " <arg1> [<arg2> ...]"<< endl;
		return WRONG_ARGUMENTS;
	}

    // loop through the arguments
    for(int i = 1; i < argc; i++){
        // Use output file stream to open command line argument for output
        ofstream outputFile(argv[i]);
        if(!outputFile.is_open()){
            cout << "Error: Cannot open the file" << argv[1] << endl;
            return FILE_NOT_FOUND;
        }
        // Write to output file
        outputFile << "Hello World" << endl;
        outputFile.close();
    }


	cout << "hello, world!" << endl; // procedural: has an effect

	return SUCCESS; // functional: returns a success/failure code
}
