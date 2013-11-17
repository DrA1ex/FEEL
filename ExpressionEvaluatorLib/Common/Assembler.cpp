#include "Assembler.h"


Assembler & Assembler::Load(double *value)
{
	Write<Byte>(0xDD);
	Write<Byte>(0x05);
	Write<double*>(value);

	return *this;
}

Assembler & Assembler::Store(double *dest)
{
	Write<Byte>(0xDD);
	Write<Byte>(0x1D);
	Write<double*>(dest);

	return *this;
}

Assembler & Assembler::StoreToStack(size_t offset)
{
	if(offset == 0)
	{
		Write<Byte>(0xDD);
		Write<Byte>(0x1C);
		Write<Byte>(0xE4);
	}
	else if(offset < 0x80)
	{
		Write<Byte>(0xDD);
		Write<Byte>(0x5C);
		Write<Byte>(0xE4);
		Write<Byte>(offset);
	}
	else
	{
		Write<Byte>(0xDD);
		Write<Byte>(0x9C);
		Write<Byte>(0xE4);
		Write<size_t>(offset);
	}

	return *this;
}

Assembler & Assembler::Call(void *address)
{
	Write<Byte>(0xB8);
	Write<void*>(address);

	Write<Byte>(0xFF);
	Write<Byte>(0xD0);

	return *this;
}

Assembler & Assembler::AllocateStack(size_t bytesCount)
{
	if(bytesCount == 0)
		return *this;

	if(bytesCount < 0x80)
	{
		Write<Byte>(0x83);
		Write<Byte>(0xEC);
		Write<Byte>(bytesCount);
	}
	else
	{
		Write<Byte>(0x81);
		Write<Byte>(0xEC);
		Write<Byte>(bytesCount);
	}

	return *this;
}

Assembler & Assembler::FreeStack(size_t bytesCount)
{
	if(bytesCount == 0)
		return *this;

	if(bytesCount < 0x80)
	{
		Write<Byte>(0x83);
		Write<Byte>(0xC4);
		Write<Byte>(bytesCount);
	}
	else
	{
		Write<Byte>(0x81);
		Write<Byte>(0xC4);
		Write<Byte>(bytesCount);
	}

	return *this;
}

Assembler & Assembler::Add(double* operand2)
{
	Write<Byte>(0xDC);
	Write<Byte>(0x05);
	Write<double*>(operand2);

	return *this;
}

Assembler & Assembler::Sub(double* operand2)
{
	Write<Byte>(0xDC);
	Write<Byte>(0x25);
	Write<double*>(operand2);

	return *this;
}

Assembler & Assembler::Div(double* operand2)
{
	Write<Byte>(0xDC);
	Write<Byte>(0x35);
	Write<double*>(operand2);

	return *this;
}

Assembler & Assembler::Div()
{
	Write<Byte>(0xD8);
	Write<Byte>(0xF1);

	return *this;
}


Assembler & Assembler::DivR()
{
	Write<Byte>(0xD8);
	Write<Byte>(0xF9);

	return *this;
}


Assembler & Assembler::Mul(double* operand2)
{
	Write<Byte>(0xDC);
	Write<Byte>(0x0D);
	Write<double*>(operand2);

	return *this;
}

Assembler & Assembler::Cos()
{
	Write<Byte>(0xD9);
	Write<Byte>(0xFF);

	return *this;
}

Assembler & Assembler::Sin()
{
	Write<Byte>(0xD9);
	Write<Byte>(0xFE);

	return *this;
}

Assembler & Assembler::Tan()
{
	Write<Byte>(0xD9);
	Write<Byte>(0xF2);

	return *this;
}

Assembler & Assembler::Neg()
{
	Write<Byte>(0xD9);
	Write<Byte>(0xE0);

	return *this;
}

Assembler & Assembler::Abs()
{
	Write<Byte>(0xD9);
	Write<Byte>(0xE1);

	return *this;
}

Assembler & Assembler::Pop()
{
	Write<Byte>(0xDD);
	Write<Byte>(0xD8);

	return *this;
}

Assembler & Assembler::Free(Byte registerNumber)
{
	if(registerNumber > 8)
		throw std::logic_error("FPU register must be in 0-7");

	Write<Byte>(0xDD);
	Write<Byte>(0xC0 | registerNumber);

	return *this;
}

Assembler & Assembler::Sqrt()
{
	Write<Byte>(0xD9);
	Write<Byte>(0xFA);

	return *this;
}

Assembler & Assembler::Mod()
{
	Write<Byte>(0xD9);
	Write<Byte>(0xF8);

	return *this;
}
