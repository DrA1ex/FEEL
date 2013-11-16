#ifndef SinOperator_h__
#define SinOperator_h__

#include "Base\UnaryOperatorBase.h"


class SinOperator :	public UnaryOperatorBase
{
public:
	ExpressionBytes GetBytes(ValueType *operand, ValueType *result) const
	{
		Assembler assembler;
		assembler.Load(operand)
			.Sin()
			.Store(result);

		return assembler.GetData();
	}

	virtual const char * OperatorName() const
	{
		return "sin";
	}

	virtual OperatorPriority Priority() const
	{
		return OperatorBase::Highest;
	}
};

#endif // SinOperator_h__
