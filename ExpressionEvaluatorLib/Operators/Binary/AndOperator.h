#pragma once

#include "Base/BinaryOperatorBase.h"

class AndOperator : public BinaryOperatorBase
{
public:
	ExpressionBytes GetBytes(ValueType *operand1, ValueType *operand2, ValueType *result) const override
	{
		Assembler trueAnswer;
		trueAnswer.LoadOne();

		Assembler checkOperand2;
		checkOperand2.Load(operand2)
			.CompareAndPop()
			.JE(uint8_t(trueAnswer.Size()));

		return Assembler()
			.LoadZero()
			.Load(operand1)
			.CompareAndPop(1)
			.JE(uint8_t(checkOperand2.Size() + trueAnswer.Size()))
			.Write(checkOperand2)
			.Write(trueAnswer)
			.Store(result)
			.GetData();
	}

	const char * OperatorName() const override
	{
		return "&&";
	}

	OperatorPriority Priority() const override
	{
		return OperatorBase::Lower;
	}
};