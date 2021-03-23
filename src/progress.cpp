#include "progress.hpp"


Progress::Progress(const std::size_t total_iterations, const Progress::callback_t &_callback):
    total_it(total_iterations), curr_it(0), callback(_callback)
{
}

void Progress::add(const std::size_t delta)
{
    if (this->curr_it >= this->total_it)
    {
        return;
    }

    #ifdef RAYTRACE_USE_OMP
    #pragma omp critical
    #endif
    {
        this->curr_it += delta;
        this->callback(this->curr_it, this->total_it);
    }
}