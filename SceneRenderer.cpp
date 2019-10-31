#include "SceneRenderer.h"
#include <iostream>

// Shader sources
// VERTEX SHADER
const GLchar* vertexShaderSource = R"glsl(
    #version 150 core
    in vec3 position;
	in vec3 normal;
	out vec3 oNormal;
	out vec3 tPos;
    uniform mat4 view;
    uniform mat4 proj;
	uniform mat4 model;

    void main()
    {	
        gl_Position = proj * view * model * vec4(position, 1.0);
		oNormal = normal;
		tPos = vec3(model * vec4(position, 1.0));
    }
)glsl";

// FRAGMENT SHADER
const GLchar* fragmentShaderSource = R"glsl(
    #version 150 core
	uniform vec3 blockColour;
	uniform vec3 lightPos;
	uniform vec3 lightColour;
	in vec3 oNormal;
	in vec3 tPos;
	out vec4 outColour;

    void main()
    {	
		float intensity = 5.0 / (5.0 + pow(length(lightPos - tPos), 1.0)); // spotlight
		float ambientMag = 0.1;
		vec3 dir = normalize(lightPos - tPos);
		vec3 resultLight =  blockColour * lightColour * (ambientMag + (intensity * max(dot(oNormal, dir), 0.0)));
        outColour = vec4(resultLight, 1.0);
    }
)glsl";

SceneRenderer::SceneRenderer() {
	// Initialize GLEW
	glewExperimental = GL_TRUE;

	if (glewInit()) {
		std::cout << "Error: GLEW could not be initialised." << std::endl;
	}

	// Vertex Array Object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create and compile the vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Create and compile the fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Link the vertex and fragment shader into a shader program
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColour");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	// get reference of view matrix for upload
	uniView = glGetUniformLocation(shaderProgram, "view");

	// set projection matrix and get reference for upload
	proj = glm::perspective(glm::radians(45.0f), 1500.0f / 1500.0f, 1.0f, 100.0f);
	uniProj = glGetUniformLocation(shaderProgram, "proj");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

	// set model matrix and get reference for upload
	model = glm::mat4(1.0f);
	uniModel = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

	lightPos = glm::vec3(4.0f, 4.0f, 1.0f);
	uniLightPos = glGetUniformLocation(shaderProgram, "lightPos");
	glUniform3fv(uniLightPos, 1, glm::value_ptr(lightPos));

	//glm::vec3 sunSetColour = glm::vec3(0.8f, 0.5f, 0.2f);
	lightColour = glm::vec3(1.0f, 1.0f, 1.0f);
	uniLightColour = glGetUniformLocation(shaderProgram, "lightColour");
	glUniform3fv(uniLightColour, 1, glm::value_ptr(lightColour));

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}