#include "../ExpressionImplementation.h"
#include "../../Operators/AllOperators.h"

OperatorsDictonary ExpressionImplementation::_operators;
std::atomic<bool> ExpressionImplementation::_initialized = false;
std::once_flag ExpressionImplementation::_initFlag;

void ExpressionImplementation::AddNewOperation(OperatorBase *operation)
{
	if(_operators.find(operation->OperatorName()) != _operators.end())
		throw std::logic_error("Operator already added in operator collection");

	_operators[operation->OperatorName()] = std::unique_ptr<OperatorBase>(operation);
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

	AddNewOperation(new GreaterOrEqualOperator());
	AddNewOperation(new LessOrEqualOperator());

	AddNewOperation(new EqualOperator());
	AddNewOperation(new NotEqualOperator());
	AddNewOperation(new GreaterOperator());
	AddNewOperation(new LessOperator());

	AddNewOperation(new AndOperator());
	AddNewOperation(new OrOperator());

	//Ternary operations
	AddNewOperation(new ChoiceOperator());
}