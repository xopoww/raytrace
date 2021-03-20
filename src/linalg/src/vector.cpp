#include "linalg/vector.hpp"

#include <cmath>

Vector3::Vector3():
    x(0), y(0), z(0)
{}

Vector3::Vector3(const coord_t _x, const coord_t _y, const coord_t _z):
    x(_x), y(_y), z(_z)
{}


coord_t Vector3::length() const
{
    return std::sqrt(this->dot(*this));
}

Vector3 Vector3::norm() const
{
    if (this->length() == 0)
    {
        return *this;
    }
    return *this * (1 / this->length());
}

coord_t Vector3::dot(const Vector3 &other) const
{
    return this->x * other.x + this->y * other.y + this->z * other.z;
}

int epsilon(const std::size_t i, const std::size_t j, const std::size_t k)
{
    if (i == j || j == k || k == i)
    {
        return 0;
    }
    if (i == 0 && j == 1 && k == 2)
    {
        return 1;
    }
    if (i == 1 && j == 0 && k == 2)
    {
        return -1;
    }
    return epsilon(j, k, i);
}

Vector3 Vector3::cross(const Vector3 &other) const
{
    Vector3 result;
    for (std::size_t i = 0; i < 3; i++)
    {
        for (std::size_t j = 0; j < 3; j++)
        {
            for (std::size_t k = 0; k < 3; k++)
            {
                result[i] += epsilon(i, j, k) * (*this)[j] * other[k];
            }
        }
    }
    return result;
}

Vector3 Vector3::project(const Vector3 &direction) const
{
    return direction * (std::abs(this->dot(direction)) / direction.length());
}

bool Vector3::operator==(const Vector3 &other) const
{
    return (
        this->x == other.x &&
        this->y == other.y &&
        this->z == other.z
    );
}

coord_t & Vector3::operator[](const std::size_t i)
{
    switch (i)
    {
        case 0:
            return this->x;
        case 1:
            return this->y;
        default:
            return this->z;
    }
}

coord_t Vector3::operator[](const std::size_t i) const
{
    switch (i)
    {
        case 0:
            return this->x;
        case 1:
            return this->y;
        default:
            return this->z;
    }
}

Vector3 operator+(const Vector3 &left, const Vector3 &right)
{
    return Vector3(
        left.x + right.x,
        left.y + right.y,
        left.z + right.z
    );
}

Vector3 operator-(const Vector3 &left, const Vector3 &right)
{
    return Vector3(
        left.x - right.x,
        left.y - right.y,
        left.z - right.z
    );
}

Vector3 operator*(const Vector3 &vec, const coord_t coef)
{
    return Vector3(
        vec.x * coef,
        vec.y * coef,
        vec.z * coef
    );
}


std::ostream & operator<<(std::ostream &os, const Vector3 &vec)
{
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}


coord_t triple_product(const Vector3 &a, const Vector3 &b, const Vector3 &c)
{
    return a.dot(b.cross(c));
}
