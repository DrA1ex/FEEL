#ifndef FloorOperator_h__
#define FloorOperator_h__

#include "Base\UnaryOperatorBase.h"
#include <math.h>

class FloorOperator : public UnaryOperatorBase
{
public:
	ExpressionBytes GetBytes(ValueType *operand, ValueType *result) const
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

	virtual const char * OperatorName() const
	{
		return "floor";
	}

	virtual OperatorPriority Priority() const
	{
		return OperatorBase::Highest;
	}
};

#endif // FloorOperator_h__
