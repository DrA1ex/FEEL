#ifndef Typedefs_h__
#define Typedefs_h__

#include <vector>
#include <string>
#include <unordered_map>

typedef double ValueType;
typedef unsigned char Byte;

typedef std::vector<Byte> ExpressionBytes;
typedef std::unordered_map<std::string, ValueType> Parameters;

#endif // Typedefs_h__
