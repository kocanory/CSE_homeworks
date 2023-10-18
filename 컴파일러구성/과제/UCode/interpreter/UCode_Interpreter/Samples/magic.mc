void main()
{
  int list[225];
  int element;
  int i, j, n, index;

  read(element);
  while(element != 0)
   {
        if(element % 2 == 1)
        {
            i = 0;
            j = element/2;
            n = 1
            while (n <= element * element) {         // read a list
                index = i * element + j;
                list[index] = n
                i = (i - 1) % element;
                j = (j + 1) % element;
                n++;
            }
                i = 0;
                j = 0;
            while(i < element)
            {
                while(j < element)
                {   
                    index = i * element + j;
                    write(list[index]);
                    j++;
                }
                i++;
            }
        }
        read(element);
   } 
}