#include "func.h"
#include "template.h"


void printit(std::ostream& os, const std::string& s) {
    os << "\"" << s << "\"";
    add_size(s);
}


void printit(std::ostream& os, const char * const s) {
    os << "[" << s << " "<< reinterpret_cast<const void *> (s) << "] ";
    add_size(s);
}

void printit(std::ostream& os, const Foo& s) {
    os << "{" << s << "} ";
    add_size(s);
}
