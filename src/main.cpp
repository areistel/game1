
#include "Gosu/Gosu.hpp"
#include "Gosu/AutoLink.hpp"
#include <iostream>
#include <vector>
using namespace std;

const int Window_size_x = 800;
const int Window_size_y = 1000;


//#################### Streifen ####################
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
			      1  	       	//z,

			      );
  }
};




//####################  Motorad  ####################

class Motorrad  {

public:
  double x_taste = 500;
  double x_moto;
  double rot_moto = 0;

};





//#################### Autos ####################
// Klasse für die Autos, mit Funktion für Setzen und Rückgabe der X und Y-Werte
class Autos {				
private:
  double x_Pos;
  double y_Pos;

public:
  double getX() {
    return x_Pos;
  }

  double getY() {
    return y_Pos;
  }

  void setX(double x) {
    x_Pos = x;
  }

  void setY(double y) {
    y_Pos = y;
  }
};






vector<Autos> verkehr(vector<Autos> verkehr, int speed) {

  Autos a;
  if (verkehr.size() < 3) {

    // Random Funktion nochmal überarbeiten Reistel!!! Passt noch nicht ganz
    a.setX((Gosu::random(2.0,7.0)) * 100);
    // Hier dasselbe nochmal 
    a.setY(Gosu::random(-400, 0.0));
    
    verkehr.push_back(a);
  }	

  
  for (int i = 0; i < verkehr.size(); i++)		// Autos nach unten bewegen
    {
      verkehr.at(i).setY((verkehr.at(i).getY() + speed));		
    }

  if (verkehr.front().getY() > Window_size_y) {	

    for (int i = 0; i < verkehr.size() - 2; i++)
      {
	verkehr.at(i) = verkehr.at(i + 1);
      }

    verkehr.pop_back();
    verkehr.pop_back();
  }

	

  return verkehr;
}




//#################### GameWindow ####################

class GameWindow : public Gosu::Window {
private:
  vector<Streifen> streifenliste;

  int speed = 5;

  Gosu::Image scrambler;
  Gosu::Image auto1;
  Gosu::Image hintergrundbild;

  Motorrad m1;	
  vector<Autos> gegenverkehr;

  
public:
  GameWindow();
	
  void update() override;
  void draw() override;
	
};


GameWindow::GameWindow() : Window(Window_size_x, Window_size_y)
	       , scrambler("media/bike.png")
	       , auto1("media/auto.png")
	       , hintergrundbild("media/strasse.png")
  {
    set_caption("Hot engine");


    //create primitive Streifen
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
  }






void GameWindow::update() {

  //Streifen animation
  for (auto it = streifenliste.begin(); it != streifenliste.end(); it++) {
    it->Streifen_ol_y = it->Streifen_ol_y + 5;
    if (it->Streifen_ol_y > Window_size_y) {
      it->Streifen_ol_y = -250;
    }
  }

  
		
  //Auto animation
  gegenverkehr = verkehr(gegenverkehr, speed);		// Vektor der die Autos speichert





  
  
  //Motorbike animation
  int x_verschiebung = 60;


  //x_moto aktualisieren
  if (m1.x_taste <= Window_size_x - x_verschiebung && m1.x_taste >= x_verschiebung)	
    {
      m1.x_moto = m1.x_taste;
    }

  //linksseitige sperre
  if (m1.x_taste < Window_size_x- x_verschiebung && m1.x_taste < x_verschiebung)	
    {
      m1.x_moto = x_verschiebung;
      m1.x_taste = x_verschiebung;
    }

  //rechtsseitige sperre
  if (m1.x_taste > Window_size_x- x_verschiebung && m1.x_taste > x_verschiebung)		
    {
      m1.x_moto = Window_size_x- x_verschiebung;
      m1.x_taste = Window_size_x- x_verschiebung;
    }


  


  //Tasten auswerten (control motorbike)
  
  //input linke pfeiltaste
  if (input().down(Gosu::KB_LEFT) == 1)		
    {
      m1.x_taste = m1.x_taste - 7;
      m1.rot_moto = -5;
    }
  
  //zurücksetzen winkel
  if (input().down(Gosu::KB_LEFT) == 0 && input().down(Gosu::KB_RIGHT) == 0)			
    {
      m1.rot_moto = 0;
    }
  
  //input rechte pfeiltaste
  if (input().down(Gosu::KB_RIGHT) == 1)		
    {
      m1.x_taste = m1.x_taste + 7;
      m1.rot_moto = 5;
    }

}





void GameWindow::draw() {

  //bild erstellen mit entsprechenden koordinaten

  //Motorad z = 2; scale = 0.2
  scrambler.draw_rot(	
		     m1.x_moto, Window_size_y-100,
		     2,
		     m1.rot_moto,
		     0.5,
		     0.5,
		     0.2, 0.2
			);

  //strasse z = 0; scale = 1
  hintergrundbild.draw(
		       0, 0
		       , 0,
		       1, 1
		       );

  //draw streifen
  for (auto it = streifenliste.begin(); it != streifenliste.end(); it++) {
    it->draw();
  }



  //draw Autos
  Autos a;
  for (int i = 0; i < gegenverkehr.size(); i++)			// Zeichnen der Autos
    {
      a = gegenverkehr.at(i);
      auto1.draw_rot(a.getX(), a.getY(), 1.0, 0.0, 0.5, 0.0, 1.0, 1.0);


    }

}




//#################### main ####################

int main() {

  GameWindow window;
  window.show();

  return 0;

}
