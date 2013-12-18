
#include "PacketHandler.h"
#include <stdio.h>
#include <assert.h>
#include "PlayerManager.h"
LogoutHandler::LogoutHandler()
{

}
LogoutHandler::~LogoutHandler()
{

}
void LogoutHandler::HandlingPacket( short packetType, NNCircularBuffer* circularBuffer, NNPacketHeader* header )
{
	switch ( packetType )
	{
	case PKT_SC_LOGOUT:
		{
			if ( circularBuffer->Read((char*)&mLogoutResultPacket, header->mSize) )
			{
				// ��Ŷó��
				if ( mLogoutResultPacket.mPlayerId == -1  )
				{
					/// �߸��� �α׾ƿ�.
					//�� �α׾ƿ� �ƴϴϱ� �ϴ��� �׳� �����Ұ�
				}
				CPlayerManager::GetInstance()->DeletePlayer( mLogoutResultPacket.mPlayerId );
				printf("Logout ClientId[%d] \n", mLogoutResultPacket.mPlayerId) ;
			}
			else
			{
				assert(false) ;
			}
		}
		break;
		
	}
}
