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
#include "..\..\Operators\Unary\AbsOperator.h"
#include "..\..\Operators\Binary\PowOperator.h"
#include "..\..\Operators\Binary\ModOperator.h"
#include "..\..\Operators\Unary\CeilOperator.h"
#include "..\..\Operators\Unary\FloorOperator.h"
#include "..\..\Operators\Unary\SqrtOperator.h"

OperatorsDictonary ExpressionImplementation::_operators;
std::atomic<bool> ExpressionImplementation::_initialized = false;
std::once_flag ExpressionImplementation::_initFlag;

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
	AddNewOperation(new ModOperator());

	AddNewOperation(new PowOperator());

	//Unary operations
	AddNewOperation(new NegOperator());
	AddNewOperation(new AbsOperator());

	AddNewOperation(new CosOperator());
	AddNewOperation(new SinOperator());
	AddNewOperation(new TanOperator());
	AddNewOperation(new CtanOperator());

	AddNewOperation(new CeilOperator());
	AddNewOperation(new FloorOperator());

	AddNewOperation(new SqrtOperator());
}