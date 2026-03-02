//
// Created by arch-excalixy on 3/2/26.
//

#pragma once

#include "ExcalCore/Objects/Object.h"

class GameObject;
class Transform;

class Component : public Object {
public:
    explicit Component(GameObject* const game_object, Transform* const transform) :
        _game_object(game_object), _transform(transform) {}

    ~Component() override = default;

    Transform* GetTransform() { return _transform; }
    [[nodiscard]] const Transform *GetTransform() const { return _transform; }

    GameObject* GetGameObject() { return _game_object; }
    [[nodiscard]] const GameObject* GetGameObject() const { return _game_object; }

    [[nodiscard]] const UUID& GetUUID() const { return _instance_id; }

    virtual void OnStart() {}
    virtual void OnUpdate() {}

protected:
    GameObject* const _game_object;
    Transform* const _transform;
};