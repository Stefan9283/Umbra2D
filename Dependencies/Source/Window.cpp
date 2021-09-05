#include "Window.h"
#include "AssetLibrary.h"

extern Umbra2D::AssetLibrary* lib;


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}
void resize(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

namespace Umbra2D {
    Window::Window() {
        if (!glfwInit())
        exit(EXIT_FAILURE);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        window = glfwCreateWindow(2000, 1000, "Umbra2D", nullptr, nullptr);

        if (!window) {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        //glfwSetKeyCallback(window, key_callback);
        glfwMakeContextCurrent(window);
        gladLoadGL();
        glfwSwapInterval(1);

        glfwSetFramebufferSizeCallback(window, resize);
        glEnable(GL_DEPTH_TEST);

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImGui::StyleColorsDark();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init( "#version 330");

        glEnable(GL_BLEND); 
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
        glClearColor(0.3f, 0.1f, 0.4f, 1.f);

        lib = new Umbra2D::AssetLibrary();
    }
    Window::~Window() {
        // glfwTerminate();
    }
    bool Window::shouldClose() {
        return glfwWindowShouldClose(window);
    }
    void Window::startFrame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    void Window::endFrame() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glm::vec<2, double> Window::getSize() {
        int w, h;
        glfwGetWindowSize(window, &w, &h);
        return {w, h};
    }
    bool Window::wasKeyPressed(int key) {
        return glfwGetKey(window, key) == GLFW_PRESS;
    }
    bool Window::wasKeyReleased(int key) {
        return glfwGetKey(window, key) == GLFW_RELEASE;
    }
}
