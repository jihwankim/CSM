#include "stdafx.h"
#include "Main.h"
#include "PacketType.h"
#include "ClientSession.h"
#include "ClientManager.h"
#include "DatabaseJobContext.h"
#include "DatabaseJobManager.h"
#include "PlayerManager.h"
#include "BulletManager.h"
#include "SkillManager.h"
#include "ItemManager.h"
#include "GameManager.h"
ClientManager* GClientManager = nullptr ;

ClientSession* ClientManager::CreateClient(SOCKET sock)
{
	ClientSession* client = new ClientSession(sock) ;
	mClientList.insert(ClientList::value_type(sock, client)) ;

	return client ;
}



void ClientManager::BroadcastPacket(ClientSession* from, PacketHeader* pkt, int gameId)
{
	///FYI: C++ STL iterator ��Ÿ���� ����
	std::map<int, Player*> players;
	int GameId;
	if(from == nullptr) GameId = gameId;
	else GameId = GPlayerManager->GetPlayer(from->mPlayerId)->GetGameId();
	GPlayerManager->GetPlayers(GameId , &players );
	for (auto it=players.begin() ; it!=players.end() ; ++it)
	{
		ClientSession* client = it->second->GetClient();
		
		if ( from == client )
			continue ;
		
		client->Write(pkt) ;
	}
}

void ClientManager::OnPeriodWork()
{
	/// ������ ���� ���ǵ� �ֱ������� ���� (1�� ���� ���� ������)
	DWORD currTick = GetTickCount() ;
	if ( currTick - mLastGCTick >= 1000 )
	{
		CollectGarbageSessions() ;
		mLastGCTick = currTick ;
	}
	/// ���ӵ� Ŭ���̾�Ʈ ���Ǻ��� �ֱ������� ����� �ϴ� �� (�ֱ�� �˾Ƽ� ���ϸ� �� - ������ 0�ʷ� ����)
	if ( currTick - mLastClientWorkTick >= 0 )
	{
		ClientPeriodWork() ;
		mLastClientWorkTick = currTick ;
	}

	/// ó�� �Ϸ�� DB �۾��� ������ Client�� dispatch
	//DispatchDatabaseJobResults() ;
		
}

void ClientManager::CollectGarbageSessions()
{
	std::vector<ClientSession*> disconnectedSessions ;
	
	///FYI: C++ 11 ���ٸ� �̿��� ��Ÿ��
	std::for_each(mClientList.begin(), mClientList.end(),
		[&](ClientList::const_reference it)
		{
			ClientSession* client = it.second ;

			if ( false == client->IsConnected() && false == client->DoingOverlappedRecvOperation() && false == client->DoingOverlappedSendOperation())
				disconnectedSessions.push_back(client) ;
		}
	) ;
	

	///FYI: C��� ��Ÿ���� ����
	for (size_t i=0 ; i<disconnectedSessions.size() ; ++i)
	{
		ClientSession* client = disconnectedSessions[i] ;
		mClientList.erase(client->mSocket) ;
		delete client ;
	}

}

void ClientManager::ClientPeriodWork()
{
	GPlayerManager->UpdatePlayers();
	int nowTime = timeGetTime();
	float dTime = (static_cast<float>(nowTime - mLastTime))/1000.f;
	mLastTime = nowTime;
	GBulletManager->Update(dTime);
	GSkillManager->Update(dTime);
	GGameManager->Update(dTime);
	GItemManager->Update(dTime);
	
	/// FYI: C++ 11 ��Ÿ���� ����
	for (auto& it : mClientList)
	{
		ClientSession* client = it.second ;
		client->OnTick() ;
		if( false == client->DoingOverlappedSendOperation() )
			client->Send();
	}
}
