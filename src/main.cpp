// engine_test.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "Gosu/Gosu.hpp"
#include "Gosu/AutoLink.hpp"
#include <iostream>
#include <vector>
using namespace std;

const int Window_size_x = 800;
const int Window_size_y = 1000;
double game_time;
double old_time = game_time - 100;

class Streifen;

vector<Streifen> streifenliste;

class Streifen {
public:
	double Streifen_ol_x = 390;
	double Streifen_ol_y = 20;			//muss verändert werden
	double Streifen_or_x = 410;
	double Streifen_or_y = Streifen_ol_y;
	double Streifen_ul_x = 390;
	double Streifen_ul_y = Streifen_ol_y + 300;
	double Streifen_ur_x = 410;
	double Streifen_ur_y = Streifen_ol_y + 300;

	void draw() {
		Gosu::Graphics::draw_quad(
			Streifen_ol_x,  	//x1,
			Streifen_ol_y, 	//y1,
			Gosu::Color::WHITE,  //c1,
			Streifen_or_x,  	//x2,
			Streifen_ol_y,  	//y2,
			Gosu::Color::WHITE,  //c2,
			Streifen_ur_x,  	//x3,
			Streifen_ol_y + 150, 	//y3,
			Gosu::Color::WHITE,  //c3,
			Streifen_ul_x,  	//x4,
			Streifen_ol_y + 150,  	//y4,
			Gosu::Color::WHITE,  //c4,
			1  					//z,

		);
	}
};


class Motorrad  {

public:
	double x_taste = 500;
	double x_moto;
	double rot_moto = 0;
	

};

//class Autos {				//autos auf 3 pos random generieren
//	public:
//
//		rand_pos
//
//	random_val = rand() % 3 + 1;
//
//	switch (random_val)
//	{
//		1:	
//
//
//	default:
//		break;
//	}
//
//};

class GameWindow : public Gosu::Window {
public:
	
	Gosu::Image scrambler;

	Gosu::Image hintergrundbild;
	GameWindow()
		: Window(Window_size_x, Window_size_y)
		, scrambler("media/bike.png")
		, hintergrundbild("media/road.png")
	{

		set_caption("Hot Engine");
	}
	
	void update() override;
	void draw() override;
	
	
	Motorrad m1;	
};





void GameWindow::update() {
	

	//if (game_time >= old_time +3)
	//{
		for (auto it = streifenliste.begin(); it != streifenliste.end(); it++) {
			it->Streifen_ol_y = it->Streifen_ol_y + 5;
			if (it->Streifen_ol_y > Window_size_y) {
				it->Streifen_ol_y = -250;
			}
		}
		//old_time = game_time;
	//}


	int x_verschiebung = 60;


	if (m1.x_taste <= Window_size_x- x_verschiebung && m1.x_taste >= x_verschiebung)		//x_moto aktualisieren
	{
		m1.x_moto = m1.x_taste;
	}

	if (m1.x_taste < Window_size_x- x_verschiebung && m1.x_taste < x_verschiebung)		//linksseitige sperre
	{
		m1.x_moto = x_verschiebung;
		m1.x_taste = x_verschiebung;
	}

	if (m1.x_taste > Window_size_x- x_verschiebung && m1.x_taste > x_verschiebung)		//rechtsseitige sperre
	{
		m1.x_moto = Window_size_x- x_verschiebung;
		m1.x_taste = Window_size_x- x_verschiebung;
	}

	if (input().down(Gosu::KB_LEFT) == 1)			//input linke pfeiltaste
	{
		m1.x_taste = m1.x_taste - 7;
		m1.rot_moto = -5;
	}
	if (input().down(Gosu::KB_LEFT) == 0 && input().down(Gosu::KB_RIGHT) == 0)			//zurücksetzen winkel
	{
		m1.rot_moto = 0;
	}
	if (input().down(Gosu::KB_RIGHT) == 1)			//input rechte pfeiltaste
	{
		m1.x_taste = m1.x_taste + 7;
		m1.rot_moto = 5;
	}

	game_time += update_interval();
}

void GameWindow::draw() {


	scrambler.draw_rot(									//bild erstellen mit entsprechenden koordinaten
		m1.x_moto, Window_size_y-100,
		2,
		m1.rot_moto,
		0.5,
		0.5,
		0.2, 0.2

	);

	hintergrundbild.draw(
		0, 0
		, 0, 1, 1
	);

	for (auto it = streifenliste.begin(); it != streifenliste.end(); it++) {
		it->draw();

	}

}


int main() {



GameWindow window;

Streifen s1;
s1.Streifen_ol_y = 0;
streifenliste.push_back(s1);
Streifen s2;
s2.Streifen_ol_y = 250;
streifenliste.push_back(s2);
Streifen s3;
s3.Streifen_ol_y = 500;
streifenliste.push_back(s3);
Streifen s4;
s4.Streifen_ol_y = 750;
streifenliste.push_back(s4);
Streifen s5;
s5.Streifen_ol_y = 1000;
streifenliste.push_back(s5);

window.show();



}
