#include <iostream>
#include <chrono>
#include <string>
// #include <windows.h>
// #include <algorithm>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

using glm::vec3;

glm::mat4 m = glm::mat4(1.0);
glm::mat4 v = glm::mat4(1.0);
glm::mat4 p = glm::mat4(1.0);

static void resize(GLFWwindow* window, int width, int height)
{
	std::cout << "resize: " << width << " " << height << std::endl;
	glViewport(0, 0, width, height);

	//int ww, hh;
	//glfwGetFramebufferSize(window, &ww, &hh);
	//std::cout << ww << " xxxx " << hh << std::endl;
}

bool pressed = false;
double lastx = 0.0;
double lasty = 0.0;

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (pressed) {
		const double dx = xpos - lastx;
		const double dy = ypos - lasty;
		lastx = xpos;
		lasty = ypos;

		v = glm::rotate(v, glm::radians((float)dx / 2.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::vec4 vc = glm::inverse(v) * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
		v = glm::rotate(v, glm::radians((float)dy / 2.0f), glm::vec3(vc.x, vc.y, vc.z));
	}
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS/* && (mods & GLFW_MOD_ALT) */) {
		pressed = true;
		glfwGetCursorPos(window, &lastx, &lasty);
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		pressed = false;
	}
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	const float SCALE = 1.2f;
	v = glm::scale(v, glm::vec3(yoffset > 0.0 ? SCALE : 1.0f/SCALE));
}

int main()
// int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1000, 600, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	//
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	if (monitor) {
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		std::cout << mode->width << " " << mode->height << std::endl;

		int w, h;
		glfwGetMonitorPhysicalSize(monitor, &w, &h);
		std::cout << w << " " << h << std::endl;

		float xs, ys;
		glfwGetMonitorContentScale(monitor, &xs, &ys);
		std::cout << xs << " " << ys << std::endl;

		glfwGetMonitorPos(monitor, &w, &h);
		std::cout << w << " " << h << std::endl;

		int x, y;
		glfwGetMonitorWorkarea(monitor, &x, &y, &w, &h);
		std::cout << x << " " << y << " " << w << " " << h << std::endl;

		std::cout << glfwGetMonitorName(monitor) << std::endl;
	}

	//
	glm::vec4 position(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 model(1.0f);
	glm::vec4 transformed = model * position;

	std::cout << transformed.x << std::endl;
	std::cout << transformed.y << std::endl;
	std::cout << transformed.z << std::endl;

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	gladLoadGL();

	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* vendor = glGetString(GL_VENDOR);
	const GLubyte* version = glGetString(GL_VERSION);
	const GLubyte* glslver = glGetString(GL_SHADING_LANGUAGE_VERSION);

	std::cout << renderer << std::endl;
	std::cout << vendor << std::endl;
	std::cout << version << std::endl;
	std::cout << glslver << std::endl;

	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	std::cout << major << "." << minor << std::endl;

	GLint extensions;
	glGetIntegerv(GL_NUM_EXTENSIONS, &extensions);
	for (int i = 0; i < extensions; i++) {
		std::cout << glGetStringi(GL_EXTENSIONS, i) << std::endl;
	}

	// glfwGetFramebufferSize
	// glfwGetWindowSize

	glfwSetWindowSizeCallback(window, resize);


	//
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	assert(vShader != 0);

	std::string src = R"(#version 460
in vec3 VertexPosition;
in vec3 VertexColor;
out vec3 Color;
uniform mat4 mvp;
void main()
{
	Color = VertexColor;
	gl_Position = mvp * vec4( VertexPosition, 1.0 );
}
)";

	const GLchar* code[] = { src.c_str() };

	glShaderSource(vShader, 1, code, nullptr);
	glCompileShader(vShader);

	src = R"(#version 460
