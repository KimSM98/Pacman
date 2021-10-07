#pragma once
#include "TileMapComponent.h"

enum GameObject
{
	PacDot = 14,
	PowerPallet = 21,
	Player = 28,
	Ghost = 35
};

class PacmanMap : public TileMapComponent
{
public:
	PacmanMap(class Actor* owner, int drawOrder = 100);
	//~PacmanMap();
private:
	void CreateTiles() override;

	class Graph* _Graph;
};
