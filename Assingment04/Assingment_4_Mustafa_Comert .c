#include <stdio.h>
#include <string.h>
#include <math.h>

double eval(double *coeff, int *power, double val, int coSize); /*sonucu hesaplayip dondurecek fonk.*/

void main()
{
	FILE *ifp1, *ifp2, *ofp;
	double val[100]; 
	char pol2[1000];/*polinomun x ile baslamasi durumunda pol' un ilk elemanina '+' karakterini ekleyebilmek icin kullandim*/
	char pol[1000];
	double coeff[1000];
	int coLen[1000]; /*coeff' lerin uzunlugunu sakladigim dizi*/
	int status;
	int i = 0, j=0, k = 0, a = 0;
	int valSize, polSize, coSize;
	int power[1000]; /*x' lerin derecesini tuttugum array*/
	double ret;/*eval fonksiyonun return degeri*/
	
	ifp1 = fopen("polynomial.txt", "r");
	ifp2 = fopen("values.txt", "r");
	ofp = fopen("evaluations.txt", "w");
	do /*polynomial dosyasından polinomu pol2 arrayine alıyoruz*/
	{
		status = fscanf(ifp1, "%c", &pol2[i]);
		i++;
	}while(status != EOF);
	
	polSize = i-1; /*polinomun uzunluğu*/
	
	for (i = 0; i < polSize; i++) /*pol2' yi pol' a kopyaliyoruz*/
	{
		pol[i] = pol2[i];
	}
	
	if (pol[0] == 'x') /*polinomun ilk elemani sifir ise, dizinin basina '+' karakterini ekliyoruz*/
	{
		pol[0] = '+';
		polSize += 1; /*polinomumuz '+' karakteri ile 1 eleman büyüdü*/
		for(i = 1; i < polSize; i++)
		{
			pol[i] = pol2[i-1];
		}
			
	}

	
	i = 0;
	do /*values dosyasindan degeleri val dizisine aldik*/
	{
		status = fscanf(ifp2,"%lf", &val[i]);
		i++;
	}while(status != EOF);
	
	valSize = i-1; /*degelerin sayisi*/
	
	for (i = 0; i < polSize; i++)	/*her bir coeff' in uzunlugunu coeff dizinde sakladik*/
	{
		if(pol[i] == 'x')
		{
			if(pol[i+1] == '^')
			{
					coLen[j] = k; 
					j++; k = 0; i += 3;
			}
			else
			{
					coLen[j] = k;
					j++; k=0; i ++;
			}
			
		}
		k++;
	}
	
	coSize = j; /*coeff sayisi*/
	
	for (i=0; i < coSize; i++)	/*coeff'leri coeff dizisine aktardik*/
	{
			while(pol[a] == ' ')
				a++;
			
			if(pol[a] == '-' && pol[a+1] == 'x')
			{
				coeff[i] = -1.0;
				a = a + coLen[i] + 1;
				
				if(pol[a] == '^')
					a += 2;
			}
			else if(pol[a] == '+' && pol[a+1] == 'x') 
			{
				coeff[i] = +1.0;
				a = a+ coLen[i] + 1;
				
				if(pol[a] == '^')
					a += 2;
			}
			else
			{
				sscanf(&pol[a], "%lf", &coeff[i]);
				a = a + coLen[i] + 1; 
				
				if(pol[a] == '^')
					a += 2;
			}
	}
	
	j = 0;
	
	for (i = 0; i < polSize; i++) /*x' in derecelerini power dizisine aktardik*/
	{
		
		if(pol[i] == 'x')
		{
			while(pol[i+1] == ' ')
				i++;
			if(pol[i+1] == '^')
			{
				while(pol[i+2] == ' ')
					i++;
				sscanf(&pol[i+2], "%d", &power[j]);
				j++;
			}
			else
			{
				power[j] = 1;
				j++;
			}
		}	
	}
	
	
	
	for(i = 0; i < valSize; i++)	/*her bir deger icin eval fonksiyonunu cagirdik, her bir dönüs degerini dosyaya yazdirdik*/
	{
		ret = eval(coeff, power, val[i], coSize);
		fprintf(ofp, "%.2f\n", ret);
	}
	fclose(ofp);
	fclose(ifp1);
	fclose(ifp2);
}

double eval(double *coeff, int *power, double val, int coSize) /*sonucu hesapladik*/
{
	double ev =  0.0;
	int i;
	for(i = 0; i < coSize; i++)
	{
		ev = ev + coeff[i] * pow(val, power[i]);
	}
	return ev;
}