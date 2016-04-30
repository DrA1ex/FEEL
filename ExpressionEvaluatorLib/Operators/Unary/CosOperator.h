#ifndef CosOperator_h__
#define CosOperator_h__

#include "Base\UnaryOperatorBase.h"


class CosOperator : public UnaryOperatorBase
{
public:
	ExpressionBytes GetBytes(ValueType *operand, ValueType *result) const override
	{
		Assembler assembler;
		assembler.Load(operand)
			.Cos()
			.Store(result);

		return assembler.GetData();
	}

	const char * OperatorName() const override
	{
		return "cos";
	}

	OperatorPriority Priority() const override
	{
		return OperatorBase::Highest;
	}
};

#endif // CosOperator_h__
