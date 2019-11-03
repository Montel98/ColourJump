#include "CubeRenderer.h"

CubeRenderer::CubeRenderer(SceneRenderer &scene) : sceneRenderer(scene) {

	GLfloat cubeVertices[] = {
	// x, y, x, norm_x, norm_y, norm_z
	0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
	0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
	0.5f, 0.0f, 0.5f, 0.0f, -1.0f, 0.0f,
	0.5f, 0.0f, 0.5f, 0.0f, -1.0f, 0.0f,
	0.0f, 0.0f, 0.5f, 0.0f, -1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,

	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
	0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
	0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f,
	0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f,
	0.0f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,

	0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.5f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

	0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f,
	0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f,

	0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.5f, -1.0f, 0.0f, 0.0f,
	0.0f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
	0.0f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
	0.0f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

	0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f
	};

	// Create Vertex Buffer Objects and copy the vertex data to it
	GLuint vbo;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	// Specify the layout of the vertex data
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	GLint posAttrib = glGetAttribLocation(sceneRenderer.shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);

	// Specify the layout of the normal data
	GLint normAttrib = glGetAttribLocation(sceneRenderer.shaderProgram, "normal");
	glEnableVertexAttribArray(normAttrib);
	glVertexAttribPointer(normAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	uniColour = glGetUniformLocation(sceneRenderer.shaderProgram, "blockColour");
}

void CubeRenderer::render(const glm::vec3 &position, const glm::vec3 &color, const Camera &camera) {
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), position);
	sceneRenderer.model = sceneRenderer.model * translate;
	glUniformMatrix4fv(sceneRenderer.uniModel, 1, GL_FALSE, glm::value_ptr(sceneRenderer.model)); // Send matrix to the vertex shader

	// Update camera positon
	glm::mat4 view = glm::lookAt(
		camera.pos,
		camera.looking,
		camera.up);

	glUniformMatrix4fv(sceneRenderer.uniView, 1, GL_FALSE, glm::value_ptr(view));

	glUniform3fv(sceneRenderer.viewingPos, 1, glm::value_ptr(camera.pos));

	glUniform3f(uniColour, color.r, color.g, color.b); // Set block colour
	glDrawArrays(GL_TRIANGLES, 0, 36);
	sceneRenderer.model = glm::mat4(1.0f); // Reset to identity matrix for next object
	glUniformMatrix4fv(sceneRenderer.uniModel, 1, GL_FALSE, glm::value_ptr(sceneRenderer.model));
}