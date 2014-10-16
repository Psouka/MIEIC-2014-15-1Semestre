#include "ANFScene.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

ANFScene :: ANFScene(char *filename)
	:  CGFscene()
{

	doc=new TiXmlDocument( filename );
	bool loadOkay = doc->LoadFile();

	if ( !loadOkay )
	{
		printf( "Could not load file '%s'. Error='%s'. Exiting.\n", filename, doc->ErrorDesc() );

	}

	TiXmlElement* anfElement= doc->FirstChildElement( "anf" );

	if (anfElement == NULL)
	{
		printf("Main anf block element not found! Exiting!\n");

	}

	globalsElement = anfElement->FirstChildElement( "globals" );
	camerasElement = anfElement->FirstChildElement( "cameras" );
	lightElement =  anfElement->FirstChildElement( "lights" );
	texturesElement =  anfElement->FirstChildElement( "textures" );
	appearancesElement =  anfElement->FirstChildElement( "appearances" );
	graphElement =  anfElement->FirstChildElement( "graph" );


	this->parseGlobals();
	printf("\n\n[GLOBAIS] DONE\n");
	this->parseLights();
	printf("\n\n[LUZES] DONE\n");
	this->parseCameras();
	printf("\n\n[CAMERAS] DONE\n");
	this->parseTextures();
	printf("\n\n[TEXTURAS] DONE\n");
	this->parseAppearences();
	printf("\n\n[APPEARENCES] DONE\n\n");
	this->parseGraph();
	printf("\n\n[GRAPH] DONE\n\n");

}

int ANFScene :: parseCameras(){
	if(camerasElement == NULL)
		printf("Camera block not found!\n");
	else {
		printf("\n[CAMERAS]");
		char *initial_c=NULL;
		char *initial=NULL;
		initial_c = (char *)camerasElement->Attribute("initial");
		if(initial_c)
			printf("	Cameras attribute: %s\n",initial_c);
		else{
			printf("Error parsing Cameras\n");
			return -1;
		}

		bool perspectiveRead = false, orthoRead = false;

		TiXmlElement* camElement=camerasElement->FirstChildElement();
		while(camElement)
		{
			if(strcmp(camElement->Value(),"perspective")==0)
			{
				printf("\n(Perspective)");
				float near, far, angle;
				char *id=NULL;
				float position[3], target[3];

				if(id = (char *)camElement->Attribute("id"))
					printf("\n	id: %s",id);
				else
					printf("ID ERROR");

				if (camElement->QueryFloatAttribute("near",&near)==TIXML_SUCCESS && 
					camElement->QueryFloatAttribute("far",&far)==TIXML_SUCCESS &&
					camElement->QueryFloatAttribute("angle",&angle)==TIXML_SUCCESS)
				{

					printf("\n	near: %f",near);
					printf("\n	far: %f",far);
					printf("\n	angle: %f",angle);


					float pos0,pos1,pos2,tar0,tar1,tar2;

					initial=(char *)camElement->Attribute("pos");

					if(initial && sscanf_s(initial,"%f %f %f",&pos0, &pos1, &pos2)==3)
					{
						printf("\n	pos: (%f,%f,%f)", pos0, pos1, pos2);
						position[0]=pos0;
						position[1]=pos1;
						position[2]=pos2;
					}
					else
					{
						cout << "\nError parsing pos...\n";		
						system("pause");
						exit(1);
					}

					initial=(char *)camElement->Attribute("target");

					if(initial && sscanf_s(initial,"%f %f %f",&tar0, &tar1, &tar2)==3)
					{
						printf("\n	target : (%f,%f,%f)", tar0, tar1, tar2);
						target[0] = tar0;
						target[1] = tar1;
						target[2] = tar2;
					}
					else
					{
						cout << "\nError parsing target...\n";		
						system("PAUSE");
						exit(1);
					}


				}
				Camera* camera = new PerspectiveCamera(string(id),near,far, angle);
				camera->setPosition(position);
				camera->setTarget(target);

				if(strcmp(id,initial_c)==0)
				{
					camera->setInitial(true);
				}
				cameras.push_back(camera);
				perspectiveRead = true;
			}
			else if(strcmp(camElement->Value(),"ortho")==0)
			{
				printf("\n(Ortho)");

				char *id=NULL;
				float near,far,left,right,top,bottom;

				if(id = (char *)camElement->Attribute("id"))
					printf("\n	id: %s",id);
				else
					printf("ID ERROR");

				if (camElement->QueryFloatAttribute("near",&near)==TIXML_SUCCESS && 
					camElement->QueryFloatAttribute("far",&far)==TIXML_SUCCESS &&
					camElement->QueryFloatAttribute("left",&left)==TIXML_SUCCESS &&
					camElement->QueryFloatAttribute("right",&right)==TIXML_SUCCESS && 
					camElement->QueryFloatAttribute("top",&top)==TIXML_SUCCESS &&
					camElement->QueryFloatAttribute("bottom",&bottom)==TIXML_SUCCESS)
				{

					printf("\n	near:%f",near);
					printf("\n	far:%f",far);
					printf("\n	left:%f",left);
					printf("\n	right:%f",right);
					printf("\n	top:%f",top);
					printf("\n	bottom:%f",bottom);

					Camera* camera = new OrthoCamera(string(id),near,far,left,right,top,bottom);

					if(strcmp(id,initial_c)==0)
					{
						camera->setInitial(true);
					}

					cameras.push_back(camera);
					orthoRead = true;
				}
				else
					printf("Error parsing ortho\n");							
			}
			camElement=camElement->NextSiblingElement();

		}

		if(!perspectiveRead)
			printf("Error reading perspective camera!\n");
		if(!orthoRead)
			printf("Error reading ortho camera!\n");

	}
	return 0;


}

