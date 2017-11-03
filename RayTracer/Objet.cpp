#include "Objet.hpp"
#include <iostream>

Objet::Objet()
{
	o = D3DXVECTOR3(10,0 ,0);
	ambiant = D3DXVECTOR3(120, 10, 10);
	dif = D3DXVECTOR3(255, 0, 0);
	spec = D3DXVECTOR3(255,255,255);
	coef_reflexion = 0.f;
	coef_refraction = 0.f;
	c_ambiant = 0.01;
	c_dif = 0.84;
	c_spec = 0.15;
	reflexion = false;
	refraction = false;
	t = NONE;
}

void Objet::setOrigine(float x, float y, float z)
{
	o = D3DXVECTOR3(x, y, z);
}

void  Objet::setTexture(TEX_PROC tex)
{
	t = tex;
}

void  Objet::setAmbiant(float b, float g, float r, float coef)
{
	ambiant = D3DXVECTOR3(b, g, r);
	c_ambiant = coef;
}

void  Objet::setDiffusion(float b, float g, float r, float coef)
{
	dif = D3DXVECTOR3(b, g, r);
	c_dif = coef;
}

void  Objet::setSpeculaire(float b, float g, float r, float coef)
{
	spec = D3DXVECTOR3(b, g, r);
	c_spec = coef;
}

void  Objet::transparent(float coef)
{
	refraction = true;
	coef_refraction = coef;
}

void  Objet::opaque()
{
	refraction = false;
}

void  Objet::reflet(float coef)
{
	reflexion = true;
	coef_reflexion = coef;
}

void  Objet::sans_reflet()
{
	reflexion = false;
}