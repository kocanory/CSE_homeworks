#include <stdio.h>

int main(void)
{
	
	int i, j, k;
	
	for (i = 0; i <= 7; i++)
	{
		
		for (j = 7; j >= 0; j--)
		{
			if (j <= i)
			{
				printf("%d", j);
			}
			
			else
			{
				printf(" ");
			}
		}
		
		
		for (k = 1; k <= i; k++)
		{
			printf("%d", k);
		}
			
		puts("");	
	}
	
	return 0;
}