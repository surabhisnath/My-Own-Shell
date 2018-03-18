#include <stdio.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[])
{

	int iflag=0;
	int rflag=0;
	for(int i=1; i<argc; i++)
   	{
   		if(argv[i][0]=='-')
   		{
   			if(strcmp(argv[i],"-R")==0)
   				rflag=1;
   			else if(strcmp(argv[i],"-I")==0)
   				iflag=1;
   			else if(strcmp(argv[i],"-IR")==0 || strcmp(argv[i],"-RI")==0)
   			{
   				printf("date: multiple output formats specified\n");
   				return 0;
   			}

   			else
   			{
   				printf("date: invalid option -- '%s'\n",argv[i]);
   				return 0;
   			}
   		}

   		else
   		{

   			printf("date: invalid date ‘%s’\n",argv[i]);
   			return 0;
   		}	
   	}

   	if(rflag==1 && iflag==1)
   	{
   		printf("date: multiple output formats specified");
   		return 0;
   	}


	time_t t;
	time(&t);
	char *var=ctime(&t);

	if(argc==1)
   		printf("%s",var);

   	else if(iflag==1)
   	{
   		printf("%c%c%c%c-",var[20],var[21],var[22],var[23]);
   		int i=0;
   		int j=0;

   		if(var[4]=='J')
   		{
   			i=0; j=1;
   		}

   		else if(var[4]=='F')
   		{
   			i=0; j=2;
   		}

   		else if(var[4]=='M')
   		{
   			if(var[6]=='r')
   			{
   				i=0; j=3;
   			}

   			else if(var[6]=='y')
   			{
   				i=0; j=5;
   			}	
   		}

   		else if(var[4]=='A')
   		{
   			if(var[6]=='r')
   			{
   				i=0; j=4;
   			}

   			else if(var[6]=='g')
   			{
   				i=0; j=8;
   			}
   		}

   		else if(var[4]=='J')
   		{
   			if(var[6]=='n')
   			{
   				i=0; j=6;
   			}

   			else if(var[6]=='l')
   			{
   				i=0; j=7;
   			}	
   		}

   		else if(var[4]=='S')
   		{
   			i=0; j=9;
   		}

   		else if(var[4]=='O')
   		{
   			i=1; j=0;
   		}

   		else if(var[4]=='N')
   		{
   			i=1; j=1;
   		}

   		else if(var[4]=='D')
   		{
   			i=1; j=2;
   		}

   		printf("%d%d-",i,j);
   		printf("%c%c\n",var[8],var[9]);
   	}

   	else if(rflag==1)
   	{
   		char *temp=strtok(var," \n");
   		char *to[5];
   		int c=0;
   		while(temp!=NULL)
		{
			to[c++]=temp;
			temp=strtok(NULL," \n");
		}

		printf("%s, %s %s %s %s +0530\n",to[0],to[2],to[1],to[4],to[3]);
   	}

   	return 0;
}