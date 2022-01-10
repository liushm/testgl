#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main(int argc, char* argv[])
{
    glfwInit();

    auto window = glfwCreateWindow(1600, 900, "test", nullptr, nullptr);

    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(1.0, 1.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
