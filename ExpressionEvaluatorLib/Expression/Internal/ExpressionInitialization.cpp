#include "..\ExpressionImplementation.h"
#include "..\..\Operators\Binary\SubOperator.h"
#include "..\..\Operators\Binary\AddOperator.h"
#include "..\..\Operators\Binary\MulOperator.h"
#include "..\..\Operators\Binary\DivOperator.h"
#include "..\..\Operators\Unary\CosOperator.h"
#include "..\..\Operators\Unary\TanOperator.h"
#include "..\..\Operators\Unary\ÑtanOperator.h"
#include "..\..\Operators\Unary\SinOperator.h"
#include "..\..\Operators\Unary\NegOperator.h"

OperatorsDictonary ExpressionImplementation::_operators;
bool ExpressionImplementation::_initialized = false;

void ExpressionImplementation::AddNewOperation(OperatorBase *operation)
{
	if(_operators.find(operation->OperatorName()) != _operators.end())
		throw std::logic_error("Operator already added in operator collection");

	_operators[operation->OperatorName()] = std::shared_ptr<OperatorBase>(operation);
}

void ExpressionImplementation::Init()
{
	//Binary operations
	AddNewOperation(new AddOperator());
	AddNewOperation(new SubOperator());
	AddNewOperation(new MulOperator());
	AddNewOperation(new DivOperator());

	//Unary operations
	AddNewOperation(new NegOperator());

	AddNewOperation(new CosOperator());
	AddNewOperation(new SinOperator());
	AddNewOperation(new TanOperator());
	AddNewOperation(new CtanOperator());
}