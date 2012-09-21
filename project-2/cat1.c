#include <stdio.h>

#define NUMB = 1;
#define NONUMB = 0;

void printlines(int linenumbers)
{
	int compare = linenumbers;
	int line = 0;
	char buffer[25];
	while(!ferror(stdin) && !feof(stdin))
	{
		fgets(buffer, 25, stdin);
		if( 0 < linenumbers)
		{
			printf("     %d  ", line);
			line++;
		}
		fputs(buffer, stdout);
	}
}

int printfiles(int linenumbers, char *filename)
{
	char buffer[64]; //I made this particularly long to make sure I caught the entire buffer; I can shorten this if necessary, but I think it's better safe than sorry.
	FILE *input;
	int line;
	line = 1;
	if((input = fopen(filename, "r")) == NULL)
	{
		printf("Could not open the file %s\n", filename);
	}
	else
	{
		while( fgets (buffer, 64, input) != NULL )
		{
			if(linenumbers == 1)
			{
				printf("     %d  ", line);
				line++;
			}	
			fputs ( buffer, stdout );
		}
		
		fclose(input);
	}
	return 0;
}

int main( int argc, char *argv[] )
{
	int numbers;
	numbers = 0;
	char buffer[25];
	if(argc == 1)
	{
		printlines(0);  //For the record:  This doesn't work with my #defined NONUMB... qq
	}
	if(argc == 2 && strncmp("-n", argv[1], 2) == 0)
	{
		printlines(1);
	}
	else
	{
		if( argc > 1 )
		{
			int argctr;
			argctr = 1; 
			if( strncmp(argv[1], "-n", 2) == 0 )
			{
				numbers = 1;
				argctr++;
			}
			while (argctr < argc)
			{
				printfiles(numbers, argv[argctr]);
				argctr++;
			}
		}
	}
	return 0;
}
