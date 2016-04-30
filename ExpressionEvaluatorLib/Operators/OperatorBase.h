#ifndef OperatorBase_h__
#define OperatorBase_h__
#include "../Common/Assembler.h"

#include <memory>
#include <map>


class OperatorBase
{
public:


	enum OperatorType
	{
		Unary, Binary
	};

	enum OperatorPriority
	{
		Low, Normal, High, Higher, Highest
	};

	virtual ~OperatorBase() {}

	virtual const char *OperatorName() const = 0;
	virtual OperatorType Type() const = 0;
	virtual OperatorPriority Priority() const = 0;
	virtual bool IsLeftAssociative() const { return Priority() == Highest; }
};

typedef std::map<std::string, std::shared_ptr<OperatorBase>> OperatorsDictonary;

#endif // OperatorBase_h__
