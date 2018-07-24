
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;


int main(int argc, char const *argv[])
{

    //Variables que empleare junto con las Constantes que me da el enunciado 
    int n = 100;    
    int nt = 4000;  
    float c  = 300; 
    float L = 1;
	float delta_x = 0.01;
    float delta_t = (delta_x/c)*0.5;
    float tiempo_i = 0.0;
    float tiempo_final_x = (n) * (delta_t);
    float constante = 0.5;  //La condicion de estabilidad: lo de (c^2)*(delta^2)/(delta_x)^2

    /*Leo los datos de las posiciones iniciales de la posicion, para eso creo un arreglo y dentro de ese arreglo 
    incluyo todos los datos del archivo, para esto lo recorro y lleno sus posiciones. 
    */
    
    ifstream posiciones_iniciales;
    posiciones_iniciales.open("init.txt");  //ojo cambiar a dat solo que en mac no lo lee, toca txt
    float pos[10000]; //guardo los datos de init.dat en un arreglo de 10000
    int m = 0; //Contador para recorrer 

    while (!posiciones_iniciales.eof())

    {
        posiciones_iniciales >> pos[m]; 
        m++;
    }

    posiciones_iniciales.close();    
    
    //Los contadores que se utilizaran para poder llevar a cabo el metodo de diferencias finitas
	int i, j, k, g;  

    //Construyo los tres arreglos de 100 por 100 que necesito, teniendo en cuenta que son arreglos en 2D 
    float U_Pasado[n][n];
	float U_Presente[n][n];
	float U_Futuro[n][n];

    //CASO 1: Bordes de la membrana fijos durante todos los instantes de tiempo

    //Inicializo el arreglo del pasado
	k =0;
    for (i = 0; i < n; ++i)
	{
        for ( j=0; j < n;j++)

            {
                U_Pasado[i][j] = pos[k];
                k++;
            }
	}
	
    /*Inicializo los demas arreglos, teniendo en cuenta que el del presente se convierte en el pasado y el del fututo es es que se quiero hallar,
    a partir de los otros dos arreglos
    */
   
    for (i = 0; i < n; ++i)
	{
        for ( j=0; j < n; j++)

            {
                U_Presente[i][j] =  U_Pasado [i][j];
                U_Futuro[i][j] =0.0;
            }	
	}

    /* Hallo U futuro: En esta parte primero escribi el metodo de diferencias finitas en el papel, luego despeje u i,j ^n+1  (que es el U_Futuro),
    y  reemplace los arreglos U_Pasado y U_Presente, esto lo hice dentro de tres for  
    */
    tiempo_i= 0;
    for (g = 0; g < nt; ++g) //for para el tiempo, como esta el sistema en el futuro, bordes fijos 
    {
        for ( i=1; i < n-1; i++)  //en n-1 para no evaluar bordes debido a las condciones forntera 
        {
            for ( j=1; j < n-1; j++)
            {
                U_Futuro [i][j] = (constante*constante) * (U_Presente[i+1][j]-2*U_Presente[i][j]+U_Presente[i-1][j]) + (constante*constante) * (U_Presente[i][j+1]-2*U_Presente[i][j]+U_Presente[i][j-1]) + 2*U_Presente[i][j] - U_Pasado[i][j];  //Aqui reemplace lo que despeje de U_Futuro (de diferencias finitas) 
            }
        }
    //Ahora cambio la correspondencia de los arreglos, pues el U_Futuro se convierte en U_Presente y el U_Presente en U_Pasado

        tiempo_i= tiempo_i + delta_t; //Esto es para poder imprimir el tiempo
        cout << tiempo_i<< " "; 

        for ( i=1; i < n-1; i++) //El presente se llamara pasado por eso 2 for por 2D
        {
            for ( j=1; j < n-1; j++)
            {
                U_Pasado[i][j] = U_Presente[i][j];
                U_Presente[i][j] = U_Futuro[i][j];
                cout<< U_Pasado[i][j] <<" ";  //Para poder hacer la grafica, imprimo todos los datos de  la membrana como una linea   
            }
        }
    cout << endl;  //para terminar la linea 
    }

    //CASO 2: Bordes de la membrana libres (Outflow)

    // Inicializo el arreglos del pasado
	for (i = 0; i < n; ++i)
	{
        for ( j=0; j < n;j++)
            {
                U_Pasado[i][j] = pos[k];
            }
	}
	
    //Inicializo los demas arreglos  
    for (i = 0; i < n; ++i)
	{
        for ( j=0; j < n;j++)
            {
                U_Presente[i][j] =  U_Pasado [i][j];
                U_Futuro[i][j] =0.0;
            }	
	}
    // Hallo U futuro, el mismo proceso que para el CASO 1

    tiempo_i= 0;
    for (g = 0; g < nt; g++)
    {
        for ( i=1; i < n-1;i++)  
        {
            for ( j=1; j < n-1;j++)
            {
                U_Futuro [i][j] = (constante*constante)* (U_Presente[i+1][j]-2*U_Presente[i][j]+U_Presente[i-1][j]) + (constante*constante) *(U_Presente[i][j+1]-2*U_Presente[i][j]+U_Presente[i][j-1]) + 2*U_Presente[i][j] - U_Pasado[i][j];
            }
        }

        for ( i=1; i < n-1;i++)  //Como es extremo libre la derivada du/dx = 0, y al simplificar me queda que Ui+1 = Ui, por eso reasigno el valor de U_futuro a continuacion 
        {
            U_Futuro[i][0] = U_Futuro[i][1];  //porque la derivada en los bordes es cero, los nodos de los bordes deben tener el mismo valor del nodo anterior mas cercano 
            U_Futuro[i][n-1] = U_Futuro[i][n-2];
            U_Futuro[i][0] = U_Futuro[1][i];
            U_Futuro[n-1][i] = U_Futuro[n-2][i];
        }

        tiempo_i= tiempo_i + delta_t; //para que imprima el tiempo
        cout << tiempo_i<<" ";
        for ( i=1; i < n-1;i++)
        {
            for ( j=1; j < n-1;j++)
            {
                U_Pasado[i][j] = U_Presente[i][j];   //reasignar las posiciones
                U_Presente[i][j] = U_Futuro[i][j];

                cout<< U_Pasado[i][j] <<" ";  //Para poder hacer la grafica, toda la membrana como una linea   

            }
        }

    
    cout << endl;  //para terminar la linea 

    }
  


    return 0;
	

}





