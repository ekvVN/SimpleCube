//
// Created by root on 06.02.18.
//

#include <array>
#include "PrimitivePainter.h"

void PrimitivePainter::draw_line(Image &image, int x0, int y0, int x1, int y1, Pixel color)
{
    bool steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1))
    {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0 > x1)
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dx = x1 - x0;
    int dy = y1 - y0;
    int derror2 = std::abs(dy) * 2;
    int error2 = 0;
    int y = y0;
    for (int x = x0; x <= x1; x++)
    {
        if (steep)
        {
            image.set(y, x, color);
        }
        else
        {
            image.set(x, y, color);
        }
        error2 += derror2;

        if (error2 > dx)
        {
            y += (y1 > y0 ? 1 : -1);
            error2 -= dx * 2;
        }
    }
}

void PrimitivePainter::draw_line(Image &image, std::array<Vec2i, 2> p, Pixel color)
{
    draw_line(image, p[0].x, p[0].y, p[1].x, p[1].y, color);
}

void PrimitivePainter::draw_triangle(Image &image, std::array<Vec2i, 3> p, Pixel color)
{
    // sort the vertices, t0, t1, t2 lower-to-upper (bubblesort yay!)
    if (p[0].y > p[1].y) std::swap(p[0], p[1]);
    if (p[0].y > p[2].y) std::swap(p[0], p[2]);
    if (p[1].y > p[2].y) std::swap(p[1], p[2]);

    draw_line(image, {p[0], p[1]}, color);
    draw_line(image, {p[1], p[2]}, color);
    draw_line(image, {p[2], p[0]}, color);
}

void PrimitivePainter::fill_triangle(Image &image, std::array<Vec2i, 3> p, Pixel color)
{
    if (p[0].y == p[1].y && p[0].y == p[2].y) return; // i dont care about degenerate triangles
    // sort the vertices, t0, t1, t2 lower-to-upper (bubblesort yay!)
    if (p[0].y > p[1].y) std::swap(p[0], p[1]);
    if (p[0].y > p[2].y) std::swap(p[0], p[2]);
    if (p[1].y > p[2].y) std::swap(p[1], p[2]);
    int total_height = p[2].y - p[0].y;
    for (int i = 0; i < total_height; i++)
    {
        bool second_half = i > p[1].y - p[0].y || p[1].y == p[0].y;
        int segment_height = second_half
            ? p[2].y - p[1].y
            : p[1].y - p[0].y;
        float alpha = (float) i / total_height;
        // be careful: with above conditions no division by zero here
        float beta = (float) (i - (second_half ? p[1].y - p[0].y : 0)) / segment_height;
        Vec2i A = p[0] + (p[2] - p[0]) * alpha;
        Vec2i B = second_half
            ? p[1] + (p[2] - p[1]) * beta
            : p[0] + (p[1] - p[0]) * beta;
        if (A.x > B.x) std::swap(A, B);
        for (int j = A.x; j <= B.x; j++)
        {
            image.set(j, p[0].y + i, color); // attention, due to int casts t0.y+i != A.y
        }
    }
}

void PrimitivePainter::fill_triangle(Image &image, std::array<Vec3i, 3> p, Pixel color, std::vector<int> &zbuffer)
{
    int width = image.width();
    int height = image.height();

    if (p[0].y == p[1].y && p[0].y == p[2].y) return; // i dont care about degenerate triangles
    if (p[0].y > p[1].y) std::swap(p[0], p[1]);
    if (p[0].y > p[2].y) std::swap(p[0], p[2]);
    if (p[1].y > p[2].y) std::swap(p[1], p[2]);
    int total_height = p[2].y - p[0].y;
    for (int i = 0; i < total_height; i++)
    {
        bool second_half = i > p[1].y - p[0].y || p[1].y == p[0].y;
        int segment_height = second_half
            ? p[2].y - p[1].y
            : p[1].y - p[0].y;
        float alpha = (float) i / total_height;
        // be careful: with above conditions no division by zero here
        float beta = (float) (i - (second_half ? p[1].y - p[0].y : 0)) / segment_height;
        Vec3i A = p[0] + Vec3f(p[2] - p[0]) * alpha;
        Vec3i B = second_half
            ? p[1] + Vec3f(p[2] - p[1]) * beta
            : p[0] + Vec3f(p[1] - p[0]) * beta;
        if (A.x > B.x) std::swap(A, B);
        for (int j = A.x; j <= B.x; j++)
        {
            float phi = B.x == A.x
                ? 1.
                : (float) (j - A.x) / (float) (B.x - A.x);
            Vec3i P = Vec3f(A) + Vec3f(B - A) * phi;
            int idx = P.x + P.y * width;
            if (idx < zbuffer.size() && zbuffer[idx] < P.z)
            {
                zbuffer[idx] = P.z;
                image.set(P.x, P.y, color);
            }
        }
    }
}

void PrimitivePainter::fill_triangle(Image &image, std::array<Vec3i, 3> p, std::array<float, 3> ity, std::vector<int> &zbuffer)
{
    int width = image.width();
    int height = image.height();

    if (p[0].y == p[1].y && p[0].y == p[2].y) return; // i dont care about degenerate triangles
    if (p[0].y > p[1].y)
    {
        std::swap(p[0], p[1]);
        std::swap(ity[0], ity[1]);
    }
    if (p[0].y > p[2].y)
    {
        std::swap(p[0], p[2]);
        std::swap(ity[0], ity[2]);
    }
    if (p[1].y > p[2].y)
    {
        std::swap(p[1], p[2]);
        std::swap(ity[1], ity[2]);
    }

    int total_height = p[2].y - p[0].y;
    for (int i = 0; i < total_height; i++)
    {
        bool second_half = i > p[1].y - p[0].y || p[1].y == p[0].y;
        int segment_height = second_half ? p[2].y - p[1].y : p[1].y - p[0].y;
        float alpha = (float) i / total_height;
        // be careful: with above conditions no division by zero here
        float beta = (float) (i - (second_half ? p[1].y - p[0].y : 0)) / segment_height;
        Vec3i A = p[0] + Vec3f(p[2] - p[0]) * alpha;
        Vec3i B = second_half
            ? p[1] + Vec3f(p[2] - p[1]) * beta
            : p[0] + Vec3f(p[1] - p[0]) * beta;
        float ityA = ity[0] + (ity[2] - ity[0]) * alpha;
        float ityB = second_half
            ? ity[1] + (ity[2] - ity[1]) * beta
            : ity[0] + (ity[1] - ity[0]) * beta;
        if (A.x > B.x)
        {
            std::swap(A, B);
            std::swap(ityA, ityB);
        }
        for (int j = A.x; j <= B.x; j++)
        {
            float phi = B.x == A.x
                ? 1.
                : (float) (j - A.x) / (B.x - A.x);
            Vec3i P = Vec3f(A) + Vec3f(B - A) * phi;
            float ityP = ityA + (ityB - ityA) * phi;
            int idx = P.x + P.y * width;
            if (P.x >= width || P.y >= height || P.x < 0 || P.y < 0)
                continue;
            if (zbuffer[idx] < P.z)
            {
                zbuffer[idx] = P.z;
                Pixel color = Pixel{255, 255, 255, 255} * ityP;
                image.set(P.x, P.y, color);
            }
        }
    }
}
