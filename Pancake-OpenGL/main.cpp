#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

const GLint WIDTH = 800;
const GLint HEIGHT = 600;
const GLchar *vertexShaderSource = "#version 330 core\n"
"layout ( location = 0 ) in vec3 position;\n" 
"void main ( )\n"
"{\n"
"gl_Position = vec4( position.x, position.y, position.z, 1.0 );\n"
"}";

const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";


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
			GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
			glCompileShader(vertexShader);
			GLint success;
			GLchar infoLog[512];
			GLuint VBO, VAO;
			GLuint shaderProgram;
			glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
			if (success)
			{
				glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
				GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
				glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
				glCompileShader(fragmentShader);
				glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
				if (success)
				{
					shaderProgram = glCreateProgram();
					glAttachShader(shaderProgram, vertexShader);
					glAttachShader(shaderProgram, fragmentShader);
					glLinkProgram(shaderProgram);
					glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
					if (success)
					{
						glDeleteShader(vertexShader);
						glDeleteShader(fragmentShader);
						GLfloat vertices[] =
						{
							-0.5f, -0.5f, 0.0f,
							0.5f, -0.5f, 0.0f,
							0.0f, 0.5f, 0.0f
						};
						glGenVertexArrays(1, &VAO);
						glGenBuffers(1, &VBO);
						glBindVertexArray(VAO);
						glBindBuffer(GL_ARRAY_BUFFER, VBO);
						glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
						glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
						glEnableVertexAttribArray(0);
						glBindBuffer(GL_ARRAY_BUFFER, 0);
						glBindVertexArray(0);
						while (!glfwWindowShouldClose(window))
						{
							glfwPollEvents();

							glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
							glClear(GL_COLOR_BUFFER_BIT);

							glUseProgram(shaderProgram);
							glBindVertexArray(VAO);
							glDrawArrays(GL_TRIANGLES, 0, 3);
							glBindVertexArray(0);

							glfwSwapBuffers(window);
						}
					}
					else
					{
						printf("Shader program error");
					}
				}
				else
				{
					printf("Shader fragment error");
				}
			}
			else
			{
				printf("Shader vertex  error");
			}
				glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
			glfwTerminate();
		}
	}

	return EXIT_SUCCESS;
}