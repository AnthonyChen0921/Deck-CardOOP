// File: Compose_T.cpp
// Purpose: Unary function composition template declaration for 
//          Functional Programming Studio

#include "Compose_T.h"

// From https://stackoverflow.com/questions/19071268/function-composition-in-c-c11
template <class F, class G> auto compose (F f, G g) {
  return [f, g](auto x) { return f(g(x)); };
}