#pragma once


#include "Shader.h"

namespace Engine {

    struct Vec3 {
        float x, y, z;

        Vec3 operator+(Vec3 other) {
            return {other.x+x, other.y+y, other.z+z};
        }
        Vec3 operator-(Vec3 other) {
            return {other.x-x, other.y-y, other.z-z};
        }
        Vec3 operator*(float scalar) {
            return {scalar*x, scalar*y, scalar*z};
        }
        Vec3 operator/(float scalar) {
            return {scalar / x, scalar / y, scalar / z};
        }

        void operator+=(Vec3 other) {
            x += other.x;
            y += other.y;
            z += other.z;
        }

        float operator[](int offset) {
            switch (offset) {
                case 0:
                    return x;
                case 1:
                    return y;
                case 2:
                    return z;
                default:
                    return (float) -INT_MAX;
            }
        }

        float* toArr() {
            return reinterpret_cast<float *>(this);
        }
    };

    struct RendererObject {
        unsigned int vao;
        unsigned int vbo;
        unsigned int bufferSize;
        Shader shader;
    };

    class Renderer {
    public:
        static RendererObject GenObject(unsigned int size,
                                        const float *Vertices,
                                        const char *vertShaderPath,
                                        const char *fragShaderPath);

        static RendererObject GenQuad(const float pos[3],
                                      const float sideLen,
                                      const char *vertShaderPath,
                                      const char *fragShaderPath);

        static void MoveQuad(RendererObject &obj, Vec3 newPos, float sideLen);

        static void DeleteQuad(RendererObject &object);

        static void SubmitObject(const RendererObject& obj);

        static float* GetVertices(RendererObject &obj);

    private:
        const static float m_QuadVerts[];
    };


}