#pragma once

//
// Matrixes
//

#include <cstddef>
#include <cstring>


// Basic matrix-like container for arbitrary data
template <typename T>
class BasicMatrix
{

    std::size_t _width;
    std::size_t _height;

    T *_array;


public:

    // Constructors / assignment ops / destructor

    BasicMatrix() = delete;

    BasicMatrix(const std::size_t w, const std::size_t h, const T &init_val):
    _width(w), _height(h)
    {
        this->_array = new T[this->size()];

        for (std::size_t i = 0; i < this->size(); i++)
        {
            this->_array[i] = init_val;
        }
    }

    BasicMatrix(const BasicMatrix<T> &other):
    _width(other._width), _height(other._height)
    {
        this->_array = new T[this->size()];

        std::memcpy(this->_array, other._array, sizeof(T) * this->size());
    }

    BasicMatrix<T> & operator=(const BasicMatrix<T> &other)
    {
        if (this == &other)
        {
            return *this;
        }

        if (this->size() != other.size())
        {
            delete[] this->_array;
            this->_array = new T[other.size()];
        }

        this->_height = other._height;
        this->_width = other._width;
        std::memcpy(this->_array, other._array, sizeof(T) * this->size());

        return *this;
    }
    
    BasicMatrix(BasicMatrix<T> &&other):
    _height(other._height), _width(other._width), _array(other._array)
    {
        other._array = nullptr;
    }

    BasicMatrix<T> & operator=(BasicMatrix<T> &&other)
    {
        if (this == &other)
        {
            return *this;
        }

        delete[] this->_array;

        this->_height = other._height;
        this->_width = other._width;
        this->_array = other._array;
        other._array = nullptr;

        return *this;
    }

    ~BasicMatrix()
    {
        delete[] this->_array;
    }


    // Getters / setters

    std::size_t size() const
    {
        return this->_height * this->_width;
    }

    std::pair<std::size_t, std::size_t> shape() const
    {
        return {this->_height, this->_width};
    }

    T & operator()(const std::size_t i, const std::size_t j)
    {
        return this->_array[i * this->_width + j];
    }

    const T & operator()(const std::size_t i, const std::size_t j) const
    {
        return this->_array[i * this->_width + j];
    }

};


// Matrix for storing numbers (mostly fractional)
// T is supposed to be a numerical type
template <typename T>
class Matrix: public BasicMatrix<T>
{
    // TODO: add matrix opearations
};
