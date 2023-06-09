#pragma once

#include "Engine/Application.h"
#include "Physics/PhysicsSolver.h"

class CirclesApp : public Engine::Application {
public:
    CirclesApp(unsigned int width, unsigned int height, const char *name,
               int numOfCircles);

    void Update(float deltaTime) override;

private:
    std::vector<std::unique_ptr<Engine::Circle>> m_Circles;

    Physics::PhysicsSolver m_PhysicsSolver;
};

void UpdateObjects(float deltaTime, Engine::GameObject *owner);