#ifndef CNS_PROB_PARM_H_
#define CNS_PROB_PARM_H_

#include <AMReX_REAL.H>
#include <AMReX_GpuMemory.H>

using namespace amrex::literals;

struct ProbParm
{
    amrex::Real pl   = 1.0;
    amrex::Real rhol = 1.0;
    amrex::Real ul   = 0.0;

    amrex::Real pr   = 0.1;
    amrex::Real rhor = 0.125;
    amrex::Real ur   = 0.0;

    amrex::Real Yl   = 0.0;
    amrex::Real Yr   = 0.0;

    int case_num = 1;
};

#endif
