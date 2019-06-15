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

#include "AmbientLight.h"
#include "DirectionalLight.h"
#include "PointLight.h"

void create_objects(Scene& scene) {
  {
    auto floor = std::make_unique<Object>(Vec3f{ 0, -(1 + 0.2f), 0 });
    floor->mesh = std::make_unique<Cube>();

    floor->transform.local_scale(Vec3f{ 2.5f, 0.2f, 2.5f });

    scene.objects.push_back(std::move(floor));
  }
  {
    auto cube = std::make_unique<Object>(Vec3f{ 0, 0, 0 });
    cube->mesh = std::make_unique<Cube>(false);

    auto parent = std::make_unique<Object>(Vec3f{ 0, 0, 0 });
    cube->parent(parent.get());

    //cube->transform.translate_locally(Vec3f::right(4));
    
    //parent->animation = std::make_unique<Animation>();
    //parent->animation->keyframes.emplace_back(0, Transform{ Vec3f{ 0, 0, 0 } });
    //parent->animation->keyframes.emplace_back(180, Transform{ Vec3f{ 0, 0, 0 }, Vec3f{ 0, float(M_PI * 2), 0 } });

    scene.objects.push_back(std::move(parent));
    scene.objects.push_back(std::move(cube));
  }
  {
    auto ambient_light = std::make_unique<AmbientLight>(0.05f, Color::WHITE);

    auto red_transform = Transform{ Vec3f{ 0, 4, 0 }, Vec3f{ 0, float(-M_PI_2), 0 } };
    auto red_light = std::make_unique<DirectionalLight>(red_transform, 0.1f, Color::RED);
    
    auto green_transform = Transform{ Vec3f{ 0, 4, 0 }, Vec3f{ float(M_PI_2), 0, 0 } };
    auto green_light = std::make_unique<DirectionalLight>(green_transform, 0.1f, Color::GREEN);
    
    auto blue_transform = Transform{ Vec3f{ 0, 4, 0 }, Vec3f{ 0, float(M_PI), 0 } };
    //auto blue_light = std::make_unique<DirectionalLight>(blue_transform, 0.1f, Color::BLUE);
    auto blue_light = std::make_unique<DirectionalLight>(blue_transform, 0.1f, Color::WHITE);

    auto orbiting_parent = std::make_unique<Object>();
    orbiting_parent->animation = std::make_unique<Animation>();
    orbiting_parent->animation->keyframes.emplace_back(0, Transform{});
    orbiting_parent->animation->keyframes.emplace_back(180, Transform{ Vec3f{}, Vec3f{ 0, 0, -float(M_PI * 2) } });

    auto orbiting_transform = Transform{ Vec3f{ 0, 0, 0 } };
    auto orbiting_light = std::make_unique<PointLight>(orbiting_transform, 0.5f, Color::RED);
    orbiting_light->parent(orbiting_parent.get());
    orbiting_light->transform.translate_locally(Vec3f::right(4));

    auto point_transform = Transform{};
    auto point_light = std::make_unique<PointLight>(point_transform, 0.2f, Color::GREEN);
    point_light->animation = std::make_unique<Animation>();
    point_light->animation->keyframes.emplace_back(0,   Transform{ Vec3f{  6,  3,  6 } });
    point_light->animation->keyframes.emplace_back(45,  Transform{ Vec3f{ -6,  3,  6 } });
    point_light->animation->keyframes.emplace_back(90,  Transform{ Vec3f{ -6,  3, -6 } });
    point_light->animation->keyframes.emplace_back(135, Transform{ Vec3f{  6,  3, -6 } });
    point_light->animation->keyframes.emplace_back(180, Transform{ Vec3f{  6,  3,  6 } });

    scene.objects.push_back(std::move(ambient_light));
    
    //scene.objects.push_back(std::move(red_light));
    //scene.objects.push_back(std::move(green_light));
    scene.objects.push_back(std::move(blue_light));
    
    scene.objects.push_back(std::move(point_light));

    scene.objects.push_back(std::move(orbiting_parent));
    scene.objects.push_back(std::move(orbiting_light));
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
  scene.settings.background_color = Color255{ 20 };
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
    camera->transform.translate(Vec3f(5, 3, 8));
    camera->transform.rotate_locally(Vec3f(-0.4f, 0.6f, 0));

    scene.objects.push_back(camera);
    scene.main_camera = camera;
  }

  // Add objects to the scene.
  create_objects(scene);
  
  // Render scene.
  return scene.render();
}
