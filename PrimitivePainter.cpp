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
    if(!sort_verts(p))
        return;

    draw_line(image, {p[0], p[1]}, color);
    draw_line(image, {p[1], p[2]}, color);
    draw_line(image, {p[2], p[0]}, color);
}

void PrimitivePainter::fill_triangle(Image &image, std::array<Vec2i, 3> p, Pixel color)
{
    if(!sort_verts(p))
        return;

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
    if(!sort_verts(p))
        return;

    int width = image.width();
    int height = image.height();

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
                ? 1.f
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
    if(!sort_verts(p, ity))
        return;

//    if(ity[0] > 0 && ity[1] > 0 && ity[2] > 0)
//    {
//        int a = 0;
//    }

    int width = image.width();
    int height = image.height();

    // Координаты треугольника
    Vec3i &A = p[0];
    Vec3i &B = p[1];
    Vec3i &C = p[2];

    // Интенсивность в координатах треугольника
    float Int_A = ity[0];
    float Int_B = ity[1];
    float Int_C = ity[2];

    // Направления векторов
    Vec3f AC = (C - A);
    Vec3f AB = (B - A);
    Vec3f BC = (C - B);

    int total_height = p[2].y - p[0].y;
    for (int i = 0; i < total_height; i++)
    {
        bool second_half = B.y == A.y || i > B.y - A.y;
        float deltaAC = (float) i / total_height;

        // QR - отрезок на ребрах треуольника, по которому будет проходить внутренний цикл
        Vec3i Q, R;
        float Int_Q, Int_R;
        if(!second_half)
        {
            // Q расположена на отрезке AC
            // R расположена на отрезке AB
            int segment_height = B.y - A.y;
            float deltaAB = (float) i / segment_height;

            Q = Vec3f(A) + AC * deltaAC;
            R = Vec3f(A) + AB * deltaAB;

            // Отношения "u" и "w"
            // u = QC / AC
            // w = RB / AB
            float u = C.x == A.x
                ? 1.f
                : (float)(C.x - Q.x) / (C.x - A.x);
            float w = B.x == A.x
                ? 1.f
                : (float)(B.x - R.x) / (B.x - A.x);

            // Интенсивность в вершинах отрезка QR
            Int_Q = u * Int_A + (1 - u) * Int_C;
            Int_R = w * Int_A + (1 - w) * Int_B;
        }
        else
        {
            // Q расположена на отрезке AC
            // R расположена на отрезке BC
            int segment_height = C.y - B.y;
            float deltaBC = (float) (i - (B.y - A.y)) / segment_height;

            // Координаты Q и R
            Q = Vec3f(A) + AC * deltaAC;
            R = Vec3f(B) + BC * deltaBC;

            // Отношения "u" и "w"
            // u = QC / AC
            // w = RC / BC
            float u = C.x == A.x
                ? 1.f
                : (float)(C.x - Q.x) / (C.x - A.x);
            float w = C.x == B.x
                ? 1.f
                : (float)(C.x - R.x) / (C.x - B.x);

            // Интенсивность в вершинах отрезка QR
            Int_Q = u * Int_A + (1 - u) * Int_C;
            Int_R = w * Int_B + (1 - w) * Int_C;
        }

//        if(ity[0] > 0 && ity[1] > 0 && ity[2] > 0)
//        {
//            std::cout << Q << " = " << Int_Q << " ; "
//                      << R << " = " << Int_R << " ; "
//                      << std::endl;
//        }

        if (Q.x > R.x)
        {
            std::swap(Q, R);
            std::swap(Int_Q, Int_R);
        }
        // Направление вектора
        Vec3f QR = Vec3f(R) - Vec3f(Q);
        int total_x = QR.x;
        // цикл по всем пикселям отрезка QR
        for (int j = 0; j <= total_x; j++)
        {
            float deltaX = (float) j / total_x;

            // Координаты отрисовываемого пикселя
            Vec3i T = Vec3f(Q) + QR * deltaX;

            // Отношение "t" и интенсивность
            float t = R.x == Q.x
                ? 1.f
                : (float)(R.x - T.x) / (R.x - Q.x);
            float Int_T = t * Int_Q + (1 - t) * Int_R;

            // Доп. проверки и отрисовка
            if (T.x >= width || T.y >= height || T.x < 0 || T.y < 0)
                continue;
            int idx = T.x + T.y * width;
            if (zbuffer[idx] < T.z)
            {
                zbuffer[idx] = T.z;
                Pixel color = Pixel{255, 255, 255, 255} * Int_T;
                image.set(T.x, T.y, color);
            }
        }
    }
}


