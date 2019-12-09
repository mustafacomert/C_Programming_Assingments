#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define FACENUM 6

typedef struct face_s
{
	int faceID;
	int **face;
	struct face_s *next;
}face_t;

void fill(face_t *root, int faceID, int n);/*to fill color ID on 2d array*/
void printFace(face_t *root, int faceID, int n);/*prints last station of each faces*/
void rotateR(face_t *root, int faceID, int row, int direction, int N);/*rotates rows*/
void rotateR0123(face_t *root, int row, int direction, int N);/*turns right or left if faces 0, 1, 2, 3. faces*/
void rotateR4(face_t *root, int row, int direction, int N);/*turns right or left if faces 4. face*/
void rotateR5(face_t *root, int row, int direction, int N);/*turns right or left if faces 5. face*/
void rotateLeft90(face_t *root, int faceID, int N);/*turns counter clockwise 2d matrix*/
void rotateRight90(face_t *root, int faceID, int N);/*turns clockwise 2d matrix*/
void rotateC(face_t *root, int faceID, int column, int direction, int N);/*rotates columns*/
void rotateC0425(face_t *root, int column, int direction, int N);/*rotates columns*/
void rotateC1(face_t *root, int column, int direction, int N);/*rotates columns when face1 directs to me*/
void rotateC3(face_t *root, int column, int direction, int N);/*rotates columns when face3 directs to me*/
void freeFace(face_t *root, int N);

int main()
{
	
	face_t *root, *iter;
	int i = 0, j;
	int N;/*size of rubic cube's edges (N*N*N)*/
	FILE *fp;
	int faceID;
	int status;
	int row;
	int column;
	int direction;
	char comm[100][10];
	int size;
	fp = fopen("commands.txt", "r");
	status = fscanf(fp, "%d", &N);
	
	root = (face_t *)malloc(sizeof(face_t));
	root -> next = NULL; 
	iter = root;
	
	while(status != EOF)
	{
		status = fscanf(fp, "%s", &comm[i]);
		i++;
	}
	size = i - 1;
	
	for(i = 1; i < FACENUM; i++)
	{
		iter->next = (face_t *)malloc(sizeof(face_t));
		iter = iter->next;
	}
	iter = NULL;
	iter = root;
	
	for(i = 0; i < FACENUM; i++)
	{
		iter->face = malloc(sizeof(int *) * N);/*n*n two dimensional array's dynamic allocation*/
		for(j = 0; j < N; j++)
		{
			iter->face[j] = malloc(sizeof(int) * N);
		}
		iter->next = (face_t *)malloc(sizeof(face_t));
		iter = iter->next;
	}
	
	iter = root;
	
	for(i = 0; i < FACENUM; i++)
	{
		fill(iter, i, N);
		iter->faceID = i;
		iter = iter->next;
	}
	iter = root;
	
	for(j = 0; j < size; j++)
	{
		if(strcmp(comm[j], "rotate") == 0)
		{
			j++;
			sscanf(comm[j], "%d", &faceID);
			j++;
			if(strcmp(comm[j], "row") == 0)
			{
				j++;
				sscanf(comm[j], "%d", &row);
				j++;
				if(strcmp(comm[j], "right") == 0)
				{
					direction = 0;
				}
				else if(strcmp(comm[j], "left") == 0)
				{
					direction = 1;
				}
				rotateR(root, faceID, row, direction, N);
			}
			else if(strcmp(comm[j], "column") == 0)
			{
				j++;
				sscanf(comm[j], "%d", &column);
				j++;
				if(strcmp(comm[j], "up") == 0)
				{
					direction = 0;
				}
				else if(strcmp(comm[j], "down") == 0)
				{
					direction = 1;
				}
				rotateC(root, faceID, column, direction, N);	
			}
		}
		/*else if(strcmp(comm[j], "shrink") == 0)
			shrink*/
	}
	
	for(i = 0; i < FACENUM; i++)
	{
		printFace(iter, i, N);
		printf("\n");
		iter = iter->next;
	}
	/*freeFace(root, N);*/
	return 0;
}

void fill(face_t *root, int faceID, int n)
{
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			root->face[i][j] = faceID;
		}
	}
}

