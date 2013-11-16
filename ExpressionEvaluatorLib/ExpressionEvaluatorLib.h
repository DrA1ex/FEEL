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
	explicit Expression(std::string expression);
	~Expression();

	Parameters &GetParameters();

	ValueType Execute() const;

};

#endif // Expression_h__