int ANFScene:: parseGlobals(){

	if(globalsElement == NULL)
		printf("Globals block not found!\n");
	else {
		printf("\n[Globals]\n");
		char* valString= NULL;
		ANFGlobals = Globals();

		TiXmlElement* gElement=globalsElement->FirstChildElement();

		if(strcmp(gElement->Value(),"drawing")==0)
		{
			char *mode, *shading;
			float bg[4];
			float bg0, bg1, bg2, bg3;


			mode =(char *)gElement->Attribute("mode");
			shading =(char *)gElement->Attribute("shading");
			valString=(char *)gElement->Attribute("background");

			if(valString &&sscanf_s(valString,"%f %f %f %f",&bg0, &bg1, &bg2, &bg3)==4)
			{
				GLenum drawmode, drawshading;

				if(strcmp(mode,"fill")==0)
					drawmode = GL_FILL;
				else if(strcmp(mode,"line")==0)
					drawmode = GL_LINE;
				else if(strcmp(mode,"point")==0)
					drawmode = GL_POINT;
				printf("\n	Drawmode: %s", mode);

				if(strcmp(shading,"flat")==0)
					drawshading = GL_FLAT;
				else if(strcmp(shading,"gouraud")==0)
					drawshading = GL_SMOOTH;
				printf("\n	Shading: %s", shading);

				bg[0] = bg0;
				bg[1] = bg1;
				bg[2] = bg2;
				bg[3] = bg3;
				printf("\n	Background  : (%f,%f,%f,%f)", bg[0], bg[1], bg[2], bg[3]);

				ANFGlobals.updateDraw(drawmode,drawshading,bg);

			}
			else
			{
				cout << "\nError parsing globals<background>...\n";		
				system("PAUSE");
				exit(1);
			}
		}
		else
		{
			cout << "\nError parsing globals<drawing>...\n";		
			system("pause");
			exit(1);
		}


		gElement=gElement->NextSiblingElement();
		if(gElement->Value(),"culling")
		{
			char * cullface, *cullorder;
			GLenum fl, ol;
			cullface =(char *)gElement->Attribute("face");
			cullorder =(char *)gElement->Attribute("order");

			if(cullorder && cullface)
			{
				if(strcmp(cullorder,"ccw")==0)
					ol = GL_CCW;
				else if(strcmp(cullorder,"cw")==0)
					ol = GL_CW;
				printf("\n	Cullorder: %s", cullorder);

				if(strcmp(cullface,"back")==0)
					fl = GL_BACK;
				else if(strcmp(cullface,"front")==0)
					fl = GL_FRONT;
				else if(strcmp(cullface,"both")==0)
					fl = GL_FRONT_AND_BACK ;
				printf("\n	Cullface: %s", cullface);

				ANFGlobals.updateCulli(fl,ol);
			}
			else
			{
				printf("Error parsing culling\n");
				return -1;
			}



		}


		gElement=gElement->NextSiblingElement();
		if(gElement->Value(),"lighting")
		{
			bool doublesided , local , enabled;
			float ambient[4];
			float a0, a1, a2, a3;

			valString =(char *)gElement->Attribute("doublesided");

			if(valString){
				if(strcmp(valString,"true")==0)
					doublesided = true;
				else
					doublesided = false;

				printf("\n	Doublesided: %s",valString);
			}
			else
				printf("\nDOUBLESIDED ERROR");

			valString =(char *)gElement->Attribute("local");

			if(valString){
				if(strcmp(valString,"true")==0)
					local= true;
				else
					local = false;
				printf("\n	Local: %s",valString);
			}
			else
				printf("\nLOCAL ERROR");

			valString =(char *)gElement->Attribute("enabled");

			if(valString){
				if(strcmp(valString,"true")==0)
					enabled = true;
				else
					enabled = false;
				printf("\n	Enabled: %s",valString);
			}
			else
				printf("\nENABLED ERROR");


			valString=(char *)gElement->Attribute("ambient");

			if(valString &&sscanf_s(valString,"%f %f %f %f",&a0, &a1, &a2, &a3)==4)
			{
				ambient[0] = a0;
				ambient[1] = a1;
				ambient[2] = a2;
				ambient[3] = a3;
				printf("Ambient: <%f %f %f %f>",ambient[0],ambient[1], ambient[2], ambient[3]);
			}
			else
				printf("\nAMBIENT ERROR");

			ANFGlobals.updateLight(doublesided,local,enabled,ambient);
		}
		else
		{
			printf("\nError parsing globals<lighting>...\n");
			return -1;
		}


	}
	return 0;
}

