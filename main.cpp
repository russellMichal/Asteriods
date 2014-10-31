//	This is the main program for the game
/*added movement/drifting its choppy but it works changed ship.cpp xpos ypos hight and width to compancate for window changes to get drift*/

#include"Ship.h"
#include"Asteroid.h"
#include"Bullit.h"

//these are for making the window and such
#include <GL/glut.h> 
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <list>	//list is better then vector for what we are doing
#include <algorithm>	//gives the for_each loop

using namespace std;

#define W_HEIGHT 800 //window dimensions changed to see ship drift
#define W_WIDTH 900

#define FRAMERATE 80	//how often the game is updated is milliseconds

//prototypes
void drawGameObject(GameObject*);
void keyOperations(GameObject*);
void moveAsteroid(GameObject*);
void collision(GameObject*);
void move(GameObject*);
bool sat(GameObject*, GameObject*);
bool pnpoly(GameObject*,int,int);

list<GameObject*> GameObjectList;

bool* keyStates = new bool[256]; // Create an array of boolean values of length 256 (0-255) for key operations

static bool dead (GameObject* value) { if(!value->isAlive()){delete value; return true; }else return false;}	//check if a object is alive or not
//put things to initialize here before the game starts
void init(){

	//<<<<<<<<graphics stuff>>>>>>>>>>>>>>>>>>
	glClearColor(0.0,0.0,0.0,0.0);	//bgcolor is black
	glColor3f(1.0f,1.0f,1.0f);		//drawing color is white
	glLineWidth(2.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D((GLdouble)0.0,(GLdouble)2000.0,(GLdouble)0.0,(GLdouble)2000.0);   //changed to get drift
	glViewport(0,0,W_WIDTH,W_HEIGHT);
	glPushMatrix();	//save the screen before any rotations

	GameObjectList.push_front (new Ship());	//add ship to list
	for(int i=0; i<1; i++){
		GameObjectList.push_back (new Asteroid());	//add asteroids to list
 		//GameObjectList.back()->setYPos(500*i);	//the way to modify a object in the list
		//GameObjectList.back()->setXPos(500*i-100*i*i);

	}
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<DRAW FUNCTIONS>>>>>>>>>>>>>>>>>>>>>>>>>>>
//This is the function that will update the screen
void render(){ 
	glClear(GL_COLOR_BUFFER_BIT);	//clear the screen
	
	//draws the list
	for_each(GameObjectList.begin(), GameObjectList.end(), drawGameObject);
	//for_each(GameObjectList.begin(), GameObjectList.end(), collision);
	GameObjectList.remove_if (dead);

	glBegin(GL_LINE_LOOP);//this triange is for referance
		glVertex2i(1000, 1000);//left corner
		glVertex2i(1000 + GameObjectList.front()->width, 1000);//right corner
		glVertex2i(1000 + GameObjectList.front()->width/2, 1000 + GameObjectList.front()->height);//top point
	glEnd();

	glBegin(GL_LINE_LOOP);//this triange was used in rotation testing
		glVertex2i(1150, 1000);//left corner
		glVertex2i(1150 + GameObjectList.front()->width, 1000);//right corner
		glVertex2i(1150 + GameObjectList.front()->width/2, 1000 + GameObjectList.front()->height);//top point
	glEnd();
	
	glutSwapBuffers();
}
//this function will do the actual drawing of a gameobject
//just pass a gameobject to it
void drawGameObject(GameObject* object){
	if(object->objectIs()=='s'){keyOperations(object);collision(object);}	//determence if the object is a ship/asteriod/bullit so it knows how to move it
	else if(object->objectIs()=='a'){object->move();}
	else if(object->objectIs()=='b'){object->move();collision(object);}
	glEnableClientState(GL_VERTEX_ARRAY);		//for drawling the vertex array
		glVertexPointer(2, GL_INT, 0, object->vertices);
		glDrawArrays(GL_LINE_LOOP, 0, object->getNumOfVertices());
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
	glPushMatrix();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<KEY FUNCTIONS>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void keyPressed(unsigned char key, int x, int y){
	keyStates[key] = true; // Set the state of the current key to pressed 
}

void keyUp (unsigned char key, int x, int y) {  
	keyStates[key] = false; // Set the state of the current key to not pressed  
}
double x,y,u,v;	//four global variables for speed... i cant see a way around it maybe 2 and a bool all global still...
void move(GameObject* flyer){
	glTranslatef(flyer->getXPos()+flyer->width/2,flyer->getYPos()+flyer->height/2,0.0);	//rotate ship to 90 degrees
	glRotatef(90-flyer->getDirection(),0.0,0.0,1.0);
	glTranslatef(-flyer->getXPos()-flyer->width/2,-flyer->getYPos()-flyer->height/2,0.0);

	if(keyStates['w']){
		flyer->setYPos(flyer->getYPos()+flyer->getSpeed()*sin(flyer->getDirection()*PI/180)+v);	//move x and y componits of ship and add u & v the dirft speed
		flyer->setXPos(flyer->getXPos()+flyer->getSpeed()*cos(flyer->getDirection()*PI/180)+u);


		x=flyer->getSpeed()*cos(flyer->getDirection()*PI/180);					//set x and y to the vector the ship should drift in
		y=flyer->getSpeed()*sin(flyer->getDirection()*PI/180);

	}else{
		flyer->setYPos(flyer->getYPos()+y);	//drift in x and y vectors
		flyer->setXPos(flyer->getXPos()+x);

		x*=flyer->getSpeedDecay();		//decrease x and y vector speed over time
		y*=flyer->getSpeedDecay();
		u=x;					//set u and v to drift speed that carrys into next move
		v=y;
	}
	flyer->setVertices();	//updata array of points

	glTranslatef(flyer->getXPos()+flyer->width/2,flyer->getYPos()+flyer->height/2,0.0);	//rotate ship back to ship angle
	glRotatef(-90+flyer->getDirection(),0.0,0.0,1.0);
	glTranslatef(-flyer->getXPos()-flyer->width/2,-flyer->getYPos()-flyer->height/2,0.0);
}
void moveAsteroid(GameObject* rock){//this method has been moved to asteroid class no need for it here it is never used
	if(rock->getHealth()==0 && rock->width!=100){	//this will be part of collision
		GameObjectList.push_back (new Asteroid(rock->width,rock->getXPos(),rock->getYPos(),rock->getDirection(),'1'));
		GameObjectList.push_back (new Asteroid(rock->height,rock->getXPos(),rock->getYPos(),rock->getDirection(),'2'));

		rock->setAlive(false);
		rock->setXPos(3000);
		rock->setYPos(3000);
	}else{
		rock->move();
	}
}
void collision(GameObject* plane){	//something is not quit right with this... and it will be hard to do when vertices is private cause you cant return an array...
	for (list<GameObject*>::iterator it= GameObjectList.begin(); it != GameObjectList.end(); it++) {
		if(true){
			//for (int i=0; i<plane->getNumOfVertices()*2; i=i+2) {
			//for (int j=0; j<(*it)->getNumOfVertices()*2; j=j+2) {
				if(
				/* (plane->vertices[i%(plane->getNumOfVertices()*2)]-((*it)->getXPos()+(*it)->width/2))
				*(plane->vertices[i%(plane->getNumOfVertices()*2)]-((*it)->getXPos()+(*it)->width/2))
				+(plane->vertices[(i+1)%(plane->getNumOfVertices()*2)]-((*it)->getYPos()+(*it)->height/2))
				*(plane->vertices[(i+1)%(plane->getNumOfVertices()*2)]-((*it)->getYPos()+(*it)->height/2))
				<
				((*it)->width/2)*((*it)->width/2)*/

				 ((plane->getXPos()+plane->width/2)-((*it)->getXPos()+(*it)->width/2))
				*((plane->getXPos()+plane->width/2)-((*it)->getXPos()+(*it)->width/2))
				+((plane->getYPos()+plane->height/2)-((*it)->getYPos()+(*it)->height/2))
				*((plane->getYPos()+plane->height/2)-((*it)->getYPos()+(*it)->height/2))
				<=
				((plane->width/2)+((*it)->width/2))*((plane->width/2)+((*it)->width/2))

				&&
				 ((plane->getXPos()+plane->width/2)-((*it)->getXPos()+(*it)->width/2))
				*((plane->getXPos()+plane->width/2)-((*it)->getXPos()+(*it)->width/2))
				+((plane->getYPos()+plane->height/2)-((*it)->getYPos()+(*it)->height/2))
				*((plane->getYPos()+plane->height/2)-((*it)->getYPos()+(*it)->height/2))
				!=0
				){
					if(plane->objectIs()=='b')
					plane->setAlive(false);
					plane->setXPos(3000);
					plane->setYPos(3000);

					if((*it)->width!=100 && (*it)->objectIs()=='a'){
						GameObjectList.push_back (new Asteroid((*it)->width,(*it)->getXPos(),(*it)->getYPos(),(*it)->getDirection(),'1'));
						GameObjectList.push_back (new Asteroid((*it)->height,(*it)->getXPos(),(*it)->getYPos(),(*it)->getDirection(),'2'));

						(*it)->setAlive(false);
						(*it)->setXPos(3000);
						(*it)->setYPos(3000);
					}//else{
					//	(*it)->setAlive(false);
					//	(*it)->setXPos(3000);
					//	(*it)->setYPos(3000);
					//}
				}
			//}//}
		}
	}
}
/*bool pnpoly(GameObject* obstruction, int x, int y){
	int count=0;
	bool c=false;
	//do{
		for (int i = 0; i < obstruction->getNumOfVertices()*2; i = i+2) {
			/*if (	x>min(obstruction->vertices[i],obstruction->vertices[(i+2)%(obstruction->getNumOfVertices()*2)]) &&
				x<max(obstruction->vertices[i],obstruction->vertices[(i+2)%(obstruction->getNumOfVertices()*2)]) &&
				y>min(obstruction->vertices[(i+1)%(obstruction->getNumOfVertices()*2)],obstruction->vertices[(i+3)%(obstruction->getNumOfVertices()*2)]) &&
				y<max(obstruction->vertices[(i+1)%(obstruction->getNumOfVertices()*2)],obstruction->vertices[(i+3)%(obstruction->getNumOfVertices()*2)])){
			if(	y>obstruction->getYPos() && y<obstruction->getYPos()+obstruction->height && x>obstruction->getXPos()}
				xinters=(y-obstruction->vertices[i+1])*(obstruction->vertices[i+2]-obstruction->vertices[i])/(obstruction->vertices[i+3]-obstruction->vertices[i+1])+obstruction->vertices[i]

				count++;
				break;
			}
		}
		//x++;
	//}while(x!=2001);
	if(count%2!=0)
		c = !c;
	return c;
}*/
void keyOperations (GameObject* player) {
	glTranslatef(player->getXPos()+player->width/2,player->getYPos()+player->height/2,0.0);	//rotate ship recusively, this just puts it to where it is on screen
	glRotatef(player->getDirection()-90,0.0,0.0,1.0);
	glTranslatef(-player->getXPos()-player->width/2,-player->getYPos()-player->height/2,0.0);

	if(keyStates['a']) {
		player->setDirection(player->getDirection()+10);					      // calculate direction for movement
		glTranslatef(player->getXPos()+player->width/2,player->getYPos()+player->height/2,0.0);   //move the ship to center
		glRotatef(10.0,0.0,0.0,1.0);							      //rotate everthing 5 degrees around the z axis
		glTranslatef(-player->getXPos()-player->width/2,-player->getYPos()-player->height/2,0.0); //move everthing back to the ship start point
	}if(keyStates['d']){
		player->setDirection(player->getDirection()-10);
		glTranslatef(player->getXPos()+player->width/2,player->getYPos()+player->height/2,0.0);
		glRotatef(-10.0,0.0,0.0,1.0);
		glTranslatef(-player->getXPos()-player->width/2,-player->getYPos()-player->height/2,0.0);
	}
	if(keyStates['x']) {
		if(GameObjectList.back()->objectIs()=='b' && GameObjectList.back()->getDistance()>=200 ||GameObjectList.back()->objectIs()!='b')
		GameObjectList.push_back (new Bullit(player->getXPos(),player->getYPos(),player->getDirection(),player->width,player->height));
	}
	if(keyStates['w'] && player->getSpeed()<=30){	//max speed
		player->setSpeed(player->getSpeed()+1);	//increase speed
		u=u*player->getSpeedDecay();		//decrease drift speed
		v=v*player->getSpeedDecay();
	}else if(!keyStates['w']&&player->getSpeed()>0){
		player->setSpeed(0);			//reset speed after new direction
	}
	if (keyStates['s']){	//move ship to center
		glLoadIdentity();
		gluOrtho2D((GLdouble)0.0,(GLdouble)2000.0,(GLdouble)0.0,(GLdouble)2000.0);	//reset the grid
		player->setYPos(1000);								//put ship in center
		player->setXPos(1000);
		player->setDirection(90);							//set direction to ship direction
		GameObjectList.back()->setHealth(0);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	move(player);
}

void updateGame(int value){
	glutPostRedisplay();	//draws everything
	glutTimerFunc(FRAMERATE, updateGame,0);
}
int main(int argc, char** argv){
	glutInit(&argc,argv);				//initialize the toolkit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 	//set the display mode
	glutInitWindowSize(W_WIDTH,W_HEIGHT);
	glutInitWindowPosition(100,150);		//here is where the upper left corner of the screen is
	glutCreateWindow("Asteroids");			//open the screen window
	init();
	
	//CALLBACK functions 
	glutDisplayFunc(render);		 //register the redraw functions
	glutTimerFunc(FRAMERATE, updateGame,0);	 //regitster the game update

	glutKeyboardFunc(keyPressed); 	// Tell GLUT to use the method "keyPressed" for key presses 
	glutKeyboardUpFunc(keyUp); 	// Tell GLUT to use the method "keyUp" for key up 

	//enter event listening loop
	glutMainLoop();
	return 0;
}
