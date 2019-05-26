#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <memory>

#include <chrono>
#include <ratio>

#include "Scene.h"
#include "Rasterizer.h"

#include "Object.h"
#include "Camera.h"

#include "Mesh.h"
#include "Cube.h"

#include "Transform.h"
#include "Keyframe.h"
#include "Color.h"

#include "Vec3.h"

void create_objects(Scene& scene) {
  // 3x3 grid of cubes.
  auto cube_mesh = std::make_shared<Cube>(true);

  {
    auto cube = std::make_unique<Object>(Transform::ORIGIN, cube_mesh);
    scene.objects.push_back(std::move(cube));
  }
  
  //std::array<Transform, 26> cube_transforms = {
  //  Transform(Vec3f(-6, -6, -6), Vec3f(0), Vec3f(1)),
  //  Transform(Vec3f(0, -6, -6), Vec3f(0), Vec3f(1)),
  //  Transform(Vec3f(6, -6, -6), Vec3f(0), Vec3f(1)),
  //  Transform(Vec3f(-6, -6,  0), Vec3f(0), Vec3f(1)),
  //  Transform(Vec3f(0, -6,  0), Vec3f(0), Vec3f(1)),
  //  Transform(Vec3f(6, -6,  0), Vec3f(0), Vec3f(1)),
  //  Transform(Vec3f(-6, -6,  6), Vec3f(0), Vec3f(1)),
  //  Transform(Vec3f(0, -6,  6), Vec3f(0), Vec3f(1)),
  //  Transform(Vec3f(6, -6,  6), Vec3f(0), Vec3f(1)),
  //
  //  Transform(Vec3f(-6,   0, -6), Vec3f(0), Vec3f(1)),
  //  Transform(Vec3f(0,   0, -6), Vec3f(0), Vec3f(1)),
  //  Transform(Vec3f(6,   0, -6), Vec3f(0), Vec3f(1)),
  //  Transform(Vec3f(-6,   0,  0), Vec3f(0), Vec3f(1)),
  //  //Transform(Vec3f( 0,   0,  0), Vec3f(0), Vec3f(1)),
  //  Transform(Vec3f(6,   0,  0), Vec3f(0), Vec3f(1)),
  //  Transform(Vec3f(-6,   0,  6), Vec3f(0), Vec3f(1)),
  //  Transform(Vec3f(0,   0,  6), Vec3f(0), Vec3f(1)),
  //  Transform(Vec3f(6,   0,  6), Vec3f(0), Vec3f(1)),
  //
  //  Transform(Vec3f(-6,  6, -6), Vec3f(0), Vec3f(1)),
  //  Transform(Vec3f(0,  6, -6), Vec3f(0), Vec3f(1)),
  //  Transform(Vec3f(6,  6, -6), Vec3f(0), Vec3f(1)),
  //  Transform(Vec3f(-6,  6,  0), Vec3f(0), Vec3f(1)),
  //  Transform(Vec3f(0,  6,  0), Vec3f(0), Vec3f(1)),
  //  Transform(Vec3f(6,  6,  0), Vec3f(0), Vec3f(1)),
  //  Transform(Vec3f(-6,  6,  6), Vec3f(0), Vec3f(1)),
  //  Transform(Vec3f(0,  6,  6), Vec3f(0), Vec3f(1)),
  //  Transform(Vec3f(6,  6,  6), Vec3f(0), Vec3f(1))
  //};
  //
  //for (const Transform& transform : cube_transforms) {
  //  auto cube = std::make_unique<Object>(transform, cube_mesh);
  //  scene.objects.push_back(std::move(cube));
  //}
}

int main() {
  // Renderer.
  auto rasterizer = std::make_shared<Rasterizer>(4);

  // Scenes.
  auto scene1 = Scene{ rasterizer };

  // Image settings.
  scene1.settings.image_width = 256;
  scene1.settings.image_height = 256;
  scene1.settings.background_color = Color255(51);
  scene1.settings.anti_aliasing = 1;
  // Animation settings.
  scene1.settings.frame_count = 30;
  scene1.settings.should_write_to_file = true;
  scene1.settings.output_folder = "animation_0";

  // Camera.
  { // Scoped since I don't need to keep ownership of the camera. 
    auto camera = std::make_shared<Camera>();
    camera->fov(70.0f);
    camera->aspect_ratio((float)scene1.settings.image_width / (float)scene1.settings.image_height);

    // TODO: Replace with keyframes on the camera object.
    camera->transform.translate(Vec3f(2, 2, 2));
    camera->transform.rotate(Vec3f(-std::atan(1.0 / sqrt(2)), M_PI_4, 0));

    scene1.objects.push_back(camera);
    scene1.main_camera = camera;
  }

  // Add objects to the scene.
  create_objects(scene1);

  // TODO: Create keyframes for individual objects instead.
  //// Camera animation.
  //std::cout << "Creating Keyframes...\n";
  //std::vector<Keyframe> keyframes;
  //Keyframe keyframe;
  //
  //keyframe.frame = 0;
  //keyframe.transform.position(Vec3f(2, 2, 2));
  //keyframe.transform.rotation(Vec3f(-std::atan(1.0/sqrt(2)), M_PI_4, 0));
  //keyframe.transform.scale(Vec3f(1));
  //keyframes.push_back(keyframe);
  //std::cout << "Done creating Keyframes.\n";
  
  // Render scene.
  scene1.render();

  std::cout << "Press Enter to exit.";
  std::cin.get();
}
