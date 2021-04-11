#include <stdio.h>
#include <stdlib.h>

int main()
{
    struct human {
        char name[32];
        int age;
    } *toread;
    const char filename[] = "saved.dat";
	FILE *fp;

	/* allocate storage */
	toread = (struct human *)malloc( sizeof(struct human) * 1);

    if (toread == NULL)
    {
        fprintf(stderr, "Unable to allocate storage\n");
        exit(1);
    }

	/* open the file */
	fp = fopen(filename,"r");
	if( fp==NULL )
	{
		fprintf(stderr,"Unable to read file\n");
		exit(1);
	}

	/* fill the buffer */
	fread(toread,sizeof(struct human),1,fp);

	/* close the file */
	fclose(fp);
	puts("Data read");

	/* output results */
	printf("NAME: %sAGE: %d\n",
			toread->name,
			toread->age
		 );

	return(0);
}
