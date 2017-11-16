
#include "Gosu/Gosu.hpp"
#include "Gosu/AutoLink.hpp"
#include <iostream>
#include <vector>
#include <ctime>

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
  Autos(double x, double y);
  
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


Autos::Autos(double x, double y): x_Pos(x), y_Pos(y)
{
  
}






//#################### GameWindow ####################

class GameWindow : public Gosu::Window {
private:


  Gosu::Image scrambler;
  Gosu::Image auto1;
  Gosu::Image hintergrundbild;

  
  Motorrad m1;
  vector<Streifen> streifenliste;
  vector<Autos*> gegenverkehr;

  
  int speed;
  
public:
  GameWindow();
	
  void update() override;
  void draw() override;
  void updateVerkehr();

  bool overlaps(double x, double y, double w, double h, int b_x, int b_y, int b_w, int b_h);
	
};


GameWindow::GameWindow() : Window(Window_size_x, Window_size_y)
	       , scrambler("media/bike.png")
	       , auto1("media/auto.png")
	       , hintergrundbild("media/strasse.png")
  {
    set_caption("Hot engine");

    speed = 5;
    

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




bool GameWindow::overlaps(double x, double y, double w, double h, int b_x, int b_y, int b_w, int b_h)
{
  int b_l = b_x - (b_w / 2.0);
  int b_r = b_x + (b_w / 2.0);
  int b_t = b_y + (b_h / 2.0);
  int b_b = b_y - (b_h / 2.0);
  
  
  int l = x - (w / 2.0);
  int r = x + (w / 2.0);
  int t = y + (h / 2.0);
  int b = y - (h / 2.0);


  
  
  if(r > b_l && b < b_t && r <= b_r && b >= b_b)
    return true;
  if(l < b_r && b < b_t && l >= b_l && b >= b_b)
    return true;
  if(r > b_l && t > b_b && r < b_r && t <= b_t)
    return true;
  if(l < b_r && t > b_b && l >= b_l && t <= b_t)
    return true;

  return false;
  
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
  updateVerkehr();

  
  
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






void GameWindow::updateVerkehr() {

  //there should be 3 cars on the screen ... 
  if (gegenverkehr.size() < 4) {
    Autos *a;

    bool block = true;
      
    double rand_x = std::rand() % Window_size_x;
    double rand_y = -(std::rand() % 1000);

    while(block){
      block = false;

      rand_x = std::rand() % Window_size_x;
      rand_y = -(std::rand() % 1000);

    
      for(std::vector<Autos*>::iterator au = gegenverkehr.begin(); au != gegenverkehr.end(); ++au) {
	if(overlaps(rand_x, rand_y,  auto1.width(), auto1.height(), (*au)->getX(), (*au)->getY(), auto1.width(), auto1.height()))
	  {
	    block = true;
	    break;
	  }
      }
	
    }

    a = new Autos(rand_x, rand_y); 

      
    gegenverkehr.push_back(a);
  }	

  // Autos nach unten bewegen
  for (int i = 0; i < gegenverkehr.size(); i++)	
    {
      gegenverkehr.at(i)->setY((gegenverkehr.at(i)->getY() + speed));		
    }


  //Autos entfernen die nicht zu sehen sind
  for (auto it = gegenverkehr.begin(); it != gegenverkehr.end(); it++) {
    if((*it)->getY() - (auto1.height() / 2.0) > Window_size_y)
      {
	delete (*it);
	gegenverkehr.erase(it);
	it--;
      }
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
  for (auto it = gegenverkehr.begin(); it != gegenverkehr.end(); it++) {

    //draw auto z = 3; scale = 1
    auto1.draw_rot((*it)->getX(), (*it)->getY(),
		   3,
		   0.0,
		   0.5, 0.5,
		   1.0, 1.0);
  }

}




//#################### main ####################

int main() {

  //randomize the random function
  std::srand(std::time(0));
  
  GameWindow window;
  window.show();

  return 0;

}
