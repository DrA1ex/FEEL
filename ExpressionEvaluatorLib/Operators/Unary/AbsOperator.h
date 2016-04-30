#ifndef AbsOperator_h__
#define AbsOperator_h__

#include "Base\UnaryOperatorBase.h"

class AbsOperator : public UnaryOperatorBase
{
public:
	ExpressionBytes GetBytes(ValueType *operand, ValueType *result) const override
	{
		Assembler assembler;
		assembler.Load(operand)
			.Abs()
			.Store(result);

		return assembler.GetData();
	}

	const char * OperatorName() const override
	{
		return "abs";
	}

	OperatorPriority Priority() const override
	{
		return OperatorBase::Highest;
	}
};

#endif // AbsOperator_h__
