#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>


#include "Batiment.hpp"
#include "Terrain.hpp"
#include "FileHandler.hpp"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>

using namespace std;
int main(int argc, const char * argv[]) {
    
    if (argc<2){
        std::cout <<"Pas d'arguments spécifiés, questions 1 à 4 exécutés"<< std::endl;
        FileHandler fileHandler("file");
        vector<Batiment> batiments =fileHandler.getBatiments();
        Terrain terrain =fileHandler.getTerrain();

        //1ere méthode
        cout <<"Question 1"<<endl;
        terrain.setBatimentAPlacer(batiments);
        terrain.placerBatiments();
        terrain.afficher();
        
        //Tri Aire
        cout <<"Tri Aire"<<endl;
        terrain.init(terrain.getLargeur(), terrain.getHauteur());
        terrain.trier(tri::aire);
        terrain.placerBatiments();
        terrain.afficher();
        
        //Tri encombrement
        cout <<"Tri encombrement"<<endl;
        terrain.init(terrain.getLargeur(), terrain.getHauteur());
        terrain.trier(tri::encombrement);
        terrain.placerBatiments();
        terrain.afficher();
        
        //Tri aléatoire
        cout <<"Tri aléatoire"<<endl;
        terrain.init(terrain.getLargeur(), terrain.getHauteur());
        terrain.trier(tri::aleatoire);
        terrain.placerBatiments();
        terrain.afficher();
        return 0;
    }
    else{
        
        int L = stoi(argv[1]);
        Terrain terrain;
        terrain.init(L, L);
        vector<Batiment> batimentAPlacer;
        srand (time(NULL));
        for(int i=0; i<L; i++){
            int largeur=2* sqrt( rand() % L + 1);  // 1 a L
            int hauteur=2* sqrt( rand() % L + 1);
            Batiment b(largeur,hauteur ,i);
            batimentAPlacer.push_back(b);
        }
        terrain.setBatimentAPlacer(batimentAPlacer);
        
        //Tri Aire
        
        terrain.init(terrain.getLargeur(), terrain.getHauteur());
        terrain.trier(tri::aire);
        cout <<"Résultat tri aire: "<<terrain.placerBatiments()<<endl;
        cout <<"\t ordre des batiments triés ";
        for (int i=0; i<terrain.batiments.size(); i++) std::cout << "\t"<<terrain.batiments[i].getNumero();
        //terrain.afficher();
        cout<<"\n"<<endl;
        
        //Tri encombrement
        cout <<"Résultat tri encombrement: ";
        terrain.init(terrain.getLargeur(), terrain.getHauteur());
        terrain.trier(tri::encombrement);
        cout <<terrain.placerBatiments()<<endl;
        cout <<"\t ordre des batiments triés ";
        for (int i=0; i<terrain.batiments.size(); i++) std::cout << "\t"<<terrain.batiments[i].getNumero();
        cout<<"\n"<<endl;
        //terrain.afficher();
        
        //Tri Aléatoire
        cout <<"Début de l'aléatoire: "<<endl; 
        int res =terrain.generer(1500);
        cout << "Résultat par génération aléatoire : " << res<<endl;
        terrain.afficher();
        
    }
    
    return 0;
}

