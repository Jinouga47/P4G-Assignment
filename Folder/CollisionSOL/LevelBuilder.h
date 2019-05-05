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
#include "ListT.h"
#include <array>
class LevelBuilder
{
public:
	//float cubeX[10];
	//float cubeY[10];
	//Model mCube;
	Model mCubes[150];
	CubeClass cubies;
	CubeClass cubiesArray[150];

	List<CubeClass> cubiesArray2;
	List<Model> mCubes2;
	//int test[3][2] = { {0,0},{1,0},{2,0} };
	//Vector2 test2[3] = { Vector2(1,1), Vector2(1,2), Vector2(1,3) };
	void Initialise(MeshManager& mgr);//, int levelSize);
	int Size();
	void Render(FX::MyFX& fx);//, int levelSize);
	Model GetCubes(int i);
	void Collision(PlayerControl&);
	void LevelLoad(PlayerControl&, int);
private:
	int size_;
	Mesh *p;
	struct Level
	{
		//int level;
		List<int> x;
		List<int> y;
	};
	List<int> Level_x;
	List<int> Level_y;

	
};
#endif