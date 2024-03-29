#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <algorithm> /* min(,) */
#include "Game.h"
#include "ressourceManager.hpp"

#define Max_FPS 60




void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseScroll_callback(GLFWwindow* window, double a, double b);

const unsigned int SCREEN_WIDTH = 1600;
const unsigned int SCREEN_HEIGHT = 1024;

Game Theater(SCREEN_WIDTH, SCREEN_HEIGHT);
static GLFWwindow * win;

void QUIT_THE_APPLICATION() {
	printf("\nBYE BYE");
	glfwSetWindowShouldClose(win, true);
	
}
int main(void)
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	glfwWindowHint(GLFW_RESIZABLE, true);
	//glfwWindowHint(GLFW_SAMPLES, 4);


	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Theater", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	win = window;

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		system("pause");
		return -1;
	}
	//Callback for Frambuffer, Keys
	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetScrollCallback(window, MouseScroll_callback);

	//OpenGL config
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_BLEND);
	//glEnable(GL_MULTISAMPLE); //AA
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSwapInterval(1);//Vsync
	Theater.State = Game::GameState::GAME_MENU;
	Theater.Quit = *QUIT_THE_APPLICATION;

	Theater.Init();
 
	double deltaTime = 0.0f;
	double lastFrame = 0.0f;

	while (!glfwWindowShouldClose(window))
	{

		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		double totalDelta =  deltaTime / (1000/ Max_FPS);
		
		
		glfwPollEvents();
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);


		Theater.Cursor.rawX = xpos; Theater.Cursor.rawY = ypos;
		Theater.Cursor.buttons[0] = glfwGetMouseButton(window, 0);
		Theater.Cursor.buttons[1] = glfwGetMouseButton(window, 1);
		Theater.ProcessInput(deltaTime);
	
		int i = 0;
		while (totalDelta > 0.0f && i < 6)
		{
			double delta = std::min(totalDelta, 1.0);
			Theater.Update(delta);
			totalDelta -= delta;
			++i;
		}
	


		Theater.Render(deltaTime);


		glfwSwapBuffers(window);
	}
	ResourceManager::Clear();
	glfwTerminate();

	return 69;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			Theater.Keys[key] = true;
		else if (action == GLFW_RELEASE)
			Theater.Keys[key] = false;
	}

}

void MouseScroll_callback(GLFWwindow* window, double x, double y)
{
	Theater.Cursor.Scroll = y;
 
}
void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{

	glViewport(0, 0, width, height);
}

/*

###### BOOST
The following directory should be added to compiler include paths:

    C:\boost_1_84_0

The following directory should be added to linker library paths:

    C:\boost_1_84_0\stage\lib
	
	*/