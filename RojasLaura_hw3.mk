

all: RojasLaura_Resultados_hw3.pdf

RojasLaura_Resultados_hw3.pdf: xcontray.png xcontraz.png ycontrat.png posicion.png Condiciones_iniciales.png membrana_fijos_60ms.png membrana_libres_60ms.png membrana_corte_fijos.png membrana_corte_libres.png
	pdflatex RojasLaura_Resultados.tex

xcontray.png xcontraz.png ycontrat.png posicion.png Condiciones_iniciales.png membrana_fijos_60ms.png membrana_libres_60ms.png membrana_corte_fijos.png membrana_corte_libres.png : datos.dat datos2.dat
	python Plots_hw3.py

datos.txt: RojasLaura_ODE.cpp
	g++ RojasLaura_ODE.cpp
	./a.out RojasLaura_ODE.cpp> datos.dat

datos2.txt: RojasLaura_PDE.cpp
	g++ RojasLaura_PDE.cpp
	./a.out RojasLaura_PDE.cpp> datos2.dat
