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

    template <std::derived_from<Component> T, typename... Args>
    T* AddComponent(Args... args);

    template <std::derived_from<Component> T>
    bool RemoveComponent();

    Transform* GetTransform() { return &_transform; }

private:
    std::string _name;
    Transform _transform;
    std::vector<std::unique_ptr<Component>> _components;
};


template <std::derived_from<Component> T>
T* GameObject::GetComponent() {
    if constexpr(std::is_same_v<T, Transform>) {
        Debug::LogWarning("GameObject already contains component Transform in it's own class. Use GetTransform() instead.");
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

template<std::derived_from<Component> T, typename... Args>
T* GameObject::AddComponent(Args... args) {
    if constexpr(std::is_same_v<T, Transform>) {
        Debug::LogWarning("GameObject already contains component Transform in it's own class. Use GetTransform() instead.");
        return &_transform;
    }


    for (std::unique_ptr<Component>& ptr : _components) {
        if (T* i = dynamic_cast<T*>(ptr.get())) {
            Debug::LogWarning("GameObject {} already contains Component {}.", _name, typeid(T).name());
            return i;
        }
    }

    auto ptr = std::make_unique<T>(this, &_transform, std::forward<Args>(args)...);
    T* ptr_ret = ptr.get();

    if (ptr != nullptr) {
        _components.push_back(std::move(ptr));
        return ptr_ret;
    }

    Debug::LogError("Failed to Add Component to GameObject {}. Component: {}.", _name, typeid(T).name());
    return nullptr;
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