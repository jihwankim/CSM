#include "stdafx.h"
#include "Player.h"
#include "Math.h"
#include "PlayerManager.h"
#include "GameManager.h"


Player::Player(void):mPosition(0,0),mPlayerState(PLAYER_STATE_IDLE)
{
}

Player::Player(int id, ClientSession* client):mHP(100),mDamage(5),mPlayerState(PLAYER_STATE_IDLE),mMoveDirection(Point(-10.f,-10.f))
	,mAttackRange(40),mRadius(24),mRotation(0),mAttackDelay(0),mUserSkillDelay(0),mTypeSkillDelay(0)
{

	mPlayerId = id;
	mClient = client;

	while(1)
	{
		float x = rand() % (GGameMap->GetWidth() * 64);
		float y = rand() % (GGameMap->GetHeight() * 64);

		if(CouldGoPosition(Point(x,y)) == true)
		{
			mPosition = Point(x,y);
			break;
		}
	}
	mTeam = GGameManager->GiveTeamNumber();
}

Player::~Player(void)
{
	//�Ҹ��ڰ� ����� ȣ�� �ȵ� ���� �����Ű�����..
	GGameManager->LogOutPlayer(mTeam);
}

void Player::TransState(short state)
{
	switch (state)
	{
	case PLAYER_STATE_IDLE:
		{
			mPlayerState = state;

			GameKeyStatesUpdateResult outPacket = GameKeyStatesUpdateResult();
			outPacket.mMyPlayerInfo = this->GetPlayerInfo();
			mClient->Broadcast(&outPacket);

		}
		break;
	case PLAYER_STATE_WALK:
		{
			Point willGoPosition = GetPosition();
			if ( mGameKeyStates.leftDirectKey ==  KEYSTATE_PRESSED )willGoPosition = willGoPosition + Point( -1.f, 0.f ) * mDTime * 100.f;
			if ( mGameKeyStates.rightDirectKey == KEYSTATE_PRESSED )willGoPosition = willGoPosition + Point( +1.f, 0.f ) * mDTime * 100.f;
			if ( mGameKeyStates.upDirectKey == KEYSTATE_PRESSED )	willGoPosition = willGoPosition + Point( 0.f, -1.f ) * mDTime * 100.f;
			if ( mGameKeyStates.downDirectKey == KEYSTATE_PRESSED )	willGoPosition = willGoPosition + Point( 0.f, 1.f ) * mDTime * 100.f;

			if ( GGameMap->isValidTile(willGoPosition) == false )
			{
				//�����ϱ� walk�� ��ȯ���� ����.
				break;
			}
			if(mPlayerState == PLAYER_STATE_IDLE)
			{	
				mMoveDirection = Point(-10.f,-10.f);
				mPlayerState = state;
				GameKeyStatesUpdateResult outPacket = GameKeyStatesUpdateResult();
				outPacket.mMyPlayerInfo = this->GetPlayerInfo();
				mClient->Broadcast(&outPacket);
			}
		}
		break;
	case PLAYER_STATE_ATTACK:
		{
			if(mAttackDelay > 0) break;
			if(mPlayerState == PLAYER_STATE_IDLE ||
				mPlayerState == PLAYER_STATE_WALK)
			{	
				mPlayerState = state;
				mAttackDelay = 1;
				GameKeyStatesUpdateResult outPacket = GameKeyStatesUpdateResult();
				outPacket.mMyPlayerInfo = this->GetPlayerInfo();
				mClient->Broadcast(&outPacket);
			}

		}
		break;
	case PLAYER_STATE_DIE:
		{
			mResponTime = 5.f;
			mPlayerState = state;

			GameKeyStatesUpdateResult outPacket = GameKeyStatesUpdateResult();
			outPacket.mMyPlayerInfo = this->GetPlayerInfo();
			mClient->Broadcast(&outPacket);
		}
		break;
	case PLAYER_STATE_TYPESKILL:
		{
			if(mTypeSkillDelay > 0 )break;
			if(mPlayerState == PLAYER_STATE_IDLE ||
				mPlayerState == PLAYER_STATE_WALK)
			{	
				mPlayerState = state;
				mTypeSkillDelay = 1;
				GameKeyStatesUpdateResult outPacket = GameKeyStatesUpdateResult();
				outPacket.mMyPlayerInfo = this->GetPlayerInfo();
				mClient->Broadcast(&outPacket);
			}
		}
	case PLAYER_STATE_USERSKILL:
		{
			if(mUserSkillDelay > 0) break;
			if(mPlayerState == PLAYER_STATE_IDLE ||
				mPlayerState == PLAYER_STATE_WALK)
			{	
				mPlayerState = state;
				mUserSkillDelay = 1;
				GameKeyStatesUpdateResult outPacket = GameKeyStatesUpdateResult();
				outPacket.mMyPlayerInfo = this->GetPlayerInfo();
				mClient->Broadcast(&outPacket);
			}
		}
		break;
	default:
		break;
	}
}


