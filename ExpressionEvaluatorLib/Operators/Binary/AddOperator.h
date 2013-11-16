#ifndef AddOperator_h__
#define AddOperator_h__

#include "Base\BinaryOperatorBase.h"


class AddOperator : public BinaryOperatorBase
{
public:
	ExpressionBytes GetBytes(ValueType *operand1, ValueType *operand2, ValueType *result) const
	{
		Assembler assembler;
		assembler.Load(operand1)
			.Add(operand2)
			.Store(result);

		return assembler.GetData();
	}

	virtual const char * OperatorName() const
	{
		return "+";
	}

	virtual OperatorPriority Priority() const
	{
		return OperatorBase::Normal;
	}

};

#endif // AddOperator_h__
