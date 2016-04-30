#ifndef ModOperator_h__
#define ModOperator_h__

#include "Base/BinaryOperatorBase.h"

class ModOperator : public BinaryOperatorBase
{
public:
	ExpressionBytes GetBytes(ValueType *operand1, ValueType *operand2, ValueType *result) const override
	{
		Assembler assembler;
		assembler.Load(operand2)
			.Load(operand1)
			.Mod().Store(result)
			.Free(0);

		return assembler.GetData();
	}

	const char * OperatorName() const override
	{
		return "%";
	}

	OperatorPriority Priority() const override
	{
		return OperatorBase::High;
	}

};

#endif // ModOperator_h__
