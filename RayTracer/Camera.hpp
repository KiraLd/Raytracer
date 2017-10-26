#include <d3d11.h>
#include <d3dx11.h>
#include <DxErr.h>
#include <DXUT.h>

#ifndef _CAMERA_
#define _CAMERA_

struct Camera
{
	D3DXMATRIX projection, view;
	D3DXVECTOR3 eye, at, up;

	//near, far
	float n, f;

	//angle d'ouverture/focale: PI/4
	float fov;

	//Résolution
	int hauteur, largeur;

	Camera();
	Camera(float fov, int W, int H, float n, float f, D3DXVECTOR3 eye, D3DXVECTOR3 at, D3DXVECTOR3 up);
	void move(float x, float y, float z);
	void translate(float x, float y, float z);
	void update();
	D3DXVECTOR3 getRay(int i, int j, D3DXVECTOR3 translat, D3DXVECTOR3& origin );
};

#endif