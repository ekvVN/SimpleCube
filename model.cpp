#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "model.h"


Model::Model(std::vector<Vec3f> verts,
             std::vector<Vec3f> normals,
             std::vector<std::vector<faceVertex> > faces)
    : verts_(verts)
    , normals_(normals)
    , faces_(faces)
{
}

Model::Model(const char *filename) : verts_(), faces_() {
    std::ifstream in;
    in.open (filename, std::ifstream::in);
    if (in.fail()) return;
    std::string line;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;
            Vec3f v;
            for (int i=0;i<3;i++) iss >> v[i];
            verts_.push_back(v);
        }  else if (!line.compare(0, 3, "vn ")) {
            iss.seekg(3, iss.cur);
            Vec3f vn;
            for (int i=0;i<3;i++) iss >> vn[i];
            normals_.push_back(vn);
        }  else if (!line.compare(0, 2, "f ")) {
            std::vector<faceVertex> faceVerts;
            faceVertex f;
            iss >> trash;
            while (iss >> f.idxVertex >> trash >> f.idxTexture >> trash >> f.idxNormal) {
                // in wavefront obj all indices start at 1, not zero
                f.idxVertex--;
                f.idxTexture--;
                f.idxNormal--;
                faceVerts.push_back(f);
            }
            faces_.push_back(faceVerts);
        }
    }
    std::cerr << "# v# " << verts_.size() << " f# "  << faces_.size() << std::endl;
}

Model::~Model() {
}

int Model::nverts() {
    return (int)verts_.size();
}

int Model::nnormals() {
    return (int)normals_.size();
}

int Model::nfaces() {
    return (int)faces_.size();
}

std::vector<faceVertex> Model::face(int idx) {
    return faces_[idx];
}

Vec3f Model::vert(int i) {
    return verts_[i];
}

Vec3f Model::normal(int i) {
    return normals_[i];
}

void Model::set_vert(int i, Vec3f v) {
    verts_[i] = v;
}
void Model::set_normal(int i, Vec3f n) {
    normals_[i] = n;
}

void Model::apply(Matrix3x3<float> m)
{
    for (int i = 0; i < verts_.size(); i++)
    {
        auto &v = verts_[i];
        v = v * m;
    }

    for (int i = 0; i < normals_.size(); i++)
    {
        auto &n = normals_[i];
        n = n * m;
    }
}