int ANFScene :: parseLights(){

	if(lightElement == NULL)
		printf("Lighting block not found!\n");
	else
	{
		TiXmlElement* lElement = lightElement->FirstChildElement();
		TiXmlElement* compElement;
		float target[3];
		float exponent, angle;
		char* lightid, *type, *ValString;
		float pos[3], a[4], d[4], s[4];
		float x0,x1,x2,x3;
		bool marker, enable;
		Light *Ltemp;
		int idlight = GL_LIGHT0;
		while(lElement){

			printf("\n[LIGHTS]");

			if(lightid = (char *)lElement->Attribute("id"))
				printf("\n	ID: %s",lightid);
			else
				printf("LIGHTS ID ERROR");

			if(type = (char *)lElement->Attribute("type"))
				printf("\n	Type: %s",type);
			else
				printf("LIGHTS TYPE ERROR");

			ValString = (char *)lElement->Attribute("pos");
			if(ValString &&sscanf_s(ValString,"%f %f %f",&x0, &x1, &x2)==3)
			{
				pos[0] = x0;
				pos[1] = x1;
				pos[2] = x2;

				printf("\n	Position: %s",ValString);
			}
			else
				printf("LIGHTS POSITION ERROR");

			if(idlight > GL_LIGHT7)
			{
				printf("\nTOO MANY LIGHTS");
				break;
			}


			if(ValString = (char *)lElement->Attribute("enabled")){

				if(strcmp(ValString,"true") == 0)
					enable = true;
				else
					enable = false;

				printf("\n	Enable: %s",ValString);

			}
			else
				printf("LIGHTS ENABLE ERROR");


			if(ValString = (char *)lElement->Attribute("marker")){
				if(strcmp(ValString,"true") == 0)
					marker = true;
				else
					marker = false;

				printf("\n	Marker: %s",ValString);
			}
			else
				printf("LIGHTS MARKER ERROR");

			compElement = lElement->FirstChildElement();
			ValString = (char *)compElement->Attribute("type");

			if(strcmp(ValString,"ambient") == 0)
			{

				ValString = (char *)compElement->Attribute("value");

				if(ValString &&sscanf_s(ValString,"%f %f %f %f",&x0, &x1, &x2, &x3)==4)
				{
					a[0] = x0;
					a[1] = x1;
					a[2] = x2;
					a[3] = x3;

					printf("\n	Ambient component: %s",ValString);
				}
				else
					printf("LIGHTS AMBIENT COMPONENT ERROR");
			}
			else
				printf("LIGHTS AMBIENT COMPONENT ERROR");

			compElement = compElement->NextSiblingElement();

			ValString = (char *)compElement->Attribute("type");
			if(strcmp(ValString,"diffuse") == 0)
			{

				ValString = (char *)compElement->Attribute("value");

				if(ValString &&sscanf_s(ValString,"%f %f %f %f",&x0, &x1, &x2,&x3)==4)
				{
					d[0] = x0;
					d[1] = x1;
					d[2] = x2;
					d[3] = x3;

					printf("\n	Diffuse component: %s",ValString);
				}
				else
					printf("LIGHTS DIFFUSE COMPONENT ERROR");
			}
			else
				printf("LIGHTS DIFFUSE COMPONENT ERROR");

			compElement = compElement->NextSiblingElement();

			ValString = (char *)compElement->Attribute("type");

			if(strcmp(ValString,"specular") == 0)
			{

				ValString = (char *)compElement->Attribute("value");

				if(ValString &&sscanf_s(ValString,"%f %f %f %f",&x0, &x1, &x2, &x3)==4)
				{
					s[0] = x0;
					s[1] = x1;
					s[2] = x2;
					s[3] = x3;

					printf("\n	Specular component: %s",ValString);
				}
				else
					printf("LIGHTS SPECULAR COMPONENT ERROR");
			}
			else
				printf("LIGHTS SPECULAR COMPONENT ERROR");


			if(strcmp(type,"spot") == 0){


				ValString = (char *)lElement->Attribute("target");
				if(ValString &&sscanf_s(ValString,"%f %f %f %f",&x0, &x1, &x2)==3)
				{
					target[0] = x0;
					target[1] = x1;
					target[2] = x2;
					printf("\n	Target : %s",ValString);

				}
				else
					printf("LIGHTS TARGET ERROR");

				if (lElement->QueryFloatAttribute("exponent",&exponent)==TIXML_SUCCESS && 
					lElement->QueryFloatAttribute("angle",&angle)==TIXML_SUCCESS)
				{
					printf("\n	Angle : %f",angle);
					printf("\n	Exponent : %f",exponent);
				}
				else
					printf("LIGHTS angle/exponent ERROR");


				Ltemp = new SpotLight(lightid,idlight,pos,type,marker, target,exponent, angle);


			}
			else{
				Ltemp = new Light(lightid,idlight,pos,type,marker);


			}
			Ltemp->setAmbient(a);
			Ltemp->setDiffuse(d);
			Ltemp->setSpecular(s);

			if(enable)
				Ltemp->enable();
			else
				Ltemp->disable();
			idlight++;

			lights.push_back(Ltemp);
			lElement = lElement->NextSiblingElement();
		}


	}

	return 0;
}

