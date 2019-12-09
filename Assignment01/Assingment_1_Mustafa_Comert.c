#include<stdio.h>
#define ATTEMP 10
/*skecth for cases of intersection of two rectangles https://i.hizliresim.com/ZOV2WV.jpg*/
int main()
{
	int boardX = 200, boardY = 300;
	double MRLengthX = 15, MRLengthY = 20;
	double DLengthX = 20, DLengthY = 20;
	double MRKoorX = 70, MRKoorY = 90;	/*Marked Region's central points*/
	double DKoorX, DKoorY;			/*Detector's central points (from user)*/
	int attemps = ATTEMP;			
	double MRcornerX1;			/*MRcornerX1 is coordinate X of left corner of Marked Region*/
	double MRcornerX2;			/*MRcornerX2 is coordinate X of rigth corner of Marked Region*/
	double MRcornerY1;			/*MRcornerY1 is coordinate Y of bottom corner of Marked Region*/
	double MRcornerY2;			/*MRcornerY2 is coordinate Y of top corner of Marked Region*/
	double DcornerX1, DcornerX2, DcornerY1, DcornerY2;
	printf("Your Detector's Size [%.2f*%.2f] and Board Size [200*300]\n", DLengthX, DLengthY);
	while(attemps > 0)
	{
		printf("\nPlease, enter the X coordinate for detector : ");
		scanf("%lf", &DKoorX);
		printf("\nPlease, enter the Y coordinate for detector : ");
		scanf("%lf", &DKoorY);
		DcornerX1 = DKoorX - DLengthX/2;	 /*Calculation corner coordinates for detector out of inputs from user*/
		DcornerX2 = DKoorX + DLengthX/2;
		DcornerY1 = DKoorY - DLengthY/2;
		DcornerY2 = DKoorY + DLengthY/2;
		MRcornerX1 = MRKoorX - MRLengthX/2;	/*Calculation corner coordinates for Marked Region*/
		MRcornerX2 = MRKoorX + MRLengthX/2;
		MRcornerY1 = MRKoorY - MRLengthY/2;
		MRcornerY2 = MRKoorY + MRLengthY/2;
		/*different calculation for each cases*/
		if(DKoorX > boardX || DKoorY > boardY || DKoorX < 0 || DKoorY < 0)/*If input values outside of board*/
		{
			printf("invalid move, remaininig attemps : %d\n\n", attemps);
		}
		else if(MRcornerX1 >= DcornerX1 &&  MRcornerX2 <= DcornerX2 
			&& MRcornerY1 >= DcornerY1 && MRcornerY2 <= DcornerY2)/*Win Case*/
		{
			attemps--;
			printf("*** Y ***\n*** o ***\n*** u ***\n \n*** W ***\n*** I ***\n*** N ***\n\nIn %d attemp's'\n", ATTEMP - 					attemps);
			break;
		}
		else if(DcornerX2 <= MRcornerX1 || DcornerX1 >= MRcornerX2 
			|| DcornerY1 >= MRcornerY2 || DcornerY2 <= MRcornerY1  )/*No intersection between two rectangles*/
		{
			attemps -= 1;
			printf("\nYou missed the target attemps remaining attemps : %d\n\n", attemps);
		}
		else if(MRcornerY2 >= DcornerY1 && MRcornerY2 <= DcornerY2 
			&& MRcornerX2 >= DcornerX1 && MRcornerX2 <= DcornerX2 
			&& MRcornerY1 <= DcornerY1 && DcornerX1 >= MRcornerX1)/*Detector'ün MR' un sağ üst köşesi ile kesişme durumu*/
		{
			MRLengthX = MRcornerX2 - DcornerX1;
			MRLengthY = MRcornerY2 - DcornerY1;
			MRKoorX = DcornerX1 + MRLengthX/2;
			MRKoorY = DcornerY1 + MRLengthY/2;
			DLengthX = DLengthX/2;
			DLengthY = DLengthY/2;
			/*printf("case 1 MRkoorX %f MRkoorY %f", MRKoorX, MRKoorY);*/
			attemps -= 1;
			printf("\nPartial Hit!, Marked Region Was Shrinked to [%.2f x %.2f],\n\nYour Detector Was Shrinked to [%.2f x%.2f], \n\nremaining attemps : %d\n\n", MRLengthX, MRLengthY, DLengthX, DLengthY, attemps);
					
					
		}
		else if(MRcornerY2 >= DcornerY1 && MRcornerY2 <= DcornerY2 
			&& MRcornerX1 >= DcornerX1 && MRcornerX1 <= DcornerX2 
			&& MRcornerY2 <= DcornerY2 && MRcornerX2 >= DcornerX2 && MRcornerY1 <= DcornerY1)/*sol üst köşe ile kesişme*/
		{
			MRLengthX = DcornerX2 - MRcornerX1;
			MRLengthY = MRcornerY2 - DcornerY1;
			MRKoorX = DcornerX2 - MRLengthX/2;
			MRKoorY = DcornerY1 + MRLengthY/2;
			DLengthX = DLengthX/2;
			DLengthY = DLengthY/2;
			attemps -= 1;
			printf("\nPartial Hit!, Marked Region Was Shrinked to [%.2f x %.2f],\n\nYour Detector Was Shrinked to [%.2f x%.2f], \n\nremaining attemps : %d\n\n", MRLengthX, MRLengthY, DLengthX, DLengthY, attemps);
			/*printf("2 %f %f\n", MRKoorX, MRKoorY);*/
		}
		else if(MRcornerY1 >= DcornerY1 && MRcornerY1 <= DcornerY2 
			&& MRcornerX1 >= DcornerX1 && MRcornerX1 <= DcornerX2 
			&& MRcornerX2 >= DcornerX2 && MRcornerY2 >= DcornerY2)/*sol alt köşe ile kesişme*/
		{
			MRLengthX = DcornerX2 - MRcornerX1;
			MRLengthY = DcornerY2 - MRcornerY1;
			MRKoorX = DcornerX2 - MRLengthX/2;
			MRKoorY = DcornerY2 - MRLengthY/2;
			DLengthX = DLengthX/2;
			DLengthY = DLengthY/2;
			attemps -= 1;
			printf("\nPartial Hit!, Marked Region Was Shrinked to [%.2f x %.2f],\n\nYour Detector Was Shrinked to [%.2f x%.2f], \n\nremaining attemps : %d\n\n", MRLengthX, MRLengthY, DLengthX, DLengthY, attemps);
			/*printf("3 %f %f\n", MRKoorX, MRKoorY);*/
		}
		else if(MRcornerY1 >= DcornerY1 && MRcornerY1 <= DcornerY2 && MRcornerX2 >= DcornerX1 && MRcornerX2 <= DcornerX2 && 				MRcornerY2 >= DcornerY2 && MRcornerX1 <= DcornerX1)/*sağ alt köşe ile kesişme*/
		{
			MRLengthX = MRcornerX2 - DcornerX1;
			MRLengthY = DcornerY2 - MRcornerY1;
			MRKoorX = DcornerX1 + MRLengthX/2;
			MRKoorY = DcornerY2 - MRLengthY/2;
			DLengthX = DLengthX/2;
			DLengthY = DLengthY/2;
			attemps -= 1;
			printf("\nPartial Hit!, Marked Region Was Shrinked to [%.2f x %.2f],\n\nYour Detector Was Shrinked to [%.2f x%.2f], \n\nremaining attemps : %d\n\n", MRLengthX, MRLengthY, DLengthX, DLengthY, attemps);
			/*printf("4\n");
			printf("%f %f", MRKoorX, MRKoorY);*/
		}
		else if(MRcornerY2 >= DcornerY2 && MRcornerY1 <= DcornerY1 && MRcornerX2 >= DcornerX1 && MRcornerX2 <= DcornerX2 && 				DcornerX1 > MRcornerX1)/**/
		{
			MRLengthX = MRcornerX2 - DcornerX1;
			MRLengthY = MRLengthY - (MRcornerY2 - DcornerY2) - (DcornerY1 - MRcornerY1);
			MRKoorX = DcornerX1 + MRLengthX/2;
			MRKoorY = DcornerY2 - MRLengthY/2;
			DLengthX = DLengthX/2;
			DLengthY = DLengthY/2;
			attemps -= 1;
			printf("\nPartial Hit!, Marked Region Was Shrinked to [%.2f x %.2f],\n\nYour Detector Was Shrinked to [%.2f x%.2f], \n\nremaining attemps : %d\n\n", MRLengthX, MRLengthY, DLengthX, DLengthY, attemps);
			/*printf("5\n");
			printf("%f %f", MRKoorX, MRKoorY);*/
			
		}
		else if(MRcornerY2 >= DcornerY2 && MRcornerY1 <= DcornerY1 && MRcornerX1 >= DcornerX1 && MRcornerX1 <= DcornerX2 && 				DcornerX2 <= MRcornerX2)
		{
			MRLengthX = DcornerX2 - MRcornerX1;
			MRLengthY = MRLengthY - (MRcornerY2 - DcornerY2) - (DcornerY1 - MRcornerY1);
			MRKoorX = DcornerX2 - MRLengthX/2;
			MRKoorY = DcornerY2 - MRLengthY/2;
			DLengthX = DLengthX/2;
			DLengthY = DLengthY/2;
			attemps -= 1;
			printf("\nPartial Hit!, Marked Region Was Shrinked to [%.2f x %.2f],\n\nYour Detector Was Shrinked to [%.2f x%.2f], \n\nremaining attemps : %d\n\n", MRLengthX, MRLengthY, DLengthX, DLengthY, attemps);
			/*printf("%f %f", MRKoorX, MRKoorY);
			printf("6\n");*/
		}
		else if(MRcornerY1 >= DcornerY1 && MRcornerY1 <= DcornerY2 && MRcornerX2 >= DcornerX2 && MRcornerX1 <= DcornerX1 && 				DcornerY2 <= MRcornerY2)
		{
			MRLengthX = DcornerX2 - DcornerX1;
			MRLengthY = DcornerY2 - MRcornerY1;
			MRKoorX = DcornerX2 - MRLengthX/2;
			MRKoorY = DcornerY2 - MRLengthY/2;
			DLengthX = DLengthX/2;
			DLengthY = DLengthY/2;
			attemps -= 1;
			printf("\nPartial Hit!, Marked Region Was Shrinked to [%.2f x %.2f],\n\nYour Detector Was Shrinked to [%.2f x%.2f], \n\nremaining attemps : %d\n\n", MRLengthX, MRLengthY, DLengthX, DLengthY, attemps);
			/*printf("7\n");
			printf("%f %f", MRKoorX, MRKoorY);*/
		}
		else if(MRcornerY2 >= DcornerY1 && MRcornerY2 <= DcornerY2 && MRcornerX2 >= DcornerX2 && MRcornerX1 <= DcornerX1 && 				DcornerY1 >= MRcornerY1)
		{
			MRLengthX = DcornerX2 - DcornerX1;
			MRLengthY = MRcornerY2 - DcornerY1;
			MRKoorX = DcornerX2 - MRLengthX/2;
			MRKoorY = DcornerY1 + MRLengthY/2;
			DLengthX = DLengthX/2;
			DLengthY = DLengthY/2;
			attemps -= 1;
			printf("\nPartial Hit!, Marked Region Was Shrinked to [%.2f x %.2f],\n\nYour Detector Was Shrinked to [%.2f x%.2f], \n\nremaining attemps : %d\n\n", MRLengthX, MRLengthY, DLengthX, DLengthY, attemps);
			/*printf("8\n");
			printf("%f %f", MRKoorX, MRKoorY);*/
		}
		else if(DcornerX2 >= MRcornerX2 && DcornerX1 <= MRcornerX1 && DcornerY2 >= MRcornerY2 
			&& MRcornerY2 >= DcornerY1 && DcornerY2 >= MRcornerY2)
		{
			MRLengthX = MRcornerX2 - MRcornerX1;
			MRLengthY = MRcornerY2 - DcornerY1;
			MRKoorX = MRcornerX2 - MRLengthX/2;
			MRKoorY = MRcornerY2 - MRLengthY/2;
			DLengthX = DLengthX/2;
			DLengthY = DLengthY/2;
			attemps -= 1;
			printf("\nPartial Hit!, Marked Region Was Shrinked to [%.2f x %.2f],\n\nYour Detector Was Shrinked to [%.2f x%.2f], \n\nremaining attemps : %d\n\n", MRLengthX, MRLengthY, DLengthX, DLengthY, attemps);
			/*printf("9\n");
			printf("%f %f", MRKoorX, MRKoorY);*/
		}
		else if(DcornerX2 >= MRcornerX2 && DcornerX1 <= MRcornerX1 && DcornerY2 >= MRcornerY1 && MRcornerY1 >= DcornerY1)
		{
			MRLengthX = MRcornerX2 - MRcornerX1;
			MRLengthY = DcornerY2 - MRcornerY1;
			MRKoorX = MRcornerX2 - MRLengthX/2;
			MRKoorY = MRcornerY1 + MRLengthY/2;
			DLengthX = DLengthX/2;
			DLengthY = DLengthY/2;
			attemps -= 1;
			printf("\nPartial Hit!, Marked Region Was Shrinked to [%.2f x %.2f],\n\nYour Detector Was Shrinked to [%.2f x%.2f], \n\nremaining attemps : %d\n\n", MRLengthX, MRLengthY, DLengthX, DLengthY, attemps);
			/*printf("10\n");
			printf("%f %f", MRKoorX, MRKoorY);*/
		}
		else if(DcornerY2 >= MRcornerY2 && DcornerY1 <= MRcornerY1 && DcornerX2 >= MRcornerX1 && MRcornerX1 >= DcornerX1)
		{
			MRLengthX = DcornerX2 - MRcornerX1;
			MRLengthY = MRcornerY2 - MRcornerY1;
			MRKoorX = MRcornerX1 + MRLengthX/2;
			MRKoorY = MRcornerY2 - MRLengthY/2;
			DLengthX = DLengthX/2;
			DLengthY = DLengthY/2;
			attemps -= 1;
			printf("\nPartial Hit!, Marked Region Was Shrinked to [%.2f x %.2f],\n\nYour Detector Was Shrinked to [%.2f x%.2f], \n\nremaining attemps : %d\n\n", MRLengthX, MRLengthY, DLengthX, DLengthY, attemps);
			/*printf("11\n");
			printf("%f %f", MRKoorX, MRKoorY);*/
		}
		else if(DcornerY2 >= MRcornerY2 && DcornerY1 <= MRcornerY1 && DcornerX2 >= MRcornerX2 && MRcornerX2 >= DcornerX1)
		{
			MRLengthX = DcornerX2 - MRcornerX2;
			MRLengthY = MRcornerY2 - MRcornerY1;
			MRKoorX = MRcornerX2 - MRLengthX/2;
			MRKoorY = MRcornerY2 - MRLengthY/2;
			DLengthX = DLengthX/2;
			DLengthY = DLengthY/2;
			attemps -= 1;
			printf("\nPartial Hit!, Marked Region Was Shrinked to [%.2f x %.2f],\n\nYour Detector Was Shrinked to [%.2f x%.2f], \n\nremaining attemps : %d\n\n", MRLengthX, MRLengthY, DLengthX, DLengthY, attemps);
			/*printf("12\n");
			printf("%f %f", MRKoorX, MRKoorY);*/
		}
		else if(DcornerY2 <= MRcornerY2 && DcornerY1 >= MRcornerY1 && DcornerX1 >= MRcornerX1 && DcornerX2 <= MRcornerX2)
		{
			MRLengthX = DcornerX2 - DcornerX1;
			MRLengthY = DcornerY2 - DcornerY1;
			MRKoorX = DcornerX2 - MRLengthX/2;
			MRKoorY = DcornerY2 - MRLengthY/2;
			DLengthX = DLengthX/2;
			DLengthY = DLengthY/2;
			attemps -= 1;
			printf("\nPartial Hit!, Marked Region Was Shrinked to [%.2f x %.2f],\n\nYour Detector Was Shrinked to [%.2f x%.2f], \n\nremaining attemps : %d\n\n", MRLengthX, MRLengthY, DLengthX, DLengthY, attemps);
			/*printf("13\n");
			printf("%f %f", MRKoorX, MRKoorY);*/
		}
		else if(DcornerY2 >= MRcornerY2 && MRcornerY1 >= DcornerY1 && DcornerX2 <= MRcornerX2 && DcornerX1 >= MRcornerX1)
		{
			MRLengthX = DcornerX2 - DcornerX1;
			MRLengthY = MRcornerY2 - MRcornerY1;
			MRKoorX = DcornerX2 - MRLengthX/2;
			MRKoorY = MRcornerY2 - MRLengthY/2;
			DLengthX = DLengthX/2;
			DLengthY = DLengthY/2;
			attemps -= 1;
			printf("\nPartial Hit!, Marked Region Was Shrinked to [%.2f x %.2f],\n\nYour Detector Was Shrinked to [%.2f x%.2f], \n\nremaining attemps : %d\n\n", MRLengthX, MRLengthY, DLengthX, DLengthY, attemps);
			printf("14\n");
			printf("%f %f", MRKoorX, MRKoorY);
		}
		else if(DcornerY2 <= MRcornerY2 && MRcornerY1 <= DcornerY1 && DcornerX2 >= MRcornerX2 && DcornerX1 <= MRcornerX1)
		{
			MRLengthX = MRcornerX2 - MRcornerX1;
			MRLengthY = DcornerY2 - DcornerY1;
			MRKoorX = MRcornerX2 - MRLengthX/2;
			MRKoorY = DcornerY2 - MRLengthY/2;
			DLengthX = DLengthX/2;
			DLengthY = DLengthY/2;
			attemps -= 1;
			printf("\nPartial Hit!, Marked Region Was Shrinked to [%.2f x %.2f],\n\nYour Detector Was Shrinked to [%.2f x%.2f], \n\nremaining attemps : %d\n\n", MRLengthX, MRLengthY, DLengthX, DLengthY, attemps);
			/*printf("15\n");
			printf("%f %f", MRKoorX, MRKoorY);*/
		}
		else
		{
			printf("ERROR");/*Case which is forgotton to be tested by me*/
		}	
	}
	return 0;	
}
