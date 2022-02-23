#ifndef REGISTROPUNTAJE_H_INCLUDED
#define REGISTROPUNTAJE_H_INCLUDED

class RegistroPuntaje
{
private:
    char  nombre[40];
    int points;
public:

    bool grabarEnDisco()
    {
        FILE *score;
        score = fopen("PuntuacionMaxima.dat", "ab");
        if(score == NULL)
        {
            cout<<"NO SE PUDO CREAR EL ARCHIVO"<<endl;
            return false;
        }
        bool grabo = fwrite(this,sizeof (RegistroPuntaje), 1, score);
        fclose(score);
        return grabo;
    }

    bool leerDeDisco(int pos)
    {
        FILE *score;
        score = fopen("PuntuacionMaxima.dat", "rb");
        if(score == NULL)
        {
            cout<<"NO SE PUDO LEER EL ARCHIVO"<<endl;
            return false;
        }
        fseek(score,sizeof (RegistroPuntaje) * pos,0);
        bool leyo = fread(this, sizeof *this, 1, score);
        fclose(score);
        return leyo;
    }

    void setNombre(const char* name)
    {
        strcpy(nombre,name);
    }

    void setPoints(int p)
    {
        points = p;
    }

    int getPoints()
    {
        return points;
    }

    char *getNombre()
    {
        return nombre;
    }


};


#endif // REGISTROPUNTAJE_H_INCLUDED
