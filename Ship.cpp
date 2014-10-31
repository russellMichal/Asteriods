#include "Ship.h"
	//constructor
	Ship :: Ship(){
		setAlive(true);
		setHealth(100);
		setDirection(90);
		setSpeed(0);
		setXPos(1000);
		setYPos(1000);
		setNumOfVertices(3);
		setSpeedDecay(.95);
		width = 150;
		height = 150;



		//define the ship
		vertices[0] = getXPos();	//left x
		vertices[1] = getYPos();	//left y
		
		vertices[2] = getXPos()+width;		//right x
		vertices[3] = getYPos();		//right y
		
		vertices[4] = getXPos()+width/2;	//top x
		vertices[5] = getYPos()+height;		//top y
	}
	//destructor
	Ship::~Ship(){}

	//methods
	float Ship:: getSpeedDecay(){
		return speedDecay;
	}
	void Ship:: setSpeedDecay(float newSpeedDecay){
		speedDecay=newSpeedDecay;
	}
	void Ship:: setVertices(){
		//redefine the ship with rap around
		if(getXPos()<0-width)
			setXPos(2000);

		else if(getXPos()>2000)
			setXPos(0-width);

		if(getYPos()<0-height)
			setYPos(2000);

		else if(getYPos()>2000)
			setYPos(0-height);

		vertices[0] = getXPos();	//left x
		vertices[1] = getYPos();	//left y
		
		vertices[2] = getXPos()+width;		//right x
		vertices[3] = getYPos();		//right y
		
		vertices[4] = getXPos()+width/2;	//top x
		vertices[5] = getYPos()+height;		//top y
	}
	void Ship:: move(){

	}
	char Ship:: objectIs(){
		return 's';
	}
