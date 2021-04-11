#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 16

enum { FALSE, TRUE };

/* define structure externally to ensure
   that it's available to all functions */
struct family {
	char name[SIZE];
	char relationship[SIZE];
	int age;
	struct family *next;
};

/* read standard input, discard newline */
char *input(void)
{
	static char buffer[SIZE];
	char *r;
	int x;

	/* initialize the buffer */
	buffer[0]='\0';

	/* gather input */
	r = fgets(buffer,SIZE,stdin);
	if( r==NULL )
	{
		fprintf(stderr,"Input error\n");
		exit(1);
	}

	/* remove the newline */
	for(x=0; x<SIZE; x++)
	{
		/* remove newline */
		if( buffer[x]=='\n' )
		{
			buffer[x]='\0';
			break;
		}
	}

	return(buffer);
}

/* allocate a new structure */
struct family *allocate(void)
{
	struct family *p;

	p = (struct family *)malloc( sizeof(struct family) * 1);
	if( p==NULL )
	{
		fprintf(stderr,"Unable to allocate memory\n");
		exit(1);
	}

	return(p);
}

/* fill the structure */
void fill(struct family *s)
{
    char temp[SIZE];

	printf("What is your name?: ");
    /* family->name is an char to pointer, so
       the ampersand isn't required */
    strcpy(s->name,input() );

    printf("What is your relationship?: ");
    /* family->relationship is an char to pointer, so
       the ampersand isn't required */
    strcpy(s->relationship,input() );

    printf("How old are you?: ");
    /* person->age is an integer, not a pointer, so
       the ampersand is required */
    strcpy(temp,input() );
    s->age = atoi(temp);
    /* the 'next' member is filled in the main() Menu function */
}

/* output the list */
void output(struct family *s)
{
	int cont;
	cont = 0;

	while( s!=NULL )
	{
		cont += 1;
		printf("%d: %s is the %s in the family and have %d years old\n",
				cont,
				s->name,
				s->relationship,
				s->age
			  );
		s = s->next;
	}
}

void save_data(struct family *s, const char *filename)
{
    FILE *fp;
    struct family *curr;

    printf("Saving...");
	fp = fopen(filename,"w");
	if( fp==NULL )
	{
		fprintf(stderr,"Unable to create file\n");
		exit(1);
	}

	/* second write all structures */
	curr = s;
	while( curr!=NULL )
	{
		fwrite(curr,sizeof(struct family),1,fp);
		curr = curr->next;
	}

	/* close the file */
	fclose(fp);
	puts("saved!");
}

void read_data(struct family *s, const char *filename)
{
    int Done, x;
    struct family *curr;
    FILE *fp;

    /* open the file */
	puts("Reading data...");
	fp = fopen(filename,"r");

	if ( fp==NULL )
	{
		fprintf(stderr,"Unable to open file\n");
		exit(1);
	}

    x = 0;
	while( Done==FALSE )
	{
	    if (x == 0)
        {
            /* allocate structure */
            curr = allocate();
        }
        else
        {
			curr->next = allocate();
			/* update the pointer member,
			   discarding the saved info */
			curr = curr->next;
		}
		/* use fread to fill the structure */
		fread(curr,sizeof(struct family),1,fp);
		if (curr == NULL)
        {
            Done = TRUE;
        }
	}
	/* cap the final structure */
	//curr->next = NULL;

    s = curr;
	/* close the file */
	fclose(fp);
	puts("readed!");
}


int main()
{
	struct family *first,*current;
	int done;
	static int cont1;
	char command[SIZE];
	char file0[] = "chalengerdata.dat";

	/* initialize first record to NULL */
	first = NULL;

	/* initialize cont of record */
    cont1 = 0;

	/* main menu and input loop */
	done = FALSE;
	puts("Family Database");
	while(!done)
	{
		/* initialize the current pointer to
		   the start of the list */
		   if (cont1 == 0)
           {
               current = first;
           }
		/* output menu */
		puts("Menu:");
		puts("A - Add record");
		puts("D - Delete record");
		puts("L - List all records");
		puts("O - Open");
		puts("S - Save");
		puts("Q - Quit");
		printf("Choice: ");
		/* read input */
		strcpy(command,input() );
		/* process selection */
		switch(command[0])
		{
			/* add a record */
			case 'A':
			case 'a':
			    if (cont1 == 0)
                {
                    /* allocate structure */
                    first = allocate();
                    current = first;
                }
                else
                {
                    /* set the next structure link */
			        current->next = allocate();
			        /* make the next structure the
			        current structure */
			        current = current->next;
                }
                fill(current);
                cont1 =+ 1;
                current->next = NULL;
				break;
			/* delete a record */
			case 'D':
			case 'd':


				break;
			/* list all records */
			case 'L':
			case 'l':
			    output(first);
				break;
			/* open/retrieve existing records */
			case 'O':
			case 'o':
			    read_data(first, file0);
				break;
			/* save all records */
			case 'S':
			case 's':
                save_data(first, file0);
				break;
			/* quit the program */
			case 'Q':
			case 'q':
				done = TRUE;
				puts("Bye!");
				break;
			/* something weird typed */
			default:
				puts("Unrecognized command");
		}
	}
	return(0);
}
