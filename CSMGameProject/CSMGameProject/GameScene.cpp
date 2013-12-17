
#include "GameScene.h"
#include "NNApplication.h"
#include "PacketType.h"
#include "NNNetworkSystem.h"
#include "PacketHandler.h"
#include "EffectManager.h"

#include "PlayerManager.h"
#include "GameManager.h"

#include "NNLogger.h"

CGameScene::CGameScene(void) : 
	mNowGameKeyStates(), mAngle(0), mLastAngleChangedTime(timeGetTime()),
	misInit(false)
{
	// Camera Setting
	GetCamera().SetCameraAnchor(CameraAnchor::MIDDLE_CENTER);

	// GameMap Create
	mGameMap = CGameMap::Create(L"map/sample2.csm");

	AddChild( mGameMap );

	// EffectManager
	AddChild( EffectManager::GetInstance() , 1);

	InitNetworkSetting();
}

CGameScene::~CGameScene(void)
{
	CPlayerManager::ReleaseInstance();
	GameManager::ReleaseInstance();
}

void CGameScene::Init()
{
}

void CGameScene::Render()
{
	NNScene::Render();
}

void CGameScene::Update( float dTime )
{
	NNScene::Update(dTime);

	if( CPlayerManager::GetInstance()->IsLogin() == true )
	{
	//	TODO :: CPlayerManager의 Score, Limit를 표현해주세요
		if(misInit == false)
		{
			misInit = true;
			// UI Setting
			SetUISet( GameUISet::Create() );
		}
		if ( GetCamera().GetPosition().GetDistance( CPlayerManager::GetInstance()->GetMyPlayer()->GetPosition() ) > 100.f ) 
		{
			GetCamera().SetPosition( CPlayerManager::GetInstance()->GetMyPlayer()->GetPosition() );
		}
		else
		{
			GetCamera().SetPosition(NNPoint().Lerp(GetCamera().GetPosition(),
				CPlayerManager::GetInstance()->GetMyPlayer()->GetPosition()
				,0.99f));
		}

		if( isChangedGameKeyStates() == true )
		{
			mLastAngleChangedTime = timeGetTime();
			mAngle = GetNowAngle();
			mNowGameKeyStates = GetNowGameKeyStates();
			
			//send packet
			mGameKeyStatesUpdateHandler->mGameKeyStatesUpdateRequest.mMyPlayerInfo.mGameKeyStates = GetNowGameKeyStates();
			mGameKeyStatesUpdateHandler->mGameKeyStatesUpdateRequest.mMyPlayerInfo.mPlayerId = CPlayerManager::GetInstance()->GetMyPlayerId();
			mGameKeyStatesUpdateHandler->mGameKeyStatesUpdateRequest.mMyPlayerInfo.mX = CPlayerManager::GetInstance()->GetMyPlayer()->GetPositionX();
			mGameKeyStatesUpdateHandler->mGameKeyStatesUpdateRequest.mMyPlayerInfo.mY = CPlayerManager::GetInstance()->GetMyPlayer()->GetPositionY();
			mGameKeyStatesUpdateHandler->mGameKeyStatesUpdateRequest.mMyPlayerInfo.mAngle = mAngle;
			NNNetworkSystem::GetInstance()->Write( (const char*)&mGameKeyStatesUpdateHandler->mGameKeyStatesUpdateRequest,
				mGameKeyStatesUpdateHandler->mGameKeyStatesUpdateRequest.mSize );
		}
		if( isChangedAngle() == true )
		{
			mLastAngleChangedTime = timeGetTime();
			mAngle = GetNowAngle();
			mMouseAngleUpdateHandler->mMouseAngleUpdateRequest.mPlayerId = CPlayerManager::GetInstance()->GetMyPlayerId();
			mMouseAngleUpdateHandler->mMouseAngleUpdateRequest.mAngle = mAngle;
			NNNetworkSystem::GetInstance()->Write( (const char*)&mMouseAngleUpdateHandler->mMouseAngleUpdateRequest,
				mMouseAngleUpdateHandler->mMouseAngleUpdateRequest.mSize );
		}

		/* 플레이어 위치의 타일 타입을 확인 */
		switch ( mGameMap->GetTileType((int)CPlayerManager::GetInstance()->GetMyPlayer()->GetPositionX()/64, 
			(int)CPlayerManager::GetInstance()->GetMyPlayer()->GetPositionY()/64) )
		{
			/* 타일 타입이 배럭일 경우 형태 변환 패킷 전송 */
		case BARRACK_A:
			{
				NNLogger::TraceLog( "In Barrack A" );
				//CPlayerManager::GetInstance()->GetMyPlayer()->SetPlayerType( TYPE_A );
				mTypeChangeHandler->mTypeChangeToARequestPacket.mPlayerId = CPlayerManager::GetInstance()->GetMyPlayerId();
				NNNetworkSystem::GetInstance()->Write( (const char*)&mTypeChangeHandler->mTypeChangeToARequestPacket,
					mTypeChangeHandler->mTypeChangeToARequestPacket.mSize );
			}
			break;
		case BARRACK_B:
			{
				NNLogger::TraceLog( "In Barrack B" );
				//CPlayerManager::GetInstance()->GetMyPlayer()->SetPlayerType( TYPE_B );
				mTypeChangeHandler->mTypeChangeToBRequestPacket.mPlayerId = CPlayerManager::GetInstance()->GetMyPlayerId();
				NNNetworkSystem::GetInstance()->Write( (const char*)&mTypeChangeHandler->mTypeChangeToBRequestPacket,
					mTypeChangeHandler->mTypeChangeToBRequestPacket.mSize );
			}
			break;
		case BARRACK_C:
			{
				NNLogger::TraceLog( "In Barrack C" );
				//CPlayerManager::GetInstance()->GetMyPlayer()->SetPlayerType( TYPE_C );
				mTypeChangeHandler->mTypeChangeToCRequestPacket.mPlayerId = CPlayerManager::GetInstance()->GetMyPlayerId();
				NNNetworkSystem::GetInstance()->Write( (const char*)&mTypeChangeHandler->mTypeChangeToCRequestPacket,
					mTypeChangeHandler->mTypeChangeToCRequestPacket.mSize );
			}
			break;
		case BARRACK_D:
			{
				NNLogger::TraceLog( "In Barrack D" );
			}
			break;
		default:
			break;
		}
	}
}

