#pragma once

#ifndef RENDER_H
#define RENDER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

class Renderer {
public:
	glm::mat4 &model;
	GLuint uniModel;
	GLuint uniColor;
	GLuint uniView;
public:
	Renderer(GLuint uniModel, GLuint uniColor, GLuint uniView, glm::mat4 &model) : model(model), uniColor(uniColor), uniView(uniView), uniModel(uniModel) {
	}
	void render(const glm::vec3 &position, const glm::vec3 &color, const Camera &camera) {
		glm::mat4 translate = glm::translate(glm::mat4(1.0f), position);
		model = model * translate;
		glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model)); //send matrix to the vertex shader

		glm::mat4 view = glm::lookAt(
			camera.pos,
			camera.looking,
			camera.up);

		glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

		glUniform3f(uniColor, color.r, color.g, color.b);
		//glDrawElements(GL_TRIANGLES, 42, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::mat4(1.0f); // reset to identity matrix for next object
		glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
	}
};

#endif // !RENDER_H
