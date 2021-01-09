#pragma once

//
// Basic mathematic functions and other utilities
//


// type for all coordinates / angles / etc
typedef long double coord_t;


#include <limits>

const coord_t infinity = std::numeric_limits<coord_t>::infinity();


#include <utility>

// Solve the quadratic equasion a*x^2 + b*x + c = 0
// If the equasion has only one real root, it will be both first and second
// field of the returned pair. If there are no real roots, the returned pair
// will have infinity as its first and second field.
std::pair<coord_t, coord_t> solve_quadratic(
    const coord_t a, const coord_t b, const coord_t c);
