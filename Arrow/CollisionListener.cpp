#include "CollisionListener.h"
#include "Box.h"
#include "Arrow.h"
#include "Player.h"


CollisionListener::CollisionListener()
{
}


CollisionListener::~CollisionListener()
{
}


void CollisionListener::BeginContact(b2Contact * contact)
{
	//check if fixture A has user data
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	bool arrow = false;
	if (bodyUserData) 
	{
		static_cast<GameObj*>(bodyUserData)->startContact();
		static_cast<GameObj*>(bodyUserData)->collision(contact->GetFixtureB());
	}
		

	//check if fixture A has user data
	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData) 
	{
		static_cast<GameObj*>(bodyUserData)->startContact();
		static_cast<GameObj*>(bodyUserData)->collision(contact->GetFixtureA());
	}
}

void CollisionListener::EndContact(b2Contact * contact)
{
	//check if fixture A has user data
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData)
	{
		static_cast<GameObj*>(bodyUserData)->endContact();
	}

	//check if fixture A has user data
	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData) 
	{
		static_cast<GameObj*>(bodyUserData)->endContact();
	}
}
