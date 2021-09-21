#include "Umbra2D.h"

extern Umbra2D::Umbra2DEngine* umbra;

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
        glEnable(GL_MULTISAMPLE);

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImNodes::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImGui::StyleColorsDark();

        /*
         * If this raises a compilation error you need to switch to the "docking" branch of ImGui:
         * cd to the Dependencies/Vendor/imgui
         * git branch -a
         * git branch docking
         * git checkout docking
         */
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init( "#version 330");

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    Window::~Window() {
        ImNodes::DestroyContext();
        ImGui::DestroyContext();
        glfwTerminate();
    }
    bool Window::shouldClose() {
        return glfwWindowShouldClose(window);
    }
    void Window::startFrame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        static bool use_work_area = true;
        ImGuiWindowFlags rootFlags =
                ImGuiWindowFlags_NoMove
                | ImGuiWindowFlags_NoCollapse
                | ImGuiWindowFlags_NoDocking
                | ImGuiWindowFlags_NoResize
                | ImGuiWindowFlags_NoTitleBar
                | ImGuiWindowFlags_MenuBar
                | ImGuiWindowFlags_NoBackground
                | ImGuiWindowFlags_NoBringToFrontOnFocus;

        const ImGuiViewport *viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
        ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);

        ImGui::Begin("RootWindow", (bool*)use_work_area, rootFlags);
        ImGui::DockSpace(ImGui::GetID("MainWindow"));
    }
    void Window::endFrame() {
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glm::vec2 Window::getSize() {
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
