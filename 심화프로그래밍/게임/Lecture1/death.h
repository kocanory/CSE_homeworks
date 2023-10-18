#pragma once

#include "Game2D.h"

namespace lsh
{
	class death : public Game2D
	{
	public:
		vec2 center = vec2(0.0f, -1.00f);
		void draw();
	};
}

void lsh::death::draw()
{
	beginTransformation();
	{
		translate(center);
		drawFilledBox(Colors::gray, 1.0f, 0.1f);		
	}
	endTransformation();
}