void printFace(face_t *root, int faceID, int n)
{
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			printf("%d", root->face[i][j]);
		}
		printf("\n");
	}
}

void rotateR(face_t *root, int faceID, int row, int direction, int N)
{
	int j;
	
	if(faceID == 0 || faceID == 1 || faceID == 2 || faceID == 3)
	{
		rotateR0123(root, row, direction, N);
	}
	else if(faceID == 4)
	{
		rotateR4(root, row, direction, N);
	}
	else if(faceID == 5)
	{
		rotateR5(root, row, direction, N);
	}
}

void rotateR0123(face_t *root, int row, int direction, int N)
{
	int j;
	int temp[N];
	int temp2[N];
	int temp3[N];
	
	if(direction == 0)
	{
		for(j=0; j < N; j++)
		{
			temp[j] = root->next->face[row][j];/*temp holds face1*/
		}
		for(j=0; j < N; j++)
		{
			root->next->face[row][j] = root->face[row][j];/*face1 holds face0*/
		}
		for(j=0; j < N; j++)
		{
			temp2[j] = root->next->next->face[row][j];/*temp2 holds face2*/
		}
		for(j=0; j < N; j++)
		{
			root->next->next->face[row][j] = temp[j];/*face2 holds face1*/
		}
		for(j=0; j < N; j++)
		{
			temp3[j] = root->next->next->next->face[row][j];/*temp3 holds face3*/
		}
		for(j=0; j < N; j++)
		{
			root->next->next->next->face[row][j] = temp2[j];/*face3 holds face2*/
		}
		for(j=0; j < N; j++)
		{
			root->face[row][j] = temp3[j];/*face0 holds face3*/
		}
	}
	else if(direction == 1)
	{
		for(j=0; j < N; j++)
		{
			temp[j] = root->face[row][j];/*temp holds face0*/
		}
		for(j=0; j < N; j++)
		{
			root->face[row][j] = root->next->face[row][j];/*face0 holds face1*/
		}
		
		for(j=0; j < N; j++)
		{
			root->next->face[row][j] = root->next->next->face[row][j];/*face1 holds face2*/
		}

		for(j=0; j < N; j++)
		{
			root->next->next->face[row][j] = root->next->next->next->face[row][j];/*face2 holds face3*/
		}
		for(j=0; j < N; j++)
		{
			root->next->next->next->face[row][j] = temp[j];/*face3 holds face0*/
		}
	}
	else
		printf("error rotateR0123");
}

void rotateR4(face_t *root, int row, int direction, int N)
{
	int j;
	int temp[N];
	int temp2[N];
	int temp3[N];
	
	/*while face4 directed to me, face1 turns left*/
	rotateLeft90(root, 1, N);
	/*face3 turns right*/
	rotateRight90(root, 3, N);
	
	if(direction == 0)/*it means turned right*/
	{
		for(j=0; j < N; j++)
		{
			temp[j] = root->next->face[row][j];/*temp holds face1*/
		}
		for(j=0; j < N; j++)
		{
			root->next->face[row][j] = root->next->next->next->next->face[row][j];/*face1 holds face4*/
		}
		for(j=0; j < N; j++)
		{
			temp2[j] = root->next->next->next->next->next->face[N - row - 1][j];/*temp2 holds face5*/
		}
		for(j=0; j < N; j++)
		{
			root->next->next->next->next->next->face[N - row - 1][j] = temp[N - 1 - j];/*face5 holds face1*/
		}
		for(j=0; j < N; j++)
		{
			temp3[j] = root->next->next->next->face[row][j];/*temp3 holds face3*/
		}
		for(j=0; j < N; j++)
		{
			root->next->next->next->face[row][j] = temp2[N - 1 - j];/*face3 holds face5*/
		}
		for(j=0; j < N; j++)
		{
			root->next->next->next->next->face[row][j] = temp3[j];/*face4 holds face3*/
		}
	}
	else if(direction == 1)/*it means turned left*/
	{
		for(j=0; j < N; j++)
		{
			temp[j] = root->next->next->next->next->face[row][j];/*temp holds face4*/
		}
		for(j=0; j < N; j++)
		{
			root->next->next->next->next->face[row][j] = root->next->face[row][j];/*face4 holds face1*/
		}
		
		for(j=0; j < N; j++)
		{
			root->next->face[row][j] = root->next->next->next->next->next->face[N - row - 1][N - 1 - j];/*face1 holds face5*/
		}

		for(j=0; j < N; j++)
		{
			root->next->next->next->next->next->face[N - row - 1][j] = root->next->next->next->face[row][N - 1 - j];/*face5 holds face3*/
		}
		for(j=0; j < N; j++)
		{
			root->next->next->next->face[row][j] = temp[j];/*face3 holds face4*/
		}
	}
	else
		printf("error rotateR4");
	
	rotateRight90(root, 1, N);
	rotateLeft90(root, 3, N);/*when the terminate turned row operation, 
							we update faces first version that is 0 face directed to me*/
}

