#include "Plan.hpp"
#include <iostream>

Plan::Plan() : Objet()
{
	n = D3DXVECTOR3(0, 1, 0);
	ambiant = D3DXVECTOR3(0, 0, 255);
	dif = D3DXVECTOR3(0, 0, 255);
	spec = D3DXVECTOR3(255, 255, 255);
	c_ambiant = 0.1f;
	c_dif = 0.8f;
	c_spec = 0.1f;
}

Plan::Plan(D3DXVECTOR3 N) : Objet()
{
	n = N;
	ambiant = D3DXVECTOR3(10, 10, 120);
	dif = D3DXVECTOR3(0, 0, 255);
	spec = D3DXVECTOR3(255, 255, 255);
}

void Plan::setNormale(float x, float y, float z)
{
	n = D3DXVECTOR3(x, y, z);
}


bool Plan::intersection(D3DXVECTOR3& A, D3DXVECTOR3& u)
{
	/*
	float Lu = D3DXVec3Length(&u);
	float Nu = D3DXVec3Length(&n);*/
	D3DXVec3Normalize(&u, &u);
	D3DXVec3Normalize(&n, &n);
	float m = D3DXVec3Dot(&n, &u);
	/*if (Lu > 0.99999 && Nu > 0.99999)
	{
		float test = m*m / ((Lu*Lu)*(Nu*Nu));
		if (test < 0.001)
		{
			return false;
		}
	}*/
	if (fabs(m) < 0.00001)
	{
		return false;
	}
	else
	{
		D3DXVECTOR3 L = A - o;
		float d = D3DXVec3Dot(&n, &L);
		float t = -d / m;
		if (t > 0)
		{
			u = t*u + A;
			return true;
		}
		else
		{
			return false;
		}
	}
}

D3DXVECTOR3 Plan::getNormal(D3DXVECTOR3 inter)
{
	return -n;
}
