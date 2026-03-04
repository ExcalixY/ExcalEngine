//
// Created by arch-excalixy on 3/2/26.
//

#pragma once

#include <string>
#include <vector>

#include "Vertex.h"

struct MeshData {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    void BindData(const std::vector<Vertex> &vert, const std::vector<unsigned int> &ind) {
        this->vertices = vert;
        this->indices = ind;
    }
};

class Mesh {
public:
    Mesh() = delete;

    explicit Mesh(std::string_view mesh_file_path);
    explicit Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

    void InitBuffers();
    void BufferData() const;
    void BindBuffer() const;
    static void UnbindBuffer();

    [[nodiscard]] unsigned int GetVAO() const { return _VAO; }
    [[nodiscard]] unsigned int GetVBO() const { return _VBO; }
    [[nodiscard]] unsigned int GetEBO() const { return _EBO; }

    [[nodiscard]] size_t GetVertexCount() const { return _data.vertices.size(); }
    [[nodiscard]] size_t GetIndexCount() const { return _data.indices.size(); }

private:
    MeshData _data;
    unsigned int _VAO = 0, _VBO = 0, _EBO = 0;
};