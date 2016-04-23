#include "simulation/Elements.h"
#include <cmath>
//#TPT-Directive ElementClass Element_FISS PT_FISS 180
Element_FISS::Element_FISS()
{
	Identifier = "DEFAULT_PT_FISS";
	Name = "FISS";
	Colour = PIXPACK(0xA07030);
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
	Description = "Nuclear fuel, undergoes fission";

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
	if (!rand()%10000)
	{
		sim->create_part(-3, x, y, PT_GMMA);
	}
	int npart = sim->photons[y][x];
	float velocity;
	if (!rand()%100000 || ((npart & 0xFF) == PT_NEUT && !(rand()%NeutInteractionChance(sim, npart >> 8, &velocity))))
	{
		if (parts[i].life == 0) {
			sim->part_change_type(i, x, y, PT_FSPR);
			parts[i].life = rand()%3;
		} else {
			parts[i].life--;
		}
		sim->kill_part(npart >> 8);
		parts[i].temp = MAX_TEMP;
		sim->pv[y/CELL][x/CELL] += (4.0 + fmin(velocity*6.0, 16.0)) * CFDS;
		parts[sim->create_part(-3, x, y, PT_NEUT)].temp = MAX_TEMP;
		parts[sim->create_part(-3, x, y, PT_NEUT)].temp = MAX_TEMP;
		Element_FIRE::update(UPDATE_FUNC_SUBCALL_ARGS);
		sim->create_part(-3, x, y, PT_GMMA);
	}
	return 0;
}

//#TPT-Directive ElementHeader Element_FISS static int NeutInteractionChance(Simulation* sim, int pid, float* velocity)
int Element_FISS::NeutInteractionChance(Simulation* sim, int pid, float* velocity) {
	*velocity = sqrt((sim->parts[pid].vx)*(sim->parts[pid].vx)+(sim->parts[pid].vy)*(sim->parts[pid].vy));
	return 20.0f*(3.0f-2.0f/(1.0f+0.5f*(*velocity)));
}

Element_FISS::~Element_FISS() {}
