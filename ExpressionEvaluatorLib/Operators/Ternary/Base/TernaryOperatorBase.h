#ifndef TernaryOperatorBase_h__
#define TernaryOperatorBase_h__

#include "../../../Typedefs.h"
#include "../../OperatorBase.h"

class TernaryOperatorBase : public OperatorBase
{
public:

	virtual ~TernaryOperatorBase() {}

	virtual ExpressionBytes GetBytes(ValueType *operand1, ValueType *operand2, ValueType *operand3, ValueType *result) const = 0;

	OperatorType Type() const override
	{
		return OperatorType::Ternary;
	}

};

#endif // TernaryOperatorBase_h__
