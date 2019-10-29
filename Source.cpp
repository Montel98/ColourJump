#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cmath>
#include "game.h"

#undef main

// Shader sources
// VERTEX SHADER
const GLchar* vertexSource = R"glsl(
    #version 150 core
    in vec3 position;
    uniform mat4 view;
    uniform mat4 proj;
	uniform mat4 model;

    void main()
    {	
        gl_Position = proj * view * model * vec4(position, 1.0);
    }
)glsl";

// FRAGMENT SHADER
const GLchar* fragmentSource = R"glsl(
    #version 150 core
	uniform vec3 blockColour;
	out vec4 outColour;
    void main()
    {
		float ambientMag = 1.0;
		vec3 resultLight = ambientMag * blockColour;
        outColour = vec4(resultLight, 1.0);
    }
)glsl";

int main(int argc, char *args[]) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SDL_Window* window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1500, 1500, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(window);
	SDL_Event windowEvent;

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	// Create Vertex Array Object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create Vertex Buffer Objects and copy the vertex data to it
	GLuint vbo;
	glGenBuffers(1, &vbo);

	GLfloat vertices[] = {
		0.0f, 0.0f, 0.0f, //0 CUBE
		0.5f, 0.0f, 0.0f, //1
		0.5f, 0.0f, 0.5f, //2
		0.0f, 0.0f, 0.5f, //3
		0.0f, 0.5f, 0.0f, //4
		0.5f, 0.5f, 0.0f, //5
		0.5f, 0.5f, 0.5f, //6
		0.0f, 0.5f, 0.5f  //7
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	// Create elements array
	GLuint ebo;
	glGenBuffers(1, &ebo);

	GLuint elements[] = {
		0, 1, 2, 2, 3, 0,
		0, 1, 5, 5, 4, 0,
		1, 2, 6, 6, 5, 1,
		3, 2, 6, 6, 7, 3,
		0, 3, 7, 7, 4, 0,
		4, 5, 6, 6, 7, 4,
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	// Create and compile the vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	// Create and compile the fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	// Link the vertex and fragment shader into a shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColour");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	// Specify the layout of the vertex data
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

	// get reference of view matrix for upload
	GLint uniView = glGetUniformLocation(shaderProgram, "view");

	// set projection matrix and get reference for upload
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1500.0f / 1500.0f, 1.0f, 100.0f);
	GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

	// set model matrix and get reference for upload
	glm::mat4 model = glm::mat4(1.0f);
	GLint uniModel = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	GLint uniColour = glGetUniformLocation(shaderProgram, "blockColour");

	WorldTime wt;
	Camera camera(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	Renderer r(uniModel, uniColour, uniView, model);
	levelMap m(16, wt);
	Player player(0.0f, 0.0f, 2.0f);
	player.initMotionSpeeds(2.0f, 3.5f);
	InputController ic(player, camera);
	Controller c(m, r, player, ic, wt);
	glm::vec3 direction;

	while (true) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		c.updateStates(camera);
		SDL_GL_SwapWindow(window);
	}
	SDL_GL_DeleteContext(context);

	SDL_Quit();
	return 0;
}