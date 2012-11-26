#include <dirent.h> //Useful for the Directory Header
#include <stdio.h>  //There isn't anything that says we *can't* use printf(), so I'm going to abuse the privelege.

#include <sys/stat.h>
#include <sys/types.h>
void dirRead(const char* filePath);

int main(int argc, char* argv[])
{
	if(argc == 1)  //If there is only one argument, the user didn't enter a directory to search.
	{              //We then proceed to run our recursive function within our current directory.
		dirRead("./");
	}
	else
	{
		dirRead(argv[1]);
	}
	return 0;
}

void dirRead(const char* filePath)
{
	DIR *dirPointer = NULL;
	struct dirent *entPointer = NULL;

	if(!(dirPointer = opendir(filePath)))
	{
		printf("Unable to open the file or directory specified.  Please check your spelling and try again.\n");
		return;
	}	
	if(!(entPointer = readdir(dirPointer)))
	{	
		printf("Couldn't initialize the dirent.  Send this in to the coder for debugging.\n");
		return;
	}	
	struct stat* fileStat;
	int status;
	do
	{
		if(strcmp(entPointer->d_name, ".") != 0 && strcmp(entPointer->d_name, "..") != 0) //Funfact:  . and .. cause all sortsa endless recursion!
		{
			
			char path[1024];
			sprintf(path, "%s/%s", filePath, entPointer->d_name);
			if((status = lstat(path, fileStat)) == 0)			
			{
  				printf("%lld B\t   %s\n", (long long)fileStat->st_size, entPointer->d_name);
			}
			else
			{
				printf("\t   %s\n", entPointer->d_name);
			}
			if(entPointer->d_type == DT_DIR)
			{
				dirRead(path);
			}
		}
	}while(entPointer = readdir(dirPointer));
	closedir(dirPointer);
}