void rotateR5(face_t *root, int row, int direction, int N)
{
	int j;
	int temp[N];
	int temp2[N];
	int temp3[N];
	
	/*while face5 directed to me, face1 turns right*/
	rotateRight90(root, 1, N);
	/*face3 turns left*/
	rotateLeft90(root, 3, N);
	
	if(direction == 0)/*it means turned right*/
	{
		for(j=0; j < N; j++)
		{
			temp[j] = root->next->face[row][j];/*temp holds face1*/
		}
		for(j=0; j < N; j++)
		{
			root->next->face[row][j] = root->next->next->next->next->next->face[row][j];/*face1 holds face5*/
		}
		for(j=0; j < N; j++)
		{
			temp2[j] =root->next->next->next->next->face[N - row - 1][j];/*temp2 holds face4*/
		}
		for(j=0; j < N; j++)
		{
			root->next->next->next->next->face[N - row - 1][j] = temp[N - 1 - j];/*face4 holds face1*/
		}
		for(j=0; j < N; j++)
		{
			temp3[j] = root->next->next->next->face[row][j];/*temp3 holds face3*/
		}
		for(j=0; j < N; j++)
		{
			root->next->next->next->face[row][j] = temp2[N - 1 - j];/*face3 holds face4*/
		}
		for(j=0; j < N; j++)
		{
			root->next->next->next->next->next->face[row][j] = temp3[j];/*face5 holds face3*/
		}
	}
	else if(direction == 1)/*it means turned left*/
	{
		for(j=0; j < N; j++)
		{
			temp[j] = root->next->next->next->next->next->face[row][j];/*temp holds face5*/
		}
		for(j=0; j < N; j++)
		{
			root->next->next->next->next->next->face[row][j] = root->next->face[row][j];/*face5 holds face1*/
		}
		
		for(j=0; j < N; j++)
		{
			root->next->face[row][j] = root->next->next->next->next->face[N - row - 1][N - 1 - j];/*face1 holds face4*/
		}

		for(j=0; j < N; j++)
		{
			root->next->next->next->next->face[N - 1 - row][j] = root->next->next->next->face[row][N - 1 - j];/*face4 holds face3*/
		}
		for(j=0; j < N; j++)
		{
			root->next->next->next->face[row][j] = temp[j];/*face3 holds face5*/
		}
	}
	else
		printf("error rotateR5");
	
	rotateLeft90(root, 1, N);
	rotateRight90(root, 3, N);/*when the terminate turned row operation, 
							we update faces first version that is 0 face directed to me*/
}


void rotateLeft90(face_t *root, int faceID, int N)
{
	int i, j;
	face_t *iter = malloc(sizeof(face_t));
	iter = root;
	int copy[N][N];
	
	for(i = 0; i < faceID; i++)
	{
		iter = iter->next;
	}
	
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
			copy[i][j] = iter->face[i][j]; 
		}
	}	
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
			iter->face[i][j] = copy[j][N - i -1];  
		}
	}	
}

void rotateRight90(face_t *root, int faceID, int N)
{
	rotateLeft90(root, faceID, N);
	rotateLeft90(root, faceID, N);
	rotateLeft90(root, faceID, N);
}

void rotateC(face_t *root, int faceID, int column, int direction, int N)
{
	int j;
	
	if(faceID == 0 || faceID == 4 || faceID == 2 || faceID == 5)
	{
		rotateC0425(root, column, direction, N);
	}
	else if(faceID == 1)
	{
		rotateC1(root, column, direction, N);
	}
	else if(faceID == 3)
	{
		rotateC3(root, column, direction, N);
	}
	else
		printf("error rotateC");
}

