#include "Ship.h"
#include "CollisionListener.h"
using namespace entityCat;

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

Thruster::Thruster()
{
}

Thruster::~Thruster()
{
}

b2FixtureDef Thruster::init(bool rand, b2Body* b, float scale)
{

	b2PolygonShape pShape;
	if (rand)
	{

	}
	else
	{
		offset.Set(0.0, -3.0);
		if (scale > 0.0)
		{
			offset *= scale;
		}	
	}
	std::vector<p2t::Point*> pLine;
	dimens[0].Set(-1, 1);
	dimens[1].Set(-1.0, 0);
	dimens[2].Set(-0.5, -1);
	dimens[3].Set(0.5, -1);
	dimens[4].Set(1.0, 0);
	dimens[5].Set(1, 1);
	
	for (int i = 0; i < 6; i++)
	{
		dimens[i] *= scale;
		dimens[i] += offset;
		pLine.push_back(new p2t::Point(dimens[i].x, dimens[i].y));
	}
	pShape.Set(dimens, 6);
	b2FixtureDef fDef;
	fDef.shape = &pShape;
	fDef.density = 1.0f;
	fDef.friction = 0.3f;
	fDef.filter.categoryBits = Player;
	fDef.filter.maskBits = Walls;
	b->CreateFixture(&fDef);

	p2t::CDT* cdt = new p2t::CDT(pLine);
	cdt->Triangulate();

	triangles = cdt->GetTriangles();

	return fDef;
}

void Thruster::draw(Engine::SpriteBatch& sBatch, b2Body* body)
{
	Engine::ColourRGBA8 color;
	color.setColour(10.0f, 20.0f, 15.0f, 255.0f);
	b2Vec2 pos = body->GetPosition();
	for (int i = 0; i < triangles.size(); i++)
	{
		glm::vec2 destRect[3];
		destRect[0].x = triangles[i]->GetPoint(0)->x + pos.x;
		destRect[0].y = triangles[i]->GetPoint(0)->y + pos.y;
		destRect[1].x = triangles[i]->GetPoint(1)->x + pos.x;
		destRect[1].y = triangles[i]->GetPoint(1)->y + pos.y;
		destRect[2].x = triangles[i]->GetPoint(2)->x + pos.x;
		destRect[2].y = triangles[i]->GetPoint(2)->y + pos.y;
		sBatch.draw(destRect, glm::vec4(0, 0, 0, 1), NULL, 0, color, body->GetAngle(), glm::vec2(pos.x, pos.y));
	}
}


Ship::Ship()
{
}


Ship::~Ship()
{
}

void Ship::init(b2World* world, const glm::vec2 position, const glm::vec2 dimensions[],bool rand, float scale)
{
	dimens[0].x = dimensions[0].x * scale;
	dimens[0].y = dimensions[0].y * scale;
	dimens[1].x = dimensions[1].x * scale;
	dimens[1].y = dimensions[1].y * scale;
	dimens[2].x = dimensions[2].x * scale;
	dimens[2].y = dimensions[2].y * scale;
	b2BodyDef bDef;
	bDef.type = b2_dynamicBody;
	bDef.position.Set(position.x, position.y);

	body = world->CreateBody(&bDef);

	b2PolygonShape pShape;
	pShape.Set(dimens, 5);

	b2FixtureDef fDef;
	fDef.shape = &pShape;
	fDef.density = 1.0f;
	fDef.friction = 0.3f;
	fDef.filter.categoryBits = Player;
	fDef.filter.maskBits = Walls;
	fixture = body->CreateFixture(&fDef);
	thruster.init(rand, body, scale);
	body->SetUserData(this);
}

void Ship::draw(Engine::SpriteBatch& sBatch)
{
	Engine::ColourRGBA8 color;
	color.setColour(100.0f, 51.0f, 15.0f, 255.0f);
	glm::vec2 destRect[3];
	b2Vec2 pos = body->GetPosition();
	destRect[0].x = dimens[0].x + pos.x;
	destRect[0].y = dimens[0].y + pos.y;
	destRect[1].x = dimens[1].x + pos.x;
	destRect[1].y = dimens[1].y + pos.y;
	destRect[2].x = dimens[2].x + pos.x;
	destRect[2].y = dimens[2].y + pos.y;
	sBatch.draw(destRect, glm::vec4(0, 0, 0, 1), NULL, 0, color, body->GetAngle(), glm::vec2(pos.x,pos.y));
	thruster.draw(sBatch, body);
}

void Ship::raycast()
{
	for (int i = 0; i < 3; i++)
	{
		rays[i].p1 = body->GetWorldPoint(b2Vec2(0, 0.8f));
	}
	rays[0].p2 = rays[0].p1 + rayLenght * b2Vec2(sinf(-body->GetAngle()), cosf(-body->GetAngle()));
	rays[1].p2 = rays[1].p1 + rayLenght * b2Vec2(sinf(-body->GetAngle() + 25 * DEGTORAD), cosf(-body->GetAngle() + 25 * DEGTORAD));
	rays[2].p2 = rays[2].p1 + rayLenght * b2Vec2(sinf(-body->GetAngle() - 25 * DEGTORAD), cosf(-body->GetAngle() - 25 * DEGTORAD));
	for (int i = 0; i < 3;i++)
	{
		callback.init();
		body->GetWorld()->RayCast(&callback, rays[i].p1, rays[i].p2);
		ray[i] = callback.getHit();
		if(ray[i])
			rays[i].hitPoint = callback.getHitPoint();
		else
		{
			rays[i].hitPoint = rays[i].p2;
		}
	}

}

void Ship::debugDraw(Engine::DebugRenderer& dRender)
{
	for (int i = 0;i < 3;i++)
	{
		Engine::ColourRGBA8 color;
		if (ray[i])
		{
			color.setColour(255.0f, 0.0f, 0.0f, 255.0f);
			glm::vec4 destRect;
			destRect.x = rays[i].hitPoint.x - 0.1f;
			destRect.y = rays[i].hitPoint.y - 0.1f;
			destRect.z = 0.2f;
			destRect.w = 0.2f;
			dRender.drawLine(glm::vec2(rays[i].p1.x, rays[i].p1.y), glm::vec2(rays[i].hitPoint.x, rays[i].hitPoint.y),color);
			dRender.drawBox(destRect, color, 0);
		}
		else
			//color.setColour(255.0f, 255.0f, 255.0f, 255.0f);
			dRender.drawLine(glm::vec2(rays[i].p1.x, rays[i].p1.y), glm::vec2(rays[i].p2.x, rays[i].p2.y), color);
	}
}

