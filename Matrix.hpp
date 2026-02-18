#pragma once
#include <algorithm>
#include <map>
#include <string>
#include <sstream>
#include <cstdint>

template <typename T>
class Matrix {
 public:
    Matrix();
    Matrix(size_t height, size_t width);
    Matrix(const Matrix<T> &m);
    Matrix(Matrix<T> &&m);
    virtual ~Matrix();
    Matrix<T> rotateClockwise() const {
        Matrix<T> result(_width, _height);
        for (size_t r = 0; r < _height; ++r) {
            for (size_t c = 0; c < _width; ++c) {
                result(c, _height - 1 - r) = this->operator()(r, c);
            }
        }
        return result;
    }
    size_t width() const { return _width; }
    size_t height() const { return _height; }
    size_t size() const { return width() * height(); }

    Matrix<T>& operator=(const Matrix<T>& m);
    Matrix<T>& operator=(Matrix<T>&& m);
    Matrix<T>& operator+=(const Matrix<T>& m);
    bool operator<(const Matrix<T>& other) const {
        return (uintptr_t)this._matrix < (uintptr_t)other._matrix;
    }

    T& operator()(size_t r, size_t c);
    const T& operator()(size_t r, size_t c) const;
    T& operator[](std::pair<size_t, size_t> pt);
    const T& operator[](std::pair<size_t, size_t> pt) const;

    T& at(size_t r, size_t c);
    const T& at(size_t r, size_t c) const;
 private:
    size_t index(size_t r, size_t c) const;
    size_t _height, _width;
    T* _matrix;
};


template <typename T>
Matrix<T>::Matrix():
     _height(1), _width(1), _matrix(new T[1 * 1]) {}

template <typename T>
Matrix<T>::Matrix(size_t height, size_t width):
    _height(height), _width(width), _matrix(new T[height * width]) {}


    
template <typename T>
Matrix<T>::Matrix(const Matrix<T> &m):
        _height(m.height()), _width(m.width()), _matrix(new T[m.size()])
{
    std::copy(m._matrix, m._matrix + m.size(), this->_matrix);
}

template <typename T>
Matrix<T>::Matrix(Matrix<T> && m):
        _height(m.height()), _width(m.width()), _matrix(m._matrix)
{
    m._matrix = nullptr;
}

template <typename T>
Matrix<T>::~Matrix() {
    delete [] _matrix;
}

template <typename T>
size_t Matrix<T>::index(size_t r, size_t c) const {
    return r * width() + c;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m) {
    if (this != &m) {
        T * copy = new T[m.size()];
        std::copy(m._matrix, m._matrix + m.size(), copy);
        delete [] this->_matrix;
        this->_matrix = copy;
        this->_height = m.height();
        this->_width = m.width();
    }
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& m) {
    if (this != &m) {
        std::swap(m._matrix, this->_matrix);
        std::swap(m._height, this->_height);
        std::swap(m._width, this->_width);
    }
    return *this;
}

template <typename T>
T& Matrix<T>::operator()(size_t r, size_t c) {
    return _matrix[index(r, c)];
}

template <typename T>
const T& Matrix<T>::operator()(size_t r, size_t c) const {
    return _matrix[index(r, c)];
}

template <typename T>
T& Matrix<T>::operator[](std::pair<size_t, size_t> pt) {
    return (*this)(pt.first, pt.second);
}

template <typename T>
const T& Matrix<T>::operator[](std::pair<size_t, size_t> pt) const {
    return (*this)(pt.first, pt.second);
}

template <typename T>
T& Matrix<T>::at(size_t r, size_t c) {
    if (r >= height() || c >= width()){ 
        std::string g= std::to_string(r);
        g+=",";
        g+=std::to_string(c);
        throw std::out_of_range(g);
    }
    return _matrix[index(r, c)];
}

template <typename T>
const T& Matrix<T>::at(size_t r, size_t c) const {
    if (r >= height() || c >= width()) throw std::out_of_range("Out f bounds");
    return _matrix[index(r, c)];
}

template <typename T>
Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    if (lhs.width() != rhs.width()) throw std::invalid_argument("Widths do not match");
    if (lhs.height() != rhs.height()) throw std::invalid_argument("Heights do not match");
    Matrix<T> result = lhs;
    result += rhs;
    return result;
}

template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& m) {
    if (width() != m.width()) throw std::invalid_argument("Widths do not match");
    if (height() != m.height()) throw std::invalid_argument("Heights do not match");
    for (size_t r = 0; r < height(); r++) {
        for (size_t c = 0; c < width(); c++) {
            (*this)(r, c) += m(r, c);
        }
    }
    return *this;
}

template <typename T>
Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    if (lhs.width() != rhs.height()) throw std::invalid_argument("Incompatible dimensions");
    Matrix<T> result(lhs.height(), rhs.width());
    for (size_t r = 0; r < result.height(); r++) {
        for (size_t c = 0; c < result.width(); c++) {
            for (size_t k = 0; k < lhs.width(); k++) {
                result(r, c) = lhs(r, k) * rhs(k, c);
            }
        }
    }
    return result;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& m) {
    for (size_t r = 0; r < m.height(); r++) {
        for (size_t c = 0; c < m.width(); c++) {
            os << m(r, c) << " ";
        }
        os << std::endl;
    }
    return os;
}
