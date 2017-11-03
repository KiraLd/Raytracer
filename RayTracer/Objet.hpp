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
	TEX_PROC t;
	bool reflexion, refraction;
	Objet();

	void setOrigine(float x, float y, float z);
	void setTexture(TEX_PROC t);
	void setAmbiant(float b, float g, float r, float coef);
	void setDiffusion(float b, float g, float r, float coef);
	void setSpeculaire(float b, float g, float r, float coef);
	void transparent(float coef);
	void opaque();
	void reflet(float coef);
	void sans_reflet();

	virtual bool intersection(D3DXVECTOR3& o, D3DXVECTOR3& ray) = 0;
	virtual D3DXVECTOR3 getNormal(D3DXVECTOR3 inter) = 0;
};

#endif