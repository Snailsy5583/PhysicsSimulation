#include "GameObject.h"

namespace Engine {

    GameObject::GameObject(RendererObject rendererObject, Vec3 pos, float rot)
        : m_RendererObject(std::move(rendererObject)), m_Position(pos), m_Rotation(rot)
    {}

    void GameObject::Move(Vec3 deltaPos, float deltaRot) {
        float *verts = Renderer::GetVertices(m_RendererObject);

        // Apply Position displacement
        for (int i=0; i<m_RendererObject.bufferSize/(sizeof(float)*3); i+=3) {
            verts[i]   = verts[i]   + deltaPos.x;
            verts[i+1] = verts[i+1] + deltaPos.y;
            verts[i+2] = verts[i+2] + deltaPos.z;
        }

        // TODO: Apply Rotation

        m_RendererObject = Renderer::GenObject(m_RendererObject.bufferSize,
                                              verts,"",
                                              "");

        m_Position += deltaPos;
        m_Rotation += deltaRot;
    }

    void GameObject::Update(float deltaTime) {
        for (Component comp : m_Components)
        {
            comp.UpdateComponent(deltaTime);
        }

        if (m_UpdateCallback)
            m_UpdateCallback(deltaTime);
    }

    void GameObject::AddComponent(const Component& component) {
        m_Components.push_back(component);
    }

    void GameObject::SetUpdateCallback(std::function<void(float)> callback) {
        m_UpdateCallback = callback;
    }

    Quad::Quad(float sideLength, Vec3 pos, float rot)
        : GameObject(
            Renderer::GenQuad(
                pos.toArr(),
                sideLength,
                "",
                ""
            )
            , pos, rot
        ), m_SideLength(sideLength)
    {}

    Circle::Circle(float radius, Vec3 pos, float rot)
        : GameObject(
        Renderer::GenQuad(
            pos.toArr(),
            radius,
            "",
            ""
        )
        , pos, rot
    ), m_Radius(radius)
    {}

} // Engine