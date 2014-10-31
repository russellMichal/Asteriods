#include "Bullit.h"
	//constructor
	Bullit :: Bullit(float xx, float yy,int dir,int ww, int hh){
		setHealth(1);
		setDirectionGoing(dir);
		setSpeed(30);
		setNumOfVertices(3);
		setDistance(0);
		width = 50;
		height = 50;
		setXPos((xx+ww/2-width/2)-(xx+ww/2));
		setYPos((yy+hh+height+10)-(yy+hh/2));
		float dist=sqrt(pow(getXPos(),2)+pow(getYPos(),2));
		setXPos(xx+ww/2-width/2+dist*cos(getDirectionGoing()*PI/180));
		setYPos(yy+hh/2-height/2+dist*sin(getDirectionGoing()*PI/180));
		x=xx;
		y=yy;
		w=ww;
		h=hh;
		setNumOfVertices(3);

		//define the bullit
		vertices[0] = getXPos();	//left x
		vertices[1] = getYPos();	//left y
		
		vertices[2] = getXPos()+width;		//right x
		vertices[3] = getYPos();		//right y
		
		vertices[4] = getXPos()+width/2;	//top x
		vertices[5] = getYPos()+height;		//top y
	}
	//destructor
	Bullit::~Bullit(){}

	//methods
	int Bullit:: getDistance(){
		return Distance;
	}
	void Bullit:: setDistance(int newDistance){
		Distance=newDistance;
	}
	float Bullit:: getX(){
		return x;
	}
	void Bullit:: setX(float newX){
		x=newX;
	}
	float Bullit:: getY(){
		return y;
	}
	void Bullit:: setY(float newY){
		y=newY;
	}
	int Bullit:: getW(){
		return w;
	}
	void Bullit:: setW(int newW){
		w=newW;
	}
	int Bullit:: getH(){
		return h;
	}
	void Bullit:: setH(int newH){
		h=newH;
	}
	void Bullit:: setVertices(){
		//redefine the ship with rap around
		if(getXPos()<0-width)
			setXPos(2000);

		else if(getXPos()>2000 && isAlive())
			setXPos(0-width);

		if(getYPos()<0-height)
			setYPos(2000);

		else if(getYPos()>2000 && isAlive())
			setYPos(0-height);

		vertices[0] = getXPos();	//left x
		vertices[1] = getYPos();	//left y
		
		vertices[2] = getXPos()+width;		//right x
		vertices[3] = getYPos();		//right y
		
		vertices[4] = getXPos()+width/2;	//top x
		vertices[5] = getYPos()+height;		//top y
	}
	void Bullit:: move(){
		setXPos(getXPos()+getSpeed()*cos(getDirectionGoing()*PI/180));
		setYPos(getYPos()+getSpeed()*sin(getDirectionGoing()*PI/180));

		//glTranslatef(getX()+getW()/2,getY()+getH()/2,0.0);
		//glRotatef(getDirectionGoing()-90,0.0,0.0,1.0);
		//glTranslatef(-getX()-getW()/2,-getY()-getH()/2,0.0);

		//setYPos(getYPos()+getSpeed());

		setDistance(getDistance()+getSpeed());
		if(getDistance()>=1000){
			setAlive(false);
			setXPos(3000);
			setYPos(3000);
		}
		setVertices();

		glTranslatef(getXPos()+width/2,getYPos()+height/2,0.0);
		glRotatef(getDirectionGoing()-90,0.0,0.0,1.0);
		glTranslatef(-getXPos()-width/2,-getYPos()-height/2,0.0);
	}
	char Bullit:: objectIs(){
		return 'b';
	}
