#include "random.hpp"

#include <random>
#include <chrono>

unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine rng(seed);

int random_int(const bool _signed)
{
    return _signed && rng() % 2 ? -(int)rng() : rng();
}

coord_t random_frac()
{
    return (coord_t)rng() / (coord_t)rng.max();
}
