#ifndef SubOperator_h__
#define SubOperator_h__

#include "Base\BinaryOperatorBase.h"

class SubOperator : public BinaryOperatorBase
{
public:
	ExpressionBytes GetBytes(ValueType *operand1, ValueType *operand2, ValueType *result) const
	{
		Assembler assembler;
		assembler.Load(operand1)
			.Sub(operand2)
			.Store(result);

		return assembler.GetData();
	}

	virtual const char * OperatorName() const
	{
		return "-";
	}

	virtual OperatorPriority Priority() const
	{
		return OperatorBase::Normal;
	}
};

#endif // SubOperator_h__
