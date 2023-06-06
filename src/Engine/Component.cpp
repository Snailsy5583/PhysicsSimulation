//
// Created by r6awe on 6/6/2023.
//

#include "Component.h"
#include "GameObject.h"

namespace Engine {

    Component::Component(GameObject *owner) : m_Owner(owner)
    {}

}