void CGameScene::InitNetworkSetting()
{
	mLoginHandler = new LoginHandler();
	mLoginBroadcastHandler = new LoginBroadcastHandler();
	mGameKeyStatesUpdateHandler = new GameKeyStatesUpdateHandler();
	mLogoutHandler = new LogoutHandler();
	mMouseAngleUpdateHandler = new MouseAngleUpdateHandler();
	mHPUpdateHandler = new HPUpdateHandler();
	mKillScoreHandler = new KillScoreHandler();
	mPlayerKillScoreHandler = new KillScoreHandler();
	mATypeSkillShootHandler = new ATypeSkillShootHandler();
	mBTypeSkillShootHandler = new BTypeSkillShootHandler();
	mCTypeSkillShootHandler = new CTypeSkillShootHandler();
	mTypeChangeHandler = new TypeChangeHandler();
	NNNetworkSystem::GetInstance()->Init();

	NNNetworkSystem::GetInstance()->SetPacketHandler( PKT_SC_KEYSTATE, mGameKeyStatesUpdateHandler );
	NNNetworkSystem::GetInstance()->SetPacketHandler( PKT_SC_LOGIN, mLoginHandler );
	NNNetworkSystem::GetInstance()->SetPacketHandler( PKT_SC_LOGIN_BROADCAST, mLoginBroadcastHandler );
	NNNetworkSystem::GetInstance()->SetPacketHandler( PKT_SC_LOGOUT, mLogoutHandler );
	NNNetworkSystem::GetInstance()->SetPacketHandler( PKT_SC_MOUSEANGLE, mMouseAngleUpdateHandler );
	NNNetworkSystem::GetInstance()->SetPacketHandler( PKT_SC_HP, mHPUpdateHandler );
	NNNetworkSystem::GetInstance()->SetPacketHandler( PKT_SC_KILLSCORE, mKillScoreHandler);
	NNNetworkSystem::GetInstance()->SetPacketHandler( PKT_SC_PLAYER_KILLSCORE_UPDATE, mPlayerKillScoreHandler);
	NNNetworkSystem::GetInstance()->SetPacketHandler(PKT_SC_A_TYPESKILL_SHOOT, mATypeSkillShootHandler);
	NNNetworkSystem::GetInstance()->SetPacketHandler(PKT_SC_B_TYPESKILL_SHOOT, mBTypeSkillShootHandler);
	NNNetworkSystem::GetInstance()->SetPacketHandler(PKT_SC_C_TYPESKILL_SHOOT, mCTypeSkillShootHandler);

	NNNetworkSystem::GetInstance()->SetPacketHandler(PKT_SC_TYPE_CHANGE_A, mTypeChangeHandler);
	NNNetworkSystem::GetInstance()->SetPacketHandler(PKT_SC_TYPE_CHANGE_B, mTypeChangeHandler);
	NNNetworkSystem::GetInstance()->SetPacketHandler(PKT_SC_TYPE_CHANGE_C, mTypeChangeHandler);
	NNNetworkSystem::GetInstance()->SetPacketHandler(PKT_SC_TYPE_CHANGE_D, mTypeChangeHandler);
	

	//NNNetworkSystem::GetInstance()->Connect( "10.73.44.30",9001);
	NNNetworkSystem::GetInstance()->Connect( "127.0.0.1", 9001 );

	NNNetworkSystem::GetInstance()->Write( (const char*)&mLoginHandler->mLoginRequestPacket, mLoginHandler->mLoginRequestPacket.mSize );
}

