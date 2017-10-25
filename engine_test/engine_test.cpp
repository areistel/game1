// engine_test.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "Gosu/Gosu.hpp"
#include "Gosu/Autolink.hpp"
using namespace std;

const int Window_size_x = 640;
const int Window_size_y = 480;

class GameWindow : public Gosu::Window {
public:
	
	Gosu::Image bild;
	GameWindow()
		: Window(Window_size_x, Window_size_y)
		, bild("scrambler_021-01.png")
	{
		set_caption("Gosu Tutorial Game");
	}
	
	double x_mouse;		//unnötig?
	double y_mouse;
	double x_moto;
	double y;
	bool mlinks = 0;
	

	void update() override {

		x_mouse = input().mouse_x();
		y_mouse = input().mouse_y();

		mlinks = input().down(Gosu::MS_LEFT);

		/*x = (x + 1) % 300;
		y = (y + 1) % 300;*/

	}
	void draw() override {
		if (mlinks == true)
		{
			Gosu::Graphics::draw_triangle(
				x_mouse, y_mouse, Gosu::Color::RED,
				200 - x_mouse, 100 + y_mouse, Gosu::Color::GREEN,
				200 + x_mouse, 400 - y_mouse, Gosu::Color::BLUE,
				0.0
			);
		}


		if (x_mouse <= 625 && x_mouse >= 25)
		{
			x_moto = x_mouse;
		}
		
		if (x_mouse < 625 && x_mouse < 25)
		{
			x_moto = 25;
		}
		
		if (x_mouse > 625 && x_mouse > 25)
		{
			x_moto = 625;
		}

		bild.draw_rot(
			x_moto, 430,
			0,
			0,
			0.5,
			0.5,
			0.1,0.1		//scale
			
		);
		
		//das is n test

		
	}

	
};


int main() {



GameWindow window;
window.show();

}
