//
// Created by arch-excalixy on 3/2/26.
//

#pragma once
#include "Component.h"

class MeshRenderer final : public Component {
public:
    explicit MeshRenderer(GameObject* const game_object, Transform* const transform) : Component(game_object, transform) {}

private:
};
