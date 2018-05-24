#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

FILE * out;

void createOutFile()
{
	out = fopen ("salida.tex", "w");
}

void writeHeader()
{
	fprintf(out,"\\documentclass[12]{beamer}\n");
  fprintf(out,"\\usetheme{Oxygen}\n");
	fprintf(out,"\\hypersetup{pdfpagemode=FullScreen}\n");
	fprintf(out,"\\usepackage{thumbpdf}\n");
	fprintf(out,"\\usepackage{wasysym}\n");
	fprintf(out,"\\usepackage{adjustbox}\n");
	fprintf(out,"\\usepackage{color, colortbl}\n");
	fprintf(out,"\\usepackage{ucs}\n");
	fprintf(out,"\\usepackage[utf8]{inputenc}\n");
	fprintf(out,"\\title{Project 04 - Simplex}\n");
	fprintf(out,"\\subtitle{Operations Research}\n");
	fprintf(out,"\\author{Luis Diego Vargas Arroyo - Carlos Villalobos Mora}\n\n");
	fprintf(out,"\\begin{document}\n");
	fprintf(out,"\\frame{\\titlepage}\n");
}

void makeBeamer()
{
	createOutFile();
	writeHeader();
}

void closeFile()
{
	fprintf(out,"\\end{document}\n");
	fclose(out);
}


void slideMatematico(double items_value[], int len, int verb){
	
	fprintf(out,"\\begin{frame}\n");
	fprintf(out,"\\frametitle{Forma Matemática}\n\n");
	if(verb==0){

		fprintf(out,"Maximizar: \n");
	}else{
		fprintf(out,"Minimizar: \n");
	}
	fprintf(out,"\\begin{center}\n");
	fprintf(out,"\\[ ");
	for (int i=0; i < len; i++) {
		if(i!=len-1){
			if(i==5){

				fprintf(out," \\] \n \\newline \\[ \n");
			}
			fprintf(out,"  %.3g  x_{%d} + ",items_value[i],i+1);
		}else{
			if(i==5){

				fprintf(out,"\\] \n \\[ \\newline\n");
			}
			fprintf(out,"  %.3g  x_{%d} ",items_value[i],i+1);
		}
	}
	fprintf(out,"\\] \n");
	fprintf(out, "\\end{center}\n\n");
	fprintf(out,"\\end{frame}\n");
}

void slideRestricciones(double items_value[13][13],int restricciones[], int selectlen, int selectRes){
	
	fprintf(out,"\\begin{frame}\n");
	fprintf(out,"\\frametitle{Restricciones}\n\n");
	
	fprintf(out,"\\begin{center}\n");
	fprintf(out,"\\tiny\n");
	fprintf(out,"\\[ ");
	for (int i=1 ; i < selectRes +1 ; i++) {
		for(int j= 0; j < selectlen + 2;  j++){
			if(j == selectlen){
				if(restricciones[i] == 0){

					fprintf(out, "  =  ");
				}else if(restricciones[i] == 1) {
					fprintf(out, "  <=  ");

				}else{
					fprintf(out, "  >=  ");
				}

			}else{
				if(j == selectlen + 1 ){
					fprintf(out,"  %.3g  ",items_value[i][j]);
					
				}else if(j!=selectlen-1){
					fprintf(out,"  %.3g  x_{%d} + ",items_value[i][j],j+1);

					

				}else{
			
					fprintf(out,"  %.3g  x_{%d} ",items_value[i][j],j+1);

				}

			}	

		}
		if(i == selectRes ){
			fprintf(out,"\\] \n  \\newline\n ");
		}else{
			fprintf(out,"\\] \n  \\[ \\newline\n ");
		}
	}
	
	fprintf(out, "\\end{center}\n\n");
	fprintf(out,"\\end{frame}\n");
}

void showBeamer()
{
	closeFile();
	system("pdflatex salida.tex");
	system("evince  salida.pdf");
}
