//#pragma once
#ifndef LEVELBUILDER_H
#define LEVELBUILDER_H

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
class LevelBuilder
{
public:
	Model mCubes[150];
	CubeClass cubies;
	CubeClass cubiesArray[150];

	void Initialise(MeshManager& mgr);
	int Size();
	void Render(FX::MyFX& fx);
	Model GetCubes(int i);
	void Collision(PlayerControl&, Key&);
	void LevelLoad(PlayerControl&, Key&, Door&, int);
private:
	int size_;
	Mesh *p;
};
#endif