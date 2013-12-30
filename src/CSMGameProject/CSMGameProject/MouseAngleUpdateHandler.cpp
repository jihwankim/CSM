#include "PacketHandler.h"
#include <stdio.h>
#include "PlayerManager.h"

MouseAngleUpdateHandler::MouseAngleUpdateHandler()
{

}
MouseAngleUpdateHandler::~MouseAngleUpdateHandler()
{

}
void MouseAngleUpdateHandler::HandlingPacket( short packetType, NNCircularBuffer* circularBuffer, NNPacketHeader* header )
{
	switch ( packetType )
	{
	case PKT_SC_MOUSEANGLE:
		{
			if ( circularBuffer->Read((char*)&mMouseAngleUpdateResult, header->mSize) )
			{
				// ��Ŷó��
				if ( mMouseAngleUpdateResult.mPlayerId == -1  )
				{
					/// �߸��� ������
					/// �����Ѵ�
					return;
				}
				//�α����� �߸��Ǿ� ĳ���Ͱ� ���� �� �����Ƿ�
				CPlayerManager::GetInstance()->NewPlayer( mMouseAngleUpdateResult.mPlayerId );
				
				CPlayerManager::GetInstance()->UpdatePlayerRotation( mMouseAngleUpdateResult.mPlayerId, mMouseAngleUpdateResult.mAngle );
				printf("Mouse Angle Changed[%d] angle : %.1f\n", mMouseAngleUpdateResult.mPlayerId,
					mMouseAngleUpdateResult.mAngle) ;
			}
			else
			{
			}
		}
		break;
	}
}
