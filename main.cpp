#include"PPM.h"
#include"PGM.h"
#include"PBM.h"


int main()
{
	PPM img;
	img.load("6colour_ppma.ppm");
	std::cout << img << '\n';
	//std::cout << img;
	//std::cout << "==============================================\n";
	//img.grayscale();
	//std::cout << img;
	//std::cout << "==============================================\n";
	//img.monochrome();
	//std::cout << img;
	//std::cout << "==============================================\n";
	img.rotation("right");
	std::cout << img;
	//std::cout << "==============================================\n";
	//img.save("newPPMGrayscale.ppm");
	//img.negative();
	//img.save("negativePPM.ppm");

	return 0;
}