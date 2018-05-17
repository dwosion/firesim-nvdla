#ifndef __FIRESIM_TOP_H
#define __FIRESIM_TOP_H

#include "simif.h"
#include "fesvr/fesvr_proxy.h"
#include "endpoints/endpoint.h"
#include "endpoints/fpga_model.h"
#include "endpoints/loadmem_m.h"

class firesim_top_t: virtual simif_t
{
    public:
        firesim_top_t(int argc, char** argv, std::vector<fesvr_proxy_t*> fesvr_vec);
        ~firesim_top_t() { }

        void run(size_t step_size);
        void loadmem();
        void print_sim_rate();

    protected:
        void add_endpoint(endpoint_t* endpoint) {
            endpoints.push_back(endpoint);
        }

    private:
        std::vector<loadmem_m> loadmem_vec;

        uint64_t start_time;

        // Memory mapped endpoints bound to software models
        std::vector<endpoint_t*> endpoints;
        // FPGA-hosted models with programmable registers & instrumentation
        std::vector<FpgaModel*> fpga_models;
        std::vector<fesvr_proxy_t*> fesvr_vec;
        uint64_t max_cycles;

        // profile interval: # of cycles to advance before profiling instrumentation registers in models
        // This sets the coarse_step_size in loop
        uint64_t profile_interval;

        // Main simulation loop
        // stepsize = number of target cycles between FESVR interactions
        // coarse_step_size = maximum number of target cycles loop may advance the simulator
        void loop(size_t step_size, uint64_t coarse_step_size);
};

#endif // __FIRESIM_TOP_H
