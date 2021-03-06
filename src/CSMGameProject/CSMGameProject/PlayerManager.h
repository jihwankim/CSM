
#pragma once

#include "Player.h"

class CPlayerManager
{
private:
	static CPlayerManager* m_Instance;

	CPlayerManager(void);
	~CPlayerManager(void);

public:
	static CPlayerManager* GetInstance();
	static void ReleaseInstance();

	void SetMyPlayerId(int id);
	CPlayer* NewPlayer(int id);
	void DeletePlayer(int id);

	bool IsLogin() { return mMyPlayerId==-1 ? false : true; };

	CPlayer* GetMyPlayer() { return mMyPlayer; };

	void UpdatePlayerMoveDirection(int _playerId, NNPoint direction);
	void UpdatePlayerPosition(int _playerId, NNPoint point);
	void UpdatePlayerRotation(int _playerId, float angle);
	void UpdatePlayerInfo(PlayerInfo info);
	void UpdatePlayerHP(int _playerId, int hp);
	void UpdatePlayerState(int _playerId, short state );
	void UpdatePlayerTeam(int _playerId, int team);
	void UpdatePlayerKillScore( int playerId, int killScore );
	void UpdatePlayerNickname(int playerId, std::wstring nickname);
	//void UpdatePlayerType(int _playerId, int type);
	void UpdatePlayerType( int playerId, PlayerType type );
	int GetMyPlayerId() { return mMyPlayerId; };

	std::map<int, CPlayer*> GetPlayerList() { return mPlayers; }
	CPlayer *FindPlayerByID(int ID);

private:
	std::map<int,CPlayer*> mPlayers;
	CPlayer* mMyPlayer;
	int mMyPlayerId; // init : -1
};