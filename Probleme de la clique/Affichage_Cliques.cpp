#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>
#include <chrono>
#include <unistd.h>


void combinationUtil(int arr[],int*matrice, int n,int k,int index,int data[],int i,int*cpt);

int verif_clique(int*matrice,int*s,int k,int n);

//**********************AFFICHAGE DES CLIQUES POSSIBLE DANS LE GRAPHS******************************************//
void Affichage_Cliques(int arr[],int*matrice, int n, int k)
{
	int data[k];
    int* cpt = (int*) malloc(sizeof(int));
    *cpt = 0;
	combinationUtil(arr,matrice, n, k, 0, data, 0,cpt);
    printf("\n Nombre total de clique de taille %d trouve dans le graph donne est: %d\n",k,*cpt);
}
//********************************************************************************************************************//

//**********************TROUVER LES COMBINAISONS POSSIBLE DANS LE GRAPHS******************************************//
void combinationUtil(int arr[], int*matrice, int n, int k, int index, int data[], int i, int*cpt)
{

	if (index == k)
	{
		if (verif_clique(matrice,data,k,n) == 1)
        {
            printf("La combinaison : ");
		    for (int j=0; j<k; j++)
            {
			    printf("%d ",data[j]);
            }
            printf("===> Une clique\n");
            *cpt = *cpt+1;
        }
        
		return;
	}

	if (i >= n)
		return;

	data[index] = arr[i];
	combinationUtil(arr,matrice, n, k, index+1, data, i+1,cpt);
	combinationUtil(arr, matrice,n, k, index, data, i+1,cpt);
}
//********************************************************************************************************************//

//**********************TROUVER LES CLIQUES POSSIBLE DANS LE GRAPHS******************************************//
int verif_clique(int*matrice,int*s,int k,int n)
{
    _Bool clique=1;
    int i=0,j;
    while(i<k-1 && clique==1)
    {
        j=i+1;
        while(j<k && clique==1)
        {
            if(matrice[s[i]*n+s[j]]==0)
            {
                clique=0;
            }
            else
            {
                j=j+1;
            }
        }
        i=i+1;
    }
    if(clique==1)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}
//********************************************************************************************************************//

//**********************PROGRAMME PRINCIPALE******************************************//
using namespace std;
int main()
{
    int* matrice,*sommets;
    int *s;
    int i,j, n,k,nbr_comb;
    srand(time(NULL));

//**********************TAILLE DE GRAPH + DECLARATION DE MATRICE D'ADJACENCE******************************************//
    do
    {
        printf("Quelles sont les dimensions de la matrice n*n? (n > 0)\n");
        printf("Donner n \n");
        scanf("%d", &n);
    }while(n <= 0);
    matrice = (int*)malloc(n*n*sizeof(int));
    sommets = (int*)malloc(n * sizeof(int));
//********************************************************************************************************************//

//**********************REMPLISSAGE DE TABLEAU CONTENANT TOUS LES SOMMETS DE GRAPH***************************************//
    for(i=0;i<n;i++)
    {
        sommets[i] = i;
    }
//********************************************************************************************************************//


//**********************REMPLISSAGE DE MATRICE D'ADJACENCE QUI REPRESENTE LE GRAPH****************************************//
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            matrice[i*n + j]=rand()%2;
        }
    }

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(matrice[i*n + j]==1)
            {
                matrice[j*n + i]=1;
            }
        }
    }
//********************************************************************************************************************//

//**********************AFFICHAGE DE MATRICE D'ADJACENCE QUI REPRESENTE LE GRAPH****************************************//

    printf("\n La matrice d'adjacence choisi par random est : \n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%d  ", matrice[i*n + j]);
        }
        printf("\n");
    }
//********************************************************************************************************************//

//**********************OBTENIR 'k' LE NOMBRE DE SOMMETS VOULU DE CLIQUE****************************************//
    do
    { 
        printf("Donner le nombre k pour verifier si il existe une k-clique (k < %d) \n",n);
        scanf("%d", &k);
    }while(k>n);
//********************************************************************************************************************//

//////////////////////CACUL TEMPS D'EXECUTION///////////////////////////////////////////
    printf("\n Les cliques de taille %d trouve dans le graph donne sont:\n");
    auto start = chrono::steady_clock::now();
    Affichage_Cliques(sommets,matrice, n, k);
    auto end = chrono::steady_clock::now();
//////////////////////CACUL TEMPS D'EXECUTION///////////////////////////////////////////
    system("pause");

//////////////////////TEMPS D'EXECUTION////////////////////////////////////////////////
    cout << "Temps D'execution en Nanosecondes: "
    << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
    << " ns" 
    << endl;
//////////////////////TEMPS D'EXECUTION////////////////////////////////////////////////
    system("pause");
    return 0;
//********************************************************************************************************************//

}

