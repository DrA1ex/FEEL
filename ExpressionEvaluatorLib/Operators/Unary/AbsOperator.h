#ifndef AbsOperator_h__
#define AbsOperator_h__

#include "Base\UnaryOperatorBase.h"

class AbsOperator : public UnaryOperatorBase
{
public:
	ExpressionBytes GetBytes(ValueType *operand, ValueType *result) const
	{
		Assembler assembler;
		assembler.Load(operand)
			.Abs()
			.Store(result);

		return assembler.GetData();
	}

	virtual const char * OperatorName() const
	{
		return "abs";
	}

	virtual OperatorPriority Priority() const
	{
		return OperatorBase::Highest;
	}
};

#endif // AbsOperator_h__
