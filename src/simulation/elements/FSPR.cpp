#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_FSPR PT_FSPR 181
Element_FSPR::Element_FSPR()
{
	Identifier = "DEFAULT_PT_FSPR";
	Name = "FSPR";
	Colour = PIXPACK(0x303030);
	MenuVisible = 1;
	MenuSection = SC_NUCLEAR;
	Enabled = 1;

	Advection = 0.4f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.99f;
	Loss = 0.95f;
	Collision = 0.0f;
	Gravity = 0.4f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 1;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 0;

	Weight = 90;

	Temperature = R_TEMP+4.0f	+273.15f;
	HeatConduct = 251;
	Description = "Fission product";

	Properties = TYPE_PART|PROP_NEUTPASS|PROP_RADIOACTIVE;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_FSPR::update;
}

//#TPT-Directive ElementHeader Element_FSPR static int update(UPDATE_FUNC_ARGS)
int Element_FSPR::update(UPDATE_FUNC_ARGS)
{
	if ((sim->photons[y][x] & 0xFF) == PT_NEUT && !(rand()%40)) {
		sim->kill_part(sim->photons[y][x] >> 8);
	}
	if (parts[i].life > 0 && !(rand()%10000)) {
		sim->create_part(-3, x, y, PT_GMMA);
		parts[i].life--;
	}
	return 0;
}


Element_FSPR::~Element_FSPR() {}
