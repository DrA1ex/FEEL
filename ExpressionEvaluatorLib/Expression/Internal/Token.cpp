#include "Token.h"




Token Token::Create(const OperatorBase &operation)
{
	Token token;
	token._type = TokenType::Operation;
	token._operation = &operation;

	return std::move(token);
}

Token Token::Create(ValueType constant)
{
	Token token;
	token._type = TokenType::Constant;
	token._constant = constant;

	return std::move(token);
}

Token Token::Create(const std::string &variable)
{
	Token token;
	token._type = TokenType::Variable;
	token._variableName = &variable;

	return std::move(token);
}

ValueType Token::GetConstant() const
{
	if(_type != TokenType::Constant)
		throw new std::runtime_error("Token is not a constant");

	return _constant;
}

const std::string & Token::GetVariableName() const
{
	if(_type != TokenType::Variable)
		throw new std::runtime_error("Token is not a variable");

	return *_variableName;
}

const OperatorBase & Token::GetOperation() const
{
	if(_type != TokenType::Operation)
		throw new std::runtime_error("Token is not a operation");

	return *_operation;
}

Token::TokenType Token::GetType() const
{
	return _type;
}
