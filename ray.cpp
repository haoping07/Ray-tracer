#include <iostream>
#include <fstream>
#include <limits>
#include <cstddef>
#include <random>
#include "sphere.h"
#include "hitablelist.h"
#include "vec3.h"
#include "ray.h"
#include "camera.h"
#include "material.h"

using namespace std;

vec3 color(const ray& r, hitable *world, int depth)
{
    hit_record rec;
    if (world->hit(r, 0.001, std::numeric_limits<double>::max(), rec))
    {
        ray scattered;
        vec3 attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * color(scattered, world, depth + 1);
        else
            return vec3(0, 0, 0);
    }
    else
    {
        vec3 unit_direction = unit_vector(r.direction());
        double t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

int main()
{
    ofstream f("test.ppm");
    int nx = 400;
    int ny = 200;
    int ns = 50;
    f << "P3" << endl << nx << " " << ny << endl << 255 << endl;
    hitable* list[4];
    list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5)));
    list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
    list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8,0.6,0.2), 0.5));
    list[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5));
    hitable* world = new hitable_list(list, 4);
    camera cam;
    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s++)
            {
                double u = double(i + dist(mt)) / double(nx);
                double v = double(j + dist(mt)) / double(ny);
                ray r = cam.get_ray(u, v);
                //vec3 p = r.point_at_parameter(2.0);
                col += color(r, world, 0);
            }
            col /= double(ns);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            int ir = 255.9 * col[0];
            int ig = 255.9 * col[1];
            int ib = 255.9 * col[2];
            f << ir << " " << ig << " " << ib << endl;
            cout << ir << " " << ig << " " << ib << endl;
        }
    }



}

