
#pragma once

enum GameState
{
	// ���� �� ��Ȳ ������ ���⼭..
	// Ex) ���� ����, ���� ��, �÷��̾ ��ü������ �����ִ� ���� ��
	READY,
	START,
	END,
};

enum TeamColor;

class GameManager
{
public:
	static GameManager* GetInstance();
	static void ReleaseInstance();

public:
	GameState GetGameState() const { return mGameState; }
	int GetKillScore( TeamColor color ) const { return mKillScore[color]; }

	void SetKillLimit( int limit ) { mKillLimit = limit; }
	void SetKillScore( int* Score ) { mKillScore[0] = Score[0]; mKillScore[1] = Score[1];}

private:
	GameState mGameState;

	int mKillScore[2];
	int mKillLimit;

private:
	GameManager();
	~GameManager();

	static GameManager* mInstance;
};