#include "GameObject.h"

class Ship: public GameObject {
	public:
		//constructor
		Ship();

		//destructor
		virtual ~Ship();

		//prototypes
		float getSpeedDecay();
		void setSpeedDecay(float);
		void setVertices();
		char objectIs();
		void move();

		//variables
	protected:
		float speedDecay;
};
