#ifndef REGISTROJUGADOR_H_INCLUDED
#define REGISTROJUGADOR_H_INCLUDED

class RegistroJugador{
private:
    int idJugador;
    char nombre[30];
    int puntos;
    Fecha fecha;

public:
    ///setter
    void setIdJugadorr(int idJugador){this->idJugador=idJugador;}
    void setNombre(char *nombre){strcpy(this->nombre,nombre);}
    void setPuntos(int puntos){this->puntos=puntos;}
    void setFecha(Fecha fecha){this->fecha=fecha;}
    ///getter
    int getIdJugador(){return idJugador;}
    char *getNombre(){return nombre;}
    int getPuntos(){return puntos;}
    Fecha getFecha(){return fecha;}

    bool leerDeDisco(int pos){
    bool leyo;
    FILE *p;
    p=fopen("registroJugadores.dat","rb");
    if(p==NULL) return false;
    fseek(p,sizeof(RegistroJugador)*pos,0);
    leyo=fread(this,sizeof(RegistroJugador),1,p);
    fclose(p);
    return leyo;
    }

    bool grabarEnDisco(){
    FILE *p;
    bool grabo;
    p=fopen("registroJugadores.dat","ab");
    if(p==NULL) return false;
    grabo=fwrite(this,sizeof(RegistroJugador),1,p);
    fclose(p);
    return grabo;
    }

};

#endif // REGISTROJUGADOR_H_INCLUDED
