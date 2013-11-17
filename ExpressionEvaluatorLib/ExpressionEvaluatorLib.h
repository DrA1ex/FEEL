#ifndef Expression_h__
#define Expression_h__

#ifdef EXPRESSIONEVALUATORLIB_EXPORTS
#define EXPRESSIONEVALUATORLIB_API __declspec(dllexport)
#else
#define EXPRESSIONEVALUATORLIB_API __declspec(dllimport)
#endif

#include "Typedefs.h"

class ExpressionImplementation;

class EXPRESSIONEVALUATORLIB_API Expression
{
	ExpressionImplementation * const _impl;

public:

	//Compiles expression from the "expression"
	explicit Expression(std::string expression);
	~Expression();

	//Returns reference to Parameters dictionary
	Parameters &GetParameters();

	//Executes expression and return result
	ValueType Execute() const;

};

#endif // Expression_h__
