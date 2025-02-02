#ifndef EXATIOGA_H
#define EXATIOGA_H

#include "TiogaAMRIface.h"
#include "StkIface.h"

namespace YAML {
class Node;
}

namespace TIOGA {
class tioga;
}

namespace tioga_amr {

class ExaTioga
{
public:
    ExaTioga(stk::ParallelMachine& comm);

    void init_amr(const YAML::Node&);

    void init_stk(const YAML::Node&);

    void execute(const YAML::Node&);

    void perform_connectivity();

    void exchange_solution();

    void check_solution_norm();

private:
    void run_timesteps(size_t ofileID);

    stk::ParallelMachine m_comm;

    tioga_nalu::StkIface m_stk;
    TiogaAMRIface m_amr;

    TIOGA::tioga& m_tioga;

    bool m_do_write{true};
    int m_output_freq{1};
};

} // namespace tioga_amr

#endif /* EXATIOGA_H */
