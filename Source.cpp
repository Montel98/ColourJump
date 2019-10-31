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

int main(int argc, char *args[]) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SDL_Window* window = SDL_CreateWindow("Colour Jump", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1500, 1500, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(window);
	SDL_Event windowEvent;
	
	SDL_SetRelativeMouseMode(SDL_TRUE);
	WorldTime wt;
	Camera camera(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	levelMap m(16, wt);
	Player player(0.0f, 0.0f, 2.0f);
	player.initMotionSpeeds(2.0f, 3.5f);
	InputController ic(player, camera);
	Controller c(m, player, ic, wt);

	while (true) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		c.updateStates(camera);
		c.drawScene(camera);
		SDL_GL_SwapWindow(window);
	}
	SDL_GL_DeleteContext(context);

	SDL_Quit();
	return 0;
}