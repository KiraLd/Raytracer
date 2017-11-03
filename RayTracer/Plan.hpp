#ifndef _PLAN_
#define _PLAN_
#include "Objet.hpp"

struct Plan : public Objet
{
	D3DXVECTOR3 n;
	Plan();
	Plan(D3DXVECTOR3 N);
	void Plan::setNormale(float x, float y, float z);
	bool intersection(D3DXVECTOR3& o, D3DXVECTOR3& ray);
	D3DXVECTOR3 getNormal(D3DXVECTOR3 inter);
};

#endif