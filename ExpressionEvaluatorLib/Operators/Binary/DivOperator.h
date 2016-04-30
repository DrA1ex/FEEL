#ifndef DivOperator_h__
#define DivOperator_h__

#include "Base/BinaryOperatorBase.h"


class DivOperator : public BinaryOperatorBase
{
public:
	ExpressionBytes GetBytes(ValueType *operand1, ValueType *operand2, ValueType *result) const override
	{
		Assembler assembler;
		assembler.Load(operand1)
			.Div(operand2)
			.Store(result);

		return assembler.GetData();
	}

	const char * OperatorName() const override
	{
		return "/";
	}

	OperatorPriority Priority() const override
	{
		return OperatorBase::High;
	}
};

#endif // DivOperator_h__
