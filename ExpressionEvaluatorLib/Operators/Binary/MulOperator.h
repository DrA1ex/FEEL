#ifndef MulOperator_h__
#define MulOperator_h__

#include "Base\BinaryOperatorBase.h"

class MulOperator : public BinaryOperatorBase
{
public:
	ExpressionBytes GetBytes(ValueType *operand1, ValueType *operand2, ValueType *result) const
	{
		Assembler assembler;
		assembler.Load(operand1)
			.Mul(operand2)
			.Store(result);

		return assembler.GetData();
	}

	virtual const char * OperatorName() const
	{
		return "*";
	}

	virtual OperatorPriority Priority() const
	{
		return OperatorBase::High;
	}
};

#endif // MulOperator_h__
