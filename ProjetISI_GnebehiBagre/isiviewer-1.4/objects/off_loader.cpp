#include "off_loader.h"

using namespace std;

off_loader::off_loader(std::string cheminAcces) {

    _name="Off_loader";

    int i=0, j=0;

    char recupCoordxVt[20];
    char recupCoordyVt[20];
    char recupCoordzVt[20];

    std::string identifiantOFF;
    long double CoordxVt;
    long double CoordyVt;
    long double CoordzVt;
    long double CoordMax;


    ifstream myfile (cheminAcces.c_str());
    ifstream myfile2 (cheminAcces.c_str());
    int nbVecteurs, nbFaces, nbEdges;
    int premierPointTriangle,deuxiemePointTriangle,troisiemePointTriangle,pointInutile;
    recupCoordxVt[0]=0;
    recupCoordyVt[0]=0;
    recupCoordzVt[0]=0;
    CoordMax=0;


    if (myfile.is_open()) {
        if (myfile) { //on parcourt le fichier pour récupérer la valeur de la vertex la plus élevée

            myfile>>identifiantOFF;
            if((identifiantOFF.compare("OFF"))==0) { // on vérifie que que la 1ere ligne contienne OFF



                myfile>>nbVecteurs>>nbFaces>>nbEdges; //lecture de la deuxième ligne du fichier.off et récupération des données qu'elle contient



                for(i=0;i<nbVecteurs;i++) {

                    myfile>>recupCoordxVt>>recupCoordyVt>>recupCoordzVt;



                    for(int k=0;k<20;k++) { //on remplace les points par des virgules pour pouvoir faire le transtypage des variables char en long double

                        if(recupCoordxVt[k]=='.') {
                            recupCoordxVt[k]=',';
                            break;
                        }
                    }

                    for(int k=0;k<20;k++) {

                        if(recupCoordyVt[k]=='.'){
                            recupCoordyVt[k]=',';
                            break;
                        }
                    }

                    for(int k=0;k<20;k++) {

                        if(recupCoordzVt[k]=='.'){
                            recupCoordzVt[k]=',';
                            break;
                        }
                    }

                    CoordxVt = strtold (recupCoordxVt, NULL);
                    CoordyVt = strtold (recupCoordyVt, NULL);
                    CoordzVt = strtold (recupCoordzVt, NULL);



                     if(CoordxVt>CoordMax)
                     {
                         CoordMax=CoordxVt;
                     }

                     if(CoordyVt>CoordMax)
                     {
                        CoordMax=CoordyVt;
                     }

                     if(CoordzVt>CoordMax)
                     {
                        CoordMax=CoordzVt;
                     }


                    for(j=0;j<20;j++) {
                        recupCoordxVt[j]=0;
                        recupCoordyVt[j]=0;
                        recupCoordzVt[j]=0;
                    }
                }

            }
        }

        myfile.close();

    }
    else {
        cout << "le fichier ne s'est pas ouvert proprement" << endl;
    }

    CoordxVt=0;
    CoordyVt=0;
    CoordzVt=0;

    if (myfile2.is_open()) { //On reparcourt le même fichier pour créer les vertexs et les triangles
        if (myfile2) {

            myfile2>>identifiantOFF;
            if((identifiantOFF.compare("OFF"))==0) { // on vérifie que que la 1ere ligne contienne OFF



                myfile2>>nbVecteurs>>nbFaces>>nbEdges;



                for(i=0;i<nbVecteurs;i++) {

                    myfile2>>recupCoordxVt>>recupCoordyVt>>recupCoordzVt;



                    for(int k=0;k<20;k++) { //on réinitialise les variables de type char

                        if(recupCoordxVt[k]=='.') {
                            recupCoordxVt[k]=',';
                            break;
                        }
                    }

                    for(int k=0;k<20;k++) {

                        if(recupCoordyVt[k]=='.'){
                            recupCoordyVt[k]=',';
                            break;
                        }
                    }

                    for(int k=0;k<20;k++) {

                        if(recupCoordzVt[k]=='.'){
                            recupCoordzVt[k]=',';
                            break;
                        }
                    }

                    CoordxVt = strtold (recupCoordxVt, NULL);//transtypage d'une variable char en long double
                    CoordyVt = strtold (recupCoordyVt, NULL);
                    CoordzVt = strtold (recupCoordzVt, NULL);

                    this->addVertex(CoordxVt/(CoordMax+0.2),CoordyVt/(CoordMax+0.2),CoordzVt/(CoordMax+0.2));

                    for(j=0;j<20;j++) {
                        recupCoordxVt[j]=0;
                        recupCoordyVt[j]=0;
                        recupCoordzVt[j]=0;
                    }
                }



                for(int ii=0;ii<nbFaces;ii++) {
                    myfile2>>pointInutile>>premierPointTriangle>>deuxiemePointTriangle>>troisiemePointTriangle;

                    if (pointInutile > 3) {

                        cout << "Vous avez chargé un fichier OFF de polygones à plus de 3 sommets" << endl;
                        myfile.close();
                        exit(1);

                    }

                    this->addTriangle(premierPointTriangle,deuxiemePointTriangle,troisiemePointTriangle);
                }
            }
        }

        myfile.close();
        computeNormalsT();
        computeNormalsV();
    }
    else {
        cout << "le fichier ne s'est pas ouvert proprement" << endl;
    }
}














