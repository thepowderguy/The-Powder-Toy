#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_GPHT PT_GPHT 185
Element_GPHT::Element_GPHT()
{
	Identifier = "DEFAULT_PT_GPHT";
	Name = "GPHT";
	Colour = PIXPACK(0x444444);
	MenuVisible = 1;
	MenuSection = SC_NUCLEAR;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.90f;
	Loss = 0.00f;
	Collision = 0.0f;
	Gravity = 0.0f;
	Diffusion = 0.0f;
	HotAir = 0.0f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 20;

	Weight = 100;

	Temperature = R_TEMP+0.0f	+273.15f;
	HeatConduct = 200;
	Description = "Graphite. Slows neutrons, flammable when exposed to air.";

	Properties = TYPE_SOLID | PROP_HOT_GLOW | PROP_NEUTPASS;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 4000.0f;
	HighTemperatureTransition = PT_LAVA;

	Update = &Element_GPHT::update;
}

//#TPT-Directive ElementHeader Element_GPHT static int update(UPDATE_FUNC_ARGS)
int Element_GPHT::update(UPDATE_FUNC_ARGS)
{
	if (parts[i].temp > 2000.0f) {
		bool flam = false;
		for (int rx = -1; rx <= 1; rx++) {
			for (int ry = -1; ry <= 1; ry++) {
				if (BOUNDS_CHECK) {
					int etype = (pmap[y+ry][x+rx] & 0xFF);
					if (etype == PT_NONE)
					{
						sim->pv[y/CELL][x/CELL] += 0.2*CFDS;
						if (!(rand()%20)) {
							parts[sim->create_part(-1, x+rx, y+ry, PT_FIRE)].temp = parts[i].temp + 50.0f;
							flam = true;
						}
					}
				}
			}
		}
		if (flam && !(rand()%3))
			sim->kill_part(i);
	}
	return 0;
}

Element_GPHT::~Element_GPHT() {}