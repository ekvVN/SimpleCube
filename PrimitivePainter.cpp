//
// Created by root on 06.02.18.
//

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

void PrimitivePainter::draw_line(Image &image, Vec2i p0, Vec2i p1, Pixel color)
{
    draw_line(image, p0.x, p0.y, p1.x, p1.y, color);
}

void PrimitivePainter::draw_triangle(Image &image, Vec2i t0, Vec2i t1, Vec2i t2, Pixel color)
{
    // sort the vertices, t0, t1, t2 lower-to-upper (bubblesort yay!)
    if (t0.y > t1.y) std::swap(t0, t1);
    if (t0.y > t2.y) std::swap(t0, t2);
    if (t1.y > t2.y) std::swap(t1, t2);

    draw_line(image, t0, t1, color);
    draw_line(image, t1, t2, color);
    draw_line(image, t2, t0, color);
}

void PrimitivePainter::fill_triangle(Image &image, Vec2i t0, Vec2i t1, Vec2i t2, Pixel color)
{
    if (t0.y == t1.y && t0.y == t2.y) return; // i dont care about degenerate triangles
    // sort the vertices, t0, t1, t2 lower-to-upper (bubblesort yay!)
    if (t0.y > t1.y) std::swap(t0, t1);
    if (t0.y > t2.y) std::swap(t0, t2);
    if (t1.y > t2.y) std::swap(t1, t2);
    int total_height = t2.y - t0.y;
    for (int i = 0; i < total_height; i++)
    {
        bool second_half = i > t1.y - t0.y || t1.y == t0.y;
        int segment_height = second_half ? t2.y - t1.y : t1.y - t0.y;
        float alpha = (float) i / total_height;
        // be careful: with above conditions no division by zero here
        float beta = (float) (i - (second_half ? t1.y - t0.y : 0)) / segment_height;
        Vec2i A = t0 + (t2 - t0) * alpha;
        Vec2i B = second_half ? t1 + (t2 - t1) * beta : t0 + (t1 - t0) * beta;
        if (A.x > B.x) std::swap(A, B);
        for (int j = A.x; j <= B.x; j++)
        {
            image.set(j, t0.y + i, color); // attention, due to int casts t0.y+i != A.y
        }
    }
}

void PrimitivePainter::fill_triangle(Image &image, Vec3i t0, Vec3i t1, Vec3i t2, Pixel color, std::vector<int> &zbuffer)
{
    int width = image.width();
    int height = image.height();

    if (t0.y == t1.y && t0.y == t2.y) return; // i dont care about degenerate triangles
    if (t0.y > t1.y) std::swap(t0, t1);
    if (t0.y > t2.y) std::swap(t0, t2);
    if (t1.y > t2.y) std::swap(t1, t2);
    int total_height = t2.y - t0.y;
    for (int i = 0; i < total_height; i++)
    {
        bool second_half = i > t1.y - t0.y || t1.y == t0.y;
        int segment_height = second_half ? t2.y - t1.y : t1.y - t0.y;
        float alpha = (float) i / total_height;
        // be careful: with above conditions no division by zero here
        float beta = (float) (i - (second_half ? t1.y - t0.y : 0)) / segment_height;
        Vec3i A = t0 + Vec3f(t2 - t0) * alpha;
        Vec3i B = second_half ? t1 + Vec3f(t2 - t1) * beta : t0 + Vec3f(t1 - t0) * beta;
        if (A.x > B.x) std::swap(A, B);
        for (int j = A.x; j <= B.x; j++)
        {
            float phi = B.x == A.x ? 1. : (float) (j - A.x) / (float) (B.x - A.x);
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