#pragma once
#include "Base/TernaryOperatorBase.h"

class ChoiceOperator : public TernaryOperatorBase
{
public:
	ExpressionBytes GetBytes(ValueType* operand1, ValueType* operand2, ValueType* operand3, ValueType* result) const override
	{
		Assembler op3;
		op3.Load(operand3);

		Assembler op2;
		op2.Load(operand2)
			.Jmp(uint8_t(op3.Size()));

		return Assembler()
			.LoadZero()
			.Load(operand1)
			.Compare(1)
			.JE(uint8_t(op2.Size()))
			.Write(op2)
			.Write(op3)
			.Store(result)
			.GetData();
	}

	const char* OperatorName() const override 
	{
		return "choice";
	}

	OperatorPriority Priority() const override 
	{
		return OperatorBase::Highest;
	}

	
};
