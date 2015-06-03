#include <iostream>

#include "Intersection.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Plane.h"
#include "Screen.h"
#include "tinystr.h"
#include "tinyxml.h"
#include "Maya.h"
#include <string>


//#define PI 3.14159265
using namespace std;

void cargar(){

	TiXmlDocument doc;
    doc.LoadFile("escena.xml");
    TiXmlElement* root = doc.FirstChildElement();
    if(root == NULL){
        doc.Clear();
    }
    Scene* s = Scene::getInstance();

    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()){
            string elemName = elem->Value();
            double r; double cx,cy,cz,ox,oy,oz; double colorr, colorg, colorb,h,w;
			double spec;
			double iRefr;
			char tipo;
			double diff;
			double tran;
			bool refracta, refleja;
			double specL,gloss;
			bool maya;
			Colour col;
            if(elemName == "Sphere"){
                r= atof( elem->Attribute("Radius"));
                cx= atof( elem->Attribute("CenterX"));
				cy= atof( elem->Attribute("CenterY"));
				cz= atof( elem->Attribute("CenterZ"));
                colorr= atof( elem->Attribute("R"));
                colorg= atof( elem->Attribute("G"));
				colorb= atof( elem->Attribute("B"));
				spec= atof( elem->Attribute("Specular"));
				iRefr= atof( elem->Attribute("Ref"));
				diff= atof( elem->Attribute("Diffuse"));
				tran= atof( elem->Attribute("MedioR"));
				refracta= 1 == atoi( elem->Attribute("Refracta"));
				refleja= 1 == atoi( elem->Attribute("Refleja"));
				specL= atof( elem->Attribute("SpecularLevel"));
				gloss= atof( elem->Attribute("Glossiness"));
                Sphere* sp= new Sphere(Vector(cx,cy,cz), r , Vector(colorr,colorg,colorb), spec, iRefr, diff, tran,refleja, refracta,gloss, specL);
                s->models.push_back(sp);
            }else if(elemName == "Plane"){
                h= atof( elem->Attribute("Height"));
                w= atof( elem->Attribute("Width"));
                cx= atof( elem->Attribute("CenterX"));
				cy= atof( elem->Attribute("CenterY"));
				cz= atof( elem->Attribute("CenterZ"));
				ox= atof( elem->Attribute("NormalX"));
                oy= atof( elem->Attribute("NormalY"));
				oz= atof( elem->Attribute("NormalZ"));
                colorr= atof( elem->Attribute("R"));
                colorg= atof( elem->Attribute("G"));
				colorb= atof( elem->Attribute("B"));
				spec= atof( elem->Attribute("Specular"));
				iRefr= atof( elem->Attribute("Ref"));
				diff= atof( elem->Attribute("Diffuse"));
				tran= atof( elem->Attribute("MedioR"));
				refracta= 1 == atoi( elem->Attribute("Refracta"));
				refleja= 1 == atoi( elem->Attribute("Refleja"));
				specL= atof( elem->Attribute("SpecularLevel"));
				gloss= atof( elem->Attribute("Glossiness"));

                Plane* pl = new Plane(Vector(ox,oy,oz),Vector(cx,cy,cz),h,w,Vector(colorr,colorg,colorb),spec, iRefr, diff, tran,refleja,refracta,gloss,specL);
                s->models.push_back(pl);

            }else if(elemName == "Maya"){
                maya= true;
                tipo=  'F';//(char) elem->Attribute("Tipo");
                colorr= atof( elem->Attribute("R"));
                colorg= atof( elem->Attribute("G"));
				colorb= atof( elem->Attribute("B"));
				spec= atof( elem->Attribute("Specular"));
				iRefr= atof( elem->Attribute("Ref"));
				diff= atof( elem->Attribute("Diffuse"));
				tran= atof( elem->Attribute("MedioR"));
				refracta= 1 == atoi( elem->Attribute("Refracta"));
				refleja= 1 == atoi( elem->Attribute("Refleja"));
				specL= atof( elem->Attribute("SpecularLevel"));
				gloss= atof( elem->Attribute("Glossiness"));
				Maya* m = new Maya(tipo,Vector(colorr,colorg,colorb),spec, iRefr, diff, tran,refleja,refracta,gloss,specL);
				s->models.push_back(m);
				while(maya)
				{
				    elem = elem->NextSiblingElement();
				    string elemName = elem->Value();
                    if(elemName == "Vertices")
                    {
                        cx= atof( elem->Attribute("PositionX"));
                        cy= atof( elem->Attribute("PositionY"));
                        cz= atof( elem->Attribute("PositionZ"));
                        Vector* w = new Vector(cx,cy,cz);
                        m->addVertex(w);

                    }else if(elemName == "FinMaya")
                        maya = false;
				}

            }else if(elemName == "Light"){
				colorr= atof( elem->Attribute("R"));
                colorg= atof( elem->Attribute("G"));
				colorb= atof( elem->Attribute("B"));
				cx= atof( elem->Attribute("PositionX"));
				cy= atof( elem->Attribute("PositionY"));
				cz= atof( elem->Attribute("PositionZ"));
				col.r = colorr;col.g = colorg;col.b = colorb;col.a = 255;
				Light* l = new Light(col,Vector(cx,cy,cz));
				s->lights.push_back(l);
            }else if(elemName == "Cylinder"){
                r= atof( elem->Attribute("Radius"));
                h= atof( elem->Attribute("Height"));
                cx= atof( elem->Attribute("CenterX"));
				cy= atof( elem->Attribute("CenterY"));
				cz= atof( elem->Attribute("CenterZ"));
				ox= atof( elem->Attribute("OrientationX"));
                oy= atof( elem->Attribute("OrientationY"));
				oz= atof( elem->Attribute("OrientationZ"));
                colorr= atof( elem->Attribute("R"));
                colorg= atof( elem->Attribute("G"));
				colorb= atof( elem->Attribute("B"));
				spec= atof( elem->Attribute("Specular"));
				iRefr= atof( elem->Attribute("Ref"));
				diff= atof( elem->Attribute("Diffuse"));
				tran= atof( elem->Attribute("MedioR"));
				refracta= 1 == atoi( elem->Attribute("Refracta"));
				refleja= 1 == atoi( elem->Attribute("Refleja"));
				specL= atof( elem->Attribute("SpecularLevel"));
				gloss= atof( elem->Attribute("Glossiness"));
				Cylinder* cyl= new Cylinder(Vector(cx,cy,cz),r,h,Vector(ox,oy,oz), Vector(colorr,colorg,colorb), spec, iRefr, diff, tran,refleja,refracta,gloss,specL);
                s->models.push_back(cyl);
            }else if(elemName == "Escena"){


                s->Width = atof( elem->Attribute("Width"));
                s->Hight = atof( elem->Attribute("Height"));
                cx= atof( elem->Attribute("LookingX"));
                cy= atof( elem->Attribute("LookingY"));
				cz= atof( elem->Attribute("LookingZ"));
				s->lookAt =(Vector (cx,cy,cz)) ;
				s->lookAt = s->lookAt.UnitVector();
                cx= atof( elem->Attribute("EyeX"));
				cy= atof( elem->Attribute("EyeY"));
				cz= atof( elem->Attribute("EyeZ"));
				s->eye = Vector (cx,cy,cz);
				cx= atof( elem->Attribute("VupX"));
                cy= atof( elem->Attribute("VupY"));
				cz= atof( elem->Attribute("VupZ"));
				Vector v = (Vector (cx,cy,cz));
				v = v.UnitVector();
				double a,b;
				b =acos(DotProduct(s->lookAt,v));
				a= PI/2 - b;

				s->vUp= (v - sin(a)*s->lookAt).UnitVector();
                s->vLeft= CrossProduct(s->vUp,s->lookAt);
                s->vLeft= s->vLeft.UnitVector();
                s->near = sqrt(s->Width^2 + s->Hight^2) / ( 2*tan( 45/2 ) );


            }
    }
}




int main()
{
    Scene* s = Scene::getInstance();
    Colour c;
    c.r = 0;c.g = 0;c.b = 0; c.a=0;
    s->backGround = c;
    cargar();


    Screen pantalla;
    pantalla.generateImg();

    return 0;
}

