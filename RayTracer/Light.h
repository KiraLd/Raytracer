#ifndef _LIGHT_
#define _LIGHT_
#include <d3d11.h>
#include <d3dx11.h>
#include <DxErr.h>
#include <DXUT.h>

struct Light
{
	D3DXVECTOR3 o;
	D3DXVECTOR3 dif, spec;
	float c_dif, c_spec;

	Light();
	Light(D3DXVECTOR3 at, D3DXVECTOR3 dif, D3DXVECTOR3 spec, float c_dif, float c_spec);
	
	void setOrigine(float x, float y, float z);
	void setDiffuse(float b, float g, float r, float coef);
	void setSpeculaire(float b, float g, float r, float coef);


};

#endif
