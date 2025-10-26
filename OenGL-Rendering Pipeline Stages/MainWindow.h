#pragma once

#include<stdio.h>
#include<GL\glew.h>
#include<GLFW\glfw3.h>

class MainWindow
{
public:
	MainWindow();

	MainWindow(GLint windowWidth, GLint windowHeight);

	int Initialize();

	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }

	bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

	bool* getKeys() { return keys; }

	GLfloat GetXChange();
	GLfloat GetYChange();

	void swapBuffers() { glfwSwapBuffers(mainWindow); }

	~MainWindow();

private:
	GLFWwindow* mainWindow;

	//For Window
	GLint width, height;
	GLint bufferWidth, bufferHeight;

	// Keyboard
	bool keys[1024]; // have initialized the size of the array as per the Ascii values of every keys in our keyboards

	//Mouse
	GLfloat lastX; // We are checking the mouse last coordinates in both x and y axis and compare them to the current coordinates
	GLfloat lastY;
	GLfloat XChange; // after comparing the last and current coordinates then we calculate how much is changed since the last movement 
	GLfloat YChange;
	bool MouseFirstMove; // This is to take into account the initial movement of the mouse that is wherever in the screen coordinates    

	void createCallbacks();

	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double XPos, double YPos);
};

