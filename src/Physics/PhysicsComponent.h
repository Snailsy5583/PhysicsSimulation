//
// Created by r6awe on 6/6/2023.
//

#pragma once

#include "Engine/GameObject.h"
#include "Engine/Component.h"

namespace Physics {

    class PhysicsComponent : public Engine::Component {
        friend class PhysicsSolver;
    public:
        PhysicsComponent(Engine::GameObject *owner, float mass, float radius);

        void UpdateComponent(float deltaTime) override;

    private:
        void ApplyPhysics();

    private:
        float m_Mass;
        float m_Radius;
        float m_coFriction{};

        float m_OldDeltaTime = 1/60.f;

        Engine::Vec3 m_OldPosition;
        const Engine::Vec3 &m_Position;
        Engine::Vec3 m_NewPosition{};

        Engine::Vec3 m_Velocity{};
        Engine::Vec3 m_Acceleration{};

        Engine::Vec3 m_Force;
        float m_Torque{};
    };

}