void rotateC0425(face_t *root, int column, int direction, int N)
{
	int j;
	int temp[N];
	int temp2[N];
	int temp3[N];
	

	if(direction == 0)/*it means rotate up*/
	{
		for(j = 0; j < N; j++)
		{
			temp[j] = root->next->next->next->next->face[N - j - 1][column];/*temp holds face4*/
		}
		for(j = 0; j < N; j++)
		{
			root->next->next->next->next->face[j][column] = root->face[j][column];/*face4 holds face0*/
		}
		for(j = 0; j < N; j++)
		{
			temp2[j] = root->next->next->face[j][N - column -1];/*temp2 holds face2*/
		}
		for(j = 0; j < N; j++)
		{
			root->next->next->face[j][N - column - 1] = temp[j];/*face2 holds face4*/
		}
		for(j = 0; j < N; j++)
		{
			temp3[j] = root->next->next->next->next->next->face[j][column];/*temp3 holds face5*/
		}
		for(j = 0; j < N; j++)
		{
			root->next->next->next->next->next->face[N - j - 1][column] = temp2[j];/*face5 holds face2*/
		}
		for(j = 0; j < N; j++)
		{
			root->face[j][column] = temp3[j];/*face0 holds face5*/
		}
		
	}
	else if(direction == 1)/*it means rotate down*/
	{
		for(j = 0; j < N; j++)
		{
			temp[j] = root->next->next->next->next->next->face[N - j - 1][column];/*temp holds face5*/
		}
		for(j = 0; j < N; j++)
		{
			root->next->next->next->next->next->face[j][column] = root->face[j][column];/*face5 holds face0*/
		}
		for(j = 0; j < N; j++)
		{
			temp2[j] = root->next->next->face[j][N - column - 1];/*temp2 holds face2*/
		}
		for(j = 0; j < N; j++)
		{
			root->next->next->face[j][N - column - 1] = temp[j];/*face2 holds face5*/
		}
		for(j = 0; j < N; j++)
		{
			temp3[j] = root->next->next->next->next->face[j][column];/*temp3 holds face4*/
		}
		for(j = 0; j < N; j++)
		{
			root->next->next->next->next->face[N - j - 1][column] = temp2[j];/*face4 holds face2*/
		}
		for(j = 0; j < N; j++)
		{
			root->face[j][column] = temp3[j];/*face0 holds face4*/
		}
	}
	else
		printf("error rotateC0425");
}

void rotateC1(face_t *root, int column, int direction, int N)
{
	int j;
	int temp[N];
	int temp2[N];
	int temp3[N];
	
	/*while face1 directed to me, face4 turns right*/
	rotateRight90(root, 4, N);
	/*face5 turns left*/
	rotateLeft90(root, 5, N);
	
	if(direction == 0)/*it means turned up*/
	{
		for(j=0; j < N; j++)
		{
			temp[j] = root->next->next->next->next->face[j][column];/*temp holds face4*/
		}
		for(j=0; j < N; j++)
		{
			temp2[j] = root->next->next->next->face[j][N - column - 1];/*temp2 holds face3*/
		}
		for(j=0; j < N; j++)
		{
			temp3[j] =root->next->next->next->next->next->face[j][column];/*temp3 holds face5*/
		}
		for(j=0; j < N; j++)
		{
			root->next->next->next->next->face[j][column] = root->next->face[j][column];/*face4 holds face1*/
		}
		for(j=0; j < N; j++)
		{
			root->next->next->next->face[N - j - 1][N - column - 1] = temp[j];/*face3 holds face4*/
		}
		for(j=0; j < N; j++)
		{
			root->next->next->next->next->next->face[j][column] = temp2[N - 1 - j];/*face5 holds face3*/
		}
		for(j=0; j < N; j++)
		{
			root->next->face[j][column] = temp3[j];/*face1 holds face5*/
		}
	}
	else if(direction == 1)/*it means turned down  */
	{
		for(j=0; j < N; j++)
		{
			temp[j] = root->next->next->next->next->next->face[j][column];/*temp holds face5*/
		}
		for(j=0; j < N; j++)
		{
			temp2[j] = root->next->next->next->next->face[j][column];/*temp2 holds face4*/
		}
		for(j=0; j < N; j++)
		{
			temp3[j] = root->next->next->next->face[N - j - 1][N - column - 1];/*temp3 holds face3*/
		}
		for(j=0; j < N; j++)
		{
			root->next->next->next->next->next->face[j][column] = root->next->face[j][column];/*face5 holds face1*/
		}
		
		for(j=0; j < N; j++)
		{
			root->next->next->next->face[N - j - 1][N - column - 1] = temp[j];/*face3 holds face5*/
		}
		
		for(j=0; j < N; j++)
		{
			root->next->next->next->next->face[j][column] = temp3[j];/*face4 holds face3*/
		}
		for(j=0; j < N; j++)
		{
			root->next->face[j][column] = temp2[j];/*face1 holds face4*/
		}
	}
	else
		printf("error rotateC1");
	
	rotateLeft90(root, 4, N);
	rotateRight90(root, 5, N);/*when the terminate turned row operation, 
							we update faces first version that is 0 face directed to me*/
}

