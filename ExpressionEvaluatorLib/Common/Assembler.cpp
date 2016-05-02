#include "Assembler.h"

//Opertation needs up to 108 bytes, also memory should be 16 bytes aligned
static const uint8_t BYTES_FOR_FPU_SAVE_LOAD = 0x80;

static const uint32_t MASK_16_BYTES_ALIGN = ~0x0F;

void Assembler::WriteTo(ExpressionBytes& dst) const
{
	const auto &src = GetData();
	dst.insert(dst.end(), src.cbegin(), src.cend());
}

Assembler &Assembler::Write(const Assembler &a)
{
	a.WriteTo(_data);

	return *this;
}

Assembler & Assembler::Load(double *value)
{
	Write<Byte>(0xDD);
	Write<Byte>(0x05);
	Write<double*>(value);

	return *this;
}

Assembler& Assembler::LoadZero()
{
	Write(Byte(0xD9), Byte(0xEE));

	return *this;
}

Assembler& Assembler::LoadOne()
{
	Write(Byte(0xD9), Byte(0xE8));

	return *this;
}

Assembler & Assembler::Store(double *dest)
{
	Write<Byte>(0xDD);
	Write<Byte>(0x1D);
	Write<double*>(dest);

	return *this;
}

Assembler & Assembler::StoreToStack(uint32_t offset)
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
		Write<uint32_t>(offset);
	}

	return *this;
}

Assembler & Assembler::Call(void *address)
{
	Mov(GeneralAsmRegisters::EAX, uint32_t(address));
	Call(GeneralAsmRegisters::EAX);

	return *this;
}

Assembler& Assembler::Call(GeneralAsmRegisters reg)
{
	Write(Byte(0xFF), Byte(0xD0 | Byte(reg)));

	return *this;
}

Assembler & Assembler::AllocateStack(uint32_t bytesCount)
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
		Write<uint32_t>(bytesCount);
	}

	return *this;
}

Assembler & Assembler::FreeStack(uint32_t bytesCount)
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
		Write<uint32_t>(bytesCount);
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
	Write(Byte(0xDD), Byte(0xD8));

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

Assembler& Assembler::Mov(GeneralAsmRegisters dst, GeneralAsmRegisters src)
{
	Byte dstN = Byte(dst);
	Byte srcN = Byte(src);
	Write(Byte(0x89), Byte(0xC0 | dstN | srcN << 3));

	return *this;
}

Assembler& Assembler::Mov(GeneralAsmRegisters dst, uint32_t src)
{
	Byte dstN = static_cast<Byte>(dst);

	Write(Byte(0xB8 | dstN), uint32_t(src));

	return *this;
}

Assembler& Assembler::Mov(double* dst, GeneralAsmRegisters src)
{
	if (src == GeneralAsmRegisters::EAX) {
		Write(Byte(0xA3), uint32_t(dst));
	} 
	else
	{
		Byte srcN = static_cast<Byte>(src);
		Write(Byte(0x89), Byte(0x04 | srcN << 3), uint32_t(dst));
	}

	return *this;
}

Assembler& Assembler::And(GeneralAsmRegisters dst, uint32_t data)
{
	Byte dstN = static_cast<Byte>(dst);

	if(data < 0x80)
	{
		Write(Byte(0x83), Byte(0xE0 | dstN), Byte(data));
	} 
	else
	{
		if (dst == GeneralAsmRegisters::EAX) 
		{
			Write(Byte(0x25), uint32_t(data));
		} 
		else
		{
			Write(Byte(0x81), Byte(0xE0 | dstN), data);
		}
	}

	return *this;
}

Assembler & Assembler::Sqrt()
{
	Write(Byte(0xD9), Byte(0xFA));

	return *this;
}

Assembler& Assembler::Ret()
{
	Write<Byte>(0xC3);

	return *this;
}

Assembler& Assembler::PushRegister(GeneralAsmRegisters reg)
{
	uint32_t index = static_cast<uint32_t>(reg);

	Write<Byte>(0x50 + index);

	return *this;
}

Assembler& Assembler::PopRegister(GeneralAsmRegisters reg)
{
	uint32_t index = static_cast<uint32_t>(reg);

	Write<Byte>(0x58 + index);

	return *this;
}

Assembler& Assembler::InitFPU()
{
	Write(Byte(0x9B), Byte(0xDB), Byte(0xE3));

	return *this;
}

Assembler& Assembler::SaveFPU()
{
	this->And(GeneralAsmRegisters::ESP, MASK_16_BYTES_ALIGN) //Make ESP 16 bytes aligned
		.AllocateStack(BYTES_FOR_FPU_SAVE_LOAD);

	Write(Byte(0x9B), Byte(0xDD), Byte(0x34), Byte(0x24));

	return *this;
}

Assembler& Assembler::RestoreFPU()
{
	Write(Byte(0xDD), Byte(0x24), Byte(0x24));

	return FreeStack(BYTES_FOR_FPU_SAVE_LOAD);
}

Assembler& Assembler::Compare(Byte registerNumber)
{
	if (registerNumber > 8)
		throw std::logic_error("FPU register must be in 0-7");

	Write<Byte>(0xDB);
	Write<Byte>(0xF0 | registerNumber);

	return *this;
}

Assembler& Assembler::CompareAndPop(Byte registerNumber)
{
	if (registerNumber > 8)
		throw std::logic_error("FPU register must be in 0-7");

	Write<Byte>(0xDF);
	Write<Byte>(0xF0 | registerNumber);

	return *this;
}

Assembler& Assembler::Jmp(int8_t offset)
{
	Write(Byte(0xEB), offset);

	return *this;
}

Assembler Assembler::JE(int8_t offset)
{
	Write(Byte(0x74), offset);

	return *this;
}

Assembler Assembler::JNE(int8_t offset)
{
	Write(Byte(0x75), offset);

	return *this;
}

Assembler Assembler::JL(int8_t offset)
{
	Write(Byte(0x72), offset);

	return *this;
}

Assembler Assembler::JG(int8_t offset)
{
	Write(Byte(0x77), offset);

	return *this;
}

Assembler Assembler::JGE(int8_t offset)
{
	Write(Byte(0x73), offset);

	return *this;
}

Assembler Assembler::JLE(int8_t offset)
{
	Write(Byte(0x76), offset);

	return *this;
}

Assembler & Assembler::Mod()
{
	Write<Byte>(0xD9);
	Write<Byte>(0xF8);

	return *this;
}
