#include "ANFScene.h"
#include <iostream>
#include <windows.h>
#include <fstream>
using namespace std;

ANFScene :: ANFScene(char *filename){


	doc=new TiXmlDocument( filename );
	bool loadOkay = doc->LoadFile();

	if ( !loadOkay )
	{
		printf( "Could not load file '%s'. Error='%s'. Exiting.\n", filename, doc->ErrorDesc() );
		Sleep(3);
		exit( 1 );
	}

		TiXmlElement* anfElement= doc->FirstChildElement( "anf" );

		if (anfElement == NULL)
	{
		printf("Main anf block element not found! Exiting!\n");
		Sleep(3);
		exit(1);
	}

    globalsElement = anfElement->FirstChildElement( "globals" );
	camerasElement = anfElement->FirstChildElement( "cameras" );
	lightsElement =  anfElement->FirstChildElement( "lights" );
	texturesElement =  anfElement->FirstChildElement( "textures" );
	appearancesElement =  anfElement->FirstChildElement( "appearances" );
	nodesElement =  anfElement->FirstChildElement( "node" );
	graphElement =  anfElement->FirstChildElement( "graph" );


	this->parseGlobals();
	this->parseCameras();
	
}

void ANFScene :: parseCameras(){
	if (camerasElement == NULL)
		printf("cameras block not found!\n");
	else
	{
		char* initial= NULL;
		initial = (char *) camerasElement->Attribute("initial");
		printf("cameras initial: %s\n", initial);

		TiXmlElement* perspectiveElement=camerasElement->FirstChildElement("perspective");
		if (perspectiveElement)
		{
			char *id, *pos, *target, *Cnear, *Cfar , *angle;

			id =(char *) perspectiveElement->Attribute("id");
			Cnear = (char *)perspectiveElement->Attribute("near");
			Cfar = (char *)perspectiveElement->Attribute("far");
			angle = (char *)perspectiveElement->Attribute("angle");
			pos =(char *) perspectiveElement->Attribute("pos");
			target=(char *) perspectiveElement->Attribute("target");
			
		
			
			printf("perspective id=%s near=%s far=%s angle=%s pos=%s target=%s\n",id, Cnear, Cfar, angle, pos, target);
		}
	
		TiXmlElement* orthoElement = camerasElement->FirstChildElement("ortho");
	if (orthoElement)
		{
			char *id, *direction, *Cnear, *Cfar , *angle, *left, *right, *top, *bottom ;

			id =(char *) perspectiveElement->Attribute("id");
			Cnear = (char *)perspectiveElement->Attribute("near");
			Cfar = (char *)perspectiveElement->Attribute("far");
			angle = (char *)perspectiveElement->Attribute("angle");
		
			
			//printf("perspective id=%s near=%s far=%s angle=%s pos=%s target=%s\n",id, Cnear, Cfar, angle, pos, target);
		}
	
	
	}



}

void ANFScene:: parseGlobals(){

		if (globalsElement == NULL)
		printf("globals block not found!\n");
	else
	{
		printf("Processing globals:\n");
		// drawing
		TiXmlElement* drawingElement=globalsElement->FirstChildElement("drawing");
		if (drawingElement)
		{

			char* mode = NULL;
			char* shading = NULL;
			char* background = NULL;

			
			mode =(char *) drawingElement->Attribute("mode");
			shading =(char *) drawingElement->Attribute("shading");
			background =(char *) drawingElement->Attribute("background");
			

			printf("drawing mode= %s shading= %s background = %s\n", mode, shading,background);
		}


		TiXmlElement* cullingElement=globalsElement->FirstChildElement("culling");
		if (cullingElement)
		{
		char* face = NULL;
		char* order = NULL;

		face =(char *) cullingElement->Attribute("face");
		order =(char *) cullingElement->Attribute("order");


		printf("culling face=%s order=%s\n", face, order);

		}


}
}


ANFScene::~ANFScene()
{
	delete(doc);
}


TiXmlElement *ANFScene::findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val)
// Searches within descendants of a parent for a node that has an attribute _attr_ (e.g. an id) with the value _val_
// A more elaborate version of this would rely on XPath expressions
{
	TiXmlElement *child=parent->FirstChildElement();
	int found=0;

	while (child && !found)
		if (child->Attribute(attr) && strcmp(child->Attribute(attr),val)==0)
			found=1;
		else
			child=child->NextSiblingElement();

	return child;
}


int main(){

	ANFScene("aula1.xml");

	system("pause");

	return 0;

}