int ANFScene :: parseTextures(){
	if(globalsElement == NULL)
		printf("Textures block not found!\n");
	else {

		printf("\n[TEXTURES]");
		char* valString= NULL;

		TiXmlElement* tElement=texturesElement->FirstChildElement();

		Texture *temp;
		char *id , *file; 
		float texlength_s , texlength_t;


		while(tElement){

			if(id =(char *)tElement->Attribute("id"))
				printf("\n	id: %s",id);
			else
				printf("\nTEXTURE ID ERROR");


			if(file =(char *)tElement->Attribute("file"))
				printf("\n	File: %s",file);
			else
				printf("\nTEXTURE FILE ERROR");


			if(tElement->QueryFloatAttribute("texlength_s",&texlength_s) ==TIXML_SUCCESS &&
				tElement->QueryFloatAttribute("texlength_t",&texlength_t) ==TIXML_SUCCESS
				&& id != "" && file != "" )
			{

				printf("\n	texlength_s: %f\n	textlenght_t :%f",texlength_s,texlength_t);
				temp = new Texture(string(id),string(file),texlength_s,texlength_t);
				textures.push_back(temp);


			}
			else
				printf("\n TEXTURE TEXTLENGHT ERROR");


			tElement=tElement->NextSiblingElement();

		}


	}
	return 0;
}

