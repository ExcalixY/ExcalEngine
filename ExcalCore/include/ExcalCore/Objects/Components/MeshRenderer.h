//
// Created by arch-excalixy on 3/2/26.
//

#pragma once

#include "Component.h"
#include "ExcalCore/Rendering/Material.h"
#include "ExcalCore/Rendering/Meshes/Mesh.h"

class MeshRenderer final : public Component {
public:
    explicit MeshRenderer(GameObject* const game_object, Transform* const transform) :
        Component(game_object, transform) {}

    explicit MeshRenderer(
        GameObject* const game_object, Transform* const transform, const bool cast_shadows,
        const bool capture_shadows, const uint32_t render_layer) :
            Component(game_object, transform), _cast_shadows(cast_shadows), _capture_shadows(capture_shadows),
            _render_layer(render_layer) {}

    [[nodiscard]] Mesh* GetMesh() const { return _mesh; }
    void SetMesh(Mesh* mesh) { _mesh = mesh; }

    void AddMaterial(Material* material) { _material_list = material; }
    [[nodiscard]] Material* GetMaterial(const size_t index) const { return _material_list; }
    // [[nodiscard]] std::vector<Material*>& GetMaterialList() { return _material_list; }
    // [[nodiscard]] size_t GetMaterialCount() const { return _material_list.size(); }

    friend class Renderer;

private:
    Mesh* _mesh = nullptr;
    Material* _material_list = nullptr;

    bool _cast_shadows = true;
    bool _capture_shadows = true;
    uint32_t _render_layer = 0;
};
