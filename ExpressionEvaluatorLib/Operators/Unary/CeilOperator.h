#ifndef CeilOperator_h__
#define CeilOperator_h__

#include "Base/UnaryOperatorBase.h"
#include <math.h>

class CeilOperator : public UnaryOperatorBase
{
public:
	ExpressionBytes GetBytes(ValueType *operand, ValueType *result) const override
	{
		typedef double(*doubleCeil)(double);
		doubleCeil ceilAddress = &ceil;

		Assembler assembler;
		assembler.AllocateStack(0x08)
			.Load(operand)
			.StoreToStack(0)
			.Call(ceilAddress)
			.Store(result)
			.FreeStack(0x08);

		return assembler.GetData();
	}

	const char * OperatorName() const override
	{
		return "ceil";
	}

	OperatorPriority Priority() const override
	{
		return OperatorBase::Highest;
	}
};

#endif // CeilOperator_h__
