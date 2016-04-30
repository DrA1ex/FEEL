#ifndef UnaryOperatorBase_h__
#define UnaryOperatorBase_h__

#include "../../OperatorBase.h"
#include "../../../Typedefs.h"

class UnaryOperatorBase : public OperatorBase
{
public:
	virtual ~UnaryOperatorBase() {}

	virtual ExpressionBytes GetBytes(ValueType *operand, ValueType *result) const = 0;

	OperatorType Type() const override
	{
		return OperatorType::Unary;
	}

};

#endif // UnaryOperatorBase_h__
