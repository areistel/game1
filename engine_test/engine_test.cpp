// engine_test.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "Gosu/Gosu.hpp"
#include "Gosu/Autolink.hpp"
using namespace std;

const int Window_size_x = 1000;
const int Window_size_y = 800;


class Motorrad  {

public:
	double x_taste = 500;
	double x_moto;

};

class GameWindow : public Gosu::Window {
public:
	
	Gosu::Image bild;
	GameWindow()
		: Window(Window_size_x, Window_size_y)
		, bild("scrambler_021-01.png")
	{

		set_caption("Nices Game");
	}
	void update() override;
	void draw() override;
	
	
	Motorrad m1;	

	
};





void GameWindow::update() {


	if (m1.x_taste <= 960 && m1.x_taste >= 40)		//x_moto aktualisieren
	{
		m1.x_moto = m1.x_taste;
	}

	if (m1.x_taste < 960 && m1.x_taste < 40)		//linksseitige sperre
	{
		m1.x_moto = 40;
		m1.x_taste = 40;
	}

	if (m1.x_taste > 960 && m1.x_taste > 40)		//rechtsseitige sperre
	{
		m1.x_moto = 960;
		m1.x_taste = 960;
	}

	if (input().down(Gosu::KB_LEFT) == 1)			//input linke pfeiltaste
	{
		m1.x_taste = m1.x_taste - 5;
	}
	if (input().down(Gosu::KB_RIGHT) == 1)			//input rechte pfeiltaste
	{
		m1.x_taste = m1.x_taste + 5;
	}
}

void GameWindow::draw() {


	bild.draw_rot(									//bild erstellen mit entsprechenden koordinaten
		m1.x_moto, Window_size_y-90,
		0,
		0,
		0.5,
		0.5,
		0.15, 0.15

	);

}


int main() {



GameWindow window;
window.show();

}
