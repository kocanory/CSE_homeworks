#pragma once

#include "Game2D.h"
#include "goal.h"
#include "Colors.h"
#include "start.h"
#include "death.h"
#include "sound.h"
#include "obstacle.h"

namespace lsh
{
	class plane
	{
	public:
		vec2 center = vec2(0.0f, -0.5f);
		//vec2 center2 = vec2(0.0f, -0.5f);

		void draw()
		{
			beginTransformation();
			{
				translate(center);
				drawFilledBox(Colors::pastel, 0.1f, 0.1f); 
				drawLine(Colors::pastel, vec2(-0.05f, -0.049f), Colors::pastel, vec2(-0.1f, -0.049f));
				drawLine(Colors::pastel, vec2(-0.1f, -0.049f), Colors::pastel, vec2(-0.05f, 0.049f));
				drawLine(Colors::pastel, vec2(0.05f, -0.049f), Colors::pastel, vec2(0.1f, -0.049f));
				drawLine(Colors::pastel, vec2(0.1f, -0.049f), Colors::pastel, vec2(0.05f, 0.049f));
				translate(0.0f, 0.155f);
				drawFilledBox(Colors::skyblue, 0.06f, 0.21f); 
				translate(0.0f, 0.12f);
				drawFilledTriangle(Colors::lightblue, 0.05f);  		
			}
			endTransformation();
		}
	};


	class planeGame : public Game2D
	{
	private:
		plane plane;
		goal g;
		start s;
		death d;
		obstacle o;
		RGB color[7] = { Colors::red,Colors::orange, Colors::yellow, Colors::green, Colors::blue,
		Colors::bluishviolet, Colors::purple };
		float gravity;
		int i = 0;
		vec2 door1 = vec2(0.05f, 0.90f);
		vec2 door2 = vec2(-0.05f, 0.90f);
		vec2 boundary1 = vec2(0.05f, 0.90f);
		vec2 boundary2 = vec2(-0.05f, 0.90f);
	public:


		planeGame()
			: Game2D("This is my digital canvas!", 1280, 720, false, 2)
		{
			auto & sound = *SoundEngine_Singleton::getInstance();
			sound.createSound("drumloop.wav", "background", true);
			sound.createSound("missile.mp3", "rocket", false);

			sound.playSound("background");
		}

		~planeGame()
		{

		}

