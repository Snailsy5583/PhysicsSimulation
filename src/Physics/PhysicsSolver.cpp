//
// Created by r6awe on 6/8/2023.
//

#include "PhysicsSolver.h"

#include <utility>
#include <iostream>

#ifdef _WIN32

#include <Windows.h>
#include <unistd.h>
#include <chrono>
#include <thread>

#else
#include <unistd.h>
#endif

namespace Physics {

    PhysicsSolver::PhysicsSolver
        (std::vector<PhysicsComponent *> objects, int substeps)
        : m_PhysicsComponents(std::move(objects)), m_NumOfSubsteps(substeps) {}

    void PhysicsSolver::SolveAll(float deltaTime) {
        deltaTime /= (float) m_NumOfSubsteps;
        for (int i = 0; i < m_NumOfSubsteps; i++) {
            for (auto comp: m_PhysicsComponents) {
                // Need this in case the component gets deleted and is
                // a wildcard ptr
                try {

                    CalculateDynamics(comp, deltaTime);
                    CalculateCollisions(comp, deltaTime);
                    ApplyPhysics(comp, deltaTime);

                } catch (std::exception &e) {
                    std::cout << e.what() << std::endl;
                    std::cout << "sus2\n";

                    // remove the item that caused this
                    std::remove(m_PhysicsComponents.begin(),
                                m_PhysicsComponents.end(), comp);
                }
            }
//            {
//                using namespace std;
//                std::this_thread::sleep_for(std::chrono::milliseconds(200));
//            }
        }
    }

    void PhysicsSolver::CalculateDynamics
        (PhysicsComponent *comp, float deltaTime) {
        comp->m_Acceleration += GRAVITY;
    }

    void PhysicsSolver::CalculateCollisions
        (PhysicsComponent *comp, float deltaTime) {
        // TODO: find collisions between balls
        for (auto other: m_PhysicsComponents) {
            if (other == comp)
                continue;

            Engine::Vec3 deltaPos = comp->m_Position - other->m_Position;
            if (deltaPos.magnitude() <= comp->m_Radius + other->m_Radius) {
//                std::cout << "collision\n";

                Engine::Vec3 moveDelta = deltaPos.normalized() *
                                         -(deltaPos.magnitude() -
                                          (comp->m_Radius + other->m_Radius));

                comp->m_Owner->Move(
                    moveDelta,
                    0
                );
                moveDelta = deltaPos.normalized() *
                            (deltaPos.magnitude() -
                             (comp->m_Radius + other->m_Radius));
                other->m_Owner->Move(
                    moveDelta,
                    0
                );
            }
        }

        CalculateCollisionDynamics(comp, deltaTime);
    }

    void PhysicsSolver::CalculateCollisionDynamics
        (PhysicsComponent *comp, float deltaTime) {
        Engine::Vec3 delta{};

        if (comp->m_Position.y - comp->m_Radius < -1.f) {
            delta += {
                0, (-1+comp->m_Radius)-comp->m_Position.y, 0
            };
        } else if (comp->m_Position.y + comp->m_Radius > 1.f) {
            delta += {
                0, (1-comp->m_Radius)-comp->m_Position.y, 0
            };
        }

        if (comp->m_Position.x - comp->m_Radius < -1.f) {
            delta += {
                (-1+comp->m_Radius)-comp->m_Position.x, 0, 0
            };
        } else if (comp->m_Position.x + comp->m_Radius > 1.f) {
            delta += {
                (1-comp->m_Radius)-comp->m_Position.x, 0, 0
            };
        }

        if (comp->m_Position.y - comp->m_Radius < -1.f ||
            comp->m_Position.y + comp->m_Radius >  1.f ||
            comp->m_Position.x - comp->m_Radius < -1.f ||
            comp->m_Position.x + comp->m_Radius >  1.f)
        {
            comp->m_OldPosition = comp->m_Position;
            comp->m_Acceleration = {};
            comp->m_Owner->Move(delta, 0);
        }
    }

    Engine::Vec3 PhysicsSolver::CalculateVerlet
        (PhysicsComponent *comp, float dt) {
        return 2 * comp->m_Position - comp->m_OldPosition +
               comp->m_Acceleration * dt * dt;
    }

    Engine::Vec3 PhysicsSolver::CalculateTCVerlet
        (PhysicsComponent *comp, float dt) {
        return comp->m_Position +
               (comp->m_Position - comp->m_OldPosition) * dt /
               comp->m_OldDeltaTime + comp->m_Acceleration * dt *
                                      (dt + comp->m_OldDeltaTime) / 2;
    }

    void PhysicsSolver::ApplyPhysics(PhysicsComponent *comp, float deltaTime) {
        comp->m_NewPosition = CalculateTCVerlet(comp, deltaTime);

        comp->m_OldDeltaTime = deltaTime;

        comp->ApplyPhysics();
    }

}