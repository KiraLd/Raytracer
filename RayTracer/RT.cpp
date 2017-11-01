#include "RT.hpp"
#include "Sphere.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>


RT::RT(int n, int l, int h)
{
	this->n = n;
	scene = new Objet*[n];
	background = D3DXVECTOR3(0, 0, 0);
	depth = new int[h*l];
	c = Camera();
	c.hauteur = h;
	c.largeur = l;
	hauteur = h;
	largeur = l;
	this->l = Light();
	rec_max = 10;

	image = new D3DXVECTOR3*[l];
	for (int i = 0; i < l; i++)
	{
		image[i] = new D3DXVECTOR3[h];
	}
}

inline float random()
{
	return float(std::rand()) / float(RAND_MAX);
}

inline float random(float min, float max)
{
	return random()*(max - min) + min;
}

void RT::generate(float r_max, float x_min, float x_max, float y_min, float y_max, float z_min, float z_max)
{
	std::srand(std::time(0));
	Sphere* temp;
	for (int i = 0; i < n; ++i)
	{
		
		temp = new Sphere(random(1, r_max));
		temp->o = D3DXVECTOR3(random(x_min + r_max, x_max + r_max), random(y_min-r_max, y_max + r_max), random(z_min-r_max, z_max + r_max));
		temp->ambiant = D3DXVECTOR3(random(0, 256), random(0, 256), random(0, 256));
		temp->dif = D3DXVECTOR3(random(0, 256), random(0, 256), random(0, 256));
		temp->spec = D3DXVECTOR3(256, 256, 256);
		temp->reflexion = true;
		temp->coef_reflexion = random(0.f, 1.0);	
		scene[i] = temp;
		
	}
	
}

void RT::intersection(int i, int j, D3DXVECTOR3& inter, int& min, bool& render)
{
	D3DXVECTOR3 ray;
	D3DXVECTOR3 org;
	D3DXVECTOR3 intersect;
	D3DXVECTOR3 vec_dist;
	float distance_min = INT_MAX;
	float dist;
	
	for (int k = 0; k < n; k++)
	{
		ray = c.getRay(i, j, scene[k]->o, org);
		intersect = ray;
		if (scene[k]->intersection(org, intersect))
		{
			render = true;
			vec_dist = scene[k]->o - c.eye;
			dist = D3DXVec3Length(&vec_dist);
			if (dist < distance_min)
			{
				distance_min = dist;
				min = k;
				inter = intersect;
			}
		}
	}
}

void RT::intersection(D3DXVECTOR3 origine, D3DXVECTOR3 dir, D3DXVECTOR3& inter, int& min, bool& render, int src)
{
	D3DXVECTOR3 ray;
	D3DXVECTOR3 org;
	D3DXVECTOR3 intersect;
	D3DXVECTOR3 vec_dist;
	float distance_min = 9999999;
	float dist;

	org = origine;

	for (int k = 0; k < n; k++)
	{
		ray = dir;
		intersect = ray;
		if (src != k && scene[k]->intersection(org, intersect))
		{
			render = true;
			vec_dist = scene[k]->o - c.eye;
			dist = D3DXVec3Length(&vec_dist);
			if (dist < distance_min)
			{
				distance_min = dist;
				min = k;
				inter = intersect;
			}
		}
	}
}

bool RT::ombre(D3DXVECTOR3 origine, int k)
{
	D3DXVECTOR3 ray = l.o - origine;
	float max = D3DXVec3Dot(&ray,&ray);
	D3DXVECTOR3 distance;
	float d;
	D3DXVECTOR3 inter;
	bool arret = false;
	for (int i = 0; i < n; i++)
	{
		if (i != k)
		{
			inter = ray;
			if (scene[i]->intersection(origine, inter))
			{
				distance = D3DXVECTOR3(inter - l.o);
				d = D3DXVec3Dot(&distance,&distance);
				if (d < max)
				{
					arret = true;
				}
				
			}
		}
	}
	return arret;
}

