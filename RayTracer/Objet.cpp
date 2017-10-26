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
	c_ambiant = 0.05;
	c_dif = 0.8;
	c_spec = 0.15;
	reflexion = false;
	refraction = false;
	t = NONE;
}