#include "GameObject.h"

class Bullit: public GameObject {
	public:
		//constructor
		Bullit(float,float,int,int,int);

		//destructor
		virtual ~Bullit();

		//prototypes
		void setVertices();
		char objectIs();
		void move();
		int getDistance();
		void setDistance(int);
		float getX();
		void setX(float);
		float getY();
		void setY(float);
		int getW();
		void setW(int);
		int getH();
		void setH(int);

		//variables
	protected:
		int Distance;
		float x;
		float y;
		int w;
		int h;
};
