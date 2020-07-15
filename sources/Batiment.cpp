using namespace std;
#include "Batiment.hpp"


std::ostream & operator << (ostream &out, const Batiment &b){
    cout << "Batiment "<< b.numero<< " L" <<b.largeur <<" H"<< b.hauteur<<endl;
    return out;
}
