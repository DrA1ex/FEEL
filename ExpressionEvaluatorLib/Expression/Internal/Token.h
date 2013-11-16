#ifndef Token_h__
#define Token_h__

#include "..\..\Typedefs.h"
#include "..\..\Operators\OperatorBase.h"

class Token
{
public:
	enum TokenType { Variable, Constant, Operation };

private:
	TokenType _type;

	union
	{
		const std::string *_variableName;
		const OperatorBase *_operation;
		ValueType _constant;
	};

	Token() {}

public:
	static Token Create(const OperatorBase &operation);
	static Token Create(ValueType constant);
	static Token Create(const std::string &variable);

	ValueType GetConstant() const;
	const std::string &GetVariableName() const;
	const OperatorBase &GetOperation() const;

	TokenType GetType() const;
};

#endif // Token_h__
