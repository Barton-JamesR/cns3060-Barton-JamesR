//A short aside:  I don't put documentation in next to every line of code that I write; so much of it is the same between simulations that I felt it to be excessive.
//	Instead, the first time a particular variable, action, etc. comes up I will explain it there, if there isn't an explanation next to something I've probably
//	already justified it earlier in the file.

#include <stdio.h>//For all the streamy-stuff like scanf().
#include <stdlib.h>//For the abs() function, which I will use a lot.

const int INITIALTRACK = 15;  //I used to have the number 15 scattered throughout my code, but it always meant the same thing, so I created a global constant instead.  And because Magic Numbers are bad form.
const int MAXARRAYSIZE = 100;  //This is used exactly once, on line 27, and then never again.  But it was a magic number, so...

void FirstCome(int origArray[], int maximum, int limit);  //The algorithm for the First-Come, First-Served method.
void ShortestSeek(int origArray[], int maximum, int limit);  //The algorithm for the Shortest Seek method.
void ScanLook(int origArray[], int maximum, int limit);  //The algorithm for the Scan-Look(Elevator) method.

int main(int argc, char* argv[])
{
	int maximum = INITIALTRACK;  //This represents the higest value in the array, or the initial track.  Set to the inital track just in case.
	int inc = 0;  //This is my 'increment' variable; I will use this for any for loops I initiate.
	int varify = 0;  //This is the output variable for scanf() during the user input, used to detect EOF errors or invalid input.
	int control = 0;  //This is how I deal with those invalid inputs.
	int variable = 0;  //This is the actual input from the user, added to the array each time.
	int limit = MAXARRAYSIZE;  //This is the number of items in the array, initialized to 100 (as a worst case).

	printf("Please enter up to 99 track numbers, seperated by spaces or new lines, followed by a negative number.\n");  //Prompts the user for input.
	//I tend to space out unrelated parts of a function, like the pre-program output and the initialization of an array.  Like this.
	int origArray[limit];  //The user's input stored in an array of size 100.  Subsequent arrays will be the actual size of the input.
	for (inc = 0; inc < limit; inc++)
	{
		origArray[inc] = 0;  //Make every number into a 0, to remove residual data from the last use of the memory.
	}

	for(inc = 0; inc < limit; inc++)
	{
		varify = scanf("%d", &variable);  //Scanning for numbers; the 'varify' variable is to catch EOF or invalid input errors.
		if(varify == EOF)
		{
			printf("Please input a valid number.\n");
			control = 0;
			while((control = getchar()) != '\n');  //this while will completely flush whatever remains in the input, letting us get on with our program.
			inc--;  //takes us back a step to make sure that we don't leave any holes in our array.
		}
		else if(varify == 0)
		{
			printf("Please input a number.\n");
			control = 0;
			while((control = getchar()) != '\n');
			inc--;
		}
		else
		{
			origArray[inc] = variable;  //Assigns the value into the next open spot in the array.
			if(variable > maximum)
				maximum = variable;  //Updates the maximum value, if applicable.
			if(variable < 0)
			{
				if(inc == 0)
				{
					printf("No entries detected in the array; please re-open the program and add new entries.\n");
					return -1;  //Typing a negative number as your first entry?  Shame on you.  Don't do that, it breaks the program...
				}			//Which is why I added this little conditional to the program, just in case.
				limit = inc;  //When the program catches a negative number, it sets the limit to the current increment, saving the number of inputs.  Then, because the limit that the increment is being compared to is changed to equal it, when the loop advances, it terminates.
			}
		}
	}
	//Here, we call upon the three methods in order to actually complete the assignment.
	FirstCome(origArray, maximum, limit);
	ShortestSeek(origArray, maximum, limit);
	ScanLook(origArray, maximum, limit);

	return 0;  //Adding a return here to indicate that all is well.
}

//Admittedly, maximum isn't used here, but I like to keep similar functions consistent.
void FirstCome(int origArray[], int maximum, int limit)
{
	int inc = 0;
	int traversed = 0;  //traversed keeps track of the "Total Tracks Traversed" statistic for the end.
	//We call a new array here so that we don't overwrite the origArray[].  Not as important here, but a good idea for the other two.
	int fcfsArray[limit];
	for(inc = 0; inc < limit; inc++)
	{
		fcfsArray[inc] = origArray[inc];
	}	//No need to initalize the fcfsArray[] members to 0; we completely fill the array with existing data.
	
	printf("\nFirst-Come, First-Served\nHead Movement\t\tTracks Traversed\n");  //We begin by printing the section header.

	printf("Tracks %i - %i\t\t%i\n", INITIALTRACK, fcfsArray[0], abs(INITIALTRACK - fcfsArray[0]));  //This little segment is to simulate having 'INITIALTRACK' as an
	traversed = (traversed + abs(INITIALTRACK - fcfsArray[0]));			//existing array member; in the following methods, this is
	for(inc = 0; inc < (limit - 1); inc++)					//generally a shortened variant that uses a constant for the
	{                            						//Array[current].
		printf("Tracks %i - %i\t\t%i\n", fcfsArray[inc], fcfsArray[inc + 1], abs(fcfsArray[inc] - fcfsArray[inc + 1]));
		traversed = (traversed + abs(fcfsArray[inc] - fcfsArray[inc + 1]));  //This is pretty simple; it just traverses the array,
	}									//keeping track of the distance travelled.

	printf("\nTotal Tracks Traversed\t%i\n", traversed);  //Tells the user exactly how many tracks were traversed.
}

