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

void showBeamer()
{
	closeFile();
	system("pdflatex salida.tex");
	system("evince  salida.pdf");
}
