#ifndef SqrtOperator_h__
#define SqrtOperator_h__

#include "Base/UnaryOperatorBase.h"
#include <math.h>

class SqrtOperator : public UnaryOperatorBase
{
public:
	ExpressionBytes GetBytes(ValueType *operand, ValueType *result) const override
	{
		Assembler assembler;
		assembler.Load(operand)
			.Sqrt()
			.Store(result);

		return assembler.GetData();
	}

	const char * OperatorName() const override
	{
		return "sqrt";
	}

	OperatorPriority Priority() const override
	{
		return OperatorBase::Highest;
	}
};

#endif // SqrtOperator_h__
