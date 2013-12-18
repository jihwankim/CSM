
#include "stdafx.h"
#include "UserSession.h"

#include "PlayerManager.h"

void ClientKeyStatePacket( ClientSession* client, PacketHeader* header, CircularBuffer* buffer )
{
	GameKeyStatesUpdateRequest inPacket ;
	buffer->Read((char*)&inPacket, header->mSize);

	Player* _player = GPlayerManager->GetPlayer(inPacket.mMyPlayerInfo.mPlayerId);
	_player->SetGameKeyStates(inPacket.mMyPlayerInfo.mGameKeyStates);
	_player->SetRotation(inPacket.mMyPlayerInfo.mAngle);
}

void ClientMouseAnglePacket( ClientSession* client, PacketHeader* header, CircularBuffer* buffer )
{
	MouseAngleUpdateRequest inPacket ;
	buffer->Read((char*)&inPacket, header->mSize);

	Player* _player = GPlayerManager->GetPlayer(inPacket.mPlayerId);
	_player->SetRotation(inPacket.mAngle);
	MouseAngleUpdateResult outPacket = MouseAngleUpdateResult();
	outPacket.mPlayerId = inPacket.mPlayerId;
	outPacket.mAngle = inPacket.mAngle;

	if( !client->Broadcast(&outPacket) )
		return;
}