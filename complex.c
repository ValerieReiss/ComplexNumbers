#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define NL printf("\n")
#define ANZ 5

typedef struct			//Erstellung der komplexen Zahl
{
 double im;
 double re;
}complex;

void writefile(char *dateiname,int anzahl)	//Fkt,die in eine Datei n Zahlen schreibt
{
 FILE *f1;
 int i;
 complex zahl;
 f1 = fopen(dateiname,"w+");
 if(f1==NULL)  {fprintf(stderr,"ERROR 1");NL;exit(1);}
 for (i=0; i<ANZ; i++)
 {
  zahl.re = rand()%301-100/10.0;
  zahl.im = rand()%301-100/10.0;
  fprintf(f1,"%.1lf ",zahl.re);
  fprintf(f1,"%.1lf",zahl.im);
  fprintf(f1,"\n");
 }
 fclose(f1);
}

int count(char *dateiname)			//Fkt,die die Anzahl liest i.d.Dat liest
{
 FILE *f1;
 int i=0;
 complex zahl;
 f1 = fopen(dateiname,"r+");
 if(f1==NULL)  {fprintf(stderr,"ERROR 2");NL;exit(2);}
  while(1)
   { 
    fscanf(f1,"%lf",&zahl);
    if(feof(f1))break;
    i++;
   }
 fclose(f1);
 return i/2;
}

void feld_einlesen(char *dateiname,complex feld[]) //Fkt,die komplexe zahlen in ein feld liest
{
 FILE *f1;
 complex zahl;
 int i=0;
 f1 = fopen(dateiname,"r+");
 if(f1==NULL)	{fprintf(stderr,"ERROR 3");NL;exit(3);}
 while(1) 
  { 
   fscanf(f1,"%lf",&zahl.re);
   fscanf(f1,"%lf",&zahl.im);
   if(feof(f1))break;
   feld[i] = zahl; 
   i++;
  }
 fclose(f1);
}

double betrag(complex *z)			//Fkt die den Betrag ausrechnet
{
 double bet=0.0;
 bet += (z->re * z->re); 
 bet += (z->im * z->im);
 bet=sqrt(bet);
 return bet;
}

double arithmetik(complex feld[],int anzahl, double *abweich) 	//Fkt fuer arithmetische Mittel
{
 int i;
 double arith;
 for(i=0; i<anzahl; i++)		//arith ausrechnen
 {
  arith += feld[i].re;
 }
 arith /= anzahl;
 for(i=0; i<anzahl; i++)		//abweich ausrechnen
 {
  *abweich += (feld[i].re - arith)*(feld[i].re - arith);
 }
 *abweich /= anzahl;
 return arith;
}

int compare(const void *a, const void *b)
{
 if (*(double*)a > *(double *)b)
 	return 1;
 else if (*(double *)a < *(double *)b)
 	return -1;
 else 	return 0;
}

void sortieren(complex feld[],double winkel[],int anzahl)	//Fkt die das Feld der komplexen Zahlen sortiert
{
 //double *winkel =(double*)malloc(anzahl*sizeof(double));
 int i=0;
 for(i=0;i<anzahl;i++)
   {
    winkel[i] = atan(feld[i].im / feld[i].re)*(180/3.14);
   }
 qsort(winkel,anzahl,sizeof(double),compare);
 //for(i=0;i<anzahl;i++)
 //  {
 //   printf("%.2lf",winkel[i]);NL;
 //  }
}

void ausgabe(complex feld[],double winkelfeld[],int anzahl)         //Fkt,die ein Feld ausgibt
{
 int i;
 double abweich=0;
 printf("es gibt %d komplexe zahlen i.d.datei",anzahl);NL;   //erklaerung wieviele es gibt
 for(i=0; i<anzahl; i++)
    {
     printf("%.2lf + %.2lf i,|z|=%.2lf",feld[i].re,feld[i].im,betrag(feld+i));NL;
    }
 NL;printf("arithmetisches mittel : %.2lf",arithmetik(feld,anzahl,&abweich));NL;
 printf("standardabweichung : %.2lf",abweich);NL; //rückgabe v.2Parametern mit weiterem Parameter *abweich
 for(i=0;i<anzahl;i++)
  {
   printf("winkel %d : %.2lf",i,winkelfeld[i]);NL;
  }
}
		 


int main(int argc, char *argv[])		//main Funktion
{
 if (argc != 2)  {printf("Wrong entry! ERROR 2");NL;exit(1);}
 writefile(argv[1],ANZ);
 int anzahl = count(argv[1]);
 complex *zeiger = (complex*)malloc(anzahl*sizeof(complex)); //feld erzeugen im speicher mit complexen zahlen
 double *winkel =(double*)malloc(anzahl*sizeof(double));
 feld_einlesen(argv[1],zeiger);NL;
 //ausgabe(zeiger,winkel,anzahl);NL;
 sortieren(zeiger,winkel,anzahl);NL;   //sort(zeiger,anzahl,sizeof(complex),comp);NL;
 ausgabe(zeiger,winkel,anzahl);NL;
 return 0;
}








