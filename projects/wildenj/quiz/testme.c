#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function
	char singleChar;
	int range, offset;
	
	range = 126-32+1; //ASCII dec codes we are interested in 
	offset = 32; // where we want to start from
	singleChar = (char) (rand()%range+offset);
	
	return singleChar;
}

char *inputString()
{
    // TODO: rewrite this function
	char *stringPtr;
	char randString[6];
	int i, range, offset;
	
	stringPtr = malloc(sizeof(char)*6);
	memset(randString,0, sizeof(char)*6); // lets us reduce our random search by initializing everything to null
	
	range = 122 - 97 + 1;
	offset = 97;
	
	for (i=0; i<5; i++)
	{
		randString[i] = (char) (rand()%range+offset);
	}
	memcpy(stringPtr,randString, sizeof(char)*6);;
	//printf("randStrings:%s\n%s\n",stringPtr,randString);
    return stringPtr;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
	free(s);
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
