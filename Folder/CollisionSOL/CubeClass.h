//#pragma once
#ifndef CUBECLASS_H
#define CUBECLASS_H

#include "Mesh.h"
#include "Model.h"
#include "Input.h"
#include "FX.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
class CubeClass
{
public:
	Model mCube;
	Model mCubes[100];
	void Initialise(Mesh& mesh, float x, float y);
	Model GetCube();
private:

};
#endif
