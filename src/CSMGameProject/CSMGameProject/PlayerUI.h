
#pragma once

#include "NNObject.h"
#include "NNSprite.h"
#include "NNLabel.h"

enum TeamColor
{
	RED = 0,
	BLUE = 1
};
class PlayerUI : public NNObject
{
public:
	PlayerUI();
	virtual ~PlayerUI();

	void Init();
	void Render();
	void Update( float dTime );

	void SetHP(int hp) { mHp = hp; }
	void SetTeam(int team) { mTeam = team; }

	NNCREATE_FUNC(PlayerUI);
private:
	NNSprite* mHpBar[2];
	NNSprite* mHpBarFrame;
	int mHp;
	int mTeam;
};