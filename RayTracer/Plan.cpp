#include "Plan.hpp"
#include <iostream>

Plan::Plan() : Objet()
{
	n = D3DXVECTOR3(1, 0, 0);
	ambiant = D3DXVECTOR3(0, 0, 255);
	dif = D3DXVECTOR3(0, 0, 255);
	spec = D3DXVECTOR3(255, 255, 255);

}

Plan::Plan(D3DXVECTOR3 N) : Objet()
{
	n = N;
	ambiant = D3DXVECTOR3(10, 10, 120);
	dif = D3DXVECTOR3(0, 0, 255);
	spec = D3DXVECTOR3(255, 255, 255);
}


bool Plan::intersection(D3DXVECTOR3& A, D3DXVECTOR3& u)
{
	D3DXVec3Normalize(&u, &u);
	D3DXVec3Normalize(&n, &n);
	float denom = D3DXVec3Dot(&u, &n);
	if (fabs(denom) > 0.0001f)
	{
		D3DXVECTOR3 temp = o - A;
		float t = D3DXVec3Dot(&temp, &n) / denom;
		if (t >= 0)
		{
			u = A + t*u;
			return true;
		}
	}
	return false;

}

D3DXVECTOR3 Plan::getNormal(D3DXVECTOR3 inter)
{
	return -n;
}
