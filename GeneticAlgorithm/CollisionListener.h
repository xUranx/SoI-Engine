#pragma once
#include <Box2D/Box2D.h>
namespace entityCat
{
	enum entityCatecory
	{
		Walls = 0x0001,
		Planet_SOI = 0x0002,
		Planet = 0x0003,
		Player = 0x0004,
		Block = 0x0008
	};
}
class CollisionListener : public b2ContactListener
{
public:
	CollisionListener();
	~CollisionListener();

	void BeginContact(b2Contact* contact);

	void EndContact(b2Contact* contact);


};

