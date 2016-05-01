#ifndef OperatorBase_h__
#define OperatorBase_h__
#include "../Common/Assembler.h"

#include <memory>
#include <unordered_map>


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

using OperatorsDictonary = std::unordered_map<std::string, std::unique_ptr<OperatorBase>>;

#endif // OperatorBase_h__
