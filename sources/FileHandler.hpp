#pragma once
#include "Batiment.hpp"
#include "Terrain.hpp"
#include <vector>

class FileHandler{
public:
    FileHandler( const std::string &pathToFile ){
        std::ifstream infile(pathToFile);
        std::cout << "fichier chargé: " <<infile.is_open()<<std::endl;
       
        //Terrain
        std::string line;
        std::getline(infile, line);
        std::istringstream iss(line);
        int hauteur, largeur;
        iss >> largeur >> hauteur;

        terrain.setLargeur(largeur);
        terrain.setHauteur(hauteur);
        terrain.init(largeur, hauteur); 
        
        std::getline(infile, line);
        
        iss.clear();
        iss.str(line);
        iss >> nbBatiments;
        std::cout <<"largeur "<< largeur << " hauteur "<<hauteur<< " nombre de batiments "<<nbBatiments<<std::endl;
        
        //Creation des batiments
        int compteur =1;
        while (std::getline(infile, line)){
            int bl,bh;
            std::istringstream iss(line);
            if (!(iss >> bl >> bh )) { break; } // error
            batiments.push_back( Batiment(bl,bh,compteur));
            compteur++;
        }
        
        //Affichage des batiments
        for (int i=0; i<batiments.size(); i++) std::cout << "\t"<<batiments[i];
        
    }
    
    Terrain getTerrain(){   return terrain;  }
    std::vector<Batiment> getBatiments(){ return batiments;}
    int getNbBatiments(){return nbBatiments;}
    
private:
    Terrain terrain;
    std::vector<Batiment> batiments;
    int nbBatiments;
    
};
    
    
