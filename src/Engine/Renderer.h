#pragma once


#include <sstream>
#include <cmath>
#include "Shader.h"

namespace Engine {

    struct Vec3 {
        float x=0, y=0, z=0;

        Vec3 operator+(const Vec3 other) const {
            return {x+other.x, y+other.y, z+other.z};
        }
        Vec3 operator-(const Vec3 other) const {
            return {x-other.x, y-other.y, z-other.z};
        }
        Vec3 operator*(const float scalar) const {
            return {scalar*x, scalar*y, scalar*z};
        }
        friend Vec3 operator*(const float scalar, const Vec3 vec) {
            return {scalar*vec.x, scalar*vec.y, scalar*vec.z};
        }
        Vec3 operator/(const float scalar) const {
            return {x/scalar, y/scalar, z/scalar};
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

        std::string toString() const {
            std::stringstream ss;
            ss << "(" << x << ", " << y << ", " << z << ")";
            return ss.str();
        }

        float magnitude() const {
            return sqrt(x*x + y*y + z*z);
        }

        Vec3 normalized() const {
            return (*this)/magnitude();
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