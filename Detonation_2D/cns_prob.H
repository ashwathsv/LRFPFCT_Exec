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
    Real y = prob_lo[1] + (j+Real(0.5))*dx[1];
#if AMREX_SPACEDIM==3
    Real z = prob_lo[2] + (k+Real(0.5))*dx[2];
#endif

    Real rad = 0.5 * prob_parm.dia_blast;
    Real dist = ((x-prob_parm.xcm)*(x-prob_parm.xcm)) 
              + ((y-prob_parm.ycm)*(y-prob_parm.ycm)) - (rad*rad);
#if AMREX_SPACEDIM==3
    dist += ((z-prob_parm.zcm)*(z-prob_parm.zcm));
#endif

    Real Pt, rhot, uxt, uyt, uzt, Yt, Temp;
    if(dist <= Real(0.0)){
        Pt = prob_parm.p1;
        rhot = Pt / (eos_parm.Rsp * prob_parm.T1);
        uxt = prob_parm.u1;
        uyt = prob_parm.v1;
        Yt  = prob_parm.Y1;
        Temp  = prob_parm.T1;
#if AMREX_SPACEDIM==3
        uzt = prob_parm.w1;
#endif  
    }else{
        Pt = prob_parm.p0;
        rhot = Pt / (eos_parm.Rsp * prob_parm.T0);
        uxt = prob_parm.u0;
        uyt = prob_parm.v0;       
        Yt = prob_parm.Y0;
        Temp  = prob_parm.T0;
#if AMREX_SPACEDIM==3
        uzt = prob_parm.w0;
#endif        
    }
    state(i,j,k,URHO ) = rhot;
    state(i,j,k,UMX  ) = rhot*uxt;
    state(i,j,k,UMY  ) = rhot*uyt;
#if AMREX_SPACEDIM==3        
    state(i,j,k,UMZ  ) = rhot*uzt;
#endif
    Real et = Pt/(eos_parm.eos_gamma-Real(1.0));
    state(i,j,k,UEINT) = et;
    state(i,j,k,UPRE)  = Pt;

#if AMREX_SPACEDIM==2
    state(i,j,k,UEDEN) = et + Real(0.5)*rhot*(uxt*uxt + uyt*uyt);
#else 
    state(i,j,k,UEDEN) = et + Real(0.5)*rhot*(uxt*uxt + uyt*uyt + uzt*uzt);
#endif
#ifdef LRFPFCT_REACTION
    state(i,j,k,URHOY) = rhot*Yt;
    state(i,j,k,SFOIL) = Real(0.0);
#endif
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

AMREX_GPU_HOST_DEVICE
inline
void
cns_probspecific_func (amrex::MultiFab& State, amrex::GeometryData const& geomdata, ProbParm& prob_parm,
                        int stepnum, amrex::Real time, amrex::Real dt)
{

}

#endif
