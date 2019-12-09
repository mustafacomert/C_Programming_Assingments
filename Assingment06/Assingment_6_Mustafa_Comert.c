#include<stdio.h>
#include<string.h>
#include <stdlib.h>

void f(char *str, int indis, int size); /*str karakter dizisi, indis dizi üzerinde nerede kaldigimizi belirten sayi, 
										  size ise dizinin eleman sayisini tutan sayi*/

int main()
{
	FILE *fp;
	fp = fopen("input.txt", "r");
	char str[100];
	int status, size = -1, i = 0;
	
	do				
	{
		size++;
		status = fscanf(fp, "%c", &str[size]);
	}while(status != EOF);
		
	f(str, 0, size); /*ilk olarak 0 indisini gönderiyoruz daha sonra
						fonksiyon kendi icinde diger indis degerleri ile kendini cagiracak*/
}

void f(char *str, int indis, int size)
{
	int i = 0, count = 0;
	
	if (indis == size)
		return;
	
	for(i = 0; i < indis; i++) /*indisin belirtigi alandaki karakterin seviyesini count icinde sakliyoruz*/
	{
		if(str[i] == '(')
			count++;
		else if(str[i] == ')')
			count--;
	}
	
	if(str[indis] != '(' && str[indis] != ')' && str[indis] != ',')/*'(', ')', ',' karakterleri ile ilgilenmiyoruz*/
	{	
		for(i = 0; i < count; i++)/*count kadar '-' karakteri yazdiriyoruz*/
			printf("-");
			
		printf("%c\n", str[indis]);/*sonra karakteri yazdirip alt satira geciyoruz*/
	}
	
	indis++;
	f(str, indis, size); /*her bir indis degeri icin kendisini cagiriyor*/
}