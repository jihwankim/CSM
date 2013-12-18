
#include "PacketHandler.h"
#include <stdio.h>
#include <assert.h>
#include "PlayerManager.h"

GameKeyStatesUpdateHandler::GameKeyStatesUpdateHandler()
{

}
GameKeyStatesUpdateHandler::~GameKeyStatesUpdateHandler()
{

}
void GameKeyStatesUpdateHandler::HandlingPacket( short packetType, NNCircularBuffer* circularBuffer, NNPacketHeader* header )
{
	switch ( packetType )
	{
	case PKT_SC_KEYSTATE:
		{
			if ( circularBuffer->Read((char*)&mGameKeyStatesUpdateResult, header->mSize) )
			{
				// ��Ŷó��
				if ( mGameKeyStatesUpdateResult.mMyPlayerInfo.mPlayerId == -1  )
				{
					/// �߸��� ������
					/// �����Ѵ�
					return;
				}
				//�α����� �߸��Ǿ� ĳ���Ͱ� ���� �� �����Ƿ�
				CPlayerManager::GetInstance()->NewPlayer( mGameKeyStatesUpdateResult.mMyPlayerInfo.mPlayerId );
				
				CPlayerManager::GetInstance()->UpdatePlayerInfo( mGameKeyStatesUpdateResult.mMyPlayerInfo );
				printf("Key State Changed[%d] Pos : %.1f, %.1f %.1f\n", mGameKeyStatesUpdateResult.mMyPlayerInfo.mPlayerId,
					mGameKeyStatesUpdateResult.mMyPlayerInfo.mX, mGameKeyStatesUpdateResult.mMyPlayerInfo.mY, mGameKeyStatesUpdateResult.mMyPlayerInfo.mAngle) ;
			}
			else
			{
				assert(false) ;
			}
		}
		break;
	}
}
