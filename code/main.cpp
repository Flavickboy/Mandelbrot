// Include important C++ libraries here

#include "ComplexPlane.h"

int main()
{

		//Calculate Aspect Ratio
	double screenwidth = VideoMode::getDesktopMode().width;
	double screenheight = VideoMode::getDesktopMode().height;
	double aspectRatio = screenwidth/screenheight;

	// Create a video mode object
	VideoMode vm(screenwidth, screenwidth);


	// Create and open a window for the game
	RenderWindow window(vm, "Mandelbrot", Style::Default);

	//Declare Font and Text objects, Set font of messageText
	Text messageText;
    Font font;

    font.loadFromFile("fonts/calibri.ttf");
    messageText.setFont(font);

	




	while (window.isOpen())
	{

		/*
		****************************************
		Handle the players input
		****************************************
		*/

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		/*
		****************************************
		Update the scene
		****************************************
		*/





		/*
		****************************************
		Draw the scene
		****************************************
		*/





		// Clear everything from the last frame
		window.clear();

		// Draw our game scene here


		// Show everything we just drew
		window.draw(messageText);
		window.display();


	}

	return 0;
}
