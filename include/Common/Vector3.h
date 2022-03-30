/**
 * @file Vector3.h
 * @author Jan Wielgus
 * @date 2020-07-30
 * 
 */

#ifndef VECTOR3_H
#define VECTOR3_H

#include <cstdint>


namespace Common
{
    template <class T>
    struct vector3
    {
        T x = {};
        T y = {};
        T z = {};

        constexpr vector3()
        {}

        constexpr vector3(T x, T y, T z):
            x(x),
            y(y),
            z(z)
        {}

// vector on vector
        constexpr vector3& operator*=(const vector3& rhs) {
            x *= rhs.x;
            y *= rhs.y;
            z *= rhs.z;
            return *this;
        }
        constexpr vector3& operator/=(const vector3& rhs) {
            x /= rhs.x;
            y /= rhs.y;
            z /= rhs.z;
            return *this;
        }
        constexpr vector3& operator+=(const vector3& rhs) {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }
        constexpr vector3& operator-=(const vector3& rhs) {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }

// scalar on vector
        constexpr vector3& operator*=(T rhs) {
            x *= rhs;
            y *= rhs;
            z *= rhs;
            return *this;
        }
        constexpr vector3& operator/=(T rhs) {
            x /= rhs;
            y /= rhs;
            z /= rhs;
            return *this;
        }
        constexpr vector3& operator+=(T rhs) {
            x += rhs;
            y += rhs;
            z += rhs;
            return *this;
        }
        constexpr vector3& operator-=(T rhs) {
            x -= rhs;
            y -= rhs;
            z -= rhs;
            return *this;
        }
    };

    template <class T>
    constexpr bool operator==(const vector3<T>& lhs, const vector3<T>& rhs) { // TODO: test with inline
        return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
    }
    template <class T>
    constexpr bool operator!=(const vector3<T>& lhs, const vector3<T>& rhs) {
        return !(lhs == rhs);
    }
    template <class T>
    constexpr vector3<T> operator*(vector3<T> lhs, const vector3<T>& rhs){
        return lhs *= rhs;
    }
    template <class T>
    constexpr vector3<T> operator/(vector3<T> lhs, const vector3<T>& rhs){
        return lhs /= rhs;
    }
    template <class T>
    constexpr vector3<T> operator+(vector3<T> lhs, const vector3<T>& rhs){
        return lhs += rhs;
    }
    template <class T>
    constexpr vector3<T> operator-(vector3<T> lhs, const vector3<T>& rhs){
        return lhs -= rhs;
    }
    template <class T>
    constexpr vector3<T> operator*(vector3<T> lhs, T rhs){
        return lhs *= rhs;
    }
    template <class T>
    constexpr vector3<T> operator/(vector3<T> lhs, T rhs){
        return lhs /= rhs;
    }
    template <class T>
    constexpr vector3<T> operator+(vector3<T> lhs, T rhs){
        return lhs += rhs;
    }
    template <class T>
    constexpr vector3<T> operator-(vector3<T> lhs, T rhs){
        return lhs -= rhs;
    }

    /**
     * @brief Convert structure that has x, y and z members to vector3<T>.
     * @tparam T vector3 members type.
     * @tparam OtherVector Type that has x, y and z members.
     * @param otherVector Instance of type that has x, y and z members.
     */
    template <class T, class OtherVector>
    inline constexpr vector3<T> toVector3(const OtherVector& otherVector) {
        return {otherVector.x, otherVector.y, otherVector.z};
    }

    typedef vector3<float> vector3Float;
    typedef vector3<double> vector3Double;

    typedef vector3<int16_t> vector3Int16;
    typedef vector3<int32_t> vector3Int32;
}


#endif
