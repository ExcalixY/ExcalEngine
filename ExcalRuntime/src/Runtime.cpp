//
// Created by arch-excalixy on 3/1/26.
//

#include "ExcalRuntime/Runtime.h"
#include "ExcalCore/Objects/Components/MeshRenderer.h"
#include "ExcalCore/Objects/GameObject.h"
#include "ExcalCore/Rendering/GPU_Data.h"

Runtime::Runtime(const RuntimeMode mode)
    : _mode(mode), _renderer(), _time(), _input_system(_renderer.GetWindow()) {}

Runtime::~Runtime() = default;

void Runtime::RunStandalone() {
  bool _running = true;

  GameObject obj_cam = GameObject();
  auto cam = obj_cam.AddComponent<Camera>();

  cam->SetFOV(90.0f);
  cam->SetNearClip(0.01f);
  cam->SetFarClip(1000.0f);

  SetActiveCamera(cam);

  std::vector<Vertex> vertices = {
      // Front face (normal: 0, 0, 1)
      {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // 0
      {{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},  // 1
      {{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},   // 2
      {{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},  // 3

      // Back face (normal: 0, 0, -1)
      {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}}, // 4
      {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},  // 5
      {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},   // 6
      {{-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},  // 7

      // Left face (normal: -1, 0, 0)
      {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, // 8
      {{-0.5f, -0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},  // 9
      {{-0.5f, 0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},   // 10
      {{-0.5f, 0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},  // 11

      // Right face (normal: 1, 0, 0)
      {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}}, // 12
      {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},  // 13
      {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},   // 14
      {{0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},  // 15

      // Top face (normal: 0, 1, 0)
      {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}, // 16
      {{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},  // 17
      {{0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},   // 18
      {{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},  // 19

      // Bottom face (normal: 0, -1, 0)
      {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}}, // 20
      {{-0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},  // 21
      {{0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},   // 22
      {{0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},  // 23
  };

  std::vector<unsigned int> indices = {
      0,  1,  2,  2,  3,  0,  // Front
      4,  6,  5,  6,  4,  7,  // Back  (winding flipped)
      8,  9,  10, 10, 11, 8,  // Left
      12, 14, 13, 14, 12, 15, // Right (winding flipped)
      16, 17, 18, 18, 19, 16, // Top
      20, 22, 21, 22, 20, 23  // Bottom (winding flipped)
  };

  GameObject obj_cube = GameObject();
  auto trans = obj_cube.GetTransform();
  auto mesh = obj_cube.AddComponent<MeshRenderer>();
  auto mesh_inst = Mesh(vertices, indices);
  auto mat = Material("vert.vert", "frag.frag");
  mesh_inst.InitBuffers();
  mesh_inst.BufferData();

  auto trans_cam = obj_cam.GetTransform();

  mesh->SetMesh(&mesh_inst);
  mesh->AddMaterial(&mat);

  _input_system.BindAxis2D("Movement", KeyCode::W, KeyCode::S, KeyCode::A,
                           KeyCode::D);

  glm::vec2 input;

  // in RunStandalone, hardcode positions
  trans_cam->SetPosition(glm::vec3(0.0f, 0.0f, 5.0f)); // camera 5 units back
  trans->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));     // cube at origin

  while (_running) {
    cam->SetAspectRatio(_renderer.GetAspectRatio());

    glfwPollEvents();
    _input_system.Update();
    _time.Update();

    input = _input_system.GetAxis2D("Movement");

    if (_input_system.GetKeyDown(KeyCode::Escape) ||
        glfwWindowShouldClose(_renderer.GetWindow())) {
      _running = false;
    }

    _renderer.BeginRendering(cam);
    _renderer.RenderMesh(mesh);
    // for (MeshRenderer& mesh : _scene.GetRendererList()) {
    //     _renderer.RenderMesh(mesh.GetMesh(), mesh.GetTransform());
    // }
    _renderer.FlushRendering();
    _renderer.EndRendering();
  }
}

void Runtime::RunEditor() {}
