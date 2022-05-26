#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos; \n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0"; 

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0"; 

int main() {
	glfwInit(); 

	//Specifying the version of OpenGL to GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	//Specifying the core profile. The core profile contains only modern functions
	//but not outdated functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

	GLfloat vertices[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
	};

	//Creating a window of 800 width and 800 height and naming it "OpenGL Tutorial"
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL Tutorial", NULL, NULL); 
	if (window == NULL) {
		std::cout << "Failed to create a window" << std::endl; 
		glfwTerminate(); 
		return -1; 
	}

	//Telling OpenGL which window to use
	glfwMakeContextCurrent(window); 

	//Loading glad to configure OpenGL
	gladLoadGL(); 
	//Specifying the viewport of the window 
	glViewport(0, 0, 800, 800); 
	
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); 
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); 
	glCompileShader(vertexShader); 

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); 
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); 
	glCompileShader(fragmentShader); 

	GLuint shaderProgram = glCreateProgram(); 
	
	glAttachShader(shaderProgram, vertexShader); 
	glAttachShader(shaderProgram, fragmentShader); 
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader); 
	glDeleteShader(fragmentShader); 
	

	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO); 
	glGenBuffers(1, &VBO); 

	glBindBuffer(GL_ARRAY_BUFFER, VBO); 

	glBindBuffer(GL_ARRAY_BUFFER, VBO); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); 
	glEnableVertexAttribArray(0); 

	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0); 

	//Specifying the background color of the window 
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f); 
	//Clean the back buffer and assign a new color to it 
	glClear(GL_COLOR_BUFFER_BIT); 
	//Swap the back buffer to the front buffer
	glfwSwapBuffers(window); 

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram); 
		glBindVertexArray(VAO); 
		glDrawArrays(GL_TRIANGLES, 0, 3); 
		glfwSwapBuffers(window);

		glfwPollEvents(); 
	}


	glDeleteVertexArrays(1, &VAO); 
	glDeleteBuffers(1, &VBO); 
	glDeleteProgram(shaderProgram); 

	glfwDestroyWindow(window); 
	glfwTerminate(); 
	return 0; 
}