void rotateC3(face_t *root, int column, int direction, int N)
{
	int j;
	int temp[N];
	int temp2[N];
	int temp3[N];
	
	/*while face3 directed to me, face4 turns left*/
	rotateLeft90(root, 4, N);
	/*face5 turns right*/
	rotateRight90(root, 5, N);
	
	if(direction == 0)/*it means turned up*/
	{
		for(j=0; j < N; j++)
		{
			temp[j] = root->next->next->next->next->face[N - 1 - j][column];/*temp holds face4*/
		}
		for(j=0; j < N; j++)
		{
			temp2[j] = root->next->face[N - 1 - j][N - column - 1];/*temp2 holds face1*/
		}
		for(j=0; j < N; j++)
		{
			temp3[j] = root->next->next->next->next->next->face[j][column];/*temp3 holds face5*/
		}
		for(j=0; j < N; j++)
		{
			root->next->next->next->next->face[j][column] = root->next->next->next->face[j][column];/*face4 holds face3*/
		}
		for(j=0; j < N; j++)
		{
			root->next->face[j][N - column - 1] = temp[j];/*face1 holds face4*/
		}
		for(j=0; j < N; j++)
		{
			root->next->next->next->next->next->face[j][column] = temp2[j];/*face5 holds face1*/
		}
		for(j=0; j < N; j++)
		{
			root->next->next->next->face[j][column] = temp3[j];/*face3 holds face5*/
		}
	}
	else if(direction == 1)/*it means turned down*/
	{
		for(j=0; j < N; j++)
		{
			temp[j] = root->next->next->next->next->next->face[j][column];/*temp holds face5*/
		}
		for(j=0; j < N; j++)
		{
			temp2[j] = root->next->next->next->next->face[j][column];/*temp2 holds face4*/
		}
		for(j=0; j < N; j++)
		{
			temp3[j] = root->next->face[N - 1- j][N - 1 - column];/*temp3 holds face1*/
		}
		for(j=0; j < N; j++)
		{
			root->next->next->next->next->next->face[j][column] = root->next->next->next->face[j][column];/*face5 holds face3*/
		}
		for(j=0; j < N; j++)
		{
			root->next->face[N - 1 -j][N - column - 1] = temp[j];/*face1 holds face5*/
		}
		for(j=0; j < N; j++)
		{
			root->next->next->next->next->face[j][column] = temp3[j];/*face4 holds face1*/
		}
		for(j=0; j < N; j++)
		{
			root->next->next->next->face[j][column] = temp2[j];/*face3 holds face4*/
		}
		
		
		
	}
	else
		printf("error rotateC1");
	
	rotateRight90(root, 4, N);
	rotateLeft90(root, 5, N);/*when the terminate turned row operation, 
							we update faces first version that is 0 face directed to me*/
}

void freeFace(face_t *root, int N)/*****this is not complated*****/
{
	int j;
	for(j = 0; j < N; j++)
	{
		free(root->face[j]);
	}
	free(root->face);
	if(root->next != NULL)
	{
		freeFace(root->next, N);
	}
	free(root);
}