#ifndef BinaryOperatorBase_h__
#define BinaryOperatorBase_h__

#include "../../../Typedefs.h"
#include "../../OperatorBase.h"

class BinaryOperatorBase : public OperatorBase
{
public:

	virtual ~BinaryOperatorBase() {}

	virtual ExpressionBytes GetBytes(ValueType *operand1, ValueType *operand2, ValueType *result) const = 0;

	OperatorType Type() const override
	{
		return OperatorType::Binary;
	}

};

#endif // BinaryOperatorBase_h__
