import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import matplotlib.pyplot as plt

#Graficas de la trayectoria de una particula en cargada en un campo magenetico dado

#Leo los datos de RojasLaura_ODE.cpp, para esto genere un archivo datos.dat

x = np.genfromtxt("datos.dat",usecols=0)
y = np.genfromtxt("datos.dat",usecols=1)
z = np.genfromtxt("datos.dat",usecols=2)
t = np.genfromtxt("datos.dat",usecols=3)

#1. Graficas de x-t, x-z , y-t  

plt.figure()
plt.plot(x,y, color = "red")
plt.title("Grafica de x contra y")
plt.savefig("xcontray.png")
#plt.show()

plt.figure()
plt.plot(x,z, color = "magenta")
plt.title("Grafica de x contra z")
plt.savefig("xcontraz.png")
#plt.show()

plt.figure()
plt.plot(t,y, color = "blue")
plt.title("Grafica de x contra t")
plt.savefig("ycontrat.png")
#plt.show()


#2. Grafica en 3D de la posicion para todos los tiempos

fig = plt.figure()
ax = fig.gca(projection="3d")
ax.plot(x, y, z, label="Posicion para todos los tiempos", color = "magenta")
mpl.rcParams["legend.fontsize"] = 20
ax.legend()
plt.savefig("posicion.png")
#plt.show()


#Graficas para la membrana del Tambor

# Leo los datos de RojasLaura_PDE.cpp

datos = np.genfromtxt("init.dat")

# Generar los valores x,y
x = np.linspace(0,1,100)  #crear 100 valores de x 
X,Y = np.meshgrid(x,x)  #valores de x y y ordenados 
 
 
#1. Grafica 3D de condiciones iniciales

fig = plt.figure()
ax = fig.gca(projection="3d")
ax.plot_surface(X, Y, datos)
plt.title("Condiciones iniciales")
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("z")
fig.savefig("Condiciones_iniciales.png")
#plt.show()


#2. Grafica en 3D de la membrana en t=60ms, para esto genere un archivo de datos2.txt donde esten todos los tiempos y datos para el caso 1 y caso 2

datos2 = np.genfromtxt("datos2.dat")

#Para extremos fijos

filas_size = np.size(datos2,0) #Aqui saco el tamano de los datos, la idea es que la mitad correspoden al caso 1 y la otra al caso 2 


fijos = datos2[0:int(filas_size/2),:] #Meto todos los datos del caso 1 en un arreglo
tiempo = fijos[:,0] #Escojo la primera columna del arrgelo que cree anteriormente, pues esta corresponde al tiempo
fijos = fijos[:,1:] # No utilizo la columna del tiempo del arreglo fijos 

m = np.reshape(fijos[5,:], (100,100)) #matematicamente clacule la linea que debo buscar donde estan los 60ms
fig = plt.figure()
ax = fig.gca(projection="3d")
ax.plot_surface(X, Y, m)
plt.title("Membrana extremos fijos para t = 60ms")
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("z")
fig.savefig("membrana_fijos_60ms.png")


#Para extremos libres 

libres = datos2[int(filas_size/2)+1:-1,:] #Meto todos los datos del caso 2 en un arreglo, cambia porque elijo los datos del caso 2 
tiempo = libres[:,0] #La Primera columna es el tiempo
libres = libres[:,1:] #Boto la columna del tiempo para libres 
 
# Grafica de condiciones iniciales
m = np.reshape(libres[5,:], (100,100)) #matematicamente clacule la linea que debo buscar donde estan los 60ms
fig = plt.figure()
ax = fig.gca(projection="3d")
ax.plot_surface(X, Y, m)
plt.title("Membrana extremos libres para t = 60ms")
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("z")
fig.savefig("membrana_libres_60ms.png")

 
# 3. Grafica de cortes transversales en x=L/2 cada 100 pasos de tiempo, para extremos fijos (Caso1)

pasos = 100 # Cada 100 pasos 
Columnas = fijos[0:-1:pasos, :] # Selecciono todas las columnas con: inicio:final:step en las filas
pasos_n = np.size(Columnas, 0)
 
fig = plt.figure()
ax = fig.gca()

for i in range(pasos_n):
    x = np.reshape(Columnas[i,:], (100,100)) # Aqui elijo el tiempo y cambio el arreglo
    mitad = x[int(100/2),:] # Seleccionar la linea de la mitad porque tengo todos los datos y asumo que la mitad corresponden al caso 1 
 
    ax.plot(x, mitad, ".-")
    
ax.grid()
plt.xlabel("x")
plt.ylabel("Pasos de tiempo")
fig.savefig("membrana_corte_fijos.png")



#Grafica de cortes transversales en x=L/2 cada 10 pasos de tiempo, para extremos libres (Caso2)

pasos = 100
Columnas = libres[0:-1:pasos, :] # Selecciono todas las columnas con: inicio:final:step en las filas
pasos_n = np.size(Columnas, 0)
 
fig = plt.figure()
ax = fig.gca()
for i in range(pasos_n):
            
    x = np.reshape(Columnas[i,:], (100,100)) # Aqui elijo el tiempo y cambio el arreglo
    mitad = x[int(100/2),:] # elegir la linea de la mitad
 
    ax.plot(x, mitad, ".-")
ax.grid()
plt.xlabel("x")
plt.ylabel("Pasos de tiempo")
fig.savefig("membrana_corte_libres.png")





























