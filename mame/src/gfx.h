#pragma once
extern "C" {

struct MachineDriver;
struct GfxElement;  

void write_gfx(int n, struct GfxElement* g, MachineDriver* drv);

} 
