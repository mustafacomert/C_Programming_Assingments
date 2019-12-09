#include<stdio.h>

double avarageOfChunk(double *chunk, int size, int indis);
double min(double *avarage, int size);
void yazdir(FILE *ofp, double *chunk, int indisMin, int *indisOfChunk, int *sizeOfChunk);
int indisMin(double minAvarage, double *avarage, int numberChunk);


int main()
{	
	
	FILE *ifp;
	FILE *ofp;
	
	double fileArr[1000];	/*dosyadaki tüm değerleri aldığımız dizi*/
	double chunk[1000];	/*çankları ardışık bir şekilde tutan dizi*/
	int indisOfChunk[255];	/*çankların bitiş adreslerini tutan dizi*/
	int sizeOfChunk[255];	/*çankların uzunluğunu tutan dizi*/
	double avarageChunk[255];/*çankların ortalamlarını tutan dizi*/
	int status = 1;
	int a = 0;
	int i = -1;
	int j = -1;
	int size = -1;
	int indisOfMin;
	int  b;
	double minAvarage;
	
	ifp = fopen("input.txt", "r");
	ofp = fopen("output.txt", "w");

	while (status != EOF)
	{
		size++;
		status = fscanf(ifp, "%lf", &fileArr[size]);
	}
	while(i < size)
	{
		
		i++; j++;	/*first value of i and j was -1*/
		if(fileArr[i] == 0.0 && fileArr[i+1] == 0.0 && fileArr[i+2] == 0.0)
		{
			indisOfChunk[a] = j;	/*last indis of each chunks */		
			a++;	/*a is also keeping number of chunks*/
					
			i += 3;
		}

		chunk[j]  = fileArr[i];
		
	}
	sizeOfChunk[0] = indisOfChunk[0];
	for(i = 1; i < a; i++)
	{
		sizeOfChunk[i] = indisOfChunk[i] - indisOfChunk[i-1];	/*it keeps size value of each chunks*/
	}
	for(i = 1; i < a; i++)
	{	
		avarageChunk[i] = avarageOfChunk(chunk, sizeOfChunk[i], indisOfChunk[i-1]);
	}
	for(i=0; i < sizeOfChunk[0]; i++)		/*calculation of first chunk's avarage others will be calculate with a function*/
	{
		avarageChunk[0] += chunk[i];
		
	}
	avarageChunk[0] = avarageChunk[0]/sizeOfChunk[0];
	/*for(i = 0; i < a; i++)
	{
		printf("avarage %f size %d indis %d\n ", avarageChunk[i], sizeOfChunk[i], indisOfChunk[i]);
	}*/
	
	
	
	for(i = 0; i < a; i++)
	{
		minAvarage = min(avarageChunk, a); /*en küçük ortalama değeri*/
		/*printf("%f\n", minAvarage);*/
		indisOfMin = indisMin(minAvarage, avarageChunk, a); /*en küçük ortalama değer sahip çankın tutulduğu indis*/
		/*printf("%d\n", indisOfMin);*/
		if(indisOfMin == 0) /*indisOfMin 0 olduğu zamandaki yazdırma diğerleri yazdir fonksiyonu ile yazdırıldı*/
		{
			for(b= 0; b<sizeOfChunk[0]; b++)
			{
				fprintf(ofp, "%f ", chunk[b]);
			}
			fprintf(ofp, "\n");
		}
		else
		{
			yazdir(ofp, chunk, indisOfMin, indisOfChunk, sizeOfChunk);
		}
		avarageChunk[indisOfMin] = 999999999;/*bir sonraki min avarageli çankı bulabilmek için*/
		
	}
	fclose(ifp);
	fclose(ofp);
	return 0;
}


double avarageOfChunk(double *chunk, int size, int indis) /*çankların ortalamasını hesaplar*/
{
	int i;
	double sum = 0;
	double avarage = 0;
	for(i = 0; i < size; i++)
	{
		sum += chunk[indis + i];  		
	}
	avarage = sum / size;
	return avarage;

}

double min(double *avarage, int size)/*en düşük ortalamaya sahip çankın değerini döndürür, 
					bu değer kullanılarak o çankın indisini 
					indisMin fonksiyonu ile döndürüyoruz*/
{
	double min;

	min = avarage[0];
	for(int i = 1; i < size; i++)
	{
		if(min > avarage[i])
		{
		
			min = avarage[i];
			
		}
	}
	return min;
}

void yazdir(FILE *ofp, double *chunk,int indisMin, int *indisOfChunk, int *sizeOfChunk)/*çankları output dosyasına 
											artan sırada yazdırır */
{
	for(int i = indisOfChunk[indisMin-1]; i < indisOfChunk[indisMin-1] + sizeOfChunk[indisMin]; i++)
	{
		fprintf(ofp, "%f ", chunk[i]);
	}
	fprintf(ofp, "\n");
	
}

int indisMin(double minAvarage, double *avarage, int numberChunk)
{
	int i;
	for(i = 0; i < numberChunk; i++)
	{
		if(avarage[i] == minAvarage)
		{ 
			break;
		}
	}
	return i;
}


