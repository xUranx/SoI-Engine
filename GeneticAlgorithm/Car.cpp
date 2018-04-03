#include "Car.h"
#include "CollisionListener.h"
#include <random>
#include <time.h>
#include <Engine/Include/ResourceManager.h>
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

Tire::Tire()
{
}

Tire::~Tire()
{
	//body->GetWorld()->DestroyJoint(joint);
	//body->GetWorld()->DestroyBody(body);
	//body = nullptr;
	//joint = nullptr;
}

void Tire::init(b2World * world, float rad, float friction, Engine::ColourRGBA8 color)
{
	colour = color;
	b2BodyDef bDef;
	bDef.position.SetZero();
	bDef.type = b2_dynamicBody;
	body = world->CreateBody(&bDef);

	b2CircleShape cShape;
	cShape.m_p.SetZero();
	radius = rad;
	cShape.m_radius = radius;
	b2FixtureDef fDef;
	fDef.shape = &cShape;
	fDef.density = 1;
	fDef.friction = friction;
	fDef.filter.categoryBits = entityCat::Player;
	fDef.filter.maskBits = entityCat::Walls;
	body->CreateFixture(&fDef);
	body->SetUserData(this);
	texture = Engine::ResourceManager::getTexture("assets/Textures/tire2.png");
}

void Tire::initJoint(b2Body* aBody, glm::vec4 pos, bool on)
{
	b2RevoluteJointDef rDef;
	rDef.bodyA = aBody;
	rDef.bodyB = body;
	rDef.collideConnected = false;
	rDef.localAnchorA.Set(pos.x, pos.y);
	rDef.localAnchorB.Set(pos.z, pos.w);

	rDef.maxMotorTorque = 100;
	rDef.motorSpeed = -360 * DEGTORAD;
	rDef.enableMotor = on;
	joint = (b2RevoluteJoint*)body->GetWorld()->CreateJoint(&rDef);
	joint->SetUserData(this);
}

void Tire::draw(Engine::GLSpriteBatch& sBatch)
{
	glm::vec4 destRect;
	
	destRect.x = body->GetPosition().x - radius;
	destRect.y = body->GetPosition().y - radius;
	destRect.z = radius*2.0f;
	destRect.w = radius*2.0f;
	sBatch.draw(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), texture.id, 0.0f, colour, body->GetAngle());
}


Car::Car()
{
}


Car::~Car()
{
	//body->GetWorld()->DestroyBody(body);
	//body = nullptr;
}

void Car::init(b2World * world, glm::vec4 Pos, Engine::ColourRGBA8 color)
{
	colour = color;
	b2BodyDef bDef;
	bDef.position.Set(Pos.x, Pos.y);
	bDef.type = b2_dynamicBody;
	body = world->CreateBody(&bDef);

	b2PolygonShape bShape;
	dimensions.x = Pos.z;
	dimensions.y = Pos.w;
	bShape.SetAsBox(dimensions.x/2 ,dimensions.y/2);
	
	b2FixtureDef fDef;
	fDef.shape = &bShape;
	fDef.density = 1;
	fDef.friction = 1;
	fDef.filter.categoryBits = entityCat::Player;
	fDef.filter.maskBits = entityCat::Walls;
	body->CreateFixture(&fDef);
	body->SetUserData(this);


	
}

void Car::draw(Engine::GLSpriteBatch & sBatch)
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
	sBatch.draw(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), NULL, 1.0f, colour, body->GetAngle());
}

