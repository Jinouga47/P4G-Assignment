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
class LevelBuilder
{
public:
	//float cubeX[10];
	//float cubeY[10];
	Model mCube;
	Model mCubes[125];
	CubeClass cubies;
	//int test[3][2] = { {0,0},{1,0},{2,0} };
	//Vector2 test2[3] = { Vector2(1,1), Vector2(1,2), Vector2(1,3) };
	void Initialise(MeshManager& mgr);//, int levelSize);
	int Size();
	void Render(FX::MyFX& fx);//, int levelSize);
	Model GetCubes(int i);
private:
	int size_;
};
#endif