//
// Created by r6awe on 6/6/2023.
//

#pragma once

#include <functional>

#include "Component.h"
#include "Renderer.h"

namespace Engine {

    class GameObject {
    public:
        GameObject(RendererObject rendererObject, Vec3 pos, float rot);

        void AddComponent(const Component& component);

        void Move(Vec3 deltaPos, float deltaRot);

        virtual void Update(float deltaTime);

        void SetUpdateCallback(std::function<void(float)> callback);

    public:
        inline const Vec3& GetPosition() const { return m_Position; }
        inline float GetRotation() const { return m_Rotation; }
        inline float GetScale   () const { return m_Scale;    }

    protected:
        RendererObject m_RendererObject;

        std::vector<Component> m_Components;

        std::function<void(float)> m_UpdateCallback;

        Vec3 m_Position;
        float m_Rotation;
        float m_Scale = 1;
    };

    class Quad : public GameObject {
    public:
        Quad(float sideLength, Vec3 pos, float rot);

    private:
        float m_SideLength;
    };

    class Circle : public GameObject {
    public:
        Circle(float radius, Vec3 pos, float rot);

    private:
        float m_Radius;
    };

} // Engine
