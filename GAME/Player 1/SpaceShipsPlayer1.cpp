#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include <iostream>
#include<SFML/System.hpp>
#include<vector>
#include<cstdlib>
#include"recvdata.h"
#include"senddata.h"
#include"displaytitle.cpp"
using namespace std;
using namespace sf;

void main()
{

	recvdata rd;
	senddata sd;
	//displayclass ds;
	//ds.displaywindow();
	rd.wsastartup();
	rd.bindsocket();
	sd.startwsa();
	sd.connect();


	float enemypositionx;
	float enemypositiony;
	float mypositionx;
	float mypositiony;
	int enemybulletcounter;
	int bulletcontrol = 0;
	string data;
	string storedata;

	RenderWindow window(VideoMode(800, 600), "Game window", Style::Fullscreen);
	window.setFramerateLimit(60);

	Texture rocket;
	Vector2f targetSize(0.3f, 0.3f);
	if (!rocket.loadFromFile("assets/spaceshipimg.png"))
	{
		cout << "image failed";
	}

	Sprite player;
	player.setTexture(rocket);
	player.setScale(targetSize.x, targetSize.y);


	CircleShape playerbullet;
	playerbullet.setFillColor(Color::Blue);
	playerbullet.setRadius(5.f);
	vector<CircleShape> playerbulletes;
	vector<CircleShape> proxybullets;

	Sprite enemy;
	enemy.setTexture(rocket);
	enemy.setScale(targetSize.x, targetSize.y);
	enemy.setRotation(180.f);

	CircleShape ememybullet;
	ememybullet.setFillColor(Color::Magenta);
	ememybullet.setRadius(5.f);

	vector<CircleShape> ememybullets;



	while (window.isOpen())
	{
		if (bulletcontrol < 5)
		{
			bulletcontrol++;
		}

		window.clear();
		window.draw(enemy);
		window.draw(player);
		data = rd.recv();
		enemypositionx = std::stof(data);
		data = rd.recv();
		enemypositiony = std::stof(data);
		enemy.setPosition(enemypositionx, enemypositiony);

		data = rd.recv();
		enemybulletcounter = std::stof(data);
		if (enemybulletcounter == 1)
		{
			ememybullet.setPosition(enemypositionx, enemypositiony);
			ememybullets.push_back(CircleShape(ememybullet));
		}
		for (size_t i = 0; i < ememybullets.size(); i++)
		{
			ememybullets[i].move(0.f, 15.f);
			window.draw(ememybullets[i]);
		}

		mypositionx = Mouse::getPosition(window).x;
		mypositiony = Mouse::getPosition(window).y;
		storedata = (std::to_string(mypositionx));
		sd.sendinfo(storedata);
		storedata = (std::to_string(mypositiony));
		sd.sendinfo(storedata);
		player.setPosition(mypositionx, mypositiony);

		if (Mouse::isButtonPressed(Mouse::Left) && bulletcontrol > 3)
		{
			int j = 0;
			bulletcontrol = 0;
			proxybullets.clear();
			playerbullet.setPosition(mypositionx, mypositiony);
			playerbulletes.push_back(CircleShape(playerbullet));
			proxybullets.push_back(CircleShape(playerbullet));
			for (size_t i = 0; i < proxybullets.size(); i++)
			{
				j++;
			}
			storedata = (std::to_string(j));
			sd.sendinfo(storedata);

		}
		else
		{
			int j = 0;
			storedata = (std::to_string(j));
			sd.sendinfo(storedata);

		}


		for (size_t i = 0; i < playerbulletes.size(); i++)
		{
			playerbulletes[i].move(0.f, -15.f);
			window.draw(playerbulletes[i]);
		}

		window.display();

		for (size_t j = 0; j < ememybullets.size(); j++)
		{
			if (player.getGlobalBounds().intersects(ememybullets[j].getGlobalBounds()))
			{
				cout << "YOU LOSE" << endl;
				window.close();
			}
		}
		for (size_t j = 0; j < playerbulletes.size(); j++)
		{
			if (enemy.getGlobalBounds().intersects(playerbulletes[j].getGlobalBounds()))
			{
				cout << "YOU WIN" << endl;
				window.close();
			}
		}

	}
	rd.closesocketserv();
	sd.closesocketclient();
}
