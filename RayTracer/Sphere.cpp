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
	//return D3DXSphereBoundProbe(&o, r, &A, &u);

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
	return true;

}
