#ifndef _SPHERE_
#define _SPHERE_
#include "Objet.hpp"

struct Sphere : public Objet
{
	float r;

	Sphere();
	Sphere(float r);
	bool intersection(D3DXVECTOR3& o, D3DXVECTOR3& ray);
	D3DXVECTOR3 getNormal(D3DXVECTOR3 inter);
};

#endif