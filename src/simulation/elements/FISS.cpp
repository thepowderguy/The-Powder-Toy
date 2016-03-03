#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_FISS PT_FISS 600
Element_FISS::Element_FISS()
{
	Identifier = "DEFAULT_PT_FISS";
	Name = "FISS";
	Colour = PIXPACK(0x703010);
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
	Description = "Accurate nuclear fission test - plutonium";

	Properties = TYPE_PART|PROP_NEUTPASS|PROP_RADIOACTIVE;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_FISS::update;
}

//#TPT-Directive ElementHeader Element_FISS static int update(UPDATE_FUNC_ARGS)
int Element_FISS::update(UPDATE_FUNC_ARGS)
{
	if (!rand()%20000 || ((sim->photons[y][x] & 0xFF) == PT_NEUT && !(rand()%40)))
	{
		sim->part_change_type(i, x, y, PT_FSPR);
		parts[i].temp += 800.0;
		sim->create_part(-3, x, y, PT_NEUT);
	}
	return 0;
}


Element_FISS::~Element_FISS() {}
