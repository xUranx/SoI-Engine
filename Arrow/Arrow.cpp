#include "Arrow.h"
#define _USE_MATH_DEFINES
#include <math.h>
Arrow::Arrow()
{
}


Arrow::~Arrow()
{
	body->GetWorld()->DestroyBody(body);
}

void Arrow::Init(b2World * world, b2Body* uBody, Engine::GLTexture text, Engine::ColourRGBA8 & color, float angle, float sVel)
{
	texture = text;
	colour = color;
	b2BodyDef bDef;
	bDef.type = b2_dynamicBody;
	bDef.position = uBody->GetPosition();

	body = world->CreateBody(&bDef);

	b2PolygonShape bShape;
	b2Vec2 vertices[4];
	vertices[0].Set(-1.4f, 0);
	vertices[1].Set(0, -0.1f);
	vertices[2].Set(0.6f, 0);
	vertices[3].Set(0, 0.1f);
	bShape.Set(vertices, 4);

	b2FixtureDef fDef;
	fDef.shape = &bShape;
	fDef.density = 1.0f;
	fDef.friction = 0.3f;
	fDef.filter.categoryBits = entityCat::Arrow;
	fixture = body->CreateFixture(&fDef);

	body->SetAngularDamping(3);
	body->SetAngularVelocity(0);
	uBody->SetTransform(uBody->GetPosition(), angle +M_PI / 2);
	body->SetTransform(uBody->GetWorldPoint({ 3,0 }), angle+ M_PI/2);
	body->SetLinearVelocity(uBody->GetWorldVector({ sVel,0 }));
	uBody->SetTransform(uBody->GetPosition(), 0);
	body->SetUserData(this);
}

void Arrow::update()
{
	b2Vec2 pointDir = body->GetWorldVector({ 1,0 });
	b2Vec2 flightDir = body->GetLinearVelocity();
	float velocity = flightDir.Normalize();

	float dot = b2Dot(flightDir, pointDir);
	float dragForceMagnitude = (1 - fabs(dot)) * velocity * velocity * .1f * body->GetMass();

	b2Vec2 arrowTailPos = body->GetWorldPoint({ -1.4f,0 });
	body->ApplyForce(dragForceMagnitude * -flightDir, arrowTailPos, true);
}
void Arrow::Draw(Engine::GLSpriteBatch& sBatch)
{
	glm::vec4 destRect(body->GetPosition().x-1.4f, body->GetPosition().y -0.1f,2.0f,0.2f);
	sBatch.draw(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), texture.id, 1.0f, colour, body->GetAngle());
}
