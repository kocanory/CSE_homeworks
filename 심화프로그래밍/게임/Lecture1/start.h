#pragma once

#include "Game2D.h"

namespace lsh
{
	class start : public Game2D
	{
	public:
		vec2 center = vec2(0.0f, -0.775f);
		void draw(RGB &rgb);
		void empty();
	};
}

void lsh::start::draw(RGB &rgb)
{
	beginTransformation();
	{		
		translate(center);
		drawFilledBox(rgb, 1.0f, 0.45f); 	
	}
	endTransformation();
}

void lsh::start::empty()
{
	beginTransformation();
	{
		translate(center);
		drawFilledBox(Colors::white, 1.0f, 0.45f);
	}
	endTransformation();
}
