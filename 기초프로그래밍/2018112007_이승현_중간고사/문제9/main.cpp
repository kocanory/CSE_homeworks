#include <stdio.h>

int main(void)
{
	
	for (int i = 1; i <= 100; i++)
		{
			if (i % 2 == 0)
				continue;
			else if (i % 3 == 0)
				continue;
			else if (i % 5 == 0)
				continue;
			else if (i % 7 == 0)
				continue;
			

			else if(i == 43 || i == 89)
			{
				printf("\n");
			}

			printf("%d ", i);
			
		}
	puts("");

	return 0;
}