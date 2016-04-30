#ifndef SubOperator_h__
#define SubOperator_h__

#include "Base\BinaryOperatorBase.h"

class SubOperator : public BinaryOperatorBase
{
public:
	ExpressionBytes GetBytes(ValueType *operand1, ValueType *operand2, ValueType *result) const override
	{
		Assembler assembler;
		assembler.Load(operand1)
			.Sub(operand2)
			.Store(result);

		return assembler.GetData();
	}

	const char * OperatorName() const override
	{
		return "-";
	}

	OperatorPriority Priority() const override
	{
		return OperatorBase::Normal;
	}
};

#endif // SubOperator_h__
