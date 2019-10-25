#pragma once
#include <cmath>
#include <stdlib.h>
#include <iostream>

class vec3
{
public:
    vec3() {}
    vec3(double e0, double e1, double e2) { e[0] = e0; e[1] = e1, e[2] = e2; }
    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }
    double r() const { return e[0]; }
    double g() const { return e[1]; }
    double b() const { return e[2]; }

    const vec3& operator +() const { return *this; }
    vec3 operator -() const { return vec3(-e[0], -e[1], -e[2]); }
    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[i]; }

    vec3& operator +=(const vec3& v2);
    vec3& operator -=(const vec3& v2);
    vec3& operator *=(const vec3& v2);
    vec3& operator /=(const vec3& v2);
    vec3& operator *=(const double t);
    vec3& operator /=(const double t);

    double length() const { return sqrt(pow(e[0], 2) + pow(e[1], 2) + pow(e[2], 2)); }
    double squared_length() const { return pow(e[0], 2) + pow(e[1], 2) + pow(e[2], 2); }
    void make_unit_vector();

    double e[3];
};

std::istream& operator >>(std::istream& is, vec3& t)
{
    is >> t.e[0] >> t.e[1] >> t.e[2];
    return is;
}

std::ostream& operator <<(std::ostream& os, const vec3& t)
{
    os << t.e[0] << " " << t.e[1] << " " << t.e[2];
    return os;
}

void vec3::make_unit_vector()
{
    double k = 1.0 / sqrt(pow(e[0], 2) + pow(e[1], 2) + pow(e[2], 2));
}

vec3 operator +(const vec3& v1, const vec3& v2)
{
    return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

vec3 operator -(const vec3& v1, const vec3& v2)
{
    return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

vec3 operator *(const vec3& v1, const vec3& v2)
{
    return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

vec3 operator /(const vec3& v1, const vec3& v2)
{
    return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

vec3 operator *(double t, const vec3& v)
{
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

vec3 operator /(vec3 v, double t)
{
    return vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

vec3 operator *(const vec3& v, double t)
{
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

double dot(const vec3& v1, const vec3& v2)
{
    return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

vec3 cross(const vec3& v1, const vec3& v2)
{
    return vec3(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
                -(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0]),
                v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
}

vec3& vec3::operator +=(const vec3& v)
{
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

vec3& vec3::operator *=(const vec3& v)
{
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    e[2] *= v.e[2];
    return *this;
}

vec3& vec3::operator /=(const vec3& v)
{
    e[0] /= v.e[0];
    e[1] /= v.e[1];
    e[2] /= v.e[2];
    return *this;
}

vec3& vec3::operator -=(const vec3& v)
{
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];
    return *this;
}

vec3& vec3::operator *=(const double t)
{
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

vec3& vec3::operator /=(const double t)
{
    double k = 1.0 / t;
    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
    return *this;
}

vec3 unit_vector(vec3 v)
{
    return v / v.length();
}