#ifndef Batiment_hpp
#define Batiment_hpp

#include <stdio.h>
#include <iostream>

class Batiment{
public:
    Batiment(float _l, float _h, int _numero):largeur(_l), hauteur(_h), numero(_numero){};
    void setLargeur(float l);
    void setHauteur(float h);
    int getLargeur(){return largeur;}
    int getHauteur(){return hauteur;}
    int getNumero(){return numero;}

    
    friend std::ostream & operator << (std::ostream &out, const Batiment &b);
    float pos_x=-1;
    float pos_y=-1;
private:
    float largeur;
    float hauteur;
    int numero;

    
};


#endif /* Batiment_hpp */
