#include "ANFScene.h"
#include "TPinterface.h"
#include <stdlib.h> 
ANFScene *Scene;
void _exit(){
	if(Scene->GameScene->getSocket()->isActive())
	Scene->GameScene->getSocket()->sendMessage("quit");
}

int main(int argc, char* argv[]) {

	CGFapplication app = CGFapplication();
	atexit (_exit);
	try {
		
		app.init(&argc, argv);
		glutReshapeWindow(710,550);
		if(argc > 1)
			app.setScene(Scene = new ANFScene(argv[1]));
		else
			app.setScene(Scene = new ANFScene("room1.anf"));

		app.setInterface(new TPinterface(Scene));

		app.run();
	}
	catch(GLexception& ex) {
		cout << "Erro: " << ex.what();
		return -1;
	}
	catch(exception& ex) {
		cout << "Erro inesperado: " << ex.what();
		return -1;
	}
	return 0;

}