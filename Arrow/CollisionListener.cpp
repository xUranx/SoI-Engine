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
	//check if fixture A was a ball
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	bool arrow = false;
	if (bodyUserData) 
	{
		if (entityCat::Arrow == contact->GetFixtureA()->GetFilterData().categoryBits)
		{
			static_cast<Arrow*>(bodyUserData)->startContact();
			bool arrow = true;
		}
	}
		

	//check if fixture B was a ball
	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData) 
	{
		if (entityCat::Arrow == contact->GetFixtureB()->GetFilterData().categoryBits)
			static_cast<Arrow*>(bodyUserData)->startContact();
		if (arrow && entityCat::Player == contact->GetFixtureB()->GetFilterData().categoryBits)
			static_cast<Player*>(bodyUserData)->startContact();
	}
}

void CollisionListener::EndContact(b2Contact * contact)
{
	//check if fixture A was a ball
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData) {}

	//check if fixture B was a ball
	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData) {}
}
