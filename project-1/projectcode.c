#include <stdio.h>

int main( int argc, char *argv[] )
{
	printf( "James Richard Barton\n" );
	printf( "CNS 3060-601\n\n" );
	int i = 1;
	while( i < argc )
	{
		printf( "%s\n", argv[i] );
		i++;
	}
	return 0;
}