int ANFScene :: parseAppearences(){
	if(appearancesElement == NULL)
		printf("Appearence block not found!\n");
	else {
		printf("\n[APPEARENCES]");
		TiXmlElement* appearanceElement=appearancesElement->FirstChildElement("appearance");
		char* valString = NULL;
		char* appid,* textref, *type;
		float ambient[4], diffuse[4], specular[4];
		float shininess;
		float x0,x1,x2,x3;
		Appearance* temp;
		CGFtexture * ttemp;

		while(appearanceElement)
		{

			if(appid = (char *)appearanceElement->Attribute("id"))
				printf("\n	Attribute: %s",appid);
			else
			{
				printf("APPEARENCES ID ERROR\n");
				return -1;
			}

			if(appearanceElement->QueryFloatAttribute("shininess",&shininess) ==TIXML_SUCCESS)
				printf("\n	Shininess:%f",shininess);
			else
				printf("APPEARENCES SHININESS ERROR\n");

			if(textref = (char *)appearanceElement->Attribute("textureref"))
			{
				printf("\n	Textureref: %s",textref);
			}
			else
				textref = "";


			TiXmlElement* compElement=appearanceElement->FirstChildElement("component");


			printf("\n(Components)");
			while(compElement){

				type = (char *)compElement->Attribute("type");
				valString = (char *)compElement->Attribute("value");

				if(strcmp(type,"ambient") == 0)
				{

					if(valString &&sscanf_s(valString,"%f %f %f %f",&x0, &x1, &x2, &x3)==4)
					{
						ambient[0] = x0;
						ambient[1] = x1;
						ambient[2] = x2;
						ambient[3] = x3;
						printf("\n	Ambient: <%f %f %f %f>", ambient[0],ambient[1],ambient[2],ambient[3]);
					}
					else
						printf("APPEARENCES AMBIENT ERROR\n");


				}


				else if(strcmp(type,"diffuse")== 0)
				{
					if(valString &&sscanf_s(valString,"%f %f %f %f",&x0, &x1, &x2, &x3)==4)
					{
						diffuse[0] = x0;
						diffuse[1] = x1;
						diffuse[2] = x2;
						diffuse[3] = x3;
						printf("\n	Diffuse: <%f %f %f %f>", diffuse[0],diffuse[1],diffuse[2],diffuse[3]);
					}


					else
						printf("APPEARENCES DIFFUSE ERROR\n");

				}


				else if(strcmp(type,"specular")== 0)
				{
					if(valString &&sscanf_s(valString,"%f %f %f %f",&x0, &x1, &x2, &x3)==4)
					{
						specular[0] = x0;
						specular[1] = x1;
						specular[2] = x2;
						specular[3] = x3;
						printf("\n	Specular: <%f %f %f %f>", specular[0],specular[1],specular[2],specular[3]);
					}


					else
						printf("APPEARENCES SPECULAR ERROR\n");

				}


				compElement = compElement->NextSiblingElement();
			}

			temp = new Appearance(ambient,diffuse,specular,shininess,string(appid),string(textref));
			ttemp = findTexture(textref);
			if(ttemp != NULL)
				temp->setTexture(ttemp);




			apps.push_back(temp);

			appearanceElement = appearanceElement->NextSiblingElement();
			printf("\n\n");
		}

	}
	return 0;
}

int ANFScene :: parseGraph(){
	if(graphElement == NULL)
		printf("Graph block not found!\n");
	else {
		printf("\n[GRAPH]");
		TiXmlElement *nodeElement=graphElement->FirstChildElement("node");

		Node *Nodetemp;
		char *ValString, *ValString2, *ValString3;
		float angle, x0,x1, x2, x3, y1, y2,y3,z1, z2, z3;
		TiXmlElement *transformsElement;
		TiXmlElement* appearanceref;
		TiXmlElement* primitiveElement;
		TiXmlElement* descendantElement;
		TiXmlElement* pElement;
		TiXmlElement* transformElement;
		TiXmlElement* dElement;
		CGFappearance* lastapp;

		if(ValString = (char *) graphElement->Attribute("rootid"))
		{
			printf("\n	Rootid: %s",ValString);
			ANFGraph = new Graph(string(ValString));
		}

		while(nodeElement){

			transformsElement=nodeElement->FirstChildElement("transforms");
			appearanceref=nodeElement->FirstChildElement("appearanceref");
			primitiveElement=nodeElement->FirstChildElement("primitives");
			descendantElement=nodeElement->FirstChildElement("descendants");


			if(ValString = (char *) nodeElement->Attribute("id"))
			{
				printf("\n	Id: %s",ValString);
			}
			else
				printf("\nID NODE ERROR");

			Nodetemp = new Node(string(ValString));
			transformElement=transformsElement->FirstChildElement();

			if(transformElement)
			{	printf("\n	(Transforms)");



			char *ttemp;
			while(transformElement)
			{

				ttemp = (char *) transformElement->Attribute("type");
				if(strcmp(ttemp,"translate")==0)

				{


					ValString = (char *) transformElement->Attribute("to");

					if(ValString && sscanf_s(ValString,"%f %f %f",&x0, &x1, &x2)==3)
					{
						printf("\n	Translate: (%f,%f,%f)", x0, x1, x2);
						Nodetemp->translate(x0,x1,x2);
					}
					else
						printf("\nERROR TRANSLATE\n");		


				}

				else if(strcmp(ttemp,"rotate")==0)
				{

					ValString=(char *) transformElement->Attribute("axis");

					if ( ValString && (transformElement->QueryFloatAttribute("angle",&angle)==TIXML_SUCCESS))
					{
						Nodetemp->rotate(string(ValString),angle);
						printf("\n	Rotate:  axis: %s  angle: %f", ValString, angle);
					}
					else
						printf("ERROR ROTATE\n");
				}

				else if(strcmp(ttemp,"scale")==0)
				{
					ValString = (char *) transformElement->Attribute("factor");

					if(ValString && sscanf_s(ValString ,"%f %f %f",&x0, &x1, &x2)==3)
					{
						Nodetemp->scale(x0,x1,x2);
						printf("\n	Scale: x: %f  y: %f  z: %f", x0, x1, x2);
					}
					else
						printf("ERROR SCALE\n");
				}
				transformElement=transformElement->NextSiblingElement();
			}
			}




			if(appearanceref)
			{
				ValString=(char *) appearanceref->Attribute("id");

				if (ValString)
				{
					if(strcmp(ValString,"inherit") == 0)

						Nodetemp->setApp(lastapp);
					else
					{
						lastapp = findApp(ValString);
						Nodetemp->setApp(lastapp);
					}
					printf("\n	Appearanceref: %s", ValString);
				}
				else
					printf("ERROR PARSING APPEARANCEREF\n");
			}


			if(primitiveElement)
			{	printf("\n	(Primitives)");

			pElement = primitiveElement->FirstChildElement();
			while(pElement)
			{

				if (strcmp(pElement->Value(),"rectangle")==0)
				{

					ValString = (char *) pElement->Attribute("xy1");
					ValString2 = (char *) pElement->Attribute("xy2");

					if(ValString && sscanf_s(ValString,"%f %f",&x1, &y1)==2
						&& ValString2 && sscanf_s(ValString2,"%f %f",&x2, &y2)==2)
					{
						Nodetemp->addPrimitive(new Rectangle(x1,y1,x2,y2));
						printf("\n	Rectangle x1: %f y1:%f x2: %f y2:%f",x1,y1,x2,y2);
					}
					else
						printf("\nERROR RECTANGLE");


				}

				else if (strcmp(pElement->Value(),"triangle")==0)
				{

					ValString = (char *) pElement->Attribute("xyz1");
					ValString2 = (char *) pElement->Attribute("xyz2");
					ValString3 = (char *) pElement->Attribute("xyz3");

					if(ValString && sscanf_s(ValString,"%f %f %f",&x1, &y1, &z1)==3
						&& ValString2 && sscanf_s(ValString2,"%f %f %f",&x2, &y2, &z2)==3
						&& ValString3 && sscanf_s(ValString3,"%f %f %f",&x3, &y3, &z3)==3)
					{
						Nodetemp->addPrimitive(new Triangle(x1,y1,z1,x2,y2,z2,x3,y3,z3));
						printf("\n	Triangle x1:%f y1:%f z1:%f x2:%f y2:%f z2:%f x3:%f y3:%f z3:%f",x1,y1,z1,x2,y2,z2,x3,y3,z3);
					}
					else
						printf("\nERROR TRIANGLE");

				}

				// <cylinder base="ff" top="ff" height="ff" slices="ii" stacks="ii" /> 

				else if (strcmp(pElement->Value(),"cylinder")==0)
				{
					ValString = (char *) pElement->Attribute("slices");
					ValString2 = (char *) pElement->Attribute("stacks");

					if (pElement->QueryFloatAttribute("base",&x0)==TIXML_SUCCESS && 
						pElement->QueryFloatAttribute("top",&x1)==TIXML_SUCCESS &&
						pElement->QueryFloatAttribute("height",&x2)==TIXML_SUCCESS
						&& ValString && ValString2)
					{
						Nodetemp->addPrimitive(new Cylinder(x0,x1,x2,atoi(ValString),atoi(ValString2)));
						printf("\n	Cylinder slices:%s stacks:%s base:%f top:%f height:%f",ValString,ValString2,x0,x1,x2);
					}
					else
						printf("\nERROR CYLINDER");
				}

				//<sphere radius="ff" slices="ii" stacks="ii" />

				else if (strcmp(pElement->Value(),"sphere")==0)
				{
					ValString = (char *) pElement->Attribute("slices");
					ValString2 = (char *) pElement->Attribute("stacks");

					if (pElement->QueryFloatAttribute("radius",&x0)==TIXML_SUCCESS
						&& ValString && ValString2)
					{
						Nodetemp->addPrimitive(new Sphere(x0,atoi(ValString),atoi(ValString2)));
						printf("\n	Shpere slices:%f stacks:%s radius:%s",x0,ValString,ValString2);
					}
					else
						printf("\nERROR SPHERE");
				}

				// <torus inner="ff" outer="ff" slices="ii" loops="ii" />

				else if (strcmp(pElement->Value(),"torus")==0)
				{
					ValString = (char *) pElement->Attribute("slices");
					ValString2 = (char *) pElement->Attribute("loops");

					if (pElement->QueryFloatAttribute("inner",&x0)==TIXML_SUCCESS && 
						pElement->QueryFloatAttribute("outer",&x1)==TIXML_SUCCESS
						&& ValString && ValString2)
					{
						Nodetemp->addPrimitive(new Torus(x0,x1,atoi(ValString),atoi(ValString2)));
						printf("\n	Shpere slices:%s loops:%s inner:%f outer:%f",ValString,ValString2,x0,x1);
					}
					else
						printf("\nERROR TORUS");
				}


				pElement = pElement->NextSiblingElement();
			}
			}


			if(descendantElement)
			{printf("\n	(Descendants)");

			dElement = descendantElement->FirstChildElement();
			if(descendantElement)
				while(dElement)
				{
					ValString=(char *) dElement->Attribute("id");

					Nodetemp->addDescend(string(ValString));

					dElement = dElement->NextSiblingElement();
				}


			}
			printf("\n\n");
			ANFGraph->addNode(Nodetemp);
			nodeElement = nodeElement->NextSiblingElement();
		} 
	}
	return 0;
}

