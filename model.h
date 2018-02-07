#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>
#include "geometry.h"
#include "Matrix3x3.h"

struct faceVertex
{
    // Индекс вершины
    int idxVertex;

    // Индекс - среднее число, возможно индекс текстуры
    int idxTexture;

    // Индекс ноhмали
    int idxNormal;
};

class Model {
private:
	std::vector<Vec3f> verts_;
    std::vector<Vec3f> normals_;
	std::vector<std::vector<faceVertex> > faces_;
public:
	Model(std::vector<Vec3f> verts, std::vector<Vec3f> normals, std::vector<std::vector<faceVertex> > faces);
	Model(const char *filename);
	~Model();
	int nverts();
	int nnormals();
	int nfaces();
	Vec3f vert(int i);
    Vec3f normal(int i);
	void set_vert(int i, Vec3f v);
	void set_normal(int i, Vec3f n);
	std::vector<faceVertex> face(int idx);

    // применить матрицу к модели
    void apply(Matrix3x3<float> m);
};

#endif //__MODEL_H__
