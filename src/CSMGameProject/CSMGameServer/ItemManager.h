#pragma once
#include "Item.h"
#include "DamageBuff.h"
#include "HPBuff.h"
#include "Flag.h"

#include "Player.h"

#include "List"
#include "Map"

class ItemManager
{
private:
	std::list<Item*> mItems;
	std::list<int> mItemIds;
public:
	ItemManager(void);
	~ItemManager(void);

	void GenerateDamageBuff(int gameId, Point position){ GenerateItem(new DamageBuff(gameId, GenerateItemId(), position)); }
	void GenerateHPBuff(int gameId, Point position){ GenerateItem(new HPBuff(gameId, GenerateItemId(), position)); }
	void GenerateFlag(int gameId, Point position){ GenerateItem(new Flag(gameId, GenerateItemId(), position)); }
	void GenerateItem(Item* item);
	void Update(float dTime); // ĳ����, ������ �Ÿ� Ȯ���ؼ� ������ Get�ϴ°͵� ���⼭. ������ ������°͵� ���⼭

	void RemoveItem(Item* item);

private:
	int GenerateItemId();
};



extern ItemManager* GItemManager;