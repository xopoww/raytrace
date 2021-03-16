#include "linalg/math.hpp"

#include <cmath>

std::pair<coord_t, coord_t> solve_quadratic(
    const coord_t a, const coord_t b, const coord_t c)
{
    if (a == 0.l)
    {
        if (b == 0.l)
        {
            return {infinity, infinity};
        }

        coord_t k = -c / b;
        return {k, k};
    }

    coord_t D2 = b*b - 4 * a * c;

    if (D2 < 0)
    {
        return {infinity, infinity};
    }

    if (D2 == 0.l)
    {
        coord_t x = -b / 2 / a;
        return {x, x};
    }

    coord_t D = std::sqrt(D2);

    return {
        (-b - D) / 2 / a,
        (-b + D) / 2 / a
    };
}