
#include "PacketHandler.h"
#include <stdio.h>
#include <assert.h>
#include "PlayerManager.h"

HPUpdateHandler::HPUpdateHandler()
{

}
HPUpdateHandler::~HPUpdateHandler()
{

}
void HPUpdateHandler::HandlingPacket( short packetType, NNCircularBuffer* circularBuffer, NNPacketHeader* header )
{
	switch ( packetType )
	{
	case PKT_SC_HP:
		{
			if ( circularBuffer->Read((char*)&mHPUpdateResult, header->mSize) )
			{
				// ��Ŷó��
				if ( mHPUpdateResult.mPlayerId == -1  )
				{
					/// �߸��� ������
					/// �����Ѵ�
					return;
				}
				//�α����� �߸��Ǿ� ĳ���Ͱ� ���� �� �����Ƿ�
				CPlayerManager::GetInstance()->NewPlayer( mHPUpdateResult.mPlayerId );
				
				CPlayerManager::GetInstance()->UpdatePlayerHP( mHPUpdateResult.mPlayerId, mHPUpdateResult.mHP );
				printf("HP Changed[%d] Pos : %d \n", mHPUpdateResult.mPlayerId,
					mHPUpdateResult.mHP) ;
			}
			else
			{
				assert(false) ;
			}
		}
		break;
	}
}
