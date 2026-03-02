//
// Created by arch-excalixy on 3/2/26.
//

#pragma once

#include "ExcalCore/Core/UUID/UUID.h"
#include "ExcalCore/Core/UUID/UUID_Manager.h"

class Object {
public:
    Object() : _instance_id(UUID_Manager::GenerateNewUUID()) {}
    virtual ~Object() { UUID_Manager::FreeUUID(_instance_id); }

    [[nodiscard]] const UUID& GetInstanceID() const { return _instance_id; }

protected:
    const UUID _instance_id;
};
