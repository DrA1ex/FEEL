#ifndef Assembler_h__
#define Assembler_h__

#include "..\Typedefs.h"

class Assembler
{
	ExpressionBytes _data;

	template<typename T>
	void Write(const T &data)
	{
		auto bytesCount = sizeof(T);

		auto bytes = reinterpret_cast<const Byte *>(&data);

		for(size_t i = 0; i < bytesCount; ++i)
		{
			_data.emplace_back(bytes[i]);
		}
	}

public:
	Assembler &Load(double *value);
	Assembler &Store(double *dest);
	Assembler &StoreToStack(size_t offset);

	Assembler &Pop();
	Assembler &Free(Byte registerNumber);

	Assembler &Call(void *address);

	Assembler &AllocateStack(size_t bytesCount);
	Assembler &FreeStack(size_t bytesCount);

	Assembler &Add(double* operand2);
	Assembler &Sub(double* operand2);
	Assembler &Div(double* operand2);
	Assembler &Div();
	Assembler &DivR();
	Assembler &Mul(double* operand2);

	Assembler &Cos();
	Assembler &Sin();
	Assembler &Tan();

	Assembler &Neg();
	Assembler &Abs();


	inline ExpressionBytes GetData() const
	{
		return _data;
	}
};

#endif // Assembler_h__
