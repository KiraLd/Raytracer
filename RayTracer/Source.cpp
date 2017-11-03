#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <d3d11.h>
#include <fstream>
#include <d3dx11.h>
#include <DxErr.h>
#include <DXUT.h>
#include "RT.hpp"
#include "Sphere.hpp"
#include "Plan.hpp"
#include <cuda.h>
#include <cuda_runtime.h>
#include <cuda_gl_interop.h>
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"DxErr.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dxut.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"comctl32.lib")
#pragma comment(linker, "/nodefaultlib:MSVCRT") 
#include <time.h>


using namespace cv;
using namespace std;



int main(int argc, char** argv)
{


	RT rt = RT(2, 1024, 768);
	Sphere* s = new Sphere(5);
	Plan* p = new Plan();
	p->setOrigine(50, -5, 0);
	p->reflet(0.5);

	rt.scene[0] = s;
	rt.scene[1] = p;

	clock_t tStart = clock();
	rt.render();
	printf("Temps de rendu: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

	rt.showImg(100000);
	rt.saveImage(string("test.jpg"));
	
	return 0;
}