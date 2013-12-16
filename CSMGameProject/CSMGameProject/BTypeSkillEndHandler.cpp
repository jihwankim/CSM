#include "PacketHandler.h"
#include <stdio.h>
#include <assert.h>
#include "EffectManager.h"
#include "TypeB.h"

BTypeSkillEndHandler::BTypeSkillEndHandler()
{

}
BTypeSkillEndHandler::~BTypeSkillEndHandler()
{

}
void BTypeSkillEndHandler::HandlingPacket(short packetType, NNCircularBuffer* circularBuffer, NNPacketHeader* header)
{
	switch (packetType)
	{
	case PKT_SC_B_TYPESKILL_END:
		{
			if (circularBuffer->Read((char*)&mBTypeSkillEndResult, header->mSize))
			{
				//�α����� �߸��Ǿ� ĳ���Ͱ� ���� �� �����Ƿ�
				EffectManager::GetInstance()->GetTypeBEffect(mBTypeSkillEndResult.mIndex)->Explosion();
			}
			else
			{
				assert(false);
			}
		}
		break;
	}
}
