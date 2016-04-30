#ifndef SinOperator_h__
#define SinOperator_h__

#include "Base/UnaryOperatorBase.h"


class SinOperator :	public UnaryOperatorBase
{
public:
	ExpressionBytes GetBytes(ValueType *operand, ValueType *result) const override
	{
		Assembler assembler;
		assembler.Load(operand)
			.Sin()
			.Store(result);

		return assembler.GetData();
	}

	const char * OperatorName() const override
	{
		return "sin";
	}

	OperatorPriority Priority() const override
	{
		return OperatorBase::Highest;
	}
};

#endif // SinOperator_h__
