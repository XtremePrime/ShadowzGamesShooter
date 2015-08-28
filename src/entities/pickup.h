#ifndef PICKUP_H
#define PICKUP_H

#include "entity.h"

class Pickup : public Entity
{
private:
public:
	enum PickupCodes{
		HEALTH = 1,
		SHOTGUN = 2
	};

};

#endif // PICKUP_H