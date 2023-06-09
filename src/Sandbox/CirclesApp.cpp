#include "CirclesApp.h"

CirclesApp::CirclesApp(unsigned int width, unsigned int height,
                       const char *name, int numOfCircles)
    : Engine::Application(width, height, name){
    srand(std::time(nullptr)*9124715734616757671/7*3%127757197238757);

    for (int i=0; i<numOfCircles; i++) {
        float radius = ((rand()%1000+700)/1700.f)/15;
        float x = ((rand() % 1000) / 1000.f) * 1.8 - 1.8 / 2;
        float y = ((rand() % 1000) / 1000.f) * 1.8 - 1.8 / 2;
        Engine::Vec3 pos = Engine::Vec3({x, y, 0});

        m_Circles.push_back(std::make_unique<Engine::Circle>(radius, pos,
                                                             0));

        m_Circles.back()->SetUpdateCallback(&UpdateObjects);

        //Physics Component
        std::unique_ptr<Physics::PhysicsComponent> comp =
            std::make_unique<Physics::PhysicsComponent>
                (m_Circles.back().get(), radius*30, radius);
        m_PhysicsSolver.AddPhysicsComponent(comp.get());
        m_Circles.back()->AddComponent(std::move(comp));

        // update shader uniforms
        m_Circles.back()->GetRendererObject().shader.SetUniform("radius",
                                                                radius);
        m_Circles.back()->GetRendererObject().shader.SetUniformVec(
            "pos", 3, pos.toArr());
    }
}

void UpdateObjects(float deltaTime, Engine::GameObject *owner) {
}

void CirclesApp::Update(float deltaTime) {
    std::cout << 1/m_DeltaTime << std::endl;
    m_PhysicsSolver.SolveAll(deltaTime);

    for (const auto & circle : m_Circles) {
        circle->Update(deltaTime);
        circle->Render();
    }
}