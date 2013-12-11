#include "PacketHandler.h"
#include <stdio.h>
#include <assert.h>
#include "EffectManager.h"
#include "ATypeEffect.h";

ATypeSkillShootHandler::ATypeSkillShootHandler()
{

}
ATypeSkillShootHandler::~ATypeSkillShootHandler()
{

}
void ATypeSkillShootHandler::HandlingPacket( short packetType, NNCircularBuffer* circularBuffer, NNPacketHeader* header )
{
	switch ( packetType )
	{
	case PKT_SC_A_TYPESKILL_SHOOT:
		{
			if ( circularBuffer->Read((char*)&mATypeSkillShootResult, header->mSize) )
			{

				//�α����� �߸��Ǿ� ĳ���Ͱ� ���� �� �����Ƿ�
				EffectManager::GetInstance()->AddEffect( new ATypeEffect(mATypeSkillShootResult.mAngle,mATypeSkillShootResult.mStartPosition) );
			}
			else
			{
				assert(false) ;
			}
		}
		break;
	}
}
