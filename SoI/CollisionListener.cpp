#include "CollisionListener.h"
#include "Planet.h"
#include "Box.h"


CollisionListener::CollisionListener()
{
}


CollisionListener::~CollisionListener()
{
}

bool Soi(b2Contact * contact, bool mode)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	bool sensorA = fixtureA->IsSensor();
	bool sensorB = fixtureB->IsSensor();
	if (!(sensorA ^ sensorB))
	{
		return false;
	}
	if (mode)
	{
		if (sensorA)
		{
			Planet * ball = static_cast<Planet*>(fixtureA->GetBody()->GetUserData());
			static_cast<Box*>(fixtureB->GetBody()->GetUserData())->startSoIcontact(ball->getBody()->GetPosition());
		}
		else
		{
			Planet * ball = static_cast<Planet*>(fixtureB->GetBody()->GetUserData());
			static_cast<Box*>(fixtureA->GetBody()->GetUserData())->startSoIcontact(ball->getBody()->GetPosition());
		}
	}
	else
	{
		if (sensorA)
		{
			static_cast<Box*>(fixtureB->GetBody()->GetUserData())->endSoIcontact();
		}
		else
		{
			static_cast<Box*>(fixtureA->GetBody()->GetUserData())->endSoIcontact();
		}
	}
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
	Soi(contact, true);
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
	Soi(contact, false);
}
