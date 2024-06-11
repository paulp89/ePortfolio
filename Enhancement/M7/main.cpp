
#include <iostream>
#include "application.h"
#include <GLFW/glfw3.h>


int main(int argc, char** argv) {
	/*
		Controls.
		Use WASD keys to move.
		Q & E to move up and down.
		Use mouse to look around.
		Left click to change background color.
		Right click to change camera mode (Orthographic/Perspective).
		Middle click to toggle animations.
		Scroll to zoom in and out.
		ESC to quit.
	*/
	Application app = Application{"Paul Pathana | Scene", 800, 600 };
	app.Run();
	
	return 0;
}