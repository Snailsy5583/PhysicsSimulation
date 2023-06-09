//
// Created by r6awe on 6/8/2023.
//

#pragma once

#include <vector>

#include "PhysicsComponent.h"
#include "Engine/GameObject.h"

namespace Physics {
    static Engine::Vec3 GRAVITY = {0, -.981f, 0};

    class PhysicsSolver {
    public:
        PhysicsSolver()=default;
        PhysicsSolver(std::vector<PhysicsComponent*> objects, int substeps=8);

        void SolveAll(float deltaTime);

        void AddPhysicsComponent(PhysicsComponent* comp) {
            m_PhysicsComponents.push_back(comp);
        }

    private:
        static void CalculateDynamics(PhysicsComponent *comp, float deltaTime);

        void CalculateCollisions(PhysicsComponent *comp, float deltaTime);

        static void CalculateCollisionDynamics(PhysicsComponent *comp,
                                               float deltaTime);

        static Engine::Vec3 CalculateVerlet(PhysicsComponent *comp, float dt);
        static Engine::Vec3 CalculateTCVerlet(PhysicsComponent *comp, float dt);

        static void ApplyPhysics(PhysicsComponent *comp, float deltaTime);

    private:
        // shouldn't use PhysicsComponent* bc the lifetime is not guaranteed
        // but idk what else to use here (can't use unique_ptr bc the App
        // should own that and shouldn't use shared_ptr because Cherno said
        // not to
        std::vector<PhysicsComponent*> m_PhysicsComponents;
        int m_NumOfSubsteps=25;
    };

}