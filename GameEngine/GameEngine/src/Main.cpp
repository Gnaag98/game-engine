#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <memory>

#include <chrono>
#include <ratio>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "Scene.h"
#include "Rasterizer.h"

#include "Object.h"
#include "Camera.h"

#include "Mesh.h"
#include "Cube.h"

#include "Transform.h"
#include "Animation.h"
#include "Color.h"

#include "Vec3.h"

#include "Renderer.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

void create_objects(Scene& scene) {
  {
    auto cube = std::make_unique<Object>(Vec3f{ 0, 0, 0 });
    cube->mesh = std::make_unique<Cube>(true);

    auto parent = std::make_unique<Object>(Vec3f{ 0, 0, 0 });
    cube->parent(parent.get());

    cube->transform.translate_locally(Vec3f::right(2) + Vec3f::up(1));
    
    parent->animation = std::make_unique<Animation>();
    parent->animation->keyframes.emplace_back(0, Transform{});
    parent->animation->keyframes.emplace_back(180, Transform{ Vec3f{ 0 }, Vec3f{ 0, float(M_PI * 2), 0 } });

    scene.objects.push_back(std::move(parent));
    scene.objects.push_back(std::move(cube));
  }
}

int main() {
  // Renderer.
  auto rasterizer = std::make_shared<Rasterizer>(4);

  // Scenes.
  auto scene = Scene{ rasterizer };

  // Image settings.
  scene.settings.image_width = 256;
  scene.settings.image_height = 256;
  scene.settings.background_color = Color255{ 51 };
  scene.settings.anti_aliasing = 1;
  // Animation settings.
  scene.settings.frame_count = 1;
  scene.settings.should_write_to_file = true;
  scene.settings.output_folder = "animation_0";

  // Camera.
  { // Scoped since I don't need to keep ownership of the camera. 
    auto camera = std::make_shared<Camera>();
    camera->fov(70.0f);
    camera->aspect_ratio((float)scene.settings.image_width / (float)scene.settings.image_height);

    // TODO: Replace with keyframes on the camera object.
    camera->transform.translate(Vec3f(1.5f, 2.5f, 4));
    camera->transform.rotate_locally(Vec3f(-0.4f, 0.4f, 0));

    scene.objects.push_back(camera);
    scene.main_camera = camera;
  }

  // Add objects to the scene.
  create_objects(scene);
  
  // Render scene.
  return scene.render();
}
