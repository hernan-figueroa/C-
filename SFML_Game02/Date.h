#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

class Fecha{
    private:
        int dia, mes, anio;
    public:

        //setters
        bool setDia(int d){
            if(d>0 && d<=31){
                dia=d;
                return true;
            }else {
                cout<<"EL DIA INGRESADO NO ES VALIDO"<<endl;
                return false;
            }
        }
        bool setMes(int m){
            int vMes[12]={31,29,31,30,31,30,31,31,30,31,30,31};
            if(m>0 && m<=12){
                if(dia<=vMes[m-1]){
                    mes=m;
                    return true;
                }else{
                    cout<<"EL MES INGRESADO NO TIENE "<<dia<<" DIAS."<<endl;
                    return false;
                }
            }
            return false;
        }
        bool setAnio(int a){
            if(a>0 && a<=2021){
                if(esBisiesto(a)==false && dia==29 && mes==2){
                    cout<<"EL ANIO INGRESADO NO ES BISIESTO. FEBRERO TIENE 28 DIAS."<<endl;
                    return false;
                }else if(esFechaValida(dia,mes,a)){
                    anio=a;
                    return true;
                }else {
                    cout<<"LA FECHA INGRESADA NO PUEDE SER MAYOR A LA FECHA DE HOY"<<endl;
                    return false;
                }
            }
            return false;
        }

        //getters
        int getDia(){return dia;}
        int getMes(){return mes;}
        int getAnio(){return anio;}

        //methods
        bool Cargar(){
            int d,m,a;
            cout<<"DIA: ";
            cin>>d;
            if(!setDia(d))return false;
            cout<<"MES: ";
            cin>>m;
            if(!setMes(m))return false;
            cout<<"ANIO: ";
            cin>>a;
            if(!setAnio(a)){
             cout<<" LA FECHA INGRESADA ES INCORRECTA"<<endl;
             return false;
            }
            return true;
        }
        void Mostrar(){
            cout<<dia<<"/"<<mes<<"/"<<anio<<endl;
        }
        bool esBisiesto(int a){
            if(a%4==0){
                if(a%100==0){
                    if(a%400==0){
                        return true;
                    }else return false;
                }else return true;
            }else return false;
        }
        bool esFechaValida(int d, int m, int a){
            int diaActual,mesActual,anioActual;
            time_t tiempo;
            struct tm *tmPtr;
            tiempo = time(NULL);
            tmPtr = localtime(&tiempo);
            diaActual=tmPtr->tm_mday;
            mesActual=tmPtr->tm_mon+1;
            anioActual=1900+tmPtr->tm_year;

            if(a<anioActual){
                return true;
            }else if(a==anioActual){
                    if(m<mesActual){
                        return true;
                    }else if(m==mesActual && d<=diaActual)return true;
                    else return false;
            }else return false;

        }
};


#endif // DATE_H_INCLUDED
