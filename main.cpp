#include <iostream>
#include <math.h>
#include "./glad/include/glad.h"
#include <GLFW/glfw3.h>
#include <filesystem>

#include "./HeaderFiles/shaderClass.h"
#include "./HeaderFiles/VAO.h"
#include "./HeaderFiles/VBO.h"
#include "./HeaderFiles/EBO.h"

int main() {

	//initializes GLFW
	glfwInit();

	//tell GLFW what OpenGL version is being used
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//tell GLFW that only the CORE profile will be used
	//meaning only modern functions will be enabled
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//vertices coordinates
	GLfloat vertices[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, //upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, //inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, //inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f //inner bottom
	};

	GLuint indices[] = {
		0, 3, 5, //lower left triangle
		3, 2, 4, //lower right triangle
		5, 4, 1 //upper triangle
		
	};
	
	//make GLFW window with dimensions of 800 by 800
	GLFWwindow* window = glfwCreateWindow(800, 800, "testOpenGL", NULL, NULL);
	//check if window is made
	if (window == NULL) {
		std::cout << "failed to create window" << std::endl;
		//terminates GLFW
		glfwTerminate();
		return 0;
	}
	//sets current context to newly created window
	glfwMakeContextCurrent(window);

	//loads glad
	gladLoadGL();

	//sets window viewport
	glViewport(0, 0, 800, 800);

	Shader shaderProgram("../ResourceFiles/shaders/default.vert", "../ResourceFiles/shaders/default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkVBO(VBO1, 0);
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	
	//make color struct and make background color
	struct rgba {
		float r = 0.0f, g = 0.0f, b = 0.0f, a = 1.0f;
	} background{0.05f, 0.05f, 0.06f};

	//set background color
	glClearColor(background.r, background.g, background.b, background.a);
	//assigns back buffer color
	glClear(GL_COLOR_BUFFER_BIT);

	//swaps back and front buffer
	glfwSwapBuffers(window);

	//game loop
	while (!glfwWindowShouldClose(window)) {
		glClearColor(background.r, background.g, background.b, background.a);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();
		VAO1.Bind();
		//draw the triangle using GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		//swaps front/back buffer
		glfwSwapBuffers(window);
		//take care of all GLFW events
		glfwPollEvents();
	}
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	//delets window before ending program
	glfwDestroyWindow(window);
	//terminates GLFW
	glfwTerminate();
	return 0;
}