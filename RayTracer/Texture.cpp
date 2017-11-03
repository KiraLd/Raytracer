#include "Texture.hpp"

const float pi = 3.1415926f;

D3DXVECTOR3 getTexture(TEX_PROC t, float x, float y, float z, D3DXVECTOR3 ambiant, D3DXVECTOR3 dif, D3DXVECTOR3 spec)
{
	if (t == PERLIN)
	{
		return perlin(x, y, z, ambiant, dif, spec);
	}
	if (t == BOIS)
	{
		return bois(x, y, z, ambiant, dif, spec);
	}
	if (t == MARBRE)
	{
		return marbre(x, y, z, ambiant, dif, spec);
	}
	return ambiant;
}

D3DXVECTOR3 perlin(float x, float y, float z, D3DXVECTOR3 ambiant, D3DXVECTOR3 dif, D3DXVECTOR3 spec)
{
	float n = SimplexNoise1234::noise(x, y, z);
	float V1 = 0.05;
	float V2 = 0.75;
	float V3 = 1;
	if (n < V1)
	{
		return ambiant;
	}
	if (n > V1 && n < V2)
	{
		return ambiant*(n - V1) / (V2 - V1) + dif*(V2 - n) / (V2 - V1);
	}
	if (V2 < n && n < V3)
	{
		return dif*(n - V2) / (V3 - V2) + spec*(V3 - n) / (V3 - V2);
	}
	return spec;
}

D3DXVECTOR3 bois(float x, float y, float z, D3DXVECTOR3 ambiant, D3DXVECTOR3 dif, D3DXVECTOR3 spec)
{
	float T = 20 * SimplexNoise1234::noise(x, y, z);
	float n = T - floorf(T);
	float ft = pi*n;
	float f = (1 - cosf(ft))*0.5f;
	return ambiant*(1.f - f) + dif*f;
}

D3DXVECTOR3 marbre(float x, float y, float z, D3DXVECTOR3 ambiant, D3DXVECTOR3 dif, D3DXVECTOR3 spec)
{
	float n = cosf(x + SimplexNoise1234::noise(x, y, z));
	return ambiant*(1.f - n) + dif*n;
}