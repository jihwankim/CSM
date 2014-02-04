
#include "PacketHandler.h"
#include <stdio.h>
#include "PlayerManager.h"
LoginBroadcastHandler::LoginBroadcastHandler()
{

}
LoginBroadcastHandler::~LoginBroadcastHandler()
{

}
void LoginBroadcastHandler::HandlingPacket( short packetType, NNCircularBuffer* circularBuffer, NNPacketHeader* header )
{
	switch ( packetType )
	{
	case PKT_SC_LOGIN_BROADCAST:
		{
			if ( circularBuffer->Read((char*)&mLoginBroadcastResultPacket, header->mSize) )
			{
				// ��Ŷó��
				if ( mLoginBroadcastResultPacket.mMyPlayerInfo.mPlayerId == -1  )
				{
					/// ���� �ɸ��� �α��� ���д�.
					//�� �α��� �ƴϴϱ� �ϴ��� �׳� �����Ұ�
				}
				CPlayerManager::GetInstance()->NewPlayer( mLoginBroadcastResultPacket.mMyPlayerInfo.mPlayerId );
				CPlayerManager::GetInstance()->UpdatePlayerInfo( mLoginBroadcastResultPacket.mMyPlayerInfo );
				CPlayerManager::GetInstance()->UpdatePlayerNickname(mLoginBroadcastResultPacket.mMyPlayerInfo.mPlayerId, mLoginBroadcastResultPacket.mMyPlayerInfo.mName);
				printf("NEW LOGIN SUCCESS ClientId[%d] \n", mLoginBroadcastResultPacket.mMyPlayerInfo.mPlayerId) ;
			}
			else
			{
			}
		}
		break;
	}
}