#pragma once

#include "../ExpressionEvaluatorLib/ExpressionEvaluatorLib.h"
#include <msclr\marshal_cppstd.h>

using namespace System;

namespace ExpressionEvaluatorNet {

	public ref class ExpressionEvaluator
	{
		Expression *_instance;

	public:

		ExpressionEvaluator(String^ expression);
		~ExpressionEvaluator();

		double Execute();

		void SetVariableValue(String^ name, double value);

		array<String^>^ Variables();
	};
}
