#ifndef _RT_
#define _RT_
#include "Objet.hpp"
#include "Light.h"
#include "Camera.hpp"
#include <opencv2/core/core.hpp>
using namespace cv;

struct RT
{
	D3DXVECTOR3 background;
	Objet** scene;
	D3DXVECTOR3** image;
	int* depth;
	int largeur, hauteur;
	int n;
	int rec_max;

	Light l;

	Camera c;

	Mat img_final;

	RT(int n, int l, int h);
	void generate(float r_max, float x_min, float x_max, float y_min, float y_max, float z_min, float z_max);
	void render();
	void getImage();
	void intersection(int i, int j, D3DXVECTOR3& inter, int& min, bool& render);
	void intersection(D3DXVECTOR3 origine, D3DXVECTOR3 dir, D3DXVECTOR3& inter, int& min, bool& render, int src);
	bool ombre(D3DXVECTOR3 origine, int k);
	D3DXVECTOR3 illumination(int min, D3DXVECTOR3& inter_point, D3DXVECTOR3& ray, int i, int j);
	D3DXVECTOR3 render_step(float i, float j);
	D3DXVECTOR3 render_step(D3DXVECTOR3 origine, D3DXVECTOR3 dir, int i, int j, int min);
	void setRecursionMax(int r);

	//TODO: changer getImage
	void saveImage(std::string file);
	void showImg(int time);

	


};

#endif