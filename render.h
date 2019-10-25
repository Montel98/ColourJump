#pragma once

#ifndef RENDER_H
#define RENDER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
/*
class Camera {
public:
	glm::vec3 pos;
	glm::vec3 looking;
	glm::vec3 up;
	glm::vec3 direction;
	float sensitivity;

public:
	Camera(glm::vec3, glm::vec3, glm::vec3);
	void rotateH(float); // rotate horizontal relative to camera orientation
	void rotateV(float); // rotate vertical relative to camera orientation
	void setPosition(glm::vec3);
	void setDirection(glm::vec3);
};

Camera::Camera(glm::vec3 position, glm::vec3 facing, glm::vec3 upwards) : pos(position), looking(facing), up(upwards) {
	direction = looking - pos;
}

void Camera::rotateH(float angle) {
	glm::mat4 rot = glm::rotate(glm::mat4(1.0f), (-1 * angle * 0.005f), up);
	glm::vec4 bla1(direction, 1);
	bla1 = rot * bla1;

	direction.x = bla1.x;
	direction.y = bla1.y;
	direction.z = bla1.z;

	looking = pos + direction;
}

void Camera::rotateV(float angle) {
	glm::mat4 rot = glm::rotate(glm::mat4(1.0f), (-1 * angle * 0.005f), glm::cross(direction, up));
	glm::vec4 bla(direction, 1);
	bla = rot * bla;

	direction.x = bla.x;
	direction.y = bla.y;
	direction.z = bla.z;

	looking = pos + direction;
}

void Camera::setPosition(glm::vec3 newPos) {
	pos = newPos + glm::vec3(0.25f, 0.25f, 1.25f);
	looking = pos + direction;
}

void Camera::setDirection(glm::vec3 newDirection) {
	direction = newDirection;
	looking = pos + direction;
}
*/
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
		glDrawElements(GL_TRIANGLES, 42, GL_UNSIGNED_INT, 0);
		model = glm::mat4(1.0f); // reset to identity matrix for next object
		glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
	}
};

#endif // !RENDER_H
