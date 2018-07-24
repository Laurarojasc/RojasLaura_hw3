import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import matplotlib.pyplot as plt

#Graficas de la trayectoria de una particula en cargada en un campo magenetico dado

#Leo los datos de RojasLaura_ODE.cpp, para esto genere un archivo datos.txt

x = np.genfromtxt("datos.txt",usecols=0)
y = np.genfromtxt("datos.txt",usecols=1)
z = np.genfromtxt("datos.txt",usecols=2)
t = np.genfromtxt("datos.txt",usecols=3)

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

datos = np.genfromtxt("init.txt")

# Generar los valores x,y
x = np.linspace(0,1,100)  #crear 100 valores de x 
X,Y = np.meshgrid(x,x)  #valores de x y y ordenados 
 
 
#1. Grafica 3D de condiciones iniciales
fig = plt.figure()
ax = fig.gca(projection="3d")
ax.plot_surface(X, Y, datos)
plt.title("Condiciones iniciales (en t0)")
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("z")
fig.savefig("Condiciones_iniciales.png")
#plt.show()


#2. Grafica en 3D de la membrana en t=60ms, para esto genere un archivo de datos2.txt donde esten todos los tiempos y datos para el caso 1 y caso 2

datos2 = np.genfromtxt("datos2.txt")

#Para extremos fijos

filas = np.size(datos2,0)

fijos = datos2[0:int(filas/2),:] #Meto todos los datos del caso 1 en una matriz 

m = np.reshape(fijos[3600,:], (n,n)) #matematicamente clacule la linea que debo buscar donde estan los 60ms
fig = plt.figure()
ax = fig.gca(projection="3d")
ax.plot_surface(X, Y, m)
plt.title("Membrana extremos fijos para t = 60ms")
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("z")
fig.savefig("membrana_fijos_60ms.png")


#Para extremos libres

libres = datos2[int(filas/2):,:] #Meto todos los datos del caso 2 en una matriz 

tiempo = libres[:,0] #La Primera columna es el tiempo
libres = libres[:,1:] #Boto la columna del tiempo para libres 
n = 100 # Tamano de datos en la membrana para reordenar los arreglos, pues deben ser del mismo tamano
 
# generar los valores x,y
x = np.linspace(0,1,n)
X,Y = np.meshgrid(x,x)
 
# Grafica de condiciones iniciales
m = np.reshape(libres[3600,:], (n,n)) #matematicamente clacule la linea que debo buscar donde estan los 60ms
fig = plt.figure()
ax = fig.gca(projection="3d")
ax.plot_surface(X, Y, m)
plt.title("Membrana extremos libres para t = 60ms")
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("z")
fig.savefig("membrana_libres_60ms.png")




 

# 3. Grafica de cortes transversales en x=L/2 cada 10 pasos de tiempo, para extremos fijos (Caso1)

pasos = 10 # Cada dos pasos de tiempo para este ejemplo
col = fijos[0:-1:pt, :] # start:stop:step en las filas, selecciono todas las columnas
n_pasos = np.size(col, 0)
 
fig = plt.figure()
ax = fig.gca()

for i in range(n_pasos):
    x = np.reshape(col[i,:], (n,n)) # Seleccionar el instante de tiempo y reformar el arreglo
    mitad = x[int(n/2),:] # Seleccionar la linea de la mitad
 
    ax.plot(x, mitad, "o-")
ax.grid()
plt.xlabel("x")
plt.ylabel("Amplitud")
fig.savefig("membrana_corte_fijos.png")



#Grafica de cortes transversales en x=L/2 cada 10 pasos de tiempo, para extremos libres (Caso2)

pasos = 10 
col = libres[0:-1:pt, :] # Selecciono todas las columnas, teniendo en cuenta que inicio:final:step en las filas
n_pasos = np.size(col, 0)
 
fig = plt.figure()
ax = fig.gca()
for i in range(n_pasos):
            
    x = np.reshape(col[i,:], (n,n)) # Aqui elijo el instante de tiempo y cambio el arreglo
    mitad = x[int(n/2),:] # elegir la linea de la mitad
 
    ax.plot(x, mitad, "o-")
ax.grid()
plt.xlabel("x")
plt.ylabel("Amplitud")
fig.savefig("membrana_corte_libres.png")


# Animacion (Intento de Bono, si me funciono pero es lento)

             
#figura = plt.figure()
#ax = fig.gca(projection="3d")
            
#tiempo = datos2[:,0]


#def Animacion(i):
#    ax.cla() # Limpiar el eje
#    x = np.reshape(tiempo[i,:], (n,n)) # Reordenar los datos del instante de tiempo a graficar
#    ax.plot_surface(X, Y, x)
 
#    plt.title("Membrana")
#    ax.set_xlabel("x")
#    ax.set_ylabel("y")
#    ax.set_zlabel("z")
#    ax.set_zlim([-1,1])
 
#animacion = FuncAnimation(fig, Animacion, frames = 10) #solo 10 para que no sea tan lento
#anim.save("Animacion_membrana.gif', writer="imagemagick", fps=2)


















