void main()
{
    int list[225];
    int element;
    int i, j, n, index, size;

    read(element);
    while(element != 0)
    {
        if(element % 2 == 1)
        {
            size = element * element;
            i = 0;
            j = element/2;
            index = i * element + j;
            n = 0;

            while (n < size) { 
		        ++n; 
                list[index] = n;
                if(n % element == 0) i++;
                else{
                    --i;
                    --j;
                }
                if(i < 0) i = element - 1;
                if(j < 0) j = element - 1;
                index = i * element + j;
            }
            n = 0;
            while(n < size)
            {
                write(list[n]);
                ++n;
                if(n % element == 0) lf();
            }
        }
        read(element);
    } 
}