void PrimitivePainter::fill_triangle2(Image &image, std::array<Vec3i, 3> p, std::array<float, 3> ity, std::vector<int> &zbuffer)
{
    if(!sort_verts(p, ity))
        return;

//    if(ity[0] > 0 && ity[1] > 0 && ity[2] > 0)
//    {
//        int a = 0;
//    }

    int width = image.width();
    int height = image.height();

    int total_height = p[2].y - p[0].y;
    for (int i = 0; i < total_height; i++)
    {
        bool second_half = i > p[1].y - p[0].y || p[1].y == p[0].y;
        int segment_height = second_half ? p[2].y - p[1].y : p[1].y - p[0].y;

        // дельты для вычисления координат вершин Q и R
        float alpha = (float) i / total_height;
        // be careful: with above conditions no division by zero here
        float beta = (float) (i - (second_half ? p[1].y - p[0].y : 0)) / segment_height;

        // QR - отрезок на ребрах треуольника, по которому будет проходить внутренний цикл
        Vec3i Q = p[0] + Vec3f(p[2] - p[0]) * alpha;
        Vec3i R = second_half
            ? p[1] + Vec3f(p[2] - p[1]) * beta
            : p[0] + Vec3f(p[1] - p[0]) * beta;

        // Интенсивность в вершинах отрезка QR
        float ityQ = ity[0] + (ity[2] - ity[0]) * alpha;
        float ityR = second_half
            ? ity[1] + (ity[2] - ity[1]) * beta
            : ity[0] + (ity[1] - ity[0]) * beta;

//        if(ity[0] > 0 && ity[1] > 0 && ity[2] > 0)
//        {
//            std::cout << Q << " = " << ityQ << " ; "
//                      << R << " = " << ityR << " ; "
//                      << std::endl;
//        }

        if (Q.x > R.x)
        {
            std::swap(Q, R);
            std::swap(ityQ, ityR);
        }
        // цикл по всем пикселям отрезка QR
        for (int j = Q.x; j <= R.x; j++)
        {
            float phi = R.x == Q.x
                ? 1.f
                : (float) (j - Q.x) / (R.x - Q.x);


            Vec3i P = Vec3f(Q) + Vec3f(R - Q) * phi;
            float ityP = ityQ + (ityR - ityQ) * phi;
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

template<typename T>
bool PrimitivePainter::sort_verts(std::array<T, 3> &p)
{
    // false - если все вершины находятся на одной высоте, чтобы не рисовать просто линию 0-ой высоты
    if (p[0].y == p[1].y && p[0].y == p[2].y)
        return true; // i dont care about degenerate triangles

    if (p[0].y > p[1].y) std::swap(p[0], p[1]);
    if (p[0].y > p[2].y) std::swap(p[0], p[2]);
    if (p[1].y > p[2].y) std::swap(p[1], p[2]);

    return true;
}

template<typename T, typename TOther>
bool PrimitivePainter::sort_verts(std::array<T, 3> &p, std::array<TOther, 3> &ity)
{
    // false - если все вершины находятся на одной высоте, чтобы не рисовать просто линию 0-ой высоты
    if (p[0].y == p[1].y && p[0].y == p[2].y)
        return true; // i dont care about degenerate triangles

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

    return true;
}