#include <iostream>
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;
class displayclass
{
public:

	void displaywindow()
	{
		RenderWindow window1(VideoMode(800, 600), "My window");
		window1.setMouseCursorVisible(false);
		window1.setFramerateLimit(60);

		Music music;
		if (!music.openFromFile("assets/Ringing Ambient Background - Sound Effect.wav"))
		{
			cout << "error loading file";// error
		}
		music.play();
		/*SoundBuffer buffer;
		if (!buffer.loadFromFile("Ringing Ambient Background - Sound Effect.wav"))
		{
			cout << "cannot load music";
		}

		Sound sound;
		sound.setBuffer(buffer);
		sound.play();*/

		Font font;
		if (!font.loadFromFile("assets/Halo3.ttf"))
		{
			cout << "cannot load ";
		}
		Text text;
		text.setFont(font);
		text.setString("SPACESHIPS");
		text.setCharacterSize(56);
		text.setFillColor(Color::Red);
		text.setPosition(160, 200);
		Font font1;
		if (!font1.loadFromFile("assets/neo-latina-demo-FFP.ttf"))
		{
			cout << "cannot load ";
		}
		Text text1;
		text1.setFont(font1);
		text1.setString("PRESS ANY KEY TO CONTINUE...");
		text1.setCharacterSize(26);
		text1.setFillColor(Color::White);
		text1.setPosition(200, 350);
		int i = 0;
		while (window1.isOpen())
		{
			window1.clear();
			if (i > 11)
			{
				window1.draw(text1);
				window1.draw(text);
				window1.display();
				sleep(seconds(1));
				i = 0;
			}
			i++;
			window1.draw(text);
			window1.display();
			if (Mouse::isButtonPressed(Mouse::Left) || Mouse::isButtonPressed(Mouse::Right))
			{
				cout << "HELLO";
				music.stop();
				break;

			}
		}
	}
};
