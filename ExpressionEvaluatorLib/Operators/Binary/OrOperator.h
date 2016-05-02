#pragma once

#include "Base/BinaryOperatorBase.h"

class OrOperator : public BinaryOperatorBase
{
public:
	ExpressionBytes GetBytes(ValueType *operand1, ValueType *operand2, ValueType *result) const override
	{
		Assembler falseAnswer;
		falseAnswer.LoadZero();

		Assembler checkOperand2;
		checkOperand2.Load(operand2)
			.CompareAndPop()
			.JE(uint8_t(falseAnswer.Size()));

		return Assembler()
			.LoadOne()
			.Load(operand1)
			.CompareAndPop(1)
			.JE(uint8_t(checkOperand2.Size() + falseAnswer.Size()))
			.Write(checkOperand2)
			.Write(falseAnswer)
			.Store(result)
			.GetData();
	}

	const char * OperatorName() const override
	{
		return "||";
	}

	OperatorPriority Priority() const override
	{
		return OperatorBase::Lower;
	}
};