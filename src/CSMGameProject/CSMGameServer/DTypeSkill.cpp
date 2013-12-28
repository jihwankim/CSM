#include "stdafx.h"
#include "DTypeSkill.h"
#include "Bullet.h"
#include "SkillManager.h"
#include "ClientManager.h"
#include "PlayerManager.h"

DTypeSkill::DTypeSkill(float angle, Player* ownerPlayer):mOwnerPlayer(ownerPlayer),mLifeTime(0.3f),mAngle(angle),mDamage(17),mVelocity(700)
{
	GSkillManager->AddSkill(this);
	DTypeSkillShootResult outPacket = DTypeSkillShootResult();
	outPacket.mAngle = mAngle;
	outPacket.mStartPosition =  ownerPlayer->GetPosition();
	outPacket.mPlayerId = ownerPlayer->GetPlayerInfo().mPlayerId;
	GClientManager->BroadcastPacket(nullptr,&outPacket);
}


DTypeSkill::~DTypeSkill(void)
{

}

void DTypeSkill::Update(float dTime)
{
	mLifeTime -= dTime;

	std::map<int,Player*> players = GPlayerManager->GetPlayers();
	for( std::map<int,Player*>::iterator playerIt = players.begin(); playerIt != players.end(); ++playerIt ) 
	{
		Player* enemyPlayer = playerIt->second;
		if( enemyPlayer -> GetTeam() == mOwnerPlayer->GetTeam() ) continue;
		if( Point().Distance( enemyPlayer->GetPosition() , mOwnerPlayer->GetPosition() ) < enemyPlayer->GetRadius() + mOwnerPlayer->GetRadius() + mVelocity * dTime )
		{
			//���߰�
			mLifeTime = -1;
			//������ �ְ�
			enemyPlayer->Damaged(17,mOwnerPlayer);
			//�����ٰ� ��Ŷ �ְ�.
			DTypeSkillEndResult outPacket = DTypeSkillEndResult();
			outPacket.mPlayerId = mOwnerPlayer->GetPlayerInfo().mPlayerId;
			GClientManager->BroadcastPacket(nullptr,&outPacket);
			// ������Ʈ�� ���� ����.
			return;
		}
	}
	
	//�̵�
	if( IsLive() == true)
	{
		if( mOwnerPlayer->CouldGoPosition(mOwnerPlayer->GetPosition() + Point(cos(mAngle),sin(mAngle)) * mVelocity * dTime) )
			mOwnerPlayer->SetPosition(mOwnerPlayer->GetPosition() + Point(cos(mAngle),sin(mAngle)) * mVelocity * dTime);
		else
		{
			//���߰�
			mLifeTime = -1;
			//�����ٰ� ��Ŷ �ְ�.
			DTypeSkillEndResult outPacket = DTypeSkillEndResult();
			outPacket.mPlayerId = mOwnerPlayer->GetPlayerInfo().mPlayerId;
			GClientManager->BroadcastPacket(nullptr,&outPacket);
			// ������Ʈ�� ���� ����.
			return;
		}
	}
}
bool DTypeSkill::IsLive()
{
	if(mLifeTime < 0)
	{
		return false;
	}
	return true;
}