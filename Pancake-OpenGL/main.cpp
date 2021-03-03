#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
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
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			Shader shader("Resources/Shaders/core.vs", "Resources/Shaders/core.frag");

            /*
            GLfloat vertices[] = {
                -0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 0.0f,
                0.5f * 500, -0.5f * 500, -0.5f * 500,  1.0f, 0.0f,
                0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
                0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
                -0.5f * 500,  0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
                -0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 0.0f,

                -0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f,
                0.5f * 500, -0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
                0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 1.0f,
                0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 1.0f,
                -0.5f * 500,  0.5f * 500,  0.5f * 500,  0.0f, 1.0f,
                -0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f,

                -0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
                -0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
                -0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
                -0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
                -0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f,
                -0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,

                0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
                0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
                0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
                0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
                0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f,
                0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,

                -0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
                0.5f * 500, -0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
                0.5f * 500, -0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
                0.5f * 500, -0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
                -0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f,
                -0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,

                -0.5f * 500,  0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
                0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
                0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
                0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
                -0.5f * 500,  0.5f * 500,  0.5f * 500,  0.0f, 0.0f,
                -0.5f * 500,  0.5f * 500, -0.5f * 500,  0.0f, 1.0f
            };
            */
            GLfloat vertices[] = {
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
                0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
                0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
            };

			GLuint VBO, VAO;
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*) 0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(2);
				glBindVertexArray(0);

			GLuint texture;
			int width = 0;
			int height = 0;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			SDL_Surface* image = IMG_Load("Resources/Images/pancakes.jpg");
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
			glGenerateMipmap(GL_TEXTURE_2D);
			SDL_FreeSurface(image);
			glBindTexture(GL_TEXTURE_2D, 0);

            glm::mat4 projection;
            projection = glm::perspective(45.0f, (GLfloat) (WIDTH / HEIGHT), 0.1f, 1000.0f);

			while (!glfwWindowShouldClose(window))
			{
				glfwPollEvents();

				glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture);
                glUniform1i(glGetUniformLocation(shader.Program, "ourTexture"), 0);

				shader.Use();

                glm::mat4 model(1);
                glm::mat4 view(1);
                model = glm::rotate(model, (GLfloat)glfwGetTime() * 1.0f, glm::vec3(0.5f, 0.1f, 0.0f));
                view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

                GLint modelLocation = glGetUniformLocation(shader.Program, "model");
                GLint viewLocation = glGetUniformLocation(shader.Program, "view");
                GLint projectionLocation = glGetUniformLocation(shader.Program, "projection");

                glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
                glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
                glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

                glBindVertexArray(VAO);
                glDrawArrays(GL_TRIANGLES, 0, 36);
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