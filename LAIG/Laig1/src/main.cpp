#include "ANFScene.h"
#include "TPinterface.h"

int main(int argc, char* argv[]){

	CGFapplication app = CGFapplication();
	try {
		ANFScene *Scene;
		app.init(&argc, argv);

		if(argc > 1)
			app.setScene(Scene = new ANFScene(argv[1]));
		else
			app.setScene(Scene = new ANFScene("LAIG_TP1_ANF_T01_G03_v2.anf"));

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