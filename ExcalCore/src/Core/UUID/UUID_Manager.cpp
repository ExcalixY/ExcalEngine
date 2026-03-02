//
// Created by arch-excalixy on 3/2/26.
//

#include "ExcalCore/Core/UUID/UUID_Manager.h"
#include "ExcalCore/Systems/Debug/Log.h"

std::unordered_set<UUID> UUID_Manager::_verified_uuids;
std::mt19937_64 UUID_Manager::_gen{std::random_device()()};
std::uniform_int_distribution<uint64_t> UUID_Manager::_dis;

void UUID_Manager::Init() {
    _verified_uuids.reserve(1024);
}

UUID UUID_Manager::GenerateNewUUID() {
    UUID uuid = _dis(_gen);

    while (_verified_uuids.contains(uuid)) {
        uuid = _dis(_gen);
    }

    _verified_uuids.insert(uuid);
    return uuid;
}

void UUID_Manager::FreeUUID(UUID uuid) {
    if (!_verified_uuids.contains(uuid)) {
        Debug::LogWarning("UUID '{}' is not registered.", uuid);
        return;
    }

    _verified_uuids.erase(uuid);
}