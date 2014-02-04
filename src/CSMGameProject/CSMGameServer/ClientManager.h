#pragma once

#include <map>
#include <winsock2.h>
#include <my_global.h>
#include <mysql.h>

#pragma comment(lib, "libmySQL.lib")

class ClientSession ;
struct PacketHeader ;
struct DatabaseJobContext ;

class ClientManager
{
public:
	ClientManager() : mLastGCTick(0), mLastClientWorkTick(0)
	{}

	ClientSession* CreateClient(SOCKET sock) ;
	
	void BroadcastPacket(ClientSession* from, PacketHeader* pkt, int gameId = -1) ;

	void OnPeriodWork() ;

	/// DB�� �÷��̾� ������ �����ϰų� �����ϴ� �Լ�
	void CreatePlayer(int pid, double x, double y, double z, const char* name, const char* comment) ;
private:
	void CreatePlayerDone(DatabaseJobContext* dbJob) ;
	void DeletePlayerDone(DatabaseJobContext* dbJob) ;

private:
	void CollectGarbageSessions() ;
	void ClientPeriodWork() ;
	void DispatchDatabaseJobResults() ;

private:
	typedef std::map<SOCKET, ClientSession*> ClientList ;
	ClientList	mClientList ;

	DWORD		mLastGCTick ;
	DWORD		mLastClientWorkTick ;
	int			mLastTime;
} ;

extern ClientManager* GClientManager ;
//extern MYSQL* GMYSQLConnection;
//extern MYSQL* GMYSQLCONN;