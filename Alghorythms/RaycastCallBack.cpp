#include "RaycastCallBack.h"
#include "CollisionListener.h"
#include "Ship.h"


RaycastCallBack::RaycastCallBack()
{
}


RaycastCallBack::~RaycastCallBack()
{
}

float32 RaycastCallBack::ReportFixture(b2Fixture * fixture, const b2Vec2 & point, const b2Vec2 & normal, float32 fraction)
{
	if (fixture->GetFilterData().categoryBits == entityCat::Walls)
	{
		static_cast<Ship*>(fixture->GetBody()->GetUserData())->setRay(true);
		return fraction;
	}
	else
	{
		static_cast<Ship*>(fixture->GetBody()->GetUserData())->setRay(false);
		return -1;
	}
}
