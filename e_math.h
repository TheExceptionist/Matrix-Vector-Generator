#ifndef E_MATH_H
#define E_MATH_H

#include <math.h>
#include "defs.h"

namespace e_math
{
    typedef struct vec3d_s vec3d_t;
    typedef struct mat3d_s mat3d_t;

    struct vec3d_s
    {
        float m_x;
        float m_y;
        float m_z;

        vec3d_s() = default;

        vec3d_s(float x, float y, float z)
        {
            m_x = x;
            m_y = y;
            m_z = z;
        }

        vec3d_s& operator*=(int scale)
        {
            m_x *= scale;
            m_y *= scale;
            m_z *= scale;
            return *this;
        }

        vec3d_s& operator/=(int scale)
        {
            m_x /= scale;
            m_y /= scale;
            m_z /= scale;
            return *this; 
        }

        float& operator[](int i)
        {
            return ((&m_x)[i]);
        }

        const float operator[](int i) const
        {
            return ((&m_x)[i]);
        }
    };

    struct mat3d_s
    {
    public:
        mat3d_s() = default;

        mat3d_s(float m00, float m01, float m02,
                float m10, float m11, float m12,
                float m20, float m21, float m22)
        {
            m[0][0] = m00;
            m[1][0] = m10;
            m[2][0] = m20;

            m[0][1] = m01;
            m[1][1] = m11;
            m[2][1] = m21;

            m[0][2] = m02;
            m[1][2] = m12;
            m[2][2] = m22;
        }

        mat3d_s(const vec3d_t& a,
                const vec3d_t& b,
                const vec3d_t& c)
        {
            m[0][0] = a.m_x;
            m[1][0] = a.m_y;
            m[2][0] = a.m_z;

            m[0][1] = b.m_x;
            m[1][1] = b.m_y;
            m[2][1] = b.m_z;

            m[0][2] = c.m_x;
            m[1][2] = c.m_y;
            m[2][2] = c.m_z;
        }

        float& operator() (int i, int n)
        {
            return (m[i][n]);
        }

        const float& operator() (int i, int n) const
        {
            return (m[i][n]);
        }

        vec3d_t& operator[] (int i)
        {
            return (*reinterpret_cast<vec3d_t*>(m[3]));
        }

        const vec3d_t& operator[] (int i) const
        {
            return (*reinterpret_cast<const vec3d_t*>(m[3]));
        }
    private:
        float m[3][3];
    };

    float pow(float num, int pow)
    {
        for(int i = 0; i < pow; i++)
        {
            num *= num;
        }

        return num;
    }
}

inline e_math::vec3d_t operator*(const e_math::vec3d_t& v, float scale)
{
    return (e_math::vec3d_t(v.m_x * scale, v.m_y * scale, v.m_z * scale));
}

inline e_math::vec3d_t operator/(const e_math::vec3d_t& v, float scale)
{
    return (e_math::vec3d_t(v.m_x / scale, v.m_y / scale, v.m_z / scale));
}

inline e_math::vec3d_t operator-(const e_math::vec3d_t& vector)
{
    return (e_math::vec3d_t(-vector.m_x, -vector.m_y, -vector.m_z));
}

inline float Magnitude(const e_math::vec3d_t& vector)
{
    return sqrt(vector.m_x * vector.m_x + vector.m_y * vector.m_y + vector.m_z * vector.m_z);
}

inline void Normalize(e_math::vec3d_t& vector)
{
    vector *= 1 / Magnitude(vector);
}

inline e_math::mat3d_t operator*(const e_math::mat3d_t& a, const e_math::mat3d_t& b)
{
    return (e_math::mat3d_t(a(0 ,0) * b(0, 0) +  a(0, 1) * b(1, 0) +  a(0, 2) * b(2, 0),
                    a(0 ,0) * b(0, 1) +  a(0, 1) * b(1, 1) +  a(0, 2) * b(2, 1),
                    a(0 ,0) * b(0, 2) +  a(0, 1) * b(1, 2) +  a(0, 2) * b(2, 2),

                    a(1 ,0) * b(0, 0) +  a(1, 1) * b(1, 0) +  a(1, 2) * b(2, 0),
                    a(1 ,0) * b(0, 1) +  a(1, 1) * b(1, 1) +  a(1, 2) * b(2, 1),
                    a(1 ,0) * b(0, 2) +  a(1, 1) * b(1, 2) +  a(1, 2) * b(2, 2),

                    a(2 ,0) * b(0, 0) +  a(2, 1) * b(1, 0) +  a(2, 2) * b(2, 0),
                    a(2 ,0) * b(0, 1) +  a(2, 1) * b(1, 1) +  a(2, 2) * b(2, 1),
                    a(2 ,0) * b(0, 2) +  a(2, 1) * b(1, 2) +  a(2, 2) * b(2, 2)));
}

inline e_math::vec3d_t operator*(const e_math::mat3d_t& mat, const e_math::vec3d_t& vec)
{
    return (e_math::vec3d_t(mat(0, 0) * vec.m_x + mat(0, 1) * vec.m_y + mat(0, 2) * vec.m_z,
                    mat(1, 0) * vec.m_x + mat(1, 1) * vec.m_y + mat(1, 2) * vec.m_z,
                    mat(2, 0) * vec.m_x + mat(2, 1) * vec.m_y + mat(2, 2) * vec.m_z));
}

#endif