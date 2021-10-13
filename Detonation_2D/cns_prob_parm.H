#ifndef CNS_PROB_PARM_H_
#define CNS_PROB_PARM_H_

#include <AMReX_REAL.H>
#include <AMReX_GpuMemory.H>

using namespace amrex::literals;

struct ProbParm
{
    amrex::Real dia_blast = 0.1;

    amrex::Real p1 = 1.0;
    amrex::Real p0 = 1.0;

    amrex::Real T1 = 3000;
    amrex::Real T0 = 298;

    amrex::Real u1 = 0.0;
    amrex::Real u0 = 0.0;

    amrex::Real v1 = 0.0;
    amrex::Real v0 = 0.0;

    amrex::Real Y1 = 0.0;
    amrex::Real Y0 = 1.0;

    amrex::Real xcm = 0.0;
    amrex::Real ycm = 0.0;

#if AMREX_SPACEDIM==3
    amrex::Real w1  = 0.0;
    amrex::Real w0  = 0.0;
    amrex::Real zcm = 0.0;
#endif

};

#endif
