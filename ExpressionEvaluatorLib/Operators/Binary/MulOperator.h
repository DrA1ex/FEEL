#ifndef MulOperator_h__
#define MulOperator_h__

#include "Base\BinaryOperatorBase.h"

class MulOperator : public BinaryOperatorBase
{
public:
	ExpressionBytes GetBytes(ValueType *operand1, ValueType *operand2, ValueType *result) const override
	{
		Assembler assembler;
		assembler.Load(operand1)
			.Mul(operand2)
			.Store(result);

		return assembler.GetData();
	}

	const char * OperatorName() const override
	{
		return "*";
	}

	OperatorPriority Priority() const override
	{
		return OperatorBase::High;
	}
};

#endif // MulOperator_h__
