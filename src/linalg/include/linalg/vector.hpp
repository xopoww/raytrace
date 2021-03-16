#pragma once

//
// 3D Vector and related operations / constants
//


#include "linalg/math.hpp"

#include <cstddef>

// 3D vector 
struct Vector3
{
    coord_t x;
    coord_t y;
    coord_t z;

    Vector3();

    Vector3(const coord_t _x, const coord_t _y, const coord_t _z);

    Vector3(const Vector3 &) = default;
    Vector3& operator=(const Vector3 &) = default;
    Vector3(Vector3 &&) = default;

    // Get the L2 norm of the vector
    coord_t length() const;

    // Get the normalized (i.e. with length = 1) vector colinear to this
    Vector3 norm() const;

    // Compute the dot product of two vectors, i.e. (this * other)
    coord_t dot(const Vector3 &other) const;
    
    // Compute the cross product of two vectors, i.e. [this * other]
    Vector3 cross(const Vector3 &other) const;

    // Get the projection of this on directon.
    Vector3 project(const Vector3 &direction) const;

    // rotate the vector for arccos(cos) around axis
    // (x for 0, y for 1, z for any other value)
    Vector3 rotate(const long double cos, const std::size_t axis) const;


    // convenience method; only valid values for i are 0, 1 or 2
    coord_t &operator[](const std::size_t i);
    coord_t operator[](const std::size_t i) const;
};

Vector3 operator+(const Vector3 &left, const Vector3 &right);

Vector3 operator-(const Vector3 &left, const Vector3 &right);

Vector3 operator*(const Vector3 &vec, const coord_t coef);


#include <iostream>

std::ostream & operator<<(std::ostream &os, const Vector3 &vec);


// Compute the triple product of three vectors, i.e. (a, b, c)
coord_t triple_product(const Vector3 &a, const Vector3 &b, const Vector3 &c);


const Vector3 inf_vector{infinity, infinity, infinity};
