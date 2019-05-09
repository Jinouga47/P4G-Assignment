//#pragma once
#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "Mesh.h"
#include "Model.h"
#include "Input.h"
#include "FX.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "CubeClass.h"
#include "PlayerControl.h"
#include "Key.h"
#include "Door.h"
#include "Enemy.h"
class LevelManager
{
public:
	Model mCubes[160];
	CubeClass cubies;
	CubeClass cubiesArray[160];

	void Initialise(MeshManager& mgr);
	int GetGameState();
	//void LevelLoad(PlayerControl & player, Key & key, Door & door, Enemy & enemy1, Enemy & enemy2, Enemy & enemy3, int level, vector<Vector3>& playerPosList);
	void Render(FX::MyFX& fx);
	Model GetCubes(int i);
	void Update(PlayerControl&, Key&, Door&, Enemy&, Enemy&, Enemy&, int, std::vector<DirectX::SimpleMath::Vector3>* playerPosList);
	void LevelLoad(PlayerControl&, Key&, Door&, Enemy&, Enemy&, Enemy&, int, std::vector<DirectX::SimpleMath::Vector3>* playerPosList);
private:
	int size_;
	Mesh *cubeMesh, *sphereMesh;
	int enemyDelay = 350;
	int gameState;
	DirectX::SimpleMath::Vector3 startPos;
};
#endif