#include "Camera.hpp"
#include <iostream>

Camera::Camera()
{
	eye = D3DXVECTOR3(0.f, 0.f, 0.f);
	at = D3DXVECTOR3(1.f, 0.f, 0.f);
	up = D3DXVECTOR3(0.f, 1.f, 0.f);
	n = 0.1;
	f = 100000;
	hauteur = 480;
	largeur = 600;
	fov = D3DX_PI / 4.f;
	D3DXMatrixPerspectiveFovLH(&projection, fov, (float)largeur / (float)hauteur, n, f);
	update();
}

Camera::Camera(float fov, int W, int H, float n, float f, D3DXVECTOR3 eye, D3DXVECTOR3 at, D3DXVECTOR3 up)
{
	D3DXMatrixPerspectiveFovLH(&projection, fov, (float)W / (float)H, n, f);
	D3DXMatrixLookAtLH(&view, &eye, &at, &up);
	this->eye = D3DXVECTOR3(eye);
	this->at = D3DXVECTOR3(at);
	this->up = D3DXVECTOR3(up);
	this->fov = fov;
	this->n = n;
	this->f = f;
	this->hauteur = H;
	this->largeur = W;
	update();
}

void Camera::move(float x, float y, float z)
{
	this->eye = D3DXVECTOR3(x, y, z);
	D3DXMatrixLookAtLH(&view, &eye, &at, &up);
}

void Camera::translate(float x, float y, float z)
{
	this->eye += D3DXVECTOR3(x, y, z);
	this->at += D3DXVECTOR3(x, y, z);
	D3DXMatrixLookAtLH(&view, &eye, &at, &up);
}

void Camera::update()
{
	D3DXMatrixLookAtLH(&view, &eye, &at, &up);
}

D3DXVECTOR3 Camera::getRay(int i, int j, D3DXVECTOR3 translat, D3DXVECTOR3& origin)
{
	D3DXVECTOR3 ray;
	ray.x = 2 * (float)i / (float)largeur - 1.f;
	ray.y = 2 * (float)j / (float)hauteur - 1.f;
	ray.x = ray.x / projection._11;
	ray.y = -ray.y / projection._22;
	ray.z = 1.f;
	
	D3DXMATRIX view;
	D3DXMATRIX translation;
	D3DXMatrixTranslation(&translation, translat.x, translat.y, translat.z);
	float det;
	view = translation*this->view;
	D3DXMatrixInverse(&view, &det, &view);

	D3DXVECTOR3 dir;
	dir.x = ray.x*view._11 + ray.y * view._21 + ray.z * view._31;
	dir.y = ray.x*view._12 + ray.y * view._22 + ray.z * view._32;
	dir.z = ray.x*view._13 + ray.y * view._23 + ray.z * view._33;

	origin.x = view._41;
	origin.y = view._42;
	origin.z = view._43;

	return dir;
}