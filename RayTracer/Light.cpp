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