		void goaldoor(RGB rgb)
		{
			beginTransformation();
			{
					if (plane.center.y > 0.05f)
					{
						drawFilledBox(Colors::white, 0.1f, 0.01f);
					}
					else
					{	
						translate(door1);
						drawFilledBox(rgb, 0.1f, 0.01f);
					}
					
			}
			endTransformation();

			beginTransformation();
			{
					
					if (plane.center.y > 0.05f)
					{
						drawFilledBox(Colors::white, 0.1f, 0.01f);
					}

					else
					{
						translate(door2);
						drawFilledBox(rgb, 0.1f, 0.01f);
					}

			}
			endTransformation();
		}
		void Gamestart()
		{
			if(i == 0)
				s.draw(color[i]);
			else
			{
				s.empty();
			}
		}
		void Gamegoal() 
		{
			goaldoor(color[i]);
			g.draw(color[i]);
			g.star();			
		}
		void Gamedeath()
		{
			d.draw();
		}
		void Gravity()
		{
			plane.center.y += gravity * getTimeStep();

			if (i == 0)
				gravity = 0;
			else
				gravity = -0.005f + -0.01f * (i - 1);
		}
		void reset()
		{
			plane.center.x = 0.0f;
			plane.center.y = -0.5f;
		}
		void mousecursor()
		{
			beginTransformation();
			{
				const vec2 mouse = getCursorPos();
				translate(mouse);
				drawFilledCircle(Colors::gold, 0.03f);
			}
			endTransformation();

			if (isMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
			{
				{
					const vec2 mouse = getCursorPos();
					beginTransformation();
					{
						translate(mouse);
						drawFilledCircle(Colors::orange, 0.03f);
					}
					endTransformation();
				}
			}

			if (isMouseButtonPressed(GLFW_MOUSE_BUTTON_2))
			{
				{
					const vec2 mouse = getCursorPos();					
					beginTransformation();
					{
						translate(mouse);
						drawFilledCircle(Colors::orange, 0.03f);
					}
					endTransformation();
				}
			}
		}
		void control()
		{
			auto & sound = *SoundEngine_Singleton::getInstance();
			if (isMouseButtonPressedAndReleased(GLFW_MOUSE_BUTTON_1))
			{
				plane.center.y += 9.0f * getTimeStep();
				sound.stopSound("rocket");
				sound.playSound("rocket");
			}
			if (isMouseButtonPressedAndReleased(GLFW_MOUSE_BUTTON_2))
			{
				plane.center.y += 9.0f * getTimeStep();
				sound.stopSound("rocket");
				sound.playSound("rocket");
			}

			if (isKeyPressedAndReleased(GLFW_KEY_SPACE))

			{
				plane.center.y += 9.0f * getTimeStep();
				sound.stopSound("rocket");
				sound.playSound("rocket");
			}
		}
		
		void aboutY()
		{
			if (plane.center.y > 0.95f)
			{
				++i;
				reset();
				move();
			}

			if (plane.center.y < -1.0f || i > 6)
			{
				exit(1);
			}
		}

		void moveobstacle(int n)
		{
			if (n == 1)
			{
				o.center1 += o.vel2 * getTimeStep();
				if (o.center1.x < -1.72f)
				{
					o.center1 = vec2(1.72f, -0.3f);
					moveobstacle(n);
				}
			}
			if (n == 2)
			{				
				o.center1 += o.vel2 * getTimeStep();
				o.center2 += o.vel1 * getTimeStep();
				if (o.center1.x < -1.72f)
				{
					o.center1 = vec2(1.72f, -0.3f);
					moveobstacle(n);
				}

				if (o.center2.x > 1.72f)
				{
					o.center2 = vec2(-1.72f, 0.2f);
					moveobstacle(n);
				}
			}
			if (n == 3)
			{
				o.center1 += o.vel2 * getTimeStep();
				o.center2 += o.vel1 * getTimeStep();
				o.center3 += o.vel2 * getTimeStep();
				if (o.center1.x < -1.72f)
				{
					o.center1 = vec2(1.72f, -0.3f);
					moveobstacle(n);
				}

				if (o.center2.x > 1.72f)
				{
					o.center2 = vec2(-1.72f, 0.2f);
					moveobstacle(n);
				}

				if (o.center3.x < -1.72f)
				{
					o.center3 = vec2(1.72f, 0.7f);
					moveobstacle(n);
				}
			}

			if (n == 4)
			{
				o.center1 += o.vel2 * getTimeStep();
				o.center2 += o.vel1 * getTimeStep();
				o.center4 += o.vel4 * getTimeStep();
				if (o.center1.x < -1.72f)
				{
					o.center1 = vec2(1.72f, -0.3f);
					moveobstacle(n);
				}

				if (o.center2.x > 1.72f)
				{
					o.center2 = vec2(-1.72f, 0.2f);
					moveobstacle(n);
				}
				if (o.center4.x < -1.72f)
				{
					o.center4 = vec2(1.72f, -0.3f);
					moveobstacle(n);
				}
			}
			if (n == 5)
			{
				o.center1 += o.vel2 * getTimeStep();
				o.center2 += o.vel1 * getTimeStep();
				o.center5 += o.vel3 * getTimeStep();
				if (o.center1.x < -1.72f)
				{
					o.center1 = vec2(1.72f, -0.3f);
					moveobstacle(n);
				}

				if (o.center2.x > 1.72f)
				{
					o.center2 = vec2(-1.72f, 0.2f);
					moveobstacle(n);
				}
				if (o.center5.x > 1.72f)
				{
					o.center5 = vec2(-1.72f, 0.2f);
					moveobstacle(n);
				}
			}
			if (n == 6)
			{
				o.center1 += o.vel2 * getTimeStep();
				o.center3 += o.vel2 * getTimeStep();
				o.center4 += o.vel4 * getTimeStep();
				o.center5 += o.vel3 * getTimeStep();
				if (o.center1.x < -1.72f)
				{
					o.center1 = vec2(1.72f, -0.3f);
					moveobstacle(n);
				}

				if (o.center3.x < -1.72f)
				{
					o.center3 = vec2(1.72f, 0.7f);
					moveobstacle(n);
				}
				if (o.center4.x < -1.72f)
				{
					o.center4 = vec2(1.72f, -0.3f);
					moveobstacle(n);
				}
				if (o.center5.x > 1.72f)
				{
					o.center5 = vec2(-1.72f, 0.2f);
					moveobstacle(n);
				}
			}
		}

		void damage(int n)
		{
			switch (n)
			{
			case 1:
				if ((((plane.center.x - o.center1.x) > -0.05f) && ((plane.center.x - o.center1.x) < -0.04f)) && ((o.center1.y > plane.center.y - 0.08f) && (o.center1.y < plane.center.y + 0.08f)))
					exit(1);
			case 2:
				if ((((plane.center.x - o.center1.x) > -0.05f) && ((plane.center.x - o.center1.x) < -0.04f)) && ((o.center1.y > plane.center.y - 0.08f) && (o.center1.y < plane.center.y + 0.08f)))
					exit(1);				
				if ((((plane.center.x - o.center2.x) < 0.05f) && ((plane.center.x - o.center2.x) > 0.04f)) && ((o.center2.y > plane.center.y - 0.08f) && (o.center2.y < plane.center.y + 0.08f)))
					exit(1);
			case 3:
				if ((((plane.center.x - o.center1.x) > -0.05f) && ((plane.center.x - o.center1.x) < -0.04f)) && ((o.center1.y > plane.center.y - 0.08f) && (o.center1.y < plane.center.y + 0.08f)))
					exit(1);
				if ((((plane.center.x - o.center2.x) < 0.05f) && ((plane.center.x - o.center2.x) > 0.04f)) && ((o.center2.y > plane.center.y - 0.08f) && (o.center2.y < plane.center.y + 0.08f)))
					exit(1);
				if ((((plane.center.x - o.center3.x) > -0.05f) && ((plane.center.x - o.center3.x) < -0.04f)) && ((o.center3.y > plane.center.y - 0.08f) && (o.center3.y < plane.center.y + 0.08f)))
					exit(1);
			case 4:
				if ((((plane.center.x - o.center1.x) > -0.05f) && ((plane.center.x - o.center1.x) < -0.04f)) && ((o.center1.y > plane.center.y - 0.08f) && (o.center1.y < plane.center.y + 0.08f)))
					exit(1);
			case 5:
				if ((((plane.center.x - o.center1.x) > -0.05f) && ((plane.center.x - o.center1.x) < -0.04f)) && ((o.center1.y > plane.center.y - 0.08f) && (o.center1.y < plane.center.y + 0.08f)))
					exit(1);
				if ((((plane.center.x - o.center2.x) < 0.05f) && ((plane.center.x - o.center2.x) > 0.04f)) && ((o.center2.y > plane.center.y - 0.08f) && (o.center2.y < plane.center.y + 0.08f)))
					exit(1);
			case 6:
				if ((((plane.center.x - o.center1.x) > -0.05f) && ((plane.center.x - o.center1.x) < -0.04f)) && ((o.center1.y > plane.center.y - 0.08f) && (o.center1.y < plane.center.y + 0.08f)))
					exit(1);
				if ((((plane.center.x - o.center2.x) < 0.05f) && ((plane.center.x - o.center2.x) > 0.04f)) && ((o.center2.y > plane.center.y - 0.08f) && (o.center2.y < plane.center.y + 0.08f)))
					exit(1);
				if ((((plane.center.x - o.center3.x) > -0.05f) && ((plane.center.x - o.center3.x) < -0.04f)) && ((o.center3.y > plane.center.y - 0.08f) && (o.center3.y < plane.center.y + 0.08f)))
					exit(1);
			}
		}
		void move()	
		{
			Gamestart();
			plane.draw();
			damage(i);
			Gamegoal();
			Gamedeath();
			o.obastacle(i);
			moveobstacle(i);
			Gravity();
			control();
			mousecursor();			
			aboutY();
		}
		void update() override
		{
			move();
		}

	};
}

