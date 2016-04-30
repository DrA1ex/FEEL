#ifndef PowOperator_h__
#define PowOperator_h__

#include "Base/BinaryOperatorBase.h"
#include <math.h>

class PowOperator : public BinaryOperatorBase
{
public:
	ExpressionBytes GetBytes(ValueType *operand1, ValueType *operand2, ValueType *result) const override
	{
		typedef double(*doublePow)(double, double);
		doublePow powAddress = &pow;

		Assembler assembler;
		assembler.AllocateStack(0x10)
			.Load(operand1)
			.StoreToStack(0)
			.Load(operand2)
			.StoreToStack(0x08)
			.Call(powAddress)
			.Store(result)
			.FreeStack(0x10);

		return assembler.GetData();
	}

	const char * OperatorName() const override
	{
		return "^";
	}

	OperatorPriority Priority() const override
	{
		return OperatorBase::Higher;
	}

};

#endif // PowOperator_h__
