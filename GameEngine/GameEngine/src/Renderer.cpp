#include "Renderer.h"

#include "Camera.h"
#include "ThreadPool.h"

Renderer::Renderer(const int thread_count) : m_thread_pool{ thread_count } {}