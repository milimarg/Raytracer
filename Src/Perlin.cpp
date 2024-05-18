/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-raytracer-florent.guittre
** File description:
** Perlin
*/

#include "Perlin.hpp"

namespace rtx
{
    Perlin::Perlin()
    {
        _randvec = new Vec3[_pointCount];
        for (int i = 0; i < _pointCount; i++) {
            _randvec[i] = Vec3::unitVector(Vec3::random(-1, 1));
        }

        _permX = perlinGeneratePerm();
        _permY = perlinGeneratePerm();
        _permZ = perlinGeneratePerm();
    }

    Perlin::~Perlin()
    {
        delete[] _randvec;
        delete[] _permX;
        delete[] _permY;
        delete[] _permZ;
    }

    double Perlin::noise(const Point3 &p) const
    {
        auto u = p.x() - floor(p.x());
        auto v = p.y() - floor(p.y());
        auto w = p.z() - floor(p.z());

        u = u * u * (3 - 2 * u);
        v = v * v * (3 - 2 * v);
        w = w * w * (3 - 2 * w);

        auto i = int(floor(p.x()));
        auto j = int(floor(p.y()));
        auto k = int(floor(p.z()));
        Vec3 c[2][2][2];

        for (int di=0; di < 2; di++)
            for (int dj=0; dj < 2; dj++)
                for (int dk=0; dk < 2; dk++)
                    c[di][dj][dk] = _randvec[
                        _permX[(i+di) & 255] ^
                        _permY[(j+dj) & 255] ^
                        _permZ[(k+dk) & 255]
                    ];

        return perlinInterp(c, u, v, w);
    }

    double Perlin::turb(const Point3 &p, int depth) const
    {
        auto accum = 0.0;
        auto temp_p = p;
        auto weight = 1.0;

        for (int i = 0; i < depth; i++) {
            accum += weight * noise(temp_p);
            weight *= 0.5;
            temp_p *= 2;
        }

        return fabs(accum);
    }

    int *Perlin::perlinGeneratePerm()
    {
        auto p = new int[_pointCount];

        for (int i = 0; i < _pointCount; i++)
            p[i] = i;

        permute(p, _pointCount);

        return p;
    }

    void Perlin::permute(int *p, int n)
    {
        for (int i = n-1; i > 0; i--) {
            int target = Math::randomInt(0, i);
            int tmp = p[i];
            p[i] = p[target];
            p[target] = tmp;
        }
    }

    double Perlin::perlinInterp(const Vec3 c[2][2][2], double u, double v, double w)
    {
        auto uu = u*u*(3-2*u);
        auto vv = v*v*(3-2*v);
        auto ww = w*w*(3-2*w);
        auto accum = 0.0;

        for (int i=0; i < 2; i++)
            for (int j=0; j < 2; j++)
                for (int k=0; k < 2; k++) {
                    Vec3 weight_v(u-i, v-j, w-k);
                    accum += (i*uu + (1-i)*(1-uu))
                        * (j*vv + (1-j)*(1-vv))
                        * (k*ww + (1-k)*(1-ww))
                        * Vec3::dot(c[i][j][k], weight_v);
                }

        return accum;
    }
};
