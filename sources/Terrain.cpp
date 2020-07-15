//
//  Terrain.cpp
//  OptimisationCombinatoire
//
//  Created by Cyril_Musique on 20/04/2019.
//  Copyright © 2019 Cyril_Musique. All rights reserved.
//

#include "Terrain.hpp"

using namespace std;


//Terrain::Terrain (float _l, float _h) : largeur(_l), hauteur(_h){
Terrain::Terrain(){}

void Terrain::init(float _l, float _h){
    batiments.clear();
    grille.clear();
    setHauteur(_h);
    setLargeur(_l);
    for (int x=0; x<largeur;x++){
        vector<int> temp;
        for (int y=0; y<largeur;y++){
            temp.push_back(0);
        }
        grille.push_back(temp);
        
    }
}

void Terrain::setLargeur(float l){
    largeur=l;
}
void Terrain::setHauteur(float h){
    hauteur=h; 
    
}

void Terrain::ajouterBatiment(Batiment &b, int i, int j, int batimentNumber ){
    batiments.push_back(b);
    //On update la grille d'affichage
    for (int k=i; k<b.getHauteur()+i; k++){
        for (int l=j; l<b.getLargeur()+j; l++){
            grille[k][l] = batimentNumber;
        }
    }
}


float Terrain::placerBatiments(){
    
    if (batimentsAPlacer.size()==0){
        std::cout <<"Aucun batiment à placer !"<<std::endl;
    }
    else{
        float aireTotale=0;
        for (int numBat=0; numBat<batimentsAPlacer.size(); numBat++){
            //cout <<"\tBATIMENT: "<< numBat+1 << endl;
            if (placerBatiment(batimentsAPlacer[numBat])){
                //cout <<(batimentsAPlacer[numBat].getHauteur()*batimentsAPlacer[numBat].getLargeur())<<" " ;
                aireTotale+=  batimentsAPlacer[numBat].getHauteur() *batimentsAPlacer[numBat].getLargeur()  ;
            }
        }
        return aireTotale;
        //Tous les batiments ont ils étés placés ?
        ///if (batiments.size() == batimentsAPlacer.size()) cout <<"J'ai placé tous les batiments"<<endl;
        //else cout <<"Je n'ai pas placé tous les batiments"<<endl;
    }
    return 0;
}

bool Terrain::placerBatiment( Batiment &b){
    for (int ligne=0; ligne<getLargeur(); ligne++){
        for (int colonne=0; colonne<getHauteur(); colonne++){
            if ( grille[ligne][colonne] == 0){//JE PEUX TESTER LE PLACEMENT, CASE VIDE
                bool jePeuxPlacer = true;
                for (int bi=0; bi<batiments.size(); bi++){
                    if (enConflitAvec(ligne,colonne,b, batiments[bi])){
                        jePeuxPlacer=false;
                    }
                }
                if (jePeuxPlacer){
                    //cout <<"\tje place sur la grille: "<<ligne<<colonne<<endl;
                    //On ajoute le batiment au terrain
                    b.pos_x=colonne;
                    b.pos_y=ligne;
                    ajouterBatiment(b, ligne, colonne, b.getNumero());
                    //cout <<*this << "\n"<<endl;
                    return true;
                }
                
            }
            
        }
    }
    return false;
}

bool Terrain::enConflitAvec(int ligne, int colonne, Batiment &batimentAPlacer, Batiment &batimentDejaPlace){
    //Point de départ > à l'autre batiment
    if ( (colonne > batimentDejaPlace.pos_x+batimentDejaPlace.getLargeur()-1 ||  ligne > batimentDejaPlace.pos_y+batimentDejaPlace.getHauteur()-1) ) {

        return !incluDansLeTerrain(ligne,colonne,batimentAPlacer, batimentDejaPlace);
    }
    //Extrémité inférieure droite < à l'autre batiment
    if ( (colonne+batimentAPlacer.getLargeur()-1 < batimentDejaPlace.pos_x ||  batimentAPlacer.getHauteur()-1+ligne < batimentDejaPlace.pos_y) ) {
        return !incluDansLeTerrain(ligne,colonne,batimentAPlacer, batimentDejaPlace);
    }
    return true;
}

bool Terrain::incluDansLeTerrain(int ligne, int colonne, Batiment &batimentAPlacer, Batiment &batimentDejaPlace ){
    return  ( batimentAPlacer.getLargeur()+colonne<=getLargeur() && batimentAPlacer.getHauteur()+ligne <=getHauteur()  );
    
}

bool compareEspace(Batiment b1, Batiment b2){
    float aireB1 = b1.getHauteur()*b1.getLargeur();
    float aireB2 = b2.getHauteur()*b2.getLargeur();
    return (aireB1 > aireB2);
}

bool compareEncombrement(Batiment b1, Batiment b2){
    float encombrement1 = b1.getHauteur()+b1.getLargeur();
    float encombrement2 = b2.getHauteur()+b2.getLargeur();
    return (encombrement1 > encombrement2);
}

bool compareAleatoire(Batiment b1, Batiment b2){
    float aireB1 = b1.getHauteur()+b1.getLargeur();
    float aireB2 = b2.getHauteur()+b2.getLargeur();
    return (aireB1 > aireB2);
}

void Terrain::trier(tri t){
    switch (t) {
        case aire:
            sort(batimentsAPlacer.begin(), batimentsAPlacer.end(), compareEspace);
            break;
        case encombrement:
            sort(batimentsAPlacer.begin(), batimentsAPlacer.end(), compareEncombrement);
            break;
        case aleatoire:
            std::random_shuffle ( batimentsAPlacer.begin(), batimentsAPlacer.end() );
            break;
        default:
            break;
    }
    
}

float Terrain::generer(int nombre){
    std::cout <<"\tGénération de "<<nombre << " ordres aléatoires "<<endl;
    std::vector<Batiment> meilleurSolution;
    float resultatPlacementBatiments=0;
    for (int i=0; i<nombre; i++){
        init(largeur,hauteur);
        trier(tri::aleatoire);
        float resultatPlacementActuel =placerBatiments();
        if ( resultatPlacementActuel >= resultatPlacementBatiments ){
            resultatPlacementBatiments=resultatPlacementActuel;
            meilleurSolution=batiments;
        }
    }
    //Affichage des batiments
    std::cout <<"\tmeilleur solution (numéro de batiment trié dans l'ordre) : ";
    for (int i=0; i<batiments.size(); i++) std::cout << "\t"<<batiments[i].getNumero();
    cout<<endl;
    batiments= meilleurSolution;
    return resultatPlacementBatiments;
}

std::ostream & operator << (ostream &out, const Terrain &t){
    int nombreMax = std::to_string(t.batiments.size()).length();
    
    for (int x=0; x<t.largeur;x++){
        cout << "\t\t";
   
        for (int y=0; y<t.hauteur;y++){

            cout << t.grille[x][y]<<" ";
            for (int i=0; i< nombreMax - std::to_string(t.grille[x][y]).length(); i++)
                cout <<" ";
        }
        cout<<endl; 
    }
    return out;
}

