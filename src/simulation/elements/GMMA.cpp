#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_GMMA PT_GMMA 182
Element_GMMA::Element_GMMA()
{
	Identifier = "DEFAULT_PT_GMMA";
	Name = "GMMA";
	Colour = PIXPACK(0xBB77FF);
	MenuVisible = 1;
	MenuSection = SC_NUCLEAR;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 1.00f;
	Loss = 1.00f;
	Collision = -0.99f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 0;

	Weight = -1;

	Temperature = R_TEMP+273.15f;
	HeatConduct = 0;
	Description = "High energy photons.";

	Properties = TYPE_ENERGY|PROP_LIFE_DEC|PROP_LIFE_KILL_DEC;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_GMMA::update;
	Graphics = &Element_GMMA::graphics;
}

//#TPT-Directive ElementHeader Element_GMMA static int update(UPDATE_FUNC_ARGS)
int Element_GMMA::update(UPDATE_FUNC_ARGS)
{
	int part = pmap[y][x] & 0xFF;
	if (part == PT_TTAN || part == PT_WATR || part == PT_DSTW || part == PT_SLTW || part == PT_TUNG) {
		if (!(rand()%2)) {
			sim->kill_part(i);
		}
	}
	return 0;
}

//#TPT-Directive ElementHeader Element_GMMA static int graphics(GRAPHICS_FUNC_ARGS)
int Element_GMMA::graphics(GRAPHICS_FUNC_ARGS)

{
	*firea = 70;
	*firer = *colr;
	*fireg = *colg;
	*fireb = *colb;

	*pixel_mode |= FIRE_ADD;
	return 0;
}


Element_GMMA::~Element_GMMA() {}
