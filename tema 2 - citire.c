//Badea Alina Ioana, grupa AB 312
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct locatie
{
	char numarLocatie[12];
	int x1;
	int y1; 
	int raza1; //coordonatele satelitului 0
	int x2;
	int y2; 
	int raza2; //coordonatele satelitului 1
	int x3;
	int y3;
	int raza3; //coordonatele satelitului 2
	int x;
	int y; //coordonatele locatiei
	struct locatie *ant; //ant = anterior
	struct locatie *urm; //urm = urmator
};

typedef struct locatie locatie;

locatie *primaLocatie, *aux1, *aux2; 
int INF = 9999; //costul drumurilor avariate

int citireLocatii(FILE *coordonate)
{
	int numarLocatii,i;
	char denumiriAuxiliare[100];
	coordonate = fopen("coordonate.in.txt","r");
	fscanf(coordonate,"%d",&numarLocatii); //citeste numarul de locatii	
	primaLocatie = (locatie *)malloc(sizeof(locatie));
	fscanf(coordonate,"%s",primaLocatie->numarLocatie);
	fscanf(coordonate,"%s",denumiriAuxiliare);
    fscanf(coordonate,"%d",&primaLocatie->x1);
	fscanf(coordonate,"%d",&primaLocatie->y1);
	fscanf(coordonate,"%d",&primaLocatie->raza1); //satelit0
	fscanf(coordonate,"%s",denumiriAuxiliare);
	fscanf(coordonate,"%d",&primaLocatie->x2);
	fscanf(coordonate,"%d",&primaLocatie->y2);
	fscanf(coordonate,"%d",&primaLocatie->raza2); //satelit1
	fscanf(coordonate,"%s",denumiriAuxiliare);
	fscanf(coordonate,"%d",&primaLocatie->x3);
	fscanf(coordonate,"%d",&primaLocatie->y3);
	fscanf(coordonate,"%d",&primaLocatie->raza3); //satelit2
	/*primaLocatie->x = NULL;
	primaLocatie->y = NULL; /*citeste prima locatie*/
    primaLocatie->ant = NULL;
    primaLocatie->urm = NULL;
    aux1 = primaLocatie;
    for(i = 1; i < numarLocatii; i++)
    {
        aux2 = (locatie *)malloc(sizeof(locatie));
        fscanf(coordonate,"%s",aux2->numarLocatie);
		fscanf(coordonate,"%s",denumiriAuxiliare);
    	fscanf(coordonate,"%d",&aux2->x1);
		fscanf(coordonate,"%d",&aux2->y1);
		fscanf(coordonate,"%d",&aux2->raza1); //satelit0
		fscanf(coordonate,"%s",denumiriAuxiliare);
		fscanf(coordonate,"%d",&aux2->x2);
		fscanf(coordonate,"%d",&aux2->y2);
		fscanf(coordonate,"%d",&aux2->raza2); //satelit1
		fscanf(coordonate,"%s",denumiriAuxiliare);
		fscanf(coordonate,"%d",&aux2->x3);
		fscanf(coordonate,"%d",&aux2->y3);
		fscanf(coordonate,"%d",&aux2->raza3); //satelit2
        /*aux2->x = NULL;
        aux2->y = NULL;*/
		aux2->urm = NULL;
        aux2->ant = aux1;
        aux1->urm = aux2;
        aux1 = aux2;
    }
	fclose(coordonate);
	return numarLocatii;
}

void coordonateLocatii(int numarLocatii)
{
	int x1, y1, R1, x2, y2, R2, x3, y3, R3, x, y;
	aux1 = primaLocatie;
	int i;
	for(i = 0; i < numarLocatii; i++)
	{
		x1 = aux1->x1;
		y1 = aux1->y1;
		R1 = aux1->raza1;
		x2 = aux1->x2;
		y2 = aux1->y2;
		R2 = aux1->raza2;
		x3 = aux1->x3;
		y3 = aux1->y3;
		R3 = aux1->raza3;
		aux1->y = ((x1-x3) * ((x1*x1 - x2*x2) + (y1*y1 - y2*y2) + (R2*R2 - R1*R1)) - (x1-x2) * ((x1*x1 - x3*x3) + (y1*y1 - y3*y3) + (R3*R3 - R1*R1))) / (2 * (y1-y2) * (x1-x3) - 2 * (x1-x2) * (y1-y3));
		aux1->x = ((x1*x1 - x2*x2) + (y1*y1 - y2*y2) + (R2*R2 - R1*R1) - 2 * (aux1->y) * (y1-y2)) / (2 * (x1-x2));
		aux1 = aux1->urm;
	}
}

void afisareCoordonate(FILE *coordonate_finale)
{
	coordonate_finale = fopen("coord_finale.out.txt","w");
	aux1 = primaLocatie;
	do
	{
		fprintf(coordonate_finale,"%d %d\n",aux1->x,aux1->y);
		aux1 = aux1->urm;
	}while(aux1 != NULL);
	fclose(coordonate_finale);
}