D3DXVECTOR3 RT::illumination(int min, D3DXVECTOR3& inter_point, D3DXVECTOR3& ray, int i, int j)
{
	D3DXVECTOR3 couleur(0, 0, 0);
	depth[j*largeur + i]++;
	if (!scene[min]->reflexion && ombre(inter_point, min))
	{
		couleur = scene[min]->ambiant * scene[min]->c_ambiant;
	}
	else
	{
		D3DXVECTOR3 normale = scene[min]->getNormal(inter_point);
		D3DXVec3Normalize(&normale, &normale);
		D3DXVECTOR3 light_dir = inter_point - l.o;
		D3DXVec3Normalize(&light_dir, &light_dir);
		float dot = -D3DXVec3Dot(&normale, &light_dir);
		if (dot < 0)
		{
			dot = 0.f;
		}
		D3DXVec3Normalize(&ray, &ray);
		D3DXVECTOR3 reflect = ray;
		reflect -= 2 * normale*D3DXVec3Dot(&normale, &reflect);
		light_dir = -light_dir;
		float coef_spec = max(D3DXVec3Dot(&light_dir,&reflect),0.f);
		coef_spec *= coef_spec;
		if (scene[min]->t == NONE)
		{
			couleur = scene[min]->dif * scene[min]->c_dif*dot + coef_spec* scene[min]->spec *scene[min]->c_spec;
			
		}
		else
		{
			couleur = getTexture(scene[min]->t, inter_point.x, inter_point.y, inter_point.z, scene[min]->ambiant, scene[min]->dif, scene[min]->spec) *(scene[min]->c_dif*dot + coef_spec*scene[min]->c_spec);
		}
		
		if (scene[min]->reflexion && depth[j*largeur + i] < rec_max)
		{
			couleur = couleur * (1.f - scene[min]->coef_reflexion);
			couleur += scene[min]->ambiant * scene[min]->c_ambiant;
			couleur += scene[min]->coef_reflexion*render_step(inter_point, reflect, i, j, min);
		}
		couleur += scene[min]->ambiant * scene[min]->c_ambiant;
		
	}

	return couleur;
	
}

D3DXVECTOR3 RT::render_step(float i, float j)
{
	
	int min;
	bool render;
	D3DXVECTOR3 inter_point;
	depth[(int)j*largeur + (int)i] = 0;
	min = 0;
	render = false;
	intersection((int)i, (int)j, inter_point, min, render);
	D3DXVECTOR3 couleur;
	if (render)
	{
		D3DXVECTOR3 org;
		D3DXVECTOR3 ray = c.getRay((int)i, (int)j, scene[min]->o, org);
		couleur = illumination(min, inter_point,ray,(int)i,(int)j);
	}
	else
	{
		couleur = background;
	}
	
	return couleur;
}

D3DXVECTOR3 RT::render_step(D3DXVECTOR3 origine, D3DXVECTOR3 dir, int i, int j, int src)
{
	int min;
	bool render;
	D3DXVECTOR3 inter_point;
	min = 0;
	render = false;
	intersection(origine,dir, inter_point, min, render, src);
	D3DXVECTOR3 couleur;
	if (render)
	{
		couleur = illumination(min, inter_point,dir,i,j);
	}
	else
	{
		couleur = background;
	}
	return couleur;
}

void RT::render()
{
	#pragma omp parallel for
	for (int i = 0; i < largeur; ++i)
	{
		for (int j = 0; j < hauteur; ++j)
		{
			image[i][j] = render_step(i, j);

		}
	}
}



void RT::getImage()
{
	img_final = Mat(hauteur, largeur, CV_8UC3);

	for (int i = 0; i < largeur; i++)
	{
		for (int j = 0; j < hauteur; j++)
		{

			
			img_final.at<Vec3b>(j,i)[0] = (uchar)image[i][j].x;
			img_final.at<Vec3b>(j,i)[1] = (uchar)image[i][j].y;
			img_final.at<Vec3b>(j,i)[2] = (uchar)image[i][j].z;
		}
	}
}