Texture* ANFScene ::findTexture(string id){

	for(unsigned int i = 0; i < textures.size(); i++){
		if(textures[i]->getId() == id)
			return textures[i];
	}
	return NULL;
}

CGFappearance* ANFScene :: findApp(string id){
	for(unsigned int i = 0; i < apps.size(); i++){
		if(apps[i]->getAppId() == id)
			return apps[i];
	}

	return NULL;

}

vector<Node*> ANFScene ::getNodes(vector<string> n){
	vector<Node*> retorno;

	for(unsigned int i = 0; i <n.size();i++)
		retorno.push_back(ANFGraph->getGraph()[n[i]]);

	return retorno;
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

void ANFScene::init(){

	srand((time(NULL)));

	if(ANFGlobals.enabled)
		glEnable(GL_LIGHTING);
	else
		glDisable(GL_LIGHTING);

	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, ANFGlobals.doublesided);

	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, ANFGlobals.local);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ANFGlobals.ambient);

	glFrontFace(ANFGlobals.order);

	glEnable(GL_CULL_FACE);

	glCullFace(ANFGlobals.face);

	glPolygonMode(GL_FRONT_AND_BACK,ANFGlobals.drawMode);

	glClearColor(ANFGlobals.background[0], ANFGlobals.background[1],
		ANFGlobals.background[2],ANFGlobals.background[3]);

	glEnable(GL_NORMALIZE);

	glEnable (GL_TEXTURE_2D);

	FillChildren(ANFGraph->getGraph()[ANFGraph->getRoot()]);

}

