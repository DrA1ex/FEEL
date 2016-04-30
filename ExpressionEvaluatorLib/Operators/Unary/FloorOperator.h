#ifndef FloorOperator_h__
#define FloorOperator_h__

#include "Base/UnaryOperatorBase.h"
#include <math.h>

class FloorOperator : public UnaryOperatorBase
{
public:
	ExpressionBytes GetBytes(ValueType *operand, ValueType *result) const override
	{
		typedef double(*doubleFloor)(double);
		doubleFloor floorAddress = &floor;

		Assembler assembler;
		assembler.AllocateStack(0x08)
			.Load(operand)
			.StoreToStack(0)
			.Call(floorAddress)
			.Store(result)
			.FreeStack(0x08);

		return assembler.GetData();
	}

	const char * OperatorName() const override
	{
		return "floor";
	}

	OperatorPriority Priority() const override
	{
		return OperatorBase::Highest;
	}
};

#endif // FloorOperator_h__
