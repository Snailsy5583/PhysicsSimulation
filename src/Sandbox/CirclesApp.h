#pragma once

#include "Engine/Application.h"
#include "Physics/PhysicsSolver.h"

class CirclesApp : public Engine::Application {
public:
    CirclesApp(unsigned int width, unsigned int height, const char *name,
               int numOfCircles);

    Engine::Circle* CreateCircle(Engine::Vec3 pos, float radius, float mass);

    void Update(float deltaTime) override;

    void OnEvent(Engine::Event &e) override;

    bool HandleMouseDown(Engine::MouseButtonPressedEvent &e);
    bool HandleMouseRelease(Engine::MouseButtonReleasedEvent &e);
    bool HandleMouseMoved(Engine::MouseMovedEvent &e);

private:
    enum ControlScheme {
        Move, Create
    };

    ControlScheme m_ControlScheme=Create;

    std::vector<std::unique_ptr<Engine::Circle>> m_Circles;

    bool m_IsMouseDown=false;
    Engine::Circle* m_ActiveCircle = nullptr;

    Physics::PhysicsSolver m_PhysicsSolver;
};

void UpdateObjects(float deltaTime, Engine::GameObject *owner);