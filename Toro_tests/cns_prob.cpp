
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

        pp.query("case_num", CNS::h_prob_parm->case_num);

        pp.query("Yl", CNS::h_prob_parm->Yl);
        pp.query("Yr", CNS::h_prob_parm->Yr);

        pp.query("pr", CNS::h_prob_parm->pr);
        pp.query("pl", CNS::h_prob_parm->pl);

        pp.query("ul", CNS::h_prob_parm->ul);
        pp.query("ur", CNS::h_prob_parm->ur);


        pp.query("rhol", CNS::h_prob_parm->rhol);
        pp.query("rhor", CNS::h_prob_parm->rhor);

#ifdef AMREX_USE_GPU
        amrex::Gpu::htod_memcpy(CNS::d_prob_parm, CNS::h_prob_parm, sizeof(ProbParm));
#else
        std::memcpy(CNS::d_prob_parm, CNS::h_prob_parm, sizeof(ProbParm));
#endif

    }
}
