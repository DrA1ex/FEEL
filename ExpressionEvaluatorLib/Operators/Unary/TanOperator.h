#ifndef TanOperator_h__
#define TanOperator_h__

#include "Base\UnaryOperatorBase.h"


class TanOperator : public UnaryOperatorBase
{
public:
	ExpressionBytes GetBytes(ValueType *operand, ValueType *result) const override
	{
		Assembler assembler;
		assembler.Load(operand)
			.Tan().Pop()
			.Store(result);

		return assembler.GetData();
	}

	const char * OperatorName() const override
	{
		return "tan";
	}

	OperatorPriority Priority() const override
	{
		return OperatorBase::Highest;
	}
};

#endif // TanOperator_h__