void Player::Update( float dTime)
{
	mDTime = dTime;
	if(mAttackDelay > 0)
		mAttackDelay -= dTime;
	if(mUserSkillDelay > 0)
		mUserSkillDelay -= dTime;
	if(mTypeSkillDelay > 0)
		mTypeSkillDelay -= dTime;
	switch (mPlayerState)
	{
	case PLAYER_STATE_IDLE:
		{
			if( mGameKeyStates.typeActiveSkillKey == KEYSTATE_PRESSED)
			{
				TransState(PLAYER_STATE_TYPESKILL);
				break;
			}
			if( mGameKeyStates.userActiveSkillKey == KEYSTATE_PRESSED)
			{
				TransState(PLAYER_STATE_USERSKILL);
				break;
			}
			if( mGameKeyStates.attackKey == KEYSTATE_PRESSED )
			{
				TransState(PLAYER_STATE_ATTACK);
				break;
			}
			else if ( mGameKeyStates.leftDirectKey ==  KEYSTATE_PRESSED 
				|| mGameKeyStates.rightDirectKey == KEYSTATE_PRESSED 
				|| mGameKeyStates.upDirectKey == KEYSTATE_PRESSED 
				|| mGameKeyStates.downDirectKey == KEYSTATE_PRESSED )
			{
				TransState(PLAYER_STATE_WALK);
			}else if ( mGameKeyStates.typeActiveSkillKey == KEYSTATE_PRESSED)
				TransState(PLAYER_STATE_TYPESKILL);
		}
		break;
	case PLAYER_STATE_WALK:
		{
			if( mGameKeyStates.typeActiveSkillKey == KEYSTATE_PRESSED)
			{
				TransState(PLAYER_STATE_TYPESKILL);
				break;
			}
			if( mGameKeyStates.userActiveSkillKey == KEYSTATE_PRESSED)
			{
				TransState(PLAYER_STATE_USERSKILL);
				break;
			}
			if( mGameKeyStates.attackKey == KEYSTATE_PRESSED )
			{
				TransState(PLAYER_STATE_ATTACK);
				break;
			}
			//Move myPlayer with Game Key States.
			//Check Moving Input, and set Position to d


			Point willGoDirection = Point(0,0);

			if ( mGameKeyStates.leftDirectKey ==  KEYSTATE_PRESSED )willGoDirection = willGoDirection + Point( -1.f, 0.f );
			if ( mGameKeyStates.rightDirectKey == KEYSTATE_PRESSED )willGoDirection = willGoDirection + Point( +1.f, 0.f );
			if ( mGameKeyStates.upDirectKey == KEYSTATE_PRESSED )	willGoDirection = willGoDirection + Point( 0.f, -1.f );
			if ( mGameKeyStates.downDirectKey == KEYSTATE_PRESSED )	willGoDirection = willGoDirection + Point( 0.f, +1.f );

			Point willGoPosition;

			//wasd ���� �� ������ Ȯ��
			if ( mGameKeyStates.leftDirectKey ==  KEYSTATE_NOTPRESSED 
				&& mGameKeyStates.rightDirectKey == KEYSTATE_NOTPRESSED 
				&& mGameKeyStates.upDirectKey == KEYSTATE_NOTPRESSED 
				&& mGameKeyStates.downDirectKey == KEYSTATE_NOTPRESSED )
			{
				TransState(PLAYER_STATE_IDLE);
				break;
			}

			//���� ������ �ϴ� ������ map���� �̵� �Ұ����� �����̴�?
			if ( CouldGoPosition( GetPosition() + willGoDirection * dTime * 100.f ) == false )
			{
				//X��ǥ�� �����ִ�?
				if ( CouldGoPosition( GetPosition() + Point(willGoDirection.x,0) * dTime * 100.f ) == true )
				{
					willGoDirection = Point(willGoDirection.x,0);
				}
				//Y��ǥ�� �� �� �ִ�?
				else if ( CouldGoPosition( GetPosition() +  Point(0,willGoDirection.y) * dTime * 100.f ) == true )
				{
					willGoDirection = Point(0,willGoDirection.y);
				}
				else
				{
					willGoDirection = Point(0,0);
				}
			}
			willGoPosition = GetPosition() + willGoDirection * dTime * 100.f;
			SetPosition(willGoPosition);


			//������ �ٸ� �������� �̵��ߴ�?
			if( mMoveDirection == Point(-10.f,-10.f) || mMoveDirection != willGoDirection)
			{
				mMoveDirection = willGoDirection;
				//����ٲ� key������ ��������.
				GameKeyStatesUpdateResult outPacket = GameKeyStatesUpdateResult();
				outPacket.mMyPlayerInfo = this->GetPlayerInfo();
				mClient->Broadcast(&outPacket);
			}

		}
		break;
	case PLAYER_STATE_ATTACK:
		{
			
			Point AttackPoint = mPosition + Point(cos(mRotation) * mAttackRange,sin(mRotation) * mAttackRange);
			std::map<int,Player*> players = GPlayerManager->GetPlayers();
			
			for( std::map<int,Player*>::iterator it = players.begin(); it != players.end(); ++it ) 
			{
				Player* enemy = it->second;
				if(enemy == this)continue;
				
				if( Point().GetDistance( enemy->GetPosition(), AttackPoint ) - mRadius < mAttackRange )
				{
					//�ǰݵ�����
					enemy->Damaged(mDamage+rand()%10);
				}
			}
			TransState(PLAYER_STATE_IDLE);
			break;
		}
		break;

	case PLAYER_STATE_DIE:
		{
			mResponTime -= dTime;
			if(mResponTime < 0)
			{
				//��������մϴ�.
				while(1)
				{
					float x = rand() % (GGameMap->GetWidth() * 64);
					float y = rand() % (GGameMap->GetHeight() * 64);
					if(CouldGoPosition(Point(x,y)) == true)
					{
						mPosition = Point(x,y);
						break;
					}
				}
				SetHP(100);
				TransState(PLAYER_STATE_IDLE);
				break;
			}
		}
		break;
	case PLAYER_STATE_TYPESKILL:
		{
			TransState(PLAYER_STATE_IDLE);
			break;
		}
		break;
	case PLAYER_STATE_USERSKILL:
		{
			TransState(PLAYER_STATE_IDLE);
			break;
		}
		break;
	default:
		break;
	}
}
void Player::Damaged(int damage)
{
	if(mHP < damage)
	{
		//�׾�����
		GGameManager->DiePlayer(mTeam);
		TransState(PLAYER_STATE_DIE);
	}
	else
	{
		mHP-=damage;
		//���� �� �󸶶�� ��ε�ĳ����
		HPUpdateResult outPacket = HPUpdateResult();
		outPacket.mPlayerId = mPlayerId;
		outPacket.mHP = mHP;
		mClient->Broadcast(&outPacket);
	}

}
PlayerInfo Player::GetPlayerInfo()
{
	PlayerInfo mPlayerInfo;
	mPlayerInfo.mGameKeyStates = mGameKeyStates;
	mPlayerInfo.mX = mPosition.x;
	mPlayerInfo.mY = mPosition.y;
	mPlayerInfo.mPlayerId = mPlayerId;
	mPlayerInfo.mAngle = mRotation;
	mPlayerInfo.mPlayerState = mPlayerState;
	mPlayerInfo.mHP = mHP;
	mPlayerInfo.mMoveDirection = mMoveDirection;
	mPlayerInfo.mTeam = mTeam;
	return mPlayerInfo;
}

bool Player::CouldGoPosition(Point position)
{
	for( int x = (position.x - mRadius)/64; x <= (position.x + mRadius)/64; x += 1 )//64 = tilesize
	{
		for( int y = (position.y - mRadius)/64; y <= (position.y + mRadius)/64; y += 1 )//64 = tilesize
		{
			if ( GGameMap->isValidTile(Point(x*64,y*64)) == false)
				return false;
		}
	}	
	std::map<int,Player*> players = GPlayerManager->GetPlayers();
	for( std::map<int,Player*>::iterator it = players.begin(); it != players.end(); ++it ) 
	{
		Player* enemy = it->second;
		if(enemy == this)continue;

		if( Point().GetDistance( enemy->GetPosition(), position ) < mRadius*2 )
		{
			return false;
		}
	}
	return true;
}