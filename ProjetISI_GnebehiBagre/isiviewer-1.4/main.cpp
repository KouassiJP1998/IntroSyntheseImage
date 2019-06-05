#include <QApplication>
#include "my_main_window.h"
#include "my_object3d.h"
#include "objects/cube.h"
#include "objects/pyramid.h"
#include "objects/cubecorner.h"
#include "objects/disk.h"
#include "objects/torus.h"
#include "objects/diskhole.h"
#include "objects/cylinder.h"
#include "objects/sphere.h"
#include "objects/cone.h"
#include "objects/func_surface.h"
#include "objects/off_loader.h"
#include <tclap/CmdLine.h>

using namespace std;


/**
* Program usage
* Should be handled with the tclap library
*/


class MyOutput : public TCLAP::StdOutput
{
    public:

        //changement de l'option help grace à la librairie TCLAP.
        virtual void usage(TCLAP::CmdLineInterface& _cmd) override
        {
            cout<< "usage: " << "isiviewer-1.4" << " [options]" <<endl;
            cout<< "options:" <<endl;
            cout<< "  -h, --help                 shows this message" <<endl;
            cout<< "  --off file                 loads OFF file" <<endl;
        }


};

int main(int argc, char *argv[]){
  QApplication app(argc, argv);

  // Parse program arguments here
  // with the tclap library
  // http://tclap.sourceforge.net/manual.html
  try {

          TCLAP::CmdLine cmd("", ' ', "0.9");
          MyOutput my;
          cmd.setOutput(&my);
          TCLAP::ValueArg<std::string> nomFichierArg("","off","chargement des fichiers OFF",false,"data/fichier.off","string");
          TCLAP::MultiArg<std::string> nomFichierArgMulti("", "", "chargement de multiples fichiers OFF", false,"string");

          cmd.add(nomFichierArg);
          cmd.add(nomFichierArgMulti);
          cmd.parse(argc, argv);

          // initialize my custom 3D scene
          float objectRadius = 1.;
          QPointer<MyScene> myScene = new MyScene(objectRadius);

          //add simple objects
          myScene->addObject(new CubeCorner());

          myScene->addObject(new Disk(22));

          myScene->addObject(new DiskHole(1.f,18));

          myScene->addObject(new Cylinder(21));

          myScene->addObject(new Cone(18));

          myScene->addObject(new Sphere(18));

          myScene->addObject(new Torus(48));

          myScene->addObject(new Pyramid());

          myScene->addObject(new Cube());

          // add surface functions
          myScene->addObject(new Func_surface(50, 50, -M_PI, M_PI, -M_PI, M_PI, func_expo_cosinus));

          myScene->addObject(new Func_surface(50, 50, -M_PI, M_PI, -M_PI, M_PI,toboggan_func));

          if(argc!=1) { // si un nom de fichier OFF est précisé

              // add user defined OFF files
              string nomFichier;
              vector<string> nomFichierBuff = nomFichierArgMulti.getValue();
              vector<string>tabNomFichier;
             // récupération des noms de fichiers OFF passé en ligne de commande
             tabNomFichier.push_back(nomFichierArg.getValue());

              for (int i=0; i<nomFichierBuff.size(); i++) {

                  tabNomFichier.push_back(nomFichierBuff[i]);
              }

              for(int i=0; i<tabNomFichier.size(); i++) {

                  nomFichier = tabNomFichier[i];
                  myScene->addObject(new off_loader(nomFichier));
              }

          }


          // initialize my custom main window
          QPointer<MyMainWindow> myMainWindow = new MyMainWindow(myScene);
          // display the window
          myMainWindow->show();
          // enter in the main loop
          return app.exec();

      } catch(TCLAP::ArgException &e) {
          std::cerr << "Erreur" << std::endl;
      }
}

