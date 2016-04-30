#ifndef ExpressionImplementation_h__
#define ExpressionImplementation_h__

#include <vector>
#include <mutex>
#include <atomic>

#include "..\Typedefs.h"
#include "..\Operators\OperatorBase.h"
#include "Internal\Token.h"
#include "Internal\Lexeme.h"

class ExpressionImplementation
{
public:

	ExpressionImplementation(const std::string &expression);

	mutable ExpressionBytes _compiledExpressionBytes;
	mutable std::vector<ValueType> _memory;
	mutable Parameters _parameters;
	mutable std::vector<Token> _tokens;
	std::string _expression;

	static OperatorsDictonary _operators;

	static std::atomic<bool> _initialized;
	static std::once_flag _initFlag;
	static void Init();
	static void AddNewOperation(OperatorBase *operation);

	Token ConstructFromLexeme(const Lexeme&  Lexeme) const;
	static const OperatorBase* GetOperationFromLexeme(const Lexeme& lexeme);
	std::vector<Token> ConvertToPrefixNotation(const std::vector<Lexeme> &lexemes) const;

	std::vector<Lexeme> ParseExpression() const;
	void CompileExpression() const;


	ValueType Execute() const;
};

#endif // ExpressionImplementation_h__

