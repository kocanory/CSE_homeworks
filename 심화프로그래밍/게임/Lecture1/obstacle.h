#pragma once

#include "plane.h"
#include "Game2D.h"

namespace lsh
{
	class obstacle : public Game2D
	{

	private:


	public:
		vec2 center1 = vec2(1.72f, -0.3f);
		vec2 center2 = vec2(-1.72f, 0.2f);
		vec2 center3 = vec2(1.72f, 0.7f);
		vec2 center4 = vec2(1.72f, -0.3f);
		vec2 center5 = vec2(-1.72f, 0.2f);
		vec2 vel1 = vec2(0.1f, 0.0f);
		vec2 vel2 = vec2(-0.1f, 0.0f);
		vec2 vel3 = vec2(0.1f, -0.02f);
		vec2 vel4 = vec2(-0.1f, 0.04f);
		void circle(vec2 a);
		void obastacle(int n);
	};
}

void lsh::obstacle::circle(vec2 a)
{
		beginTransformation();
		{
			translate(a);
			drawFilledCircle(Colors::red, 0.05f);			
		}
		endTransformation();
}

void lsh::obstacle::obastacle(int n)
{	
	if (n == 1)
	{
		circle(center1);
	}

	if (n == 2)
	{		
		circle(center1);
		circle(center2);
	}

	if (n == 3)
	{
		circle(center1);
		circle(center2);
		circle(center3);
	}

	if (n == 4)
	{
		circle(center1);
		circle(center2);
		circle(center4);
	}

	if (n == 5)
	{
		circle(center1);
		circle(center2);
		circle(center5);
	}

	if (n == 6)
	{
		circle(center1);
		circle(center3);
		circle(center4);
		circle(center5);
	}
}