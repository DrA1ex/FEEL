#ifndef Typedefs_h__
#define Typedefs_h__

#include <vector>
#include <string>
#include <unordered_map>

typedef double ValueType;
typedef unsigned char Byte;

using ExpressionBytes = std::vector<Byte>;
using Parameters = std::unordered_map<std::string, ValueType>;

#endif // Typedefs_h__
