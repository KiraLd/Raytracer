#include "Sphere.hpp"
#include <iostream>

Sphere::Sphere() : Objet()
{
	r = 10.f;
}

Sphere::Sphere(float r) : Objet()
{
	this->r = r;
}


bool Sphere::intersection(D3DXVECTOR3& A, D3DXVECTOR3& u)
{
	D3DXVec3Normalize(&u, &u);
	D3DXVECTOR3 L = o - A;
	float tca = D3DXVec3Dot(&L, &u);
	if (tca < 0)
	{
		return false;
	}
	float d2 = D3DXVec3Dot(&L, &L) - tca*tca;
	if (d2 > r*r)
	{
		return false;
	}
	float thc = sqrtf(r*r - d2);
	float t0 = tca - thc;
	float t1 = tca + thc;
	if (t0 > t1)
	{
		std::swap(t0, t1);
	}
	if (t0 < 0)
	{
		t0 = t1;
		if (t0 < 0)
		{
			return false;
		}
	}
	float t = t0;
	u.x = A.x + t*u.x;
	u.y = A.y + t*u.y;
	u.z = A.z + t*u.z;
	return true;

	/*
	D3DXVec3Normalize(&u, &u);
	D3DXVECTOR3 L = o - A;
	float d = D3DXVec3Dot(&L, &u);
	float l2 = D3DXVec3Dot(&L, &L);
	float r2 = r*r;
	if (d < 0 && l2 > r2)
	{
		return false;
	}
	float m2 = l2 - d*d;
	if (m2 > r2)
	{
		return false;
	}
	float q = sqrtf(r2 - m2);
	float t;
	if (l2 > r2)
	{
		t = d - q;
	}
	else
	{
		t = d + q;
	}
	u.x = A.x + t*u.x;
	u.y = A.y + t*u.y;
	u.z = A.z + t*u.z;
	return true;*/

}

D3DXVECTOR3 Sphere::getNormal(D3DXVECTOR3 inter)
{
	return inter - o;
}