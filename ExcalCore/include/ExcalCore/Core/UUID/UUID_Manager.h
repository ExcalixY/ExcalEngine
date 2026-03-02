//
// Created by arch-excalixy on 3/2/26.
//

#pragma once

#include <random>
#include <unordered_set>

#include "UUID.h"

class UUID_Manager final {
public:
    UUID_Manager() = delete;

    static void Init();
    static UUID GenerateNewUUID();
    static void FreeUUID(UUID uuid);

private:
    static std::unordered_set<UUID> _verified_uuids;
    static std::mt19937_64 _gen;
    static std::uniform_int_distribution<uint64_t> _dis;
};
