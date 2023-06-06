#pragma once

#include "Engine/Application.h"
#include "Physics/PhysicsComponent.h"

class CirclesApp : public Engine::Application {
public:
    CirclesApp(unsigned int width, unsigned int height, const char *name,
               int numOfCircles);

    virtual void Update(float deltaTime) override;

protected:
    std::vector<std::unique_ptr<Engine::Circle>> m_Circles;
};
