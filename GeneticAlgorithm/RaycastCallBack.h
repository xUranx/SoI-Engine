#pragma once
#include <Box2D/Box2D.h>
class RaycastCallBack : public b2RayCastCallback
{
public:
	RaycastCallBack();
	~RaycastCallBack();

	void init();
	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);
	b2Vec2 getHitPoint() const { return hitPoint; }
	bool getHit() const { return hit; }
private:
	b2Fixture* fixtu = nullptr;
	b2Vec2 hitPoint;
	b2Vec2 norm;
	float32 frag;
	bool hit = false;
};

