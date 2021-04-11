#include <stdio.h>
#include <stdlib.h>

int main()
{
    struct human {
        char name[32];
        int age;
    } *person;
    const char filename[] = "saved.dat";
    char *r;
	FILE *fp;

    /* allocate structure */
    person = (struct human *)malloc( sizeof(struct human) * 1);

    if (person == NULL)
    {
        fprintf(stderr, "Unable to allocate storage\n");
        exit(1);
    }

    /* fill the person structure; prompt the user */
	printf("Enter your name: ");
	/* person->name is an string, not a pointer, so
	   the ampersand isn't required */
	r = fgets(person->name,32,stdin);

	if (r == NULL)
    {
        fprintf(stderr, "Input error\n");
        exit(1);
    }

	printf("How old are you: ");
	/* person->age is an integer, not a pointer, so
	   the ampersand is required */
	scanf("%d",&person->age);

    /* write the structure to a file */
	/* open the file */
	fp = fopen(filename,"w");
	if( fp==NULL )
	{
		fprintf(stderr,"Unable to create %s\n",filename);
		exit(1);
	}

	/* write the structure */
	fwrite(person,sizeof(struct human),1,fp);
	/* close the file */
	fclose(fp);
	printf("Data written to %s\n",filename);

    return(0);
}
