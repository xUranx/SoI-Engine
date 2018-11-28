#pragma once
#include <Box2D\Box2D.h>
namespace entityCat
{
	enum entityCatecory
	{
		Walls = 0x0001,
		Arrow = 0x0004,
		Player = 0x0006,
		Block = 0x0010
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

