#include "MainWindow.h"

MainWindow::MainWindow()
{
	width = 800;
	height = 600;

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;

		XChange = 0;
		YChange = 0;
	}
}

MainWindow::MainWindow(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;

		XChange = 0;
		YChange = 0;
	}
}

int MainWindow::Initialize()
{
	// We know that in C++ the program execution starts from the main() function likewise GLFW initialization starts with this function().
	// Initialize GLFW
	if (!glfwInit())
	{
		printf("GLFW initialization failed");
		glfwTerminate();
		return 1;
	}

	// Set Windows Properties
	// Set the version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

	// Set no for backward compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Set ok for Forward Compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Creating a Window
	 mainWindow = glfwCreateWindow(width, height, "Main Window", NULL, NULL);


	if (!mainWindow)
	{
		printf("GLFW window creation failed");
		glfwTerminate();
		return 1;
	}

	//get the information of the buffer size
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//Set Context for Glew to Use
	glfwMakeContextCurrent(mainWindow);

	//Handle Keys and Mouse inputs 
	createCallbacks();
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	//-------------------------------------------------------------------------------

	// Allow modern extensions features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("GLEW Initialization failed");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
	}

	//Depth test
	glEnable(GL_DEPTH_TEST);

	// Setting up the viewport 
	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(mainWindow, this);
}

void MainWindow::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, handleKeys);
	glfwSetCursorPosCallback(mainWindow, handleMouse);
}

GLfloat MainWindow::GetXChange()
{
	GLfloat theChange = XChange;
	XChange = 0.0f;
	return theChange;
}

GLfloat MainWindow::GetYChange()
{
	GLfloat theChange = YChange;
	YChange = 0.0f;
	return theChange;
}

void MainWindow :: handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	MainWindow* theWindow = static_cast<MainWindow*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//printf("Pressed: %d\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//printf("Released: %d\n", key);
		}
	}
}

void MainWindow::handleMouse(GLFWwindow* window, double XPos, double YPos)
{
	MainWindow* theWindow = static_cast<MainWindow*>(glfwGetWindowUserPointer(window));

	if (theWindow->MouseFirstMove) // checking the mouses very first movement
	{
		theWindow->lastX = XPos; // we are initializing the last position to the current position the same goes for the Y-axis too. 
		theWindow->lastY = YPos;
		theWindow->MouseFirstMove = false; // as it will no longer be the first movement we make it as false 
	}

	theWindow->XChange = XPos - theWindow->lastX; //its like reset
	theWindow->YChange = theWindow->lastY - YPos; // this calculation can be done the same way as done for the x-axis, as we are we trying to avoid the inverted up and down movement
	 
	theWindow->lastX = XPos;
	theWindow->lastY = YPos;

	//printf("x:%.6f, y:%.6f\n", theWindow->XChange, theWindow->YChange);

}

MainWindow::~MainWindow()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}