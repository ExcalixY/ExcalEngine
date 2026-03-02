//
// Created by arch-excalixy on 3/2/26.
//

#pragma once

#include "Object.h"
#include "Components/Transform.h"

#include <memory>

#include "ExcalCore/Systems/Debug/Log.h"

class GameObject : public Object {
public:
    explicit GameObject() : _transform(this) {}
    explicit GameObject(std::string name) : _name(std::move(name)), _transform(this) {}

    template <std::derived_from<Component> T>
    T* GetComponent();

    template <std::derived_from<Component> T>
    T* AddComponent();

    template <std::derived_from<Component> T>
    bool RemoveComponent();

private:
    std::string _name;
    Transform _transform;
    std::vector<std::unique_ptr<Component>> _components;
};


template <std::derived_from<Component> T>
T* GameObject::GetComponent() {
    if (typeid(T) == typeid(Transform)) {
        return &_transform;
    }

    for (std::unique_ptr<Component>& ptr : _components) {
        if (T* i = dynamic_cast<T*>(ptr.get())) {
            return i;
        }
    }

    Debug::LogWarning("GameObject {} does not contain Component {}.", _name, typeid(T).name());
    return nullptr;
}

template<std::derived_from<Component> T>
T* GameObject::AddComponent() {
    for (auto& ptr : _components) {
        if (auto i = dynamic_cast<T*>(ptr.get())) {
            Debug::LogWarning("GameObject {} already contains Component {}.", _name, typeid(T).name());
            return nullptr;
        }
    }

    auto ptr = std::make_unique<T>(this, &_transform);
    T* ptr_ret = ptr.get();

    if (ptr != nullptr) {
        _components.push_back(std::move(ptr));
        return nullptr;
    }

    Debug::LogError("Failed to Add Component to GameObject {}. Component: {}.", _name, typeid(T).name());
    return ptr_ret;
}

template<std::derived_from<Component> T>
bool GameObject::RemoveComponent() {
    auto it = _components.begin();
    while (it != _components.end()) {
        if (dynamic_cast<T*>(it->get())) {
            _components.erase(it);
            return true;
        }

        ++it;
    }

    Debug::LogWarning("GameObject {} does not contain Component {}.", _name, typeid(T).name());
    return false;
}