#include "MyRenderer.h"

#include "Camera.h"
#include "ThreadPool.h"

MyRenderer::MyRenderer(const int thread_count) : m_thread_pool{ thread_count } {}