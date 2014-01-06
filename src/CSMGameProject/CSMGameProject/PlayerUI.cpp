
#include "PlayerUI.h"
#include "Player.h"
#include "NNApplication.h"
#include "PlayerManager.h"
#include "NNInputSystem.h"
#include "EffectManager.h"

#include "EmoticonEffect.h"

PlayerUI::PlayerUI()
{
}

PlayerUI::~PlayerUI()
{
}

void PlayerUI::Init()
{
	float width = (float)NNApplication::GetInstance()->GetScreenWidth();
	float height = (float)NNApplication::GetInstance()->GetScreenHeight();

	mHpBar[BLUE] = NNSprite::Create( L"Resource/Sprite/UI/GameUI/BlueHpBar.png" );
	mHpBar[RED] = NNSprite::Create(L"Resource/Sprite/UI/GameUI/RedHpBar.png");

	mHpBar[BLUE]->SetPosition( 0.f, -40.f );
	mHpBar[RED]->SetPosition( 0.f, -40.f );

	wsprintf(mNicknameBuf, L"NICKNAME");
	mNickname = NNLabel::Create(mNicknameBuf, L"���� ���", 10.f);
	mNickname->SetPosition(0.f, -50.f);

	AddChild(mHpBar[BLUE]);
	AddChild(mHpBar[RED]);
	AddChild(mNickname, 99);

	SetCenter( mHpBar[BLUE]->GetImageWidth()/2.f, mHpBar[BLUE]->GetImageHeight()/2.f );
}

void PlayerUI::Render()
{
	NNObject::Render();
}

void PlayerUI::Update( float dTime )
{
	NNObject::Update( dTime );

	mHpBar[BLUE]->SetVisible(false);
	mHpBar[RED]->SetVisible(false);

	TeamColor result = (TeamColor)(dynamic_cast<CPlayer*>(GetParent())->GetTeam());
	
	mHpBar[result]->SetVisible(true);
	mHpBar[result]->SetScale(mHp / 50.f, 1.f);

	

}