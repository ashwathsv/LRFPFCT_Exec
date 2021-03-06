#ifndef CNS_PROB_H_
#define CNS_PROB_H_

#include <AMReX_Geometry.H>
#include <AMReX_FArrayBox.H>
#include "CNS_index_macros.H"
#include "CNS_parm.H"
#include "LRFPFCT_EOS_parm.H"
#include "cns_prob_parm.H"

// #ifdef AMREX_USE_GPU
AMREX_GPU_DEVICE
inline
void
cns_initdata (int i, int j, int k, amrex::Array4<amrex::Real> const& state,
              amrex::GeometryData const& geomdata, 
              Parm const& parm, EOSParm const& eos_parm,  ProbParm const& prob_parm)
{
    using amrex::Real;

    const Real* prob_lo = geomdata.ProbLo();
    const Real* prob_hi = geomdata.ProbHi();
    const Real* dx      = geomdata.CellSize();

    Real x = prob_lo[0] + (i+Real(0.5))*dx[0];

    Real Pt, rhot, uxt, uyt, Yt, Temp;
    if(x < 0.5*(prob_lo[0] + prob_hi[0])){
        Pt = prob_parm.pl;
        rhot = prob_parm.rhol;
        uxt = prob_parm.ul;
        uyt = Real(0.0);
        Yt  = prob_parm.Yl;
        Temp  = Pt / (rhot * eos_parm.Rsp);  
    }else{
        Pt = prob_parm.pr;
        rhot = prob_parm.rhor;
        uxt = prob_parm.ur;
        uyt = Real(0.0);       
        Yt = prob_parm.Yr;
        Temp  = Pt / (rhot * eos_parm.Rsp);  
    }
    state(i,j,k,URHO ) = rhot;
    state(i,j,k,UMX  ) = rhot*uxt;
    state(i,j,k,UMY  ) = rhot*uyt;
    
    Real et = Pt/(eos_parm.eos_gamma-Real(1.0));
    state(i,j,k,UEINT) = et;
    state(i,j,k,UPRE)  = Pt;

    state(i,j,k,UEDEN) = et + Real(0.5)*rhot*(uxt*uxt + uyt*uyt);
    state(i,j,k,UTEMP) = Temp;
    
}

AMREX_GPU_DEVICE
AMREX_FORCE_INLINE
void
cns_probspecific_bc(
  const amrex::Real x[AMREX_SPACEDIM],
  const amrex::Real s_int[NGROW][NCONS],
  amrex::Real s_ext[NCONS],
  const int /*idir*/,
  const int /*ind*/,
  const int /*sgn*/,
  const amrex::Real /*time*/,
  amrex::GeometryData const& /*geomdata*/,
  ProbParm const& /*prob_parm*/)
{

}

AMREX_GPU_HOST
inline
void
cns_probspecific_func (amrex::MultiFab& State, amrex::GeometryData const& geomdata, ProbParm& prob_parm,
                        int stepnum, amrex::Real time, amrex::Real dt)
{

}

#endif
