//#pragma once
#ifndef CUBECLASS_H
#define CUBECLASS_H

#include "Mesh.h"
#include "Model.h"
#include "Input.h"
#include "FX.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "PlayerControl.h"
class CubeClass
{
public:
	Model mCube;
	Model mCubes[100];
	void Initialise(Mesh& mesh, float x, float y);
	Model GetCube();
	
	bool CollisionCheck(/*Model&*/PlayerControl& player);
	bool CollisionManager(/*Model&*/PlayerControl& player);
private:
	float y, x;
};
#endif
