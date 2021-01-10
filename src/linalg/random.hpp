#pragma once

//
// Random number generation utilities
//

#include "math.hpp"

// Generate random integer
// if _signed is false, the integer will be non-negative
int random_int(const bool _signed = true);

// Generate random fractional from range [0, 1)
coord_t random_frac();