void ShortestSeek(int origArray[], int maximum, int limit)
{
	int inc = 0;
	int traversed = 0;
	int dist = maximum + 1;  //We assign maximum + 1 here so that the first value we see will ALWAYS have a shorter distance.
	int target = 0;  //This is the user-inputted track we're currently considering moving to next, unless a better candidate comes up.
	int current = -1;  //Assigned to a perfectly sensible value, because '15' comes before the array input.  It makes sense, okay?
	int activated = 0;  //This tracks how many values we've already moved to.  Once activated == limit, we've reached everything.

	int ssArray[limit];  //This one is named ssArray[] for shortest seek.  The first one was fcfsArray[] for first-come, first-serve.
	for(inc = 0; inc < limit; inc++)
	{
		ssArray[inc] = origArray[inc];
	}
	
	printf("\nShortest Seek\nHead Movement\t\tTracks Tracks Traversed\n");

	for(inc = 0; inc < limit; inc++)
	{  //Again, this little for loop and the code between it and the while loop are to simulate having a '15' tacked on to the front.
		if(abs(INITIALTRACK - ssArray[inc]) < dist)
		{
			dist = abs(INITIALTRACK - ssArray[inc]);
			target = inc;
		}
	}
	printf("Tracks %i - %i\t\t%i\n", INITIALTRACK, ssArray[target], abs(INITIALTRACK - ssArray[target]));
	traversed = (traversed + INITIALTRACK - ssArray[target]);
	current = target;
	activated++;
	dist = maximum + 1;
	while(activated < limit)
	{  //Whenever I have three or more conditions connected in a single if() by '&&', I break them up for ease of reading.
		for(inc = 0; inc < limit; inc++)
		{  //I add the extra space between each if because I have trouble reading them if I don't.  I'll take these out in the
			if(inc != current)	//future if you don't like it.
			{
				if(ssArray[inc] >= 0)
				{	//The conditionals are asking if it's:  not the current value, not a negative value, and closer.
					if(abs(ssArray[current] - ssArray[inc]) < dist)
					{
						dist = abs(ssArray[current] - ssArray[inc]);
						target = inc;
					}
				}
			}
		}
		printf("Tracks %i - %i\t\t%i\n", ssArray[current], ssArray[target], abs(ssArray[current] - ssArray[target]));
		traversed = (traversed + abs(ssArray[current] - ssArray[target]));
		ssArray[current] = -1;  //This entry ensures we don't just bounce between two specific values, by making the current one
		current = target;	//invalid.  It then assigns the target track the current track to check from there.
		activated++;
		dist = maximum + 1;
	}

	printf("\nTotal Tracks Traversed\t%i\n", traversed);
}

void ScanLook(int origArray[], int maximum, int limit)
{
	int inc = 0;
	int traversed = 0;
	int current = -1;
	int target = -1;
	int direction = 1; //Assign a positive direction because the head moved from 12->15, a positive change.
	int dist = maximum + 1;
	int activated = 0;

	int slArray[limit];  //Similarly to the last two, this one is named slArray[] for scan-look.  Good to be consistent.
	for(inc = 0; inc < limit; inc++)
	{
		slArray[inc] = origArray[inc];
	}

	printf("\nScan-Look\nHead Movement\t\tTracks Traversed\n");

	if(maximum == INITIALTRACK)
	{	//This short conditional makes sure that it doesn't try to go farther than track 15 if nothing greater than 15 was entered.
		direction = -1;
	}
	for(inc = 0; inc < limit; inc++)
	{	//Next, we check each number in the array to find the closest track in the appropriate direction.
		if(abs(INITIALTRACK - slArray[inc]) < dist)
		{	
			if(direction == 1 && slArray[inc] >= 15)
			{	//This ensures that it only finds higher numbers if it's going upward,
				dist = abs(INITIALTRACK - slArray[inc]);
				target = inc;
			}
			if(direction == -1 && slArray[inc] <= 15)
			{	//While this ensures that only lower numbers are found if going downward.
				dist = abs(INITIALTRACK - slArray[inc]);
				target = inc;
			}
		}	
	}		

	printf("Tracks %i - %i\t\t%i\n", INITIALTRACK, slArray[target], abs(INITIALTRACK - slArray[target]));
	traversed = (traversed + abs(INITIALTRACK - slArray[target]));
	current = target;
	if(slArray[current] == maximum)
	{	//This conditional makes sure we don't ever pass the maximum value by, searching ever higher for
		direction = -1;	//A value that can never be found.  Instead, it just turns around and goes back.
	}
	activated++;
	dist = maximum + 1;
	while(activated < limit)
	{	//This all pretty much does the same thing as the initial case above, with some extra conditions:
		for(inc = 0; inc < limit; inc++)
		{	
			if(current != inc)
			{	//IF we're not looking at the same track as the one we're comparing to, and
				if(slArray[inc] >= 0)
				{	//IF we've never visited that track before, and
					if(abs(slArray[current] - slArray[inc] < dist))
					{	//IF the distance is actually shorter than the distance to our current target, and
						if(direction == 1 && slArray[inc] >= slArray[current])
						{	//If the possible target is higher than our current track AND we're travelling upward, or
							dist = abs(slArray[current] - slArray[inc]);
							target = inc;
						}	//We get a new target to compare to.
						if(direction == -1 && slArray[inc] <= slArray[current])
						{	//If the possible target is lower than our current track AND we're travelling downward...
							dist = (slArray[current] - slArray[inc]);
							target = inc;
						}	//We get a new target to compare to.
					}
				}
			}
		}
		printf("Tracks %i - %i\t\t%i\n", slArray[current], slArray[target], abs(slArray[current] - slArray[target]));
		traversed = (traversed + abs(slArray[current] - slArray[target]));
		slArray[current] = -1;
		current = target;
		if(slArray[current] == maximum)
		{
			direction = -1;
		}
		activated++;
		dist = maximum + 1;
	}

	printf("\nTotal Tracks Traversed \t%i\n", traversed);
}
