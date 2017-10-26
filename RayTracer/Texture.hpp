#ifndef _TEXTURE_
#define _TEXTURE
#include "SimplexNoise.hpp"
#include <d3d11.h>
#include <d3dx11.h>
#include <DxErr.h>
#include <DXUT.h>

enum TEX {NONE,PERLIN,BOIS,MARBRE};

D3DXVECTOR3 getTexture(TEX t, float x, float y, float z, D3DXVECTOR3 ambiant, D3DXVECTOR3 dif, D3DXVECTOR3 spec);

D3DXVECTOR3 perlin(float x, float y, float z, D3DXVECTOR3 ambiant, D3DXVECTOR3 dif, D3DXVECTOR3 spec);
D3DXVECTOR3 bois(float x, float y, float z, D3DXVECTOR3 ambiant, D3DXVECTOR3 dif, D3DXVECTOR3 spec);
D3DXVECTOR3 marbre(float x, float y, float z, D3DXVECTOR3 ambiant, D3DXVECTOR3 dif, D3DXVECTOR3 spec);




#endif