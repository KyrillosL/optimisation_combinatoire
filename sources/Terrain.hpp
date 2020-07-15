#pragma once


#include <stdio.h>
#include <iostream>
#include <vector>
#include "Batiment.hpp"


enum tri{
    aire,
    encombrement,
    aleatoire
};


class Terrain{
public:
    Terrain();
    //Terrain(float _l, float _h);
    void setLargeur(float l);
    void setHauteur(float h);
    int getLargeur(){return largeur;}
    int getHauteur(){return hauteur;}
    void init(float l, float h);
    
    float placerBatiments();
    bool placerBatiment( Batiment &b);
    bool enConflitAvec(int ligne, int colonne, Batiment &batimentAPlacer, Batiment &batimentDejaPlace);
    bool incluDansLeTerrain(int ligne, int colonne, Batiment &batimentAPlacer, Batiment &batimentDejaPlace); 
    
    void trier(tri t);
    float generer(int nombre);
    void afficher(){std::cout <<"Affichage: \n"<<*this<<std::endl;}
    
    void ajouterBatiment(Batiment &b, int i, int j, int batimentNumber );
    void setBatimentAPlacer(std::vector<Batiment> &b){batimentsAPlacer=b;}
    
    friend std::ostream & operator << (std::ostream &out, const Terrain &t);
    std::vector<std::vector<int>> grille;
    std::vector<Batiment> batiments;
    std::vector<Batiment> batimentsAPlacer;
    
private:
    float largeur;
    float hauteur;

};
