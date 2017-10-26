#ifndef _OBJET_
#define _OBJET_
#include <d3d11.h>
#include <d3dx11.h>
#include <DxErr.h>
#include <DXUT.h>
#include "Texture.hpp"

struct Objet
{
	D3DXVECTOR3 o;
	D3DXVECTOR3 ambiant, dif, spec;
	float c_ambiant, c_dif, c_spec;
	float coef_reflexion, coef_refraction;
	TEX t;
	bool reflexion, refraction;
	Objet();
	virtual bool intersection(D3DXVECTOR3& o, D3DXVECTOR3& ray) = 0;
};

#endif