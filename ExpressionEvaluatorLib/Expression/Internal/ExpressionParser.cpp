#include "..\ExpressionImplementation.h"
#include "..\..\Operators\Unary\Base\UnaryOperatorBase.h"
#include "Lexeme.h"

#include <stack>
#include <string>
#include "..\..\Helpers.h"


enum SymbolType
{
	NumberPart,
	Character,
	Symbol,
	Bracket,
	Divider
};

SymbolType DetectSymbolType(char ch)
{
	if (isdigit(ch) || ch == '.')
	{
		return NumberPart;
	}
	else if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')
	{
		return Character;
	}
	else if (ch == '(' || ch == ')')
	{
		return Bracket;
	}
	else if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')
		return Divider;

	return Symbol;
}

void ProcessLexeme(std::vector<Lexeme>& lexemes, SymbolType type, const std::string& data)
{
	switch (type)
	{
	case NumberPart:
		{
			std::string dataCopy = data;

			if (lexemes.size() >= 1)
			{
				auto lastLexeme = lexemes.back();

				Lexeme preLastLexeme(Lexeme::None);
				if (lexemes.size() >= 2)
					preLastLexeme = *(lexemes.end() - 2);

				//if last lexeme is sign and previous lexeme is operation\bracket, 
				//so we can say, that this sign relates with number
				if (lastLexeme.Type == Lexeme::Operation && (lastLexeme.LexemeData == "-" || lastLexeme.LexemeData == "+")
					&& (lexemes.size() == 1 || preLastLexeme.Type == Lexeme::Operation || preLastLexeme.Type == Lexeme::OpenBracket))
				{
					lexemes.pop_back();
					if (lastLexeme.LexemeData == "-")
						dataCopy = lastLexeme.LexemeData + dataCopy;
				}
			}
			lexemes.emplace_back(Lexeme(Lexeme::Number, dataCopy));
		}
		break;

	case Symbol:
	case Character:
		{
			if (lexemes.size() >= 1)
			{
				auto lastLexeme = lexemes.back();

				Lexeme preLastLexeme(Lexeme::None);
				if (lexemes.size() >= 2)
					preLastLexeme = *(lexemes.end() - 2);

				//if last lexeme is sign and previous lexeme is operation\bracket, 
				//so we can say, that this sign relates with variable\operation
				if (lastLexeme.Type == Lexeme::Operation && (lastLexeme.LexemeData == "-" || lastLexeme.LexemeData == "+")
					&& (lexemes.size() == 1 || preLastLexeme.Type == Lexeme::Operation || preLastLexeme.Type == Lexeme::OpenBracket))
				{
					if (lastLexeme.LexemeData == "-")
						lexemes.back().LexemeData = "neg";
					else
						lexemes.pop_back();
				}
			}

			if (ExpressionImplementation::_operators.find(data) != ExpressionImplementation::_operators.end())
			{
				lexemes.emplace_back(Lexeme(Lexeme::Operation, data));
			}
			else if (type == Character)
			{
				lexemes.emplace_back(Lexeme(Lexeme::Variable, data));
			}
			else
			{
				throw std::runtime_error(MakeString() << "Unknown lexeme: " << data << " with type " << type);
			}
		}
		break;

	case Bracket:
		{
			if (data == "(")
			{
				if (lexemes.size() >= 1)
				{
					auto lastLexeme = lexemes.back();

					Lexeme preLastLexeme(Lexeme::None);
					if (lexemes.size() >= 2)
						preLastLexeme = *(lexemes.end() - 2);

					//if last lexeme is sign and previous lexeme is operation\bracket, 
					//so we can say, that this sign relates with open bracket
					if (lastLexeme.Type == Lexeme::Operation && (lastLexeme.LexemeData == "-" || lastLexeme.LexemeData == "+")
						&& (lexemes.size() == 1 || preLastLexeme.Type == Lexeme::Operation || preLastLexeme.Type == Lexeme::OpenBracket))
					{
						if (lastLexeme.LexemeData == "-")
							lexemes.back().LexemeData = "neg";
						else
							lexemes.pop_back();
					}
				}

				lexemes.emplace_back(Lexeme(Lexeme::OpenBracket));
			}
			else
			{
				lexemes.emplace_back(Lexeme(Lexeme::CloseBracket));
			}
		}
		break;

	case Divider:
	default:
		//Do nothing
		break;
	}
}

std::vector<Lexeme> ExpressionImplementation::ParseExpression() const
{
	std::vector<Lexeme> lexemes;
	std::string accumulator;

	SymbolType lastSymbType = Divider, currentSymbolType;

	for (auto it = _expression.begin(); it != _expression.end(); ++it)
	{
		const char& symb = *it;

		currentSymbolType = DetectSymbolType(symb);

		if (currentSymbolType != lastSymbType && lastSymbType != Divider || lastSymbType == Symbol || lastSymbType == Bracket)
		{
			ProcessLexeme(lexemes, lastSymbType, accumulator);
			accumulator.clear();
		}

		if (currentSymbolType != Divider)
			accumulator.push_back(symb);

		lastSymbType = currentSymbolType;
	}

	if (!accumulator.empty())
		ProcessLexeme(lexemes, lastSymbType, accumulator);

	return std::move(lexemes);
}

Token ExpressionImplementation::ConstructFromLexeme(const Lexeme& lexeme) const
{
	switch (lexeme.Type)
	{
	case Lexeme::Operation:
		{
			auto operation = _operators.find(lexeme.LexemeData);
			if (operation != _operators.end())
				return Token::Create(*operation->second.get());

			throw std::runtime_error(MakeString() << "Unknown operation: " << lexeme.LexemeData);
		}

	case Lexeme::Variable:
		{
			return Token::Create(_parameters.find(lexeme.LexemeData)->first);
		}

	case Lexeme::Number:
		{
			return Token::Create(std::stod(lexeme.LexemeData));
		}

	default:
		throw std::logic_error(MakeString() << "Unsupported lexeme type: " << lexeme.Type << " with data: " << lexeme.LexemeData);
	}
}

const OperatorBase* ExpressionImplementation::GetOperationFromLexeme(const Lexeme& lexeme)
{
	if (_operators.find(lexeme.LexemeData) != _operators.end())
	{
		return _operators[lexeme.LexemeData].get();
	}

	throw std::runtime_error(MakeString() << "Unknown operation: " << lexeme.LexemeData);
}

std::vector<Token> ExpressionImplementation::ConvertToPrefixNotation(const std::vector<Lexeme>& lexemes) const
{
	std::vector<Token> result;
	std::stack<Lexeme> stack;

	for (auto it = lexemes.begin(); it != lexemes.end(); ++it)
	{
		const Lexeme& currentLexeme = *it;

		switch (currentLexeme.Type)
		{
		case Lexeme::Number:
			result.emplace_back(ConstructFromLexeme(currentLexeme));
			break;

		case Lexeme::Variable:
			if (_parameters.find(currentLexeme.LexemeData) == _parameters.end())
				_parameters[currentLexeme.LexemeData] = NAN;
			result.emplace_back(ConstructFromLexeme(currentLexeme));
			break;

		case Lexeme::OpenBracket:
			stack.emplace(currentLexeme);
			break;

		case Lexeme::CloseBracket:
			{
				if (stack.empty())
					throw std::runtime_error("Syntactic error. Bracket mismatch");

				Lexeme tempLexeme(Lexeme::None);

				while ((tempLexeme = pop(stack)).Type != Lexeme::OpenBracket)
					result.emplace_back(ConstructFromLexeme(tempLexeme));
			}
			break;

		case Lexeme::Operation:
			{
				auto operation = GetOperationFromLexeme(currentLexeme);
				auto currentOperationPriority = operation->Priority();

				if (currentOperationPriority == OperatorBase::Highest)
					stack.emplace(currentLexeme);
				else
				{
					if (!operation->IsLeftAssociative())
					{
						while (!stack.empty() && (stack.top().Type == Lexeme::Operation && currentOperationPriority
							<= GetOperationFromLexeme(stack.top())->Priority()))
						{
							result.push_back(ConstructFromLexeme(pop(stack)));
						}
					}
					else
					{
						while (!stack.empty() && (stack.top().Type == Lexeme::Operation && currentOperationPriority
							< GetOperationFromLexeme(stack.top())->Priority()))
						{
							result.push_back(ConstructFromLexeme(pop(stack)));
						}
					}

					stack.emplace(currentLexeme);
				}
			}
			break;

		default:
			throw new std::logic_error(MakeString() << "Unknown lexeme type: " << currentLexeme.Type << " with data: " << currentLexeme.LexemeData);
		}
	}

	while (!stack.empty())
	{
		auto currentLexeme = pop(stack);

		if (currentLexeme.Type != Lexeme::Operation)
			throw std::runtime_error("Syntactic error. Bracket mismatch");

		result.push_back(ConstructFromLexeme(currentLexeme));
	}

	return result;
}
