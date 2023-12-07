#include "Engine.h"
#include <filesystem>

using namespace std;


Engine::Engine()
{
	int x = VideoMode::getDesktopMode().width;
	int y = VideoMode::getDesktopMode().height;
	m_Window.create(sf::VideoMode(x, y), "Particle System");
	
	// Load the sound in the constructor
	if (!buffer.loadFromFile("sounds/fireworks.wav"))
	{
		cout << "Error loading sound file" << endl;
	}
	sound.setBuffer(buffer);
}

void Engine::run()
{

	Clock clock;

	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;

	while (m_Window.isOpen())
	{

		Time dt = clock.restart();

		// Convert the time to seconds
		float dtAsSeconds = dt.asSeconds();

		// The Classic: input --> update --> draw
		input();

		update(dtAsSeconds);

		draw();
	}
}

void Engine::input()
{
	Event event;
	while (m_Window.pollEvent(event))
	{
		// if the escape key is pressed, close
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Escape)
			{
				m_Window.close();
			}
		}
		if (event.type == Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == Mouse::Left)
			{
				for (int i = 0; i < 20; i++)
				{
					// Play the firework sound whenever they click
					sound.play();
					int numPoints = rand() % 25 + 50; // random number between 25 and 50
					Vector2i mousePos = Mouse::getPosition(m_Window);
					Particle p(m_Window, numPoints, mousePos);
					m_particles.push_back(p);
				}
			}
		}
	}
}

void Engine::update(float dtAsSeconds)
{
	// loop through the particles and update them
	for (auto p = m_particles.begin(); p != m_particles.end();)
	{
		if (p->getTTL() > 0.0)
		{
			p->update(dtAsSeconds);
			p++;
		}
		else
		{
			p = m_particles.erase(p);
		}
	}
}

void Engine::draw()
{
	m_Window.clear();
	for (auto p = m_particles.begin(); p != m_particles.end(); p++)
	{
		m_Window.draw(*p);
	}
	m_Window.display();
}