GameKeyStates CGameScene::GetNowGameKeyStates()
{
	GameKeyStates nowGameKeyState;
	if( NNInputSystem::GetInstance()->GetKeyState('W') == KEY_PRESSED ||
		NNInputSystem::GetInstance()->GetKeyState('W') == KEY_DOWN )
		nowGameKeyState.upDirectKey = KEYSTATE_PRESSED;
	if( NNInputSystem::GetInstance()->GetKeyState('S') == KEY_PRESSED ||
		NNInputSystem::GetInstance()->GetKeyState('S') == KEY_DOWN )
		nowGameKeyState.downDirectKey = KEYSTATE_PRESSED;
	if( NNInputSystem::GetInstance()->GetKeyState('A') == KEY_PRESSED ||
		NNInputSystem::GetInstance()->GetKeyState('A') == KEY_DOWN )
		nowGameKeyState.leftDirectKey = KEYSTATE_PRESSED;
	if( NNInputSystem::GetInstance()->GetKeyState('D') == KEY_PRESSED ||
		NNInputSystem::GetInstance()->GetKeyState('D') == KEY_DOWN )
		nowGameKeyState.rightDirectKey = KEYSTATE_PRESSED;
	if( NNInputSystem::GetInstance()->GetKeyState(VK_LBUTTON) == KEY_PRESSED ||
		NNInputSystem::GetInstance()->GetKeyState(VK_LBUTTON) == KEY_DOWN )
		nowGameKeyState.attackKey = KEYSTATE_PRESSED;
	if( NNInputSystem::GetInstance()->GetKeyState(VK_RBUTTON) == KEY_PRESSED ||
		NNInputSystem::GetInstance()->GetKeyState(VK_RBUTTON) == KEY_DOWN )
		nowGameKeyState.typeActiveSkillKey = KEYSTATE_PRESSED;
	if( NNInputSystem::GetInstance()->GetKeyState(VK_SPACE) == KEY_PRESSED ||
		NNInputSystem::GetInstance()->GetKeyState(VK_SPACE) == KEY_DOWN )
		nowGameKeyState.userActiveSkillKey = KEYSTATE_PRESSED;

	return nowGameKeyState;
}
bool CGameScene::isChangedGameKeyStates()
{
	GameKeyStates nowGameKeyState = GetNowGameKeyStates();
	if( nowGameKeyState.attackKey != mNowGameKeyStates.attackKey
		||nowGameKeyState.upDirectKey != mNowGameKeyStates.upDirectKey
		||nowGameKeyState.downDirectKey != mNowGameKeyStates.downDirectKey
		||nowGameKeyState.leftDirectKey != mNowGameKeyStates.leftDirectKey
		||nowGameKeyState.rightDirectKey != mNowGameKeyStates.rightDirectKey
		||nowGameKeyState.typeActiveSkillKey != mNowGameKeyStates.typeActiveSkillKey
		||nowGameKeyState.userActiveSkillKey != mNowGameKeyStates.userActiveSkillKey)
		return true;
	return false;
}

float CGameScene::GetNowAngle()
{
	NNPoint mousePoint = NNInputSystem::GetInstance()->GetMousePosition();
	// characterPositionByWC, WC -> window center. 화면 가운데를 0,0으로 했을때의 캐릭터 좌표
	//NNPoint characterPositionByWC = GetCamera().GetPosition() -	CPlayerManager::GetInstance()->GetMyPlayer()->GetPosition();
	NNPoint referencePointForMouse = NNPoint(GetCamera().GetScreenWidth()/2.f,GetCamera().GetScreenHeight()/2.f);// + characterPositionByWC;
	return atan2f( NNPoint(mousePoint-referencePointForMouse).GetY() , NNPoint(mousePoint-referencePointForMouse).GetX() );
}
bool CGameScene::isChangedAngle()
{
	DWORD time_A = timeGetTime();
	if( (timeGetTime() - mLastAngleChangedTime ) > 20 )
	{
		//20 밀리세컨드마다 마우스 방향 변경.
		if( mAngle != GetNowAngle() )
			return true;
	}
	return false;
}