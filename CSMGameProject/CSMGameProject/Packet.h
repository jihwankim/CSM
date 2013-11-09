
#pragma once

#include "NNPacketHeader.h"

enum PacketTypes
{
	PKT_TEST = 0,
};

#pragma pack(push,1)

struct TestPacket : public NNPacketHeader
{
	TestPacket()
	{
		m_Size = sizeof(TestPacket) ;
		m_Type = PKT_TEST;
		m_Int = 0;
		m_Float = 0.f;
		m_Char = 0;
	}

	int m_Int;
	float m_Float;
	char m_Char;
};

#pragma pack(pop)