in vec3 Color;
out vec4 FragColor;
void main() {
	FragColor = vec4(Color, 1.0);
}
)";

	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fcode[] = { src.c_str() };
	glShaderSource(fShader, 1, fcode, nullptr);
	glCompileShader(fShader);

	/*GLint result;
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		std::cout << "compile failed" << std::endl;
	}*/

	GLuint program = glCreateProgram();
	assert(program != 0);

	glAttachShader(program, vShader);
	glAttachShader(program, fShader);

	glLinkProgram(program);
	GLint result;
	glGetShaderiv(vShader, GL_LINK_STATUS, &result);
	if (result == GL_FALSE) {
		std::cout << "link failed" << std::endl;
	}

	glUseProgram(program);


	//
	float positionData[] = {
		-0.8f, -0.8f, 0.0f,
		0.8f, -0.8f, 0.0f,
		0.0f, 0.8f, 0.0f,

		-0.2f, -0.2f, 1.0f,
		0.2f, -0.2f, 1.0f,
		0.0f, 0.2f, 1.0f
	};
	float colorData[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,

		1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f
	};
	GLuint index[] = { 0, 1, 2, 3, 4, 5 };

	float positionCood[] = {
		-5.0f, 0.0f, -5.0f,    -5.0f, 0.0f, 5.0f,
		-4.0f, 0.0f, -5.0f,    -4.0f, 0.0f, 5.0f,
		-3.0f, 0.0f, -5.0f,    -3.0f, 0.0f, 5.0f,
		-2.0f, 0.0f, -5.0f,    -2.0f, 0.0f, 5.0f,
		-1.0f, 0.0f, -5.0f,    -1.0f, 0.0f, 5.0f,
		0.0f, 0.0f, -5.0f,    0.0f, 0.0f, 5.0f,
		1.0f, 0.0f, -5.0f,    1.0f, 0.0f, 5.0f,
		2.0f, 0.0f, -5.0f,    2.0f, 0.0f, 5.0f,
		3.0f, 0.0f, -5.0f,    3.0f, 0.0f, 5.0f,
		4.0f, 0.0f, -5.0f,    4.0f, 0.0f, 5.0f,
		5.0f, 0.0f, -5.0f,    5.0f, 0.0f, 5.0f,
		-5.0f, 0.0f, -5.0f,    5.0f, 0.0f, -5.0f,
		-5.0f, 0.0f, -4.0f,    5.0f, 0.0f, -4.0f,
		-5.0f, 0.0f, -3.0f,    5.0f, 0.0f, -3.0f,
		-5.0f, 0.0f, -2.0f,    5.0f, 0.0f, -2.0f,
		-5.0f, 0.0f, -1.0f,    5.0f, 0.0f, -1.0f,
		-5.0f, 0.0f, 0.0f,    5.0f, 0.0f, 0.0f,
		-5.0f, 0.0f, 1.0f,    5.0f, 0.0f, 1.0f,
		-5.0f, 0.0f, 2.0f,    5.0f, 0.0f, 2.0f,
		-5.0f, 0.0f, 3.0f,    5.0f, 0.0f, 3.0f,
		-5.0f, 0.0f, 4.0f,    5.0f, 0.0f, 4.0f,
		-5.0f, 0.0f, 5.0f,    5.0f, 0.0f, 5.0f,
	};
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positionCood), positionCood, GL_STATIC_DRAW);
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
	//
	//

	// Create and populate the buffer objects
	GLuint vboHandles[2];
	glGenBuffers(2, vboHandles);
	GLuint positionBufferHandle = vboHandles[0];
	GLuint colorBufferHandle = vboHandles[1];
	// Populate the position buffer
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positionData), positionData, GL_STATIC_DRAW);
	// Populate the color buffer
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);

	GLuint vboIndex;
	glGenBuffers(1, &vboIndex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndex);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

	GLuint vaoHandle;

	// Create and set-up the vertex array object
	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);
	// Enable the vertex attribute arrays
	glEnableVertexAttribArray(0); // Vertex position
	glEnableVertexAttribArray(1); // Vertex color
	// Map index 0 to the position buffer
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	// Map index 1 to the color buffer
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndex);

	v = glm::lookAt(vec3(0.0f, 0.0f, 5.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	p = glm::perspective(glm::radians(45.0f), (float)5.0f / 3.0f, 0.1f, 5.0f);


	v = glm::rotate(v, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));


	GLuint loc = glGetUniformLocation(program, "mvp");


	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);


	//
	glfwSwapInterval(1);


	glEnable(GL_DEPTH_TEST);

	//
	glClearColor(1.0, 1.0, 0.0, 0.0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// glClear(GL_COLOR_BUFFER_BIT);

		//
		// v = glm::rotate(v, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(p * v * m));

		glm::vec4 xx = p * glm::vec4(1, 1, 100, 0);
		//printf("==> %f %f %f %f\n", xx.x, xx.y, xx.z, xx.w);

		static int fcnt = 0;
		static auto tm = std::chrono::system_clock::now();
		fcnt++;
		auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - tm);
		if (diff.count() >= 1000) {
			std::cout << fcnt << std::endl;
			// glfwSetWindowTitle(window, (std::string("Hello World ") + std::to_string(fcnt * 1000.0 / diff.count())).c_str());
			tm = std::chrono::system_clock::now();
			fcnt = 0;
		}
		// std::cout << glfwGetTime() << std::endl;

		//
		glBindVertexArray(vaoHandle);
		// glDrawArrays(GL_TRIANGLES, 0, 3);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindVertexArray(vao);
		glDrawArrays(GL_LINES, 0, 44);


		glBindVertexArray(0);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}