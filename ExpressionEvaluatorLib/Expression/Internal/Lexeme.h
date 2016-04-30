#ifndef Lexeme_h__
#define Lexeme_h__

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

	Lexeme(LexemeType type, std::string value) : LexemeData(value), Type(type)
	{}

	Lexeme(LexemeType type) : Type(type)
	{}
};

#endif // Lexeme_h__
