#ifndef GameObject_H   // if x.h hasn't been included yet...	header guards!!
#define GameObject_H   // #define this so the compiler knows it has been included

#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <cmath>	//needed for sin and cos
#define PI 3.14159265	//needed for converting form degrees to radians

using namespace std;
class GameObject
{
	public:
		//constructor
		GameObject();


		//destructor
		virtual ~GameObject();

		//prototypes
		bool isAlive();
		void setAlive(bool);
		int getXPos();
		void setXPos(float);
		int getYPos();
		void setYPos(float);
		void setSpeed(int);
		int getSpeed();
		void setHealth(int);
		int getHealth();
		int getDamage();
		void setDamage(int);
		int getDirection();
		void setDirection(int);
		int getDirectionGoing();
		void setDirectionGoing(int);
		int getNumOfVertices();
		void setNumOfVertices(int);
		virtual void setVertices()=0;
		virtual char objectIs()=0;
		virtual void move();
		virtual float getSpeedDecay();
		virtual int getDistance();

		int vertices[24];//for drawing the object
		
		//these are for testing 
		int width;
		int height;

		//variables
	protected:
		//variables
		bool alive;
		float xPos;
		float yPos;
		int speed;
		int health;
		int damage;
		int direction;
		int directionGoing;
		int numofVertices;
};
#endif	//for header guard
