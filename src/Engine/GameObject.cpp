#include <memory>
#include <utility>
#include "GameObject.h"

namespace Engine {

    GameObject::GameObject(RendererObject rendererObject, Vec3 pos, float rot)
        : m_RendererObject(std::move(rendererObject)), m_Position(pos), m_Rotation(rot)
    {}

    void GameObject::Move(Vec3 deltaPos, float deltaRot) {
//        float *verts = Renderer::GetVertices(m_RendererObject);

        // Apply Position displacement
//        for (int i=0; i<m_RendererObject.bufferSize/(sizeof(float)*3); i+=3) {
//            verts[i]   = verts[i]   + deltaPos.x;
//            verts[i+1] = verts[i+1] + deltaPos.y;
//            verts[i+2] = verts[i+2] + deltaPos.z;
//        }
//
        // TODO: Apply Rotation
        // TODO: Currently this doesn't work
//        RendererObject newRO = Renderer::GenObject(m_RendererObject.bufferSize,
//                                              verts,"",
//                                              "");
//        newRO.shader = m_RendererObject.shader;
//        m_RendererObject = newRO;

        m_Position += deltaPos;
        m_Rotation += deltaRot;
    }

    void GameObject::Update(float deltaTime) {
        for (std::unique_ptr<Component> &comp : m_Components)
        {
            comp->UpdateComponent(deltaTime);
        }

        if (m_UpdateCallback)
            m_UpdateCallback(deltaTime, this);
    }

    void GameObject::AddComponent(std::unique_ptr<Component> component) {
        m_Components.push_back(std::move(component));
    }

    void GameObject::SetUpdateCallback(std::function<void(float, GameObject*)>
        callback) {
        m_UpdateCallback = std::move(callback);
    }

    void GameObject::Render() {
        float pos[] = {
            m_Position.x, m_Position.y, m_Position.z
        };

        m_RendererObject.shader.SetUniformVec(
            "pos", 3, pos
        );
        Renderer::SubmitObject(m_RendererObject);
    }

    Quad::Quad(float sideLength, Vec3 pos, float rot)
        : GameObject(
            Renderer::GenQuad(
                new float[] {0,0,0},
                sideLength,
                "Assets/circle.vert",
                "Assets/circle.frag"
            )
            , pos, rot
        ), m_SideLength(sideLength)
    {}

    void Quad::Move(Vec3 deltaPos, float deltaRot) {
//        Renderer::MoveQuad(m_RendererObject, m_Position+deltaPos, m_SideLength);
        m_Position += deltaPos;
        m_Rotation += deltaRot;
    }

    Circle::Circle(float radius, Vec3 pos, float rot)
        : Quad(radius*2, pos, rot), m_Radius(m_SideLength)
    {}

} // Engine