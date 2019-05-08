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
	Model mCubes[150];
	Model mPlayer, mEnemy_1, mEnemy_2, mEnemy_3, mKey, mDoor;
	CubeClass cubies;
	CubeClass cubiesArray[150];

	void Initialise(MeshManager& mgr);
	int Size();
	void Render(FX::MyFX& fx);
	Model GetCubes(int i);
	void Update(PlayerControl&, Key&, Door&, int);
	void LevelLoad(PlayerControl&, Key&, Door&, int);
private:
	int size_;
	Mesh *cubeMesh, *sphereMesh;
	int enemyDelay = 350;
};
#endif