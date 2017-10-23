#include "RaycastCallBack.h"
#include "CollisionListener.h"
#include "Ship.h"


RaycastCallBack::RaycastCallBack()
{
}


RaycastCallBack::~RaycastCallBack()
{
}

void RaycastCallBack::init()
{
	fixtu = nullptr;
	hitPoint.SetZero();
	norm.SetZero();
	frag = NULL;
	hit = false;
}

float32 RaycastCallBack::ReportFixture(b2Fixture * fixture, const b2Vec2 & point, const b2Vec2 & normal, float32 fraction)
{
	fixtu = fixture;
	hitPoint = point;
	norm = normal;
	frag = fraction;
	if (fixture->GetFilterData().categoryBits == entityCat::Walls)
	{
		hit = true;
		return fraction;
	}
	else
	{
		hit = false;
		return -1;
	}
}

