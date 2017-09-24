#include "CollisionListener.h"
#include "Planet.h"
#include "Box.h"


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
	if (bodyUserData)
		static_cast<Box*>(bodyUserData)->startContact();

	//check if fixture B was a ball
	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData)
		static_cast<Planet*>(bodyUserData)->startContact();
}

void CollisionListener::EndContact(b2Contact * contact)
{
	//check if fixture A was a ball
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData)
		static_cast<Box*>(bodyUserData)->endContact();

	//check if fixture B was a ball
	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData)
		static_cast<Planet*>(bodyUserData)->endContact();
}
