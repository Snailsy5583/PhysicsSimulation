//
// Created by r6awe on 6/6/2023.
//

#include <iostream>
#include "PhysicsComponent.h"

namespace Physics {

    PhysicsComponent::PhysicsComponent(Engine::GameObject *owner, float mass,
                                       float radius)
        : Engine::Component(owner), m_Position(owner->GetPosition()),
          m_OldPosition(owner->GetPosition()), m_Mass(mass), m_Radius(radius),
          m_Force({0, 0, 0})
    {}

    void PhysicsComponent::ApplyPhysics() {
        m_Acceleration = {};
        m_OldPosition = m_Position;

        m_Owner->Move(m_NewPosition-m_Position, 0);
    }

    void PhysicsComponent::UpdateComponent(float deltaTime) {
    }

}
