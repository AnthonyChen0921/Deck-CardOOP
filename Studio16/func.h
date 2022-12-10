#ifndef FUNC_H
#define FUNC_H

#include <string>
#include <ostream>
#include "Foo.h"


void printit (std::ostream& os, const std::string& s);
void printit(std::ostream& os, const char * const s);
void printit(std::ostream& os, const Foo& s);


#endif // FUNC_H