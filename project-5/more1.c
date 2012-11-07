#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

struct termios terminalSettings;
FILE *openFile;
int fdTerminal;
FILE *fpTerminal;

void catchSignal(int);
void catchSigWithFile(int);

int getInput();

int main(int argc, char* argv[])
{
	sigset_t sigCatch;
	sigemptyset(&sigCatch);
	sigaddset(&sigCatch, SIGINT);
	sigprocmask(SIG_BLOCK, &sigCatch, NULL);
	int rv;
	fdTerminal = open("/dev/tty", O_RDONLY);
	fpTerminal = fdopen(fdTerminal, "r");
	if((rv = (tcgetattr(fdTerminal, &terminalSettings))) == -1)
	{		
		signal(SIGINT, catchSignal);	
		sigprocmask(SIG_UNBLOCK, &sigCatch, NULL);
		printf("Couldn't save Terminal Settings.  Terminating Program.\n");
		fclose(fpTerminal);
		close(fdTerminal);
		return -1;
	}
	terminalSettings.c_lflag &= ~ECHO;
	tcsetattr(fdTerminal, TCSANOW, &terminalSettings);

	

	if(argc == 1)
	{	
		signal(SIGINT, catchSignal);	
		sigprocmask(SIG_UNBLOCK, &sigCatch, NULL);
		char read = ' ';
		int lead = 0;
		int bytes = 0;
		terminalSettings.c_lflag &= ~ECHO;
		tcsetattr(fdTerminal, TCSANOW, &terminalSettings);
		while(read != EOF)
		{
			if(lead == 1)
			{
				putchar(read);
				bytes++;
			}
			else
				lead = 1;
			read =  getc(stdin);
		}
		printf("\033[7m%i bytes\033[m\n", bytes);
		terminalSettings.c_lflag |= ECHO;
		tcsetattr(fdTerminal, TCSANOW, &terminalSettings);
		fclose(fpTerminal);
		close(fdTerminal);

		return 0;
	}
	else if(argc == 2)
	{		
		terminalSettings.c_lflag &= ~ICANON;
		tcsetattr(fdTerminal, TCSANOW, &terminalSettings);
			
		signal(SIGINT, catchSigWithFile);
		sigprocmask(SIG_UNBLOCK, &sigCatch, NULL);
		int showBoolean = 0;
		int hasShown = 0;
		int readLines = 0;
		int totalLines = 0;
		int respond = -1;
		char Line[512];
		openFile = fopen(argv[1], "rt");
		if(openFile == NULL)
		{
			printf("Failed to open the file: %s.  Aborting program.\n", argv[1]);
			return -3;
		}
		
		while(fgets(Line, 512, openFile) != NULL)
		{
			totalLines++;
		}
		fclose(openFile);
		fopen(argv[1], "rt");

		while((fgets(Line, 512, openFile) != NULL))
		{
			fputs(Line, stdout);
			readLines++;
			hasShown++;
			
			if(readLines == 23)
			{
				if(showBoolean == 0)
				{
					printf("\033[7m%s %02i%%\033[m", argv[1], ((hasShown*100)/totalLines));
				}
				else if(showBoolean == 1)
				{
					printf("\033[7m%02i%%\033[m", ((hasShown*100)/totalLines));
				}

				respond = getInput();
				if(respond == 2)
				{
					terminalSettings.c_lflag |= ECHO;
					tcsetattr(fdTerminal, TCSANOW, &terminalSettings);
					terminalSettings.c_lflag |= ICANON;
					tcsetattr(fdTerminal, TCSANOW, &terminalSettings);
					return 0;
				}
				if(respond == 1)
				{
					if(showBoolean == 0)
					{
						int i = 0;
						for(i = 0; i < (strlen(argv[1]) + 4); i++)
							printf("\b");
						showBoolean = 1;
					}
					else
						printf("\b\b\b");
					readLines = 0;
				}
				if(respond == 0)
				{
					if(showBoolean == 0)
					{
						int i = 0;
						for(i = 0; i < (strlen(argv[1]) + 4); i++)
							printf("\b");
						showBoolean = 1;
					}
					else
						printf("\b\b\b");
					readLines = 22;
				}
			}
		}
		if(readLines != 0)
		{
			printf("\b\033[7m%02i%%\033[m\n", ((hasShown*100)/totalLines));
		}

		fclose(openFile);
		terminalSettings.c_lflag |= ECHO;
		tcsetattr(fdTerminal, TCSANOW, &terminalSettings);
		fclose(fpTerminal);
		close(fdTerminal);
		return 0;
	}
	else
	{		
		signal(SIGINT, catchSignal);
		sigprocmask(SIG_UNBLOCK, &sigCatch, NULL);
		terminalSettings.c_lflag |= ECHO;
		tcsetattr(fdTerminal, TCSANOW, &terminalSettings);
		fclose(fpTerminal);
		close(fdTerminal);
		printf("You entered too many arguments!  Please only use one or two.\n");
		return -2;
	}
	return 5;  //THIS SHOULD NEVER HAPPEN.  But just in case.
}

void catchSignal(int SigNum)
{
	write(1, "\nCaught a Ctrl-C!  Closing files now...\n", 40);
	terminalSettings.c_lflag |= ECHO;
	tcsetattr(fdTerminal, TCSANOW, &terminalSettings);
	fclose(fpTerminal);
	close(fdTerminal);
	exit(0);
}

void catchSigWithFile(int SigNum)
{
	write(1, "\nCaught a Ctrl-C!  Closing all files now...\n", 45);
	terminalSettings.c_lflag |= ECHO;
	tcsetattr(fdTerminal, TCSANOW, &terminalSettings);
	terminalSettings.c_lflag |= ICANON;
	tcsetattr(fdTerminal, TCSANOW, &terminalSettings);
	fclose(fpTerminal);
	close(fdTerminal);
	fclose(openFile);
	exit(0);
}

int getInput()
{
	int input;
	while(1)
	{
		input = getc(stdin);
		if(strchr(" ", input))
			return 0;
		if(strchr("\n", input))
			return 1;
		if(strchr("qQ", input))
			return 2;
	}
}
