#ifndef NegOperator_h__
#define NegOperator_h__

#include "Base\UnaryOperatorBase.h"


class NegOperator : public UnaryOperatorBase
{
public:
	ExpressionBytes GetBytes(ValueType *operand, ValueType *result) const override
	{
		Assembler assembler;
		assembler.Load(operand)
			.Neg()
			.Store(result);

		return assembler.GetData();
	}

	const char * OperatorName() const override
	{
		return "neg";
	}

	OperatorPriority Priority() const override
	{
		return OperatorBase::Highest;
	}
};

#endif // NegOperator_h__
