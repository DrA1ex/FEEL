#ifndef Lexeme_h__
#define Lexeme_h__

#include <string>

struct Lexeme
{
	enum LexemeType
	{
		Number,
		Operation,
		Variable,

		OpenBracket,
		CloseBracket,

		None
	};

	std::string LexemeData;
	LexemeType Type;

	Lexeme(LexemeType type, std::string value) : Type(type), LexemeData(value)
	{}

	Lexeme(LexemeType type) : Type(type)
	{}
};

#endif // Lexeme_h__
