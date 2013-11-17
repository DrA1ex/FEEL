#ifndef CeilOperator_h__
#define CeilOperator_h__

#include "Base\UnaryOperatorBase.h"
#include <math.h>

class CeilOperator : public UnaryOperatorBase
{
public:
	ExpressionBytes GetBytes(ValueType *operand, ValueType *result) const
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

	virtual const char * OperatorName() const
	{
		return "ceil";
	}

	virtual OperatorPriority Priority() const
	{
		return OperatorBase::Highest;
	}
};

#endif // CeilOperator_h__
