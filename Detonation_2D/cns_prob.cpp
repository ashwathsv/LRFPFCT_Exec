
#include <AMReX_PROB_AMR_F.H>
#include <AMReX_ParmParse.H>
#include "cns_prob_parm.H"
#include "CNS.H"

extern "C" {
    void amrex_probinit (const int* /*init*/,
                         const int* /*name*/,
                         const int* /*namelen*/,
                         const amrex_real* /*problo*/,
                         const amrex_real* /*probhi*/)
    {
        amrex::ParmParse pp("prob");

        pp.get("p1", CNS::h_prob_parm->p1);
        pp.get("p0", CNS::h_prob_parm->p0);

        pp.get("T1", CNS::h_prob_parm->T1);
        pp.get("T0", CNS::h_prob_parm->T0);

        pp.query("u1", CNS::h_prob_parm->u1);
        pp.query("u0", CNS::h_prob_parm->u0);

        pp.query("v1", CNS::h_prob_parm->v1);
        pp.query("v0", CNS::h_prob_parm->v0);

        pp.get("dia_blast", CNS::h_prob_parm->dia_blast);

        pp.get("Y1", CNS::h_prob_parm->Y1);
        pp.get("Y0", CNS::h_prob_parm->Y0);

        pp.get("xcm", CNS::h_prob_parm->xcm);
        pp.get("ycm", CNS::h_prob_parm->ycm);

#if AMREX_SPACEDIM==3
        pp.get("zcm", CNS::h_prob_parm->zcm);

        pp.query("w1", CNS::h_prob_parm->w1);
        pp.query("w0", CNS::h_prob_parm->w0);

#endif

#ifdef AMREX_USE_GPU
        amrex::Gpu::htod_memcpy(CNS::d_prob_parm, CNS::h_prob_parm, sizeof(ProbParm));
#else
        std::memcpy(CNS::d_prob_parm, CNS::h_prob_parm, sizeof(ProbParm));
        // amrex::Gpu::copy(amrex::Gpu::hostToDevice, CNS::h_prob_parm, CNS::h_prob_parm+1,
        //                  CNS::d_prob_parm);
#endif

    }
}
