//glfw setting replay
#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"
const int width = 800;
const int height = 600;
float* pixels = new float[width*height * 3];

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	if (i0 == i1) {
		for (int j = j0; j < j1; j++)
			drawPixel(i0, j, red, green, blue);
		return;
	}
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);
	}
}
void drawCircle(const int& i0, const int& j0, const float& red, const float& green, const float& blue, GLFWwindow *window) {
	int r = 50;
	double xpos, ypos;

	for (int i = i0 - r; i < i0 + r; i++) {
		for (int j = j0 - r; j < j0 + r; j++) {
			int n = (i - i0)*(i - i0) + (j - j0)*(j - j0) - r*r;
			int n2 = (i - i0)*(i - i0) + (j - j0)*(j - j0) - (r - 1)*(r - 1) + 2 * r - 1;
			glfwGetCursorPos(window, &xpos, &ypos);
			ypos = height - ypos - 1;
			int n3 = (xpos - i0)*(xpos - i0) + (ypos - j0)*(ypos - j0) - r*r;
			if (n < 0 && n2>0) {
				drawPixel(i, j, 1.0f, 0.0f, 0.0f);
				if (n3 < 0)
					drawPixel(i, j, 0.0, 0.0f, 1.0f);

			}
		}
	}
}
// draw circle into the previous circle
void drawCircle_2(const int& i0, const int& j0, const float& red, const float& green, const float& blue) {
	int r = 20;

	for (int i = i0 - r; i < i0 + r; i++) {
		for (int j = j0 - r; j < j0 + r; j++) {
			int n = (i - i0)*(i - i0) + (j - j0)*(j - j0) - r*r;
			int n2 = (i - i0)*(i - i0) + (j - j0)*(j - j0) - (r - 3)*(r - 3) + 6*r - 9;
			if (n < 0 && n2>0) {
				drawPixel(i, j, 1.0f, 0.0f, 0.0f);
			}
		}
	}
}

void drawOnPixelBuffer(GLFWwindow *window)
	{

	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background

													/*	for (int i = 0; i<width*height; i++) {
													pixels[i * 3 + 0] = 1.0f; // red
													pixels[i * 3 + 1] = 1.0f; // green
													pixels[i * 3 + 2] = 1.0f; // blue
													}*/

	const int i = rand() % width, j = rand() % height;
	drawPixel(i, j, 0.0f, 0.0f, 0.0f);

	// drawing a line
	//TODO: anti-aliasing

	/*	drawing ten circle */
	drawCircle(100, 150, 0.0f, 0.0f, 0.0f, window);
	drawCircle(250, 150, 0.0f, 0.0f, 0.0f, window);
	drawCircle(400, 150, 0.0f, 0.0f, 0.0f, window);
	drawCircle(550, 150, 0.0f, 0.0f, 0.0f, window);
	drawCircle(700, 150, 0.0f, 0.0f, 0.0f, window);

	drawCircle(100, 400, 0.0f, 0.0f, 0.0f, window);
	drawCircle(250, 400, 0.0f, 0.0f, 0.0f, window);
	drawCircle(400, 400, 0.0f, 0.0f, 0.0f, window);
	drawCircle(550, 400, 0.0f, 0.0f, 0.0f, window);
	drawCircle(700, 400, 0.0f, 0.0f, 0.0f, window);
	// ' / ' 
	drawLine(70, 375, 130, 425, 1.0f, 0.0f, 0.0f);
	drawLine(70, 376, 129, 425, 1.0f, 0.0f, 0.0f);
	drawLine(71, 375, 130, 424, 1.0f, 0.0f, 0.0f);

	// ' -> '
	drawLine(70, 150, 130, 150, 1.0f, 0.0f, 0.0f);
	drawLine(105, 175, 130, 150, 1.0f, 0.0f, 0.0f);
	drawLine(105, 176, 130, 151, 1.0f, 0.0f, 0.0f);
	drawLine(105, 125, 130, 150, 1.0f, 0.0f, 0.0f);
	drawLine(105, 124, 130, 150, 1.0f, 0.0f, 0.0f);

	// ' o '
	drawCircle_2(250, 400, 0.0f, 0.0f, 0.0f);

	// ' ¤± '
	drawLine(420, 380, 420, 420, 1.0f, 0.0f, 0.0f);
	drawLine(380, 420, 420, 420, 1.0f, 0.0f, 0.0f);
	drawLine(380, 380, 420, 380, 1.0f, 0.0f, 0.0f);
	drawLine(380, 380, 380, 420, 1.0f, 0.0f, 0.0f);

	// ' A '
	drawLine(225, 130, 250, 180, 1.0f, 0.0f, 0.0f);
	drawLine(225, 131, 250, 181, 1.0f, 0.0f, 0.0f);
	drawLine(250, 181, 275, 131, 1.0f, 0.0f, 0.0f);
	drawLine(250, 180, 275, 130, 1.0f, 0.0f, 0.0f);
	drawLine(235, 150, 265, 150, 1.0f, 0.0f, 0.0f);
	drawLine(235, 151, 265, 151, 1.0f, 0.0f, 0.0f);

	// ' l '
	drawLine(400, 120, 400, 180, 1.0f, 0.0f, 0.0f);
	
	// ' X '
	drawLine(530, 380, 570, 420, 1.0f, 0.0f, 0.0f);
	drawLine(530, 381, 570, 421, 1.0f, 0.0f, 0.0f);
	drawLine(530, 420, 570, 380, 1.0f, 0.0f, 0.0f);
	drawLine(530, 421, 570, 381, 1.0f, 0.0f, 0.0f);

	// ' <- '
	drawLine(520, 150, 580, 150, 1.0f, 0.0f, 0.0f);
	drawLine(520, 151, 545, 176, 1.0f, 0.0f, 0.0f);
	drawLine(520, 150, 545, 175, 1.0f, 0.0f, 0.0f);
	drawLine(520, 150, 545, 125, 1.0f, 0.0f, 0.0f);
	drawLine(520, 149, 545, 124, 1.0f, 0.0f, 0.0f);

	// ' ¡è '
	drawLine(700, 120, 700, 180, 1.0f, 0.0f, 0.0f);
	drawLine(680, 160, 700, 180, 1.0f, 0.0f, 0.0f);
	drawLine(700, 180, 720, 160, 1.0f, 0.0f, 0.0f);


	// ' ¡é '
	drawLine(700, 370, 700, 430, 1.0f, 0.0f, 0.0f);
	drawLine(680, 390, 700, 370, 1.0f, 0.0f, 0.0f);
	drawLine(700, 370, 720, 390, 1.0f, 0.0f, 0.0f);



	//TODO: try moving object

}

int main(void)
{
	GLFWwindow* window;

	
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Get Position of cursor", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

							  /* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);

		drawOnPixelBuffer(window);

		//TODO: RGB struct
		//Make a pixel drawing function
		//Make a line drawing function

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();


		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 




	return 0;
}
