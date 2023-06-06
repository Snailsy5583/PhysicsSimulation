#include "CirclesApp.h"

void CirclesApp::Update(float deltaTime) {
    std::cout << deltaTime*1000 << "ms" << std::endl;
    for (const auto & circle : m_Circles) {
        circle->Update(deltaTime);
    }
}

void UpdateObjects(float deltaTime);

CirclesApp::CirclesApp(unsigned int width, unsigned int height,
                       const char *name, int numOfCircles)
    : Engine::Application(width, height, name) {
    for (int i=0; i<numOfCircles; i++) {
        m_Circles.push_back(
            std::make_unique<Engine::Circle>(
                5, Engine::Vec3({0, 0,0}), 0)
        );
        m_Circles.back()->SetUpdateCallback(&UpdateObjects);
    }
}

void UpdateObjects(float deltaTime) {
    std::cout << "sus" << std::endl;
}