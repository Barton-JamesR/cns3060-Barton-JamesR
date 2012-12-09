#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void printInfo();
int doProgram();
void childDoesWork();

void parentUSR1Rec(int arg);
void parentUSR2Rec(int arg);
void childUSR1Rec(int arg);
void childUSR2Rec(int arg);

int main(int argc, char* argv[])
{
	printInfo();
	if(doProgram() == -1)
	{
		perror("Something went wrong... sorry.\n");
		return -1;
	}
	return 0;
}

void printInfo()
{
	printf("Name:  James R. Barton\n");
	printf("Class: CS 3060-601\n\n");
}

char HandleP1[] = "****Parent SIGUSR1 handler -- Recieved a 'task started' signal from child****\n";
void parentUSR1Rec(int arg)
{
	write(1, HandleP1, strlen(HandleP1));
}

char HandleP2[] = "****Parent SIGUSR2 handler -- Recieved a 'task completed' signal from child****\n";
void parentUSR2Rec(int arg)
{
	write(1, HandleP2, strlen(HandleP2));
}

char HandleC1[] = "****Child SIGUSR1 handler -- Recieved a 'task start' signal from parent****\n";
void childUSR1Rec(int arg)
{
	write(1, HandleC1, strlen(HandleC1));
}

char HandleC2[] = "****Child SIGUSR2 handler -- Recieved a 'task complete verification' signal from parent****\n";
void childUSR2Rec(int arg)
{
	write(1, HandleC2, strlen(HandleC2));
}

void childDoesWork()
{
	int nap;
	printf("Komachi is slacking off... again...(as opposed to, you know, doing work...)\n");
	//It might as well do *something* in this block.  It was this or put a Shmup here, and I'm not that good at C...
}

int doProgram()
{
	pid_t ChildPID;

	sigset_t SigPrep;
	sigset_t Sig1;
	sigset_t Sig2;

	sigfillset(&Sig1);
	sigdelset(&Sig1, SIGUSR1);
	sigfillset(&Sig2);
	sigdelset(&Sig2, SIGUSR2);

	sigemptyset(&SigPrep);
	sigaddset(&SigPrep, SIGUSR1);
	sigaddset(&SigPrep, SIGUSR2);
	
	sigprocmask(SIG_BLOCK, &SigPrep, NULL);
	struct sigaction Act;
	Act.sa_handler = parentUSR1Rec;
	sigemptyset(&Act.sa_mask);
	Act.sa_flags = 0;
	if(sigaction(SIGUSR1, &Act, NULL) < 0)
		return -1;
	Act.sa_handler = parentUSR2Rec;
	if(sigaction(SIGUSR2, &Act, NULL) < 0)
		return -1;
	sigprocmask(SIG_UNBLOCK, &SigPrep, NULL);
	
	ChildPID = fork();
	if(ChildPID == -1)
		return -1;
	if(ChildPID == 0) //This is where the child process doesn't work at all, but says it does.
	{	//...Yeah, I named it Komachi.  I couldn't resist.  So what?
		sigprocmask(SIG_BLOCK, &SigPrep, NULL);
		Act.sa_handler = childUSR1Rec;
		if(sigaction(SIGUSR1, &Act, NULL) < 0)
			return -1;
		Act.sa_handler = childUSR2Rec;
		if(sigaction(SIGUSR2, &Act, NULL) < 0)
			return -1;
		sigprocmask(SIG_UNBLOCK, &SigPrep, NULL);
		printf("CHILD:   Child process is now running, awaiting Parental Approval...\n");
		sigsuspend(&Sig1);
		printf("CHILD:   Child process is notifying parent that it is starting the task...\n");
		sleep(3);
		kill(getppid(), SIGUSR1);
		childDoesWork();
		printf("CHILD:   Child process is finished working.  Waiting for parent verification...\n");
		//This one almost said 'Child process is napping, waiting to be woken up by parent...'.
		sigsuspend(&Sig2);
		printf("CHILD:   Woken up by the Parent Process.  Sending final verification now...\n");
		kill(getppid(), SIGUSR2);
		printf("CHILD:   Signal Sent.  Terminating child process now...\n");
	}
	else //This is where the parent process thinks the child does work.
	{	//I was very temped to name it Shikieiki, but AGAIN, pay that no mind.
		printf("PARENT:   Child Process has been Created; finally taking a break...\n");
		sleep(3);
		printf("PARENT:   The Parent Process has awoken is waiting warmly...\n");
		kill(ChildPID, SIGUSR1);
		sigsuspend(&Sig1);
		sleep(3);
		kill(ChildPID, SIGUSR2);
		printf("PARENT:   Sent a message to the child process requesting verification...\n");
		sigsuspend(&Sig2);
		printf("PARENT:   Verification recieved.  Terminating parent process...\n");
		wait();//I put this part in to make sure that the child was ended as well.  Unsure if this was necessary, but it made me feel better inside.
	}
	return 0;
}
