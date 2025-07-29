#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TGA.h"
#define GL_BGR 0x80E0
#define GL_BGRA 0x80E1

struct Vertex {
    float x, y, z;       // Posisi
    float nx, ny, nz;    // Normal
    float u, v;          // UV koordinat
};

std::vector<Vertex> vertices;
std::vector<unsigned int> indices;
GLuint textureID;
float angle = 0.0f;

void loadModel(const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Gagal membuka " << filename << std::endl;
        return;
    }

    std::string line;
    int totalVertices = 0, totalIndices = 0;

    std::getline(file, line);
    sscanf(line.c_str(), "NrVertices:%d", &totalVertices);

    for (int i = 0; i < totalVertices; ++i) {
        Vertex v;
        std::getline(file, line);
        sscanf(line.c_str(),
               "%*d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; %*[^;]; %*[^;]; uv:[%f, %f];",
               &v.x, &v.y, &v.z,
               &v.nx, &v.ny, &v.nz,
               &v.u, &v.v);
        vertices.push_back(v);
    }

    std::getline(file, line);
    sscanf(line.c_str(), "NrIndices:%d", &totalIndices);

    for (int i = 0; i < totalIndices / 3; ++i) {
        std::getline(file, line);
        unsigned int a, b, c;
        sscanf(line.c_str(), "%*d. %u,%u,%u", &a, &b, &c);
        indices.push_back(a);
        indices.push_back(b);
        indices.push_back(c);
    }

    std::cout << "Berhasil load " << vertices.size() << " vertex, "
              << indices.size() / 3 << " segitiga\n";
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 1.0, 3.0, 0, 1.0, 0, 0, 1, 0);

    glRotatef(angle, 0, 1, 0); // rotasi otomatis

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBegin(GL_TRIANGLES);
    for (size_t i = 0; i + 2 < indices.size(); i += 3) {
        for (int j = 0; j < 3; ++j) {
            const Vertex& v = vertices[indices[i + j]];
            glNormal3f(v.nx, v.ny, v.nz);
            glTexCoord2f(v.u, v.v);
            glVertex3f(v.x, v.y, v.z);
        }
    }
    glEnd();

    glutSwapBuffers();
}

void idle() {
    angle += 0.1f;
    if (angle > 360.0f) angle -= 360.0f;
    glutPostRedisplay();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float aspect = (float)w / h;
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 0.1, 100);

    glMatrixMode(GL_MODELVIEW);
}

void initGL() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    int width, height, bpp;
    char* imageData = LoadTGA("assets/Woman1.tga", &width, &height, &bpp);
    if (!imageData) {
        std::cerr << "ERROR: Tidak bisa buka 'Woman1.tga'.\n";
        return;
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, (bpp == 32 ? GL_RGBA : GL_RGB),
             width, height, 0,
             (bpp == 32 ? GL_RGBA : GL_RGB),
             GL_UNSIGNED_BYTE, imageData);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    loadModel("assets/Woman1.nfg");
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Model Wanita 3D");

    initGL();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}
