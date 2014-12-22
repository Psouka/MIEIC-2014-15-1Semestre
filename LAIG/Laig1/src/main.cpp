#include "ANFScene.h"
#include "TPinterface.h"
#include "PickInterface.h"

int main(int argc, char* argv[]) {

	CGFapplication app = CGFapplication();
	try {
		ANFScene *Scene;
		app.init(&argc, argv);

		if(argc > 1)
			app.setScene(Scene = new ANFScene(argv[1]));
		else
			app.setScene(Scene = new ANFScene("room.anf"));

		app.setInterface(new TPinterface(Scene));

		app.setInterface(new PickInterface());

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