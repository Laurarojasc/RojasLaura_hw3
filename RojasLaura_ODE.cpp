#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

//Trayectoria de una particula en cargada en un campo magenetico dado 

int main(int argc, char const *argv[])
{
    //Creo las variables de los valores iniciales que me da el enunciado, y las variables que voy a emplear para llevar a cabo el metodo de Runge_Kutta 
    int nt = 1000;
    float dt = 0.01;
    float t = 0.0;
    float q = 1.5;
    float m = 2.5;
    
    //El campo magnetico B solo existe en la componente z, por ende solo se tendran fuerzas en x y y
    float Bx = 0.0;
    float By = 0.0;
    float Bz = 3.0; 

    //Velocidades en x,y,z (dato que me dan)
    float Vx[nt]; 
    float Vy[nt];
    float Vz[nt];
    Vx[0] = 0.0;
    Vy[0] = 1.0;
    Vz[0] = 2.0; 

    //Condiciones iniciales para la posicion en x,y,z
    float x[nt];    
    float y[nt];
    float z[nt];
    x[0] = 1.0;
    y[0] = 0.0;
    z[0] = 0.0;

    //Variables que empleare para el metodo de Runge_Kutta de 4rto orden
    float K1x, K2x,K3x,K4x;
    float K1y,K2y,K3y,K4y;
    float K1z,K2z,K3z,K4z;

    float K1Vx, K2Vx,K3Vx,K4Vx;
    float K1Vy, K2Vy,K3Vy,K4Vy;
    float K1Vz, K2Vz,K3Vz,K4Vz;

    int i; 
    for ( i = 0; i < nt; ++i)    
    /* Al realizar los calculos  para hallar las fuerzas en x,y,z  me quedaron tres ecuaciones diferenciales de segundo orden x,y,z
    estas se pueden dividir en dos ecuaciones de primer orden, de manera que me queda un total de seis ecuaciones de primer orden por resolver 
    la primera: dx/dt = q/m(producto cruz) lo mismo para y,z
    la segunda: dx/dt = v lo mismo para y,z
    Ahora, para resolver las estas ecuaciones utilice el metodo de Runge_Kutta, donde me guie de la formula 
    Resuelvo las ecuaciones de manera simultanea  porque necesito una para crear la otra


    //Calcular la trayecotria de la particula en funcion del tiempo mediante el metodo de Runge_Kutta
    */ 

    {
        
        //Hallo los K1 del Runge_Kutta para las posiciones y para las velocidades 
        K1x = Vx[i];
        K1y = Vy[i];
        K1z = Vz[i];
        K1Vx = q/m*(Vy[i]*Bz - Vz[i]*By) ;    //Producto cruz: de v y B (la velocidad y el campo magenetico) la velocidad en la posicion i 
        K1Vy = -q/m*(Vx[i]*Bz - Vz[i]*Bx);
        K1Vz = q/m*(Vx[i]*By - Vy[i]*Bx);

        //Hallo los K2 del Runge_Kutta para las posiciones y para las velocidades 
        K2x = K1x + (0.5*dt*K1Vx);   //Aplico la formula para K2 
        K2y = K1y + (0.5*dt*K1Vy);
        K2z = K1z + (0.5*dt*K1Vz);
        K2Vx = q/m*( (Vy[i]+0.5*dt*K1Vy)*Bz -  (Vz[i]+0.5*K1Vz*dt)*By); //De nuevo producto cruz pero cambia
        K2Vy = -q/m*( (Vx[i]+0.5*dt*K1Vx)*Bz - (Vz[i]+0.5*K1Vz*dt)*Bx);
        K3Vz = q/m*( (Vx[i]+0.5*dt*K1Vx)*By -  (Vy[i]+0.5*K1Vy*dt)*Bx);

        //Hallo los K3 del Runge_Kutta para las posiciones y para las velocidades 
        K3x = K1x + (0.5*dt*K2Vx);
        K3y = K1y + (0.5*dt*K2Vy);
        K3z = K1z + (0.5*dt*K3Vz);
        K3Vx = q/m*( (Vy[i]+0.5*dt*K2Vy)*Bz -  (Vz[i]+0.5*K3Vz*dt)*By);
        K3Vy = -q/m*( (Vx[i]+0.5*dt*K2Vx)*Bz -  (Vz[i]+0.5*K3Vz*dt)*Bx);
        K3Vz = q/m*( (Vx[i]+0.5*dt*K2Vx)*By -  (Vy[i]+0.5*K2Vy*dt)*Bx);

        //Hallo los K4 del Runge_Kutta para las posiciones y para las velocidades 
        K4x = K1x + K3Vx*dt;
        K4y = K1y + K3Vy*dt;
        K4z = K1z + K3Vz*dt;
        K4Vx = q/m*( (Vy[i]+dt*K3Vy)*Bz -  (Vz[i]+dt*K3Vz)*By);
        K4Vy = -q/m*( (Vx[i]+dt*K3Vx)*Bz - (Vz[i]+K3Vz*dt)*Bx);
        K4Vz = q/m*( (Vx[i]+dt*K3Vx)*By -  (Vy[i]+K3Vy*dt)*Bx);

        //Sumo los K hallados anteriormente (es basicamente aplicar la formula general de Runge_Kuta 4orden)
        //Para las posicines y para las velocidades en x,y,z
        y[i+1] = y[i] + (1.0/6.0)*dt*(K1y + 2*K2y +2*K3y + K4y);        
        x[i+1] = x[i] + (1.0/6.0)*dt*(K1x + 2*K2x +2*K3x + K4x);
        z[i+1] = z[i] + (1.0/6.0)*dt*(K1z + 2*K2z +2*K3z + K4z);

        Vx[i+1] = Vx[i] + (1.0/6.0)*dt*(K1Vx + 2*K2Vx +2*K3Vx + K4Vx);
        Vy[i+1] = Vy[i] + (1.0/6.0)*dt*(K1Vy + 2*K2Vy +2*K3Vy + K4Vy);
        Vz[i+1] = Vz[i] + (1.0/6.0)*dt*(K1Vz + 2*K3Vz +2*K3Vz + K4Vz);

        t = t+dt;  //Para poder hacer la grafica

        cout<< x[i]<<" "<< y[i] << " " << z[i] << " " <<t << endl;

        

    }

    return 0; 



    










}




