#include<stdio.h>
#include<string.h>
#define WORDNUM 5	/*aradigimiz kelimelerin sayisi*/

int findH(char arr[], char word[]);/*yatay wordleri bulan fonksiyon, 
									parametre olarak 2  string alir,
									wordü bulamazsa 0 döndürür, 
									bulursa baslangic column indisini döndürür*/
int findV(char arr[][250], int size, char word[], int *indisi, int *indisj);/*dikey wordleri bulan fonksiyon,
																			  parametre olarak 2 boyutlu array, 
																			  bu arrayin satir sayisi, aranacak string,
																			  ve baslangic indisleri döndürebilmek icin
																			  2 int pointer alir,
																			  wordü bulursa 1 döndürür, 
																			  satir ve sutün baslangic indislerini 
																			  indisi ve indisj olarak döndürür*/

void main ()
{
	FILE *fp;
	char arr[100][250];
	char word[WORDNUM][9] = {"Xanthos", "Patara", "Myra", "Arycanda", "Phaselis"};
	int size = -1,  i=0, j = 0, k = WORDNUM+1;
	int status;
	int flagH, flagV;
	int indisi, indisj;
	
	fp = fopen("input.txt", "r");
	
	do/*input file' i iki boyutlu array olan arr' e aktariyoruz*/
	{
		
		size++;/*satir sayisi*/
		status = fscanf(fp, "%s", arr[size]);
	
	}while(status != EOF);
	
	for(i = 0; i < size; i++)/*FindH fonksiyonuna arr' imizin her bir satirini(string) gönderiyoruz*/
	{
		flagH = findH(arr[i], word[j]);/*FindH fonksiyonunun dönüs degeri 0 ise aranan word' ü bulamadik*/
	
		if(flagH != 0)
			printf("%s (%d,%d) Horizontal\n", word[j], i+1, flagH+1);/*dönüs degeri 0 degilse 
																		aranan kelime bulundu demektir 
																		ve FindH' in dönüs degeri o kelimenin column baslangic indisidir*/
		
		flagV = findV(arr, size, word[j], &indisi, &indisj);
		if(flagV == 1 && k != j)					/*findV fonksiyonunun dönüs degeri 1 ise word bulundu demektir.
									                  ilk giriste herhangi bir sorun cikmamasi 
													  icin k' nın ilk degerini NUMWORD+1 olarak belirledim*/
		{
			printf("%s (%d,%d) Vertical\n", word[j], indisi+1, indisj+1);	
			k = j;	/*k sayesinde ayni kelimeyi tekrar tekrar yazmasini engelleyecegiz*/
		}
		if(i == size-1 && j < WORDNUM)/*bu islem FİndH fonksiyonuna 
										her bir word'ü göndermemize yarayacak.*/
		{
			i=-1; j++;/*i' yi -1 yaptiktan hemen sonra for'un icinde i++ yapildigindan i 0 degerini alacaktir*/
		}
	}
}

int findH(char arr[], char word[])
{
   int i = 0, j = 0;
   int indis;
   while(arr[i] != '\0') 
	{

		while(arr[i] != word[0] && arr[i] != '\0')
			i++;
		
		if(arr[i] == '\0') /*eğer bir önceki if stamentdan, 
							arr bittigi icin ciktiysak word[0]' i bulamadik ve arama tamamlandi demektir*/
			return 0;
		
		indis = i; 	/*eğer ilk if stament' dan word[0]' a rastladigimiz için ciktiysak*/

        while(arr[i] == word[j] && arr[i] != '\0' && word[j] != '\0') 
		{
			i++; j++;
        }

        if (word[j] == '\0')/*eger bir önceki while aradigimiz word
							  end of string' e ulasana kadar döndüyse word' ün tamamini bulduk*/
			return indis;
      
	    else if (arr[i] == '\0')/*eger arr word' den önce bittiyse bulamadik ve arama tamamlandi demektir*/
			return 0;
		
		else if(arr[i] != word[j])/*eger arr[i], word[j]' ye esit olmadigi icin ciktiysak,
									bulamadik ama arama devam ediyor demektir.*/
		{
			i = indis + 1;	
			j = 0;
		}	
    }
}


int findV(char arr[][250],int size, char word[], int *indisi, int *indisj)
{
    int i = 0, j = 0, k = 0;
 
    while(i < size && j < strlen(arr[i])) 
	{
		while(arr[i][j] != word[0] && j < strlen(arr[i]))
		{
			j++;
			if(j == strlen(arr[i]))
			{
				j = 0; i++;
			}
		}	
	
		*indisi = i; 	
		*indisj = j;
		
        while(arr[i][j] == word[k] && i < size && word[k] != '\0') 
		{
			k++; i++;
        }

        if (word[k] == '\0')
			return 1;
      
	    else if (i == size)
			return 0;
		
		else if(arr[i][j] != word[k])
		{
			j = *indisj + 1;	
			k = 0;
		}	
   }
}