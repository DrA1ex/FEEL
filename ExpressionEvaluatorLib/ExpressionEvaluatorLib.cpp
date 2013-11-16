#include "ExpressionEvaluatorLib.h"
#include "Typedefs.h"
#include "Expression\ExpressionImplementation.h"

Expression::Expression(std::string expression) : _impl(new ExpressionImplementation(expression))
{
}

Expression::~Expression()
{
	delete _impl;
}

Parameters & Expression::GetParameters()
{
	return _impl->_parameters;
}

ValueType Expression::Execute() const
{
	return _impl->Execute();
}