void creareMatriceAdiacenta(int matriceAdiacenta[250][250], int numarLocatii)
{
	int i, j;
	for(i = 0; i < numarLocatii; i++)
	{
		for(j = 0; j < numarLocatii; j++)
		{
			matriceAdiacenta[i][j] = 0;
		}
	}
}

void completareMatriceAdiacenta(int matriceAdiacenta[250][250], int numarLocatii)
{
	int i, j, x1, y1, x2, y2, distanta;
	for(i = 0, aux1 = primaLocatie; aux1->urm != NULL; aux1 = aux1->urm, i++)
	{
		for(j = i + 1, aux2 = aux1->urm; aux2 != NULL; aux2 = aux2->urm, j++)
		{
			x1 = aux1->x;
			y1 = aux1->y;
			x2 = aux2->x;
			y2 = aux2->y;
			distanta = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
			matriceAdiacenta[i][j] = distanta;
			matriceAdiacenta[j][i] = distanta;
		}
	}
}

void afisareMatriceAdiacenta(int matriceAdiacenta[250][250], int numarLocatii)
{
	int i, j;
	for(i = 0; i < numarLocatii; i++)
	{
		for(j = 0; j < numarLocatii; j++)
		{
			printf("%d ",matriceAdiacenta[i][j]);
		}
		printf("\n");
	}
}

void citireSiCompletareAvarii(int matriceAdiacenta[250][250], FILE *avarii)
{
	char avarie[12], eof;
	int i, j;
	avarii = fopen("avarii.in.txt","r");
	do
	{	
		i = 0;
		fscanf(avarii,"%s",avarie);
		fflush(stdin);
		aux1 = primaLocatie;
		while(strcmp(aux1->numarLocatie,avarie) != 0)
		{
			i++;
			aux1 = aux1->urm;
		}
		fflush(stdin);
		fscanf(avarii,"%s",avarie);
		j = 0;
		aux1 = primaLocatie;
		while(strcmp(aux1->numarLocatie,avarie) != 0)
		{
			j++;
			aux1 = aux1->urm;
		}
		matriceAdiacenta[i][j] = INF;
		matriceAdiacenta[j][i] = INF;
		eof = getc(avarii);
	}while(eof != EOF);
	fclose(avarii);
}

int dijsktra(int matriceAdiacenta[250][250],int startTraseu,int sfarsitTraseu, int numarLocatii)
{
    int distanta[250], anterior[250], selectat[250] = {0}, aux, min, start, d, i, j;
    //char traseu[250];
    for(i = 0; i < numarLocatii; i++)
    {
        distanta[i] = INF;
        anterior[i] = -1;
    }
    start = startTraseu;
    distanta[start] = 0;
    selectat[start] = 1;
    while(selectat[sfarsitTraseu] == 0)
    {
        min = INF;
        aux = 0;
        for(i = 0; i < numarLocatii; i++)
        {
            d = distanta[start] + matriceAdiacenta[start][i];
            if((d < distanta[i]) && (selectat[i] == 0))
            {
                distanta[i] = d;
                anterior[i] = start;
            }
            if((min > distanta[i]) && (selectat[i] == 0))
            {
                min = distanta[i];
                aux = i;
            }
        }
        start = aux;
        selectat[start] = 1;
    }
    start = sfarsitTraseu;
    j = 0;
    /*while(start != -1)
    {
        traseu[j++] = start + 65;
        start = anterior[start];
    }
    traseu[j]='\0';*/
    //strrev(traseu);
    return distanta[sfarsitTraseu];
}

void distantaMinima(int distanta, FILE *rezultate)
{
	rezultate = fopen("rezultat.out.txt","w");
	fprintf(rezultate,"%d",distanta);
	fclose(rezultate);
}

int main()
{
	FILE *coordonate, *avarii, *coordonate_finale, *rezultate; //fisierele de intrare si iesire
	int numarLocatii, distanta, startTraseu, sfarsitTraseu, matriceAdiacenta[250][250];
	char locatie[12];
	numarLocatii = citireLocatii(coordonate);
	coordonateLocatii(numarLocatii);
	afisareCoordonate(coordonate_finale);
	creareMatriceAdiacenta(matriceAdiacenta, numarLocatii);
	completareMatriceAdiacenta(matriceAdiacenta, numarLocatii);
	citireSiCompletareAvarii(matriceAdiacenta,avarii);
	//afisareMatriceAdiacenta(matriceAdiacenta, numarLocatii);
	startTraseu = 0;
	sfarsitTraseu = 0;
	printf("yeep");
	scanf("%s",locatie);
	printf("%s",locatie);
	aux1 = primaLocatie;
	printf("yep");
	while(strcmp(aux1->numarLocatie,locatie) != 0)
	{
		sfarsitTraseu++;
		aux1 = aux1->urm;
		printf("yeeep");
	}
	distanta = dijsktra(matriceAdiacenta, startTraseu, sfarsitTraseu, numarLocatii);
	distantaMinima(distanta, rezultate);
	return 0;
}
