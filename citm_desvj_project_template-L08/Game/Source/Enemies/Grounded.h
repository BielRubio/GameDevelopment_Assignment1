#ifndef __GROUNDED_H__
#define __GROUNDED_H__

#include "../Enemy.h"

class Grounded : public Enemy
{
public:
	Grounded();

	virtual ~Grounded();

	bool Awake();

	bool Start();

	bool Update();

	bool CleanUp();

	void OnCollision(PhysBody* physA, PhysBody* physB);

	bool IsAlive();

	bool LoadState(pugi::xml_node& data);

	bool SaveState(pugi::xml_node& data);

public:


private:


};


#endif // __GROUNDED_H__

