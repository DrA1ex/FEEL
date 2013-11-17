#ifndef SqrtOperator_h__
#define SqrtOperator_h__

#include "Base\UnaryOperatorBase.h"
#include <math.h>

class SqrtOperator : public UnaryOperatorBase
{
public:
	ExpressionBytes GetBytes(ValueType *operand, ValueType *result) const
	{
		Assembler assembler;
		assembler.Load(operand)
			.Sqrt()
			.Store(result);

		return assembler.GetData();
	}

	virtual const char * OperatorName() const
	{
		return "sqrt";
	}

	virtual OperatorPriority Priority() const
	{
		return OperatorBase::Highest;
	}
};

#endif // SqrtOperator_h__
