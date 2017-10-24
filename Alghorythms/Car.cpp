#include "Car.h"
#include "CollisionListener.h"
#include <random>
#include <time.h>
#include <Engine\ResourceManager.h>
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

Tire::Tire()
{
}

Tire::~Tire()
{
}

void Tire::init(b2World * world, bool ra)
{
	colour.setColour(25, 25, 25, 255);
	b2BodyDef bDef;
	bDef.position.SetZero();
	bDef.type = b2_dynamicBody;
	body = world->CreateBody(&bDef);

	b2CircleShape cShape;
	cShape.m_p.Set(0,0);
	if(ra)
	{
		srand(time(NULL));
		radius = rand() % 20 / 10;
		cShape.m_radius = radius;
	}
	else
	{
		radius = 3;
		cShape.m_radius = radius;
	}
	b2FixtureDef fDef;
	fDef.shape = &cShape;
	fDef.density = 1;
	fDef.friction = 2.0f;
	fDef.filter.categoryBits = entityCat::Player;
	fDef.filter.maskBits = entityCat::Walls;
	body->CreateFixture(&fDef);
	body->SetUserData(this);
	texture = Engine::ResourceManager::getTexture("Include/Textures/tire.png");
}

void Tire::draw(Engine::SpriteBatch& sBatch)
{
	glm::vec4 destRect;
	
	destRect.x = body->GetPosition().x - radius;
	destRect.y = body->GetPosition().y - radius;
	destRect.z = radius*2.0f;
	destRect.w = radius*2.0f;
	sBatch.draw(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), texture.id, 1.0f, colour, body->GetAngle());
}


Car::Car()
{
}


Car::~Car()
{
}

void Car::init(b2World * world, glm::vec2 Pos)
{
	colour.setColour(255, 128, 43, 255);
	b2BodyDef bDef;
	bDef.position.Set(Pos.x, Pos.y);
	bDef.type = b2_dynamicBody;
	body = world->CreateBody(&bDef);

	b2PolygonShape bShape;
	bShape.SetAsBox(3,1);
	dimensions.x = 6;
	dimensions.y = 2;
	b2FixtureDef fDef;
	fDef.shape = &bShape;
	fDef.density = 1;
	fDef.friction = 0.3f;
	fDef.filter.categoryBits = entityCat::Player;
	fDef.filter.maskBits = entityCat::Walls;
	body->CreateFixture(&fDef);
	body->SetUserData(this);

	Tire tire1;
	Tire tire2;

	tire1.init(world, false);
	tires.push_back(tire1);
	tire2.init(world, false);
	tires.push_back(tire2);

	b2RevoluteJointDef rDef;
	rDef.bodyA = body;
	rDef.bodyB = tires[0].getBody();
	rDef.collideConnected = false;

	rDef.localAnchorA.Set(1, 0.5);
	rDef.localAnchorB.Set(0, 0);

	rDef.maxMotorTorque = 100;
	rDef.motorSpeed = -360 * 5 * DEGTORAD;
	rDef.enableMotor = true;
	tires[0].setJoint((b2RevoluteJoint*)world->CreateJoint(&rDef));
	rDef.bodyB = tires[1].getBody();
	rDef.localAnchorA.Set(-1, 0.5);
	tires[1].setJoint((b2RevoluteJoint*)world->CreateJoint(&rDef));
}

void Car::draw(Engine::SpriteBatch & sBatch)
{
	for (int i = 0; i < tires.size(); i++)
	{
		tires[i].draw(sBatch);
	}
	glm::vec4 destRect;
	destRect.x = body->GetPosition().x - dimensions.x / 2.0f;
	destRect.y = body->GetPosition().y - dimensions.y / 2.0f;
	destRect.z = dimensions.x;
	destRect.w = dimensions.y;
	sBatch.draw(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), NULL, 2.0f, colour, body->GetAngle());
}