void  ANFScene::FillChildren(Node* node){
	vector<Node*> nodes = getNodes(node->getChildren());
	node->setChilds(nodes);

	for(unsigned int i = 0; i < nodes.size(); i++) {
		FillChildren(nodes[i]);
	}

}

void ANFScene:: display(){

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	CGFscene::activeCamera->applyView(); 

	axis.draw();

	for(unsigned int i = 0; i < lights.size(); i++) {
		if(lights[i]->getMarker())
			lights[i]->draw();
	}

	process(ANFGraph->getGraph()[ANFGraph->getRoot()]);

	glutSwapBuffers();

}

void ANFScene::process(Node* node) {
	if(node == NULL)
	{
		printf("\nNode nao encontrado");
		system("pause");
		exit(1);
	}

	glMultMatrixf(node->getMatrix());

	//processar texturas e aparencia
	vector<string> temp  = node->getChildren();
	unsigned int i = temp.size();

	vector<Node*> nodes = node->getNChilds();

	vector<Primitives*> prim = node->getPrimitives();
	for(unsigned int a = 0; a < prim.size(); a++) {
		prim[a]->draw();
	}

	for(unsigned int i = 0; i < nodes.size(); i++) {
		glPushMatrix();
		nodes[i]->ApplyApp();
		process(nodes[i]);
		glPopMatrix();
	}

}

int main(int argc, char* argv[]){

	CGFapplication app = CGFapplication();

	try {
		app.init(&argc, argv);

		if(argc > 1)
			app.setScene(new ANFScene(argv[1]));
		else
			app.setScene(new ANFScene("LAIG_TP1_ANF_T01_G03_v2.anf"));
		//app.setScene(new ANFScene("scene.anf"));

		app.setInterface(new CGFinterface());

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