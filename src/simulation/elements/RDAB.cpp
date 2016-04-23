#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_RDAB PT_RDAB 184
Element_RDAB::Element_RDAB()
{
	Identifier = "DEFAULT_PT_RDAB";
	Name = "RDAB";
	Colour = PIXPACK(0x603030);
	MenuVisible = 1;
	MenuSection = SC_NUCLEAR;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.90f;
	Loss = 0.00f;
	Collision = 0.0f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 1;
	Hardness = 1;

	Weight = 100;

	Temperature = R_TEMP+0.0f	+273.15f;
	HeatConduct = 251;
	Description = "Radiation absorbing";

	Properties = TYPE_SOLID|PROP_HOT_GLOW;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 4500.0f;
	HighTemperatureTransition = PT_LAVA;

	Update = &Element_RDAB::update;
}

//#TPT-Directive ElementHeader Element_RDAB static int update(UPDATE_FUNC_ARGS)
int Element_RDAB::update(UPDATE_FUNC_ARGS)
{
	return 0;
}

Element_RDAB::~Element_RDAB() {}
