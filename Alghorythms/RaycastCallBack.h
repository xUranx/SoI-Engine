#pragma once
#include <Box2D\Box2D.h>
class RaycastCallBack : public b2RayCastCallback
{
public:
	RaycastCallBack();
	~RaycastCallBack();

	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);
	bool getHit() const { return hit; }
private:
	bool hit = false;
};

