//
// Created by r6awe on 6/6/2023.
//

#pragma once

#include "Engine/GameObject.h"
#include "Engine/Component.h"

namespace Physics {

    class PhysicsComponent : public Engine::Component {
    public:
        PhysicsComponent(Engine::GameObject *owner);

    private:
        float m_Mass;

        const Engine::Vec3 &m_Position;
        Engine::Vec3 m_Velocity;
        Engine::Vec3 m_Acceleration;

        Engine::Vec3 m_Force;
        float m_Torque;
    };

}