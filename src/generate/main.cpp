#include "main.h"
#include "generate.h"

int main(int argc, char **argv)
{
	//ScreenResolution screenRes = {320, 200};
    //generate(GEN_ROTO, &screenRes, false);
	//generate(GEN_PLASMA, &screenRes, true);

	ScreenResolution screenRes = {80, 50};
	//generate(GEN_ROTO80, &screenRes, false);
	
	generate(GEN_DRAWTEXT, &screenRes, false);

    return 0;
}
