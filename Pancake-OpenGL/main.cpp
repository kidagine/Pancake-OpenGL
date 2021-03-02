#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h" 

const GLint WIDTH = 800;
const GLint HEIGHT = 600;


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Pancake-OpenGL", NULL, NULL);
	if (window != NULL)
	{
		glfwMakeContextCurrent(window);
		glewExperimental = GL_TRUE;

		if (GLEW_OK == glewInit())
		{
			glViewport(0, 0, WIDTH, HEIGHT);
			Shader shader("Resources/Shaders/core.vs", "Resources/Shaders/core.frag");
			GLfloat vertices[] =
			{
				-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
				0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
				0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f
			};
			GLuint VBO, VAO;
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) 0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);

			glBindVertexArray(0);
			while (!glfwWindowShouldClose(window))
			{
				glfwPollEvents();

				glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT);

				shader.Use();
				glBindVertexArray(VAO);
				glDrawArrays(GL_TRIANGLES, 0, 3);
				glBindVertexArray(0);

				glfwSwapBuffers(window);
			}

			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
			glfwTerminate();
		}
	}

	return EXIT_SUCCESS;
}