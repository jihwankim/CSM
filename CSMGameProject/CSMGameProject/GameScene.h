#pragma once

#include "NNScene.h"
#include "GameMap.h"
#include "Player.h"
#include "NNLabel.h"
#include "NNInputSystem.h"
#include "PacketType.h"
#include "PlayerManager.h"
#include "PacketHandler.h"

#include "GameUISet.h"

class CGameScene : public NNScene
{
private:
	CGameMap* m_GameMap;
	GameKeyStates m_NowGameKeyStates;
	GameKeyStatesUpdateHandler* m_GameKeyStatesUpdateHandler;
	LoginHandler* m_LoginHandler;
	LoginBroadcastHandler* m_LoginBroadcastHandler;
	LogoutHandler* m_LogoutHandler;
	MouseAngleUpdateHandler* m_MouseAngleUpdateHandler;
	HPUpdateHandler* m_HPUpdateHandler;
	float m_Angle;
	DWORD m_LastAngleChangedTime;
	bool m_isInit;

public:
	CGameScene(void);
	virtual ~CGameScene(void);

	void Render();
	void Update( float dTime );
	NNCREATE_FUNC(CGameScene);
private:
	GameKeyStates GetNowGameKeyStates();
	bool isChangedGameKeyStates();
	float GetNowAngle();
	bool isChangedAngle();

	void InitNetworkSetting();
};