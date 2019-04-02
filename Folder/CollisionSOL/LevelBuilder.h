//#pragma once
#ifndef LEVELBUILDER_H
#define LEVELBUILDER_H

#include "Mesh.h"
#include "Model.h"
#include "Input.h"
#include "FX.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
class LevelBuilder
{
public:
	Model mCube;
	void Initialise(MeshManager& mgr);
	void Render(FX::MyFX& fx);
	void Start();
private:
	struct cube {
		int x, y;
		Model model;
	};
	cube test;
	std::vector<cube> mCubes;
};
#endif