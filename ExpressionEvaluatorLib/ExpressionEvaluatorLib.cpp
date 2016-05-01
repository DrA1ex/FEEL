#include "ExpressionEvaluatorLib.h"
#include "Typedefs.h"
#include "Expression/ExpressionImplementation.h"

Expression::Expression(const std::string& expression) : _impl(new ExpressionImplementation(expression))
{
}

Expression::~Expression()
{
	delete _impl;
}

const Parameters & Expression::GetParameters()
{
	return _impl->_parameters;
}


void Expression::SetParameter(const std::string& name, ValueType value)
{
	auto param = _impl->_parameters.find(name);
	if (param != _impl->_parameters.end()) 
	{
		*param->second = value;
	} 
	else
	{
		throw std::invalid_argument("Unknown parameter");
	}
}

ValueType Expression::Execute() const
{
	return _impl->Execute();
}
