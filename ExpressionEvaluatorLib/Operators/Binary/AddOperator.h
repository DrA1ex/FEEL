#ifndef AddOperator_h__
#define AddOperator_h__

#include "Base\BinaryOperatorBase.h"


class AddOperator : public BinaryOperatorBase
{
public:
	ExpressionBytes GetBytes(ValueType *operand1, ValueType *operand2, ValueType *result) const override
	{
		Assembler assembler;
		assembler.Load(operand1)
			.Add(operand2)
			.Store(result);

		return assembler.GetData();
	}

	const char * OperatorName() const override
	{
		return "+";
	}

	OperatorPriority Priority() const override
	{
		return OperatorBase::Normal;
	}

};

#endif // AddOperator_h__
