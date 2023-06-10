#include "CirclesApp.h"

#include "Physics/PhysicsComponent.h"

CirclesApp::CirclesApp(unsigned int width, unsigned int height,
                       const char *name, int numOfCircles)
    : Engine::Application(width, height, name){
    srand(std::time(nullptr)*9124715734616757671/7*3%127757197238757);

    for (int i=0; i<numOfCircles; i++) {
        Engine::Vec3 pos{((rand() % 1000) / 1000.f) * 1.8f - 1.8f / 2,
                         ((rand() % 1000) / 1000.f) * 1.8f - 1.8f / 2,
                         0};
        float radius = ((rand()%1000+200)/1200.f)/15;
        float mass = (radius*15)*1000;

        CreateCircle(pos, radius, mass);
    }
}

Engine::Circle *CirclesApp::CreateCircle
    (Engine::Vec3 pos, float radius, float mass) {
    m_Circles.push_back(std::make_unique<Engine::Circle>(radius, pos,
                                                         0));

    m_Circles.back()->SetUpdateCallback(&UpdateObjects);

    //Physics Component
    std::unique_ptr<Physics::PhysicsComponent> comp =
        std::make_unique<Physics::PhysicsComponent>
            (m_Circles.back().get(), mass, radius);
    m_PhysicsSolver.AddPhysicsComponent(comp.get());
    m_Circles.back()->AddComponent(std::move(comp));

    // update shader uniforms
    m_Circles.back()->GetRendererObject().shader.SetUniform("radius",
                                                            radius);
    m_Circles.back()->GetRendererObject().shader.SetUniformVec(
        "pos", 3, pos.toArr());

    return m_Circles.back().get();
}

void UpdateObjects(float deltaTime, Engine::GameObject *owner) {
}

void CirclesApp::Update(float deltaTime) {
//    std::cout << 1/m_DeltaTime << std::endl;
    m_PhysicsSolver.SolveAll(deltaTime);

    for (const auto & circle : m_Circles) {
        circle->Update(deltaTime);
        circle->Render();
    }
}

void CirclesApp::OnEvent(Engine::Event &e) {
    Engine::EventDispatcher dispatcher(e);

    dispatcher.Dispatch<Engine::MouseButtonPressedEvent>(
        BIND_EVENT_FUNC(CirclesApp::HandleMouseDown, this));
    dispatcher.Dispatch<Engine::MouseButtonReleasedEvent>(
        BIND_EVENT_FUNC(CirclesApp::HandleMouseRelease, this));
    dispatcher.Dispatch<Engine::MouseMovedEvent>(
        BIND_EVENT_FUNC(CirclesApp::HandleMouseMoved, this));

    Application::OnEvent(e);
}

bool CirclesApp::HandleMouseDown(Engine::MouseButtonPressedEvent &e) {
    Engine::Vec3 mousePos{};
    e.GetMousePosition(mousePos.x, mousePos.y);

    m_IsMouseDown = e.GetMouseButton()==1;
    for (const auto &circle : m_Circles) {
        if ((circle->GetPosition() - mousePos).magnitude() < circle->GetRadius()) {
            m_ActiveCircle = circle.get();

            auto *comp = m_ActiveCircle->
                TryGetComponent<Physics::PhysicsComponent>();
            if (comp)
                comp->SetKinematic(true);

            return true;
        }
    }
    return false;
}

bool CirclesApp::HandleMouseRelease(Engine::MouseButtonReleasedEvent &e) {
    m_IsMouseDown = false;

    if (!m_ActiveCircle)
        return false;

    m_ActiveCircle->TryGetComponent<Physics::PhysicsComponent>()
        ->SetKinematic(false);
    m_ActiveCircle = nullptr;

    return true;
}

bool CirclesApp::HandleMouseMoved(Engine::MouseMovedEvent &e) {
    Engine::Vec3 mousePos{};
    e.GetMousePosition(mousePos.x, mousePos.y);
    if (m_IsMouseDown) {
        float radius = ((rand()%1000+200)/1200.f)/15;
        float mass = (radius*15)*1000;

        CreateCircle(mousePos, radius, mass);
    } else {
        if (m_ActiveCircle) {
            Engine::Vec3 mouseDelta = (mousePos -
                                       m_ActiveCircle->GetPosition());
            m_ActiveCircle->Move(mouseDelta, 0);
            return true;
        }
    }
    return false;
}
