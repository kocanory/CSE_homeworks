#pragma once

#include "Game2D.h"

namespace lsh
{
	class goal : public Game2D
	{

	private:
		float time = 0;
	public:
		vec2 center = vec2(1.0f, 0.90f);
		vec2 center2 = vec2(-1.0f, 0.90f);
		vec2 circle1 = vec2(0.125f, 0.90f);
		vec2 circle2 = vec2(-0.125f, 0.90f);

		void draw(RGB rgb);
		void star();
	};
}

void lsh::goal::draw(RGB rgb)
{
	beginTransformation();
	{
		translate(center);
		drawFilledBox(rgb, 1.7f, 0.01f); 
	}
	endTransformation();

	beginTransformation();
	{
		translate(center2);
		drawFilledBox(rgb, 1.7f, 0.01f);
	}
	endTransformation();

	beginTransformation();
	{
		translate(circle1);
		drawFilledCircle(Colors::yellow, 0.023f);
	}
	endTransformation();

	beginTransformation();
	{
		translate(circle2);
		drawFilledCircle(Colors::yellow, -0.023f);
	}
	endTransformation();
}

void lsh::goal::star()
{
	for (int i = 0; i < 13; i++)
	{
		beginTransformation();
		{
			translate(i * 0.15f, 0.98f);
			rotate(time * 30.0f);
			drawFilledStar(Colors::yellow, 0.07f, 0.035f);	
		}
		endTransformation();
	}
	for (int i = 0; i < 13; i++)
	{
		beginTransformation();
		{
			translate(-i * 0.15f, 0.98f);
			rotate(time * 30.0f);
			drawFilledStar(Colors::yellow, 0.07f, 0.035f);
		}
		endTransformation();
	}

	time += this->getTimeStep();
}
