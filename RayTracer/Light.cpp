#include "Light.h"

Light::Light()
{
	o = D3DXVECTOR3(0, 0, 0);
}

Light::Light(D3DXVECTOR3 at, D3DXVECTOR3 dif, D3DXVECTOR3 spec, float c_dif, float c_spec)
{
	o = at;
	this->dif = dif;
	this->spec = spec;
	this->c_dif = c_dif;
	this->c_spec = c_spec;
}

void Light::setOrigine(float x, float y, float z)
{
	o.x = x;
	o.y = y;
	o.z = z;
}

void Light::setDiffuse(float b, float g, float r, float coef)
{
	dif.x = b;
	dif.y = g;
	dif.z = r;
	c_dif = coef;
}

void Light::setSpeculaire(float b, float g, float r, float coef)
{
	spec.x = b;
	spec.y = g;
	spec.z = r;
	c_spec = coef;
}