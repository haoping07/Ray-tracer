#pragma once
#include "hitable.h"

class sphere : public hitable
{
public:
    sphere() {}
    sphere(vec3 cen, double r, material* m) : center(cen), radius(r), mat_ptr(m) {}
    bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;

    vec3 center;
    double radius;
    material* mat_ptr;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
    vec3 oc = r.origin() - center;
    double a = dot(r.direction(), r.direction());
    double b = 2 * dot(oc, r.direction());
    double c = dot(oc, oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;
    if (discriminant > 0)
    {
        double temp = (-b - sqrt(b * b - 4 * a * c)) / (2*a);
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
        temp = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}