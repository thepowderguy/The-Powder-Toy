#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_MODR PT_MODR 183
Element_MODR::Element_MODR()
{
	Identifier = "DEFAULT_PT_MODR";
	Name = "MODR";
	Colour = PIXPACK(0x203040);
	MenuVisible = 1;
	MenuSection = SC_NUCLEAR;
	Enabled = 1;

	Advection = 0.3f;
	AirDrag = 0.02f * CFDS;
	AirLoss = 0.98f;
	Loss = 0.80f;
	Collision = 0.0f;
	Gravity = 0.3f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 2;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 2;

	Weight = 90;

	Temperature = R_TEMP-2.0f	+273.15f;
	HeatConduct = 220;
	Description = "Slows neutrons.";

	Properties = TYPE_LIQUID|PROP_NEUTPASS;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 3500.0f;
	HighTemperatureTransition = PT_PLSM;

	Update = &Element_MODR::update;
}

//#TPT-Directive ElementHeader Element_MODR static int update(UPDATE_FUNC_ARGS)
int Element_MODR::update(UPDATE_FUNC_ARGS)
{
	return 0;
}

Element_MODR::~Element_MODR() {}