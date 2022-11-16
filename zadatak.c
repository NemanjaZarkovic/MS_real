#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main ()
{
	FILE* fp1;
	FILE* fp2;
	FILE* fp3;
	float faktor_ispune = 0;
	char *str1;
	char *str2;
	size_t num_of_bytes = 6;
	char tval1, tval2, tval3, tval4;
	float ispuna =0;
	int svetli = 1;
	int taster_novi, taster_stari = 0;
	long int perioda = 20000L;
	
	while (1)
	{
		printf("faktor_ispune = %f\n", faktor_ispune);
		fp1 = fopen("/dev/switch", "r");
		if (fp1 == NULL)
		{
			puts("Problem pri otvaranju fp1\n");
			return -1;
		}
		
		str1 = (char *)malloc(num_of_bytes + 1);
		getline(&str1, &num_of_bytes, fp1);
		
		if (fclose(fp1))
		{
			puts("Problem pri zatvaranju fp1\n");
			return -1;
		}
		
		tval1 = str[2] - 48;
		tval2 = str[3] - 48;
		tval3 = str[4] - 48;
		tval4 = str[5] - 48;
		free(str1);
		
		if (sval1 == 0)
		{
			svetli = 0;
		}
		else
		{
			svetli = 1;
			if (sval2 == 1) ispuna += 4;
			if (sval2 == 1) ispuna += 2;
			if (sval2 == 1) ispuna += 1;
		}
		
		ispuna *= 0.05;
		
		fp2 = fopen("/dev/button", "r");
		if(fp2 == NULL)
		{
			puts("Problem pri otvaranju fp2\n");
			return -1;
		}
		
		str2 = (char *)malloc(num_of_bytes + 1);
		getline(&str2, &num_of_bytes, fp2);
		
		if(fclose(fp2))
		{
			puts("Problem pri zatvaranju fp2\n");
			return -1;
		}
		taster_novi = 0;
		if(str2[2]-48 == 1) taster_novi = 1;
		if(str2[3]-48 == 1) taster_novi = 2;
		
		if (taster_novi != taster_stari)
		{
			taster_stari = taster_novi;
			
			free(str2);
			
			if (taster_novi == 1 && faktor_ispune < 1)
			{
				faktor_ispune += ispuna;
				printf("Faktor ispune povecan\n");
				
				if( faktor_ispune > 1)
				{
					faktor_ispune = 1;
				}
			}
			if (taster_novi == 2 && faktor_ispune > 0)
			{
				faktor_ispune -= ispuna;
				printf("Faktor ispune smanjen\n");
				
				if( faktor_ispune < 0)
				{
					faktor_ispune = 0;
				}
			}
		}
		
		fp3 = fopen("/dev/led", "w");
		if (fp3 == NULL)
		{
			puts("Problem pri otvaranju fp3\n");
			return -1;
		}
		
		if(svetli == 0)
		{
			fputs("0x00\n", fp3);
			printf("Diode ne svetle\n");
		}
		else
		{
			fputs("0x0F\n", fp3);
			if (fclose(fp3))
			{
				puts("Problem pri zatvaranju fp3\n");
				return -1;
			}
			usleep(faktor_ispune + period*100);
			
			fp3 = fopen("/dev/led","w");
			if(fp3==NULL)
			{
				puts("Problem pri otvaranju fp3\n");
				return -1;
			}
			
			fputs("0x00\n", fp3);
			if(fclose(fp3))
			{
				puts("Problem pri zatvaranju fp3\n");
				return -1;
			}
			usleep((1-faktor_ispune)*period*100);
		}
	}
}