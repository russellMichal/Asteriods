#include "GameObject.h"

		//constructor
		GameObject::GameObject(){
			alive = true;
		}
		//destructor
		GameObject::~GameObject(){}

		//methods
		bool GameObject:: isAlive(){
			return alive;
		}
		void GameObject:: setAlive(bool newAlive){
			alive = newAlive;
		}
		int GameObject:: getXPos(){
			return xPos;
		}
		void GameObject:: setXPos(float newXPos){
			xPos = newXPos;
		}
		int GameObject:: getYPos(){
			return yPos;
		}
		void GameObject:: setYPos(float newYPos){
			yPos = newYPos;
		}
		void GameObject:: setSpeed(int newSpeed){
			speed = newSpeed;
		}
		int GameObject:: getSpeed(){
			return speed;
		}
		void GameObject:: setHealth(int newHealth){
			health = newHealth;
		}
		int GameObject:: getHealth(){
			return health;
		}
		int GameObject:: getDamage(){
			return damage;
		}
		void GameObject:: setDamage(int newDamage){
			damage = newDamage;
		}
		int GameObject:: getDirection(){
			return direction;
		}
		void GameObject:: setDirection(int newDirection){
			direction = newDirection;
		}
		int GameObject:: getDirectionGoing(){
			return directionGoing;
		}
		void GameObject:: setDirectionGoing(int newDirectionGoing){
			directionGoing = newDirectionGoing;
		}
		int GameObject:: getNumOfVertices(){
			return numofVertices;
		}
		void GameObject:: setNumOfVertices(int numVer){
			numofVertices = numVer;
		}
		float GameObject:: getSpeedDecay(){
			return 0;
		}
		void GameObject:: move(){}
		int GameObject:: getDistance(){}
