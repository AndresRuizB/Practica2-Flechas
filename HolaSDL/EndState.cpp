#include "EndState.h"
#include "MenuButton.h"
#include "Scores.h"
#include <iterator>

EndState::EndState(App* a)
{
	app = a;
	aux = new MenuButton(a, this, a->returnTexture(backbutton), 250, 230, retunToMenu);
	escenario.push_back(aux);
	manejadoresEventos.push_back(static_cast<MenuButton*>(aux));

	aux = new MenuButton(a, this, a->returnTexture(exitbutton), 500, 230, exit);
	escenario.push_back(aux);
	manejadoresEventos.push_back(static_cast<MenuButton*>(aux));

	fondo = app->returnTexture(background0);
	obj.x = obj.y = 0;
	obj.w = WIN_WIDTH;
	obj.h = WIN_HEIGHT;
}

EndState::~EndState()
{
}

void EndState::render()
{
	fondo->render(obj);
	for (list<GameObject*>::const_iterator it = escenario.begin(); it != escenario.end(); ++it) (*it)->render();
}

void EndState::update()
{
}

void EndState::handleEvent()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		for (list<EventHandler*>::const_iterator it = manejadoresEventos.begin(); it != manejadoresEventos.end(); ++it)(*it)->handleEvent(event);
	}
}

void EndState::Records(int puntuacion)
{
	Scores* scores = new Scores();

	try {
		scores->load("top.txt");  //carga todos los records anteriores de archivo		
		string name;
		cout << "\n\nCual es tu nombre: \n";
		cin >> name;
		if (scores->addScore(name, puntuacion)) { //si has entrado en el top actualiza el archivo
			scores->save("top.txt");
		}
		else cout << "Lo siento " << name << " no has entrado en el top 10\n"; //si no has entrado en el top

		scores->print(); //muestra los leaderboards por consola
	}
	catch (FileNotFoundError e) { cout << "Error al intentar acceder al archivo de records. " << e.what(); }
	catch (FileFormatError e) { cout << "Error al intentar leer el archivo de records. " << e.what(); };

	delete scores;
}


void EndState::exit(App* app)
{
	app->salir();
}

void EndState::retunToMenu(App* app)
{
	app->volverMenu();
}
