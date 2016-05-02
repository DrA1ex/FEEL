#pragma once

#include "Base/BinaryOperatorBase.h"

class NotEqualOperator : public BinaryOperatorBase
{
public:
	ExpressionBytes GetBytes(ValueType *operand1, ValueType *operand2, ValueType *result) const override
	{
		Assembler trueAnswer;
		trueAnswer.LoadOne();

		Assembler falseAnswer;
		falseAnswer.LoadZero()
			.Jmp(uint8_t(trueAnswer.Size()));

		return Assembler()
			.Load(operand2)
			.Load(operand1)
			.Compare(1)
			.JNE(uint8_t(falseAnswer.Size()))
			.Write(falseAnswer)
			.Write(trueAnswer)
			.Store(result)
			.GetData();
	}

	const char * OperatorName() const override
	{
		return "!=";
	}

	OperatorPriority Priority() const override
	{
		return OperatorBase::Low;
	}
};