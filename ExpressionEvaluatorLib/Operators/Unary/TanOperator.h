#ifndef TanOperator_h__
#define TanOperator_h__

#include "Base\UnaryOperatorBase.h"


class TanOperator : public UnaryOperatorBase
{
public:
	ExpressionBytes GetBytes(ValueType *operand, ValueType *result) const
	{
		Assembler assembler;
		assembler.Load(operand)
			.Tan().Pop()
			.Store(result);

		return assembler.GetData();
	}

	virtual const char * OperatorName() const
	{
		return "tan";
	}

	virtual OperatorPriority Priority() const
	{
		return OperatorBase::Highest;
	}
};

#endif // TanOperator_h__