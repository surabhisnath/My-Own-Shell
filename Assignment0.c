#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#define Red   "\x1B[31m"
#define Green   "\x1B[32m"
#define Yellow   "\x1B[33m"
#define Blue   "\x1B[34m"
#define Magenta   "\x1B[35m"
#define Cyan   "\x1B[36m"
#define White   "\x1B[37m"
#define Default "\x1B[0m"



void inecho(char *parameters[20], int c)
{

	char *lastchar="\n";
	int pointer=1;
	int eflag=0;
	int nflag=0;
	int save=-1;

	for(int i=1; i<c; i++)
	{
		if(parameters[i][0]=='-')
   		{
   			if(strcmp(parameters[i],"-E")==0)
   				eflag=1;
   			else if(strcmp(parameters[i],"-n")==0)
   				nflag=1;
   			else if(strcmp(parameters[i],"-En")==0 || strcmp(parameters[i],"-nE")==0)
   			{
   					nflag=1;
   					eflag=1;
   			}
   		}

   		else
   		{
   			save=i;
   			break;
   		}
	}

	if(nflag==1)
	{
			lastchar="";
	}

	if(save==-1)
	{
		
	}
	

	else
	{
		for(int k=save; k<c; k++)
		{
			int one=-1;
			//int two=-1;
			char tillnow1[100];
			//printf(tillnow1);
			// if(*tillnow1==NULL)
			// 	printf("yesnull");
			//char tillnow2[1000];
			int a=0;
			char ch;
			char savedst[1000];
			int b=0;
			for(int z=0; parameters[k][z]!='\0'; z++)
			{	

				//printf("a");
				if(parameters[k][z]=='\\')
					continue;

				if(one==0 && parameters[k][z]==ch)
				{
					//printf("b");
					one=1;
					for(int h=0; h<a; h++)
					{
						savedst[b++]=tillnow1[h];
					}
					a=0;
				}

				else if(one==0)
				{
					//printf("c");
					tillnow1[a++]=parameters[k][z];
				}

				else if(parameters[k][z]=='\'' || parameters[k][z]=='"')
				{
					//printf("d");
					ch=parameters[k][z];
					one=0;
				}

				else if(one!=0)
					savedst[b++]=parameters[k][z];

				else
					printf("e");
				
			}

			if(one==0)
			{
				printf("Error ");
				break;
			}

			else
			{
				for(int m=0; m<b; m++)
				{
					printf("%c",savedst[m]);
				}
			}

			printf(" ");
		}
	}

	printf("%s",lastchar);
}


char *inpwd()
{
	char cwd[1024];
    //chdir("/path/to/change/directory/to");
    getcwd(cwd, sizeof(cwd));

    char *toret=(char *)malloc(sizeof(char)*1024);
    strcpy(toret,cwd);
    return toret;
}


void inhistory(char *historyarr[10], int hac)
{

	FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
	
	fp = fopen("historykeeper.txt","r");
	int cnt=1;

	while ((read = getline(&line, &len, fp)) != -1) 
    {
    	printf("%d %s",cnt,line);
    	cnt++;
    }

	for(int i=0; i<hac; i++)
	{
		printf("%d %s\n",i+cnt, historyarr[i]);
	}
}


int main()
{
	int var=0;

	static char *historyarr[1000];
	int hac=0;
	char *prevdir;
	char *newprev;
	
	char *homedir;
	homedir=inpwd();
	


	while(1)
	{	


		if(var==0)
		{
			printf("\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			printf("\t\t\t WELCOME TO SHELL\n");
			printf("\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			var++;
		}
	
		char *command;
		char *parameters[20];
		char str[100];
		int i=0;
		char *temp;
		int c=1;
		
		printf(Green "Surabhi's Simple Shell:" Default);

		printf(Blue "%s $$$$$ ",inpwd());
		printf(Default);

		gets(str);
		

		historyarr[hac++]=strdup(str);
		temp=strtok(str," \n");
		
		
		int cnt=0;
		

		while(temp!=NULL)
		{
			if(cnt==0)
			{
				command=temp;
				parameters[0]=command;	
				cnt++;
			}

			else
			{
				parameters[c++]=temp;
			}

			temp=strtok(NULL," \n");
		}

		parameters[c]=NULL;	

		
		if(strcmp(command, "exit")==0)		
		{
			FILE * fp;
   			fp = fopen ("historykeeper.txt","a");
   		
   			for(int i = 0; i < hac; i++)
   			{
       			fprintf (fp, "%s\n",historyarr[i]);
   			}

   			fclose (fp);
			return 0;
		}


		
		else if(strcmp(command, "echo")==0)		
		{
			inecho(parameters, c);
		}

		

		else if(strcmp(command, "cd")==0)
		{

			
			if(parameters[1]==NULL || strcmp(parameters[1],"~")==0)
			{
				
				prevdir=strdup(inpwd());
				chdir(homedir);
			}

			else if(strcmp(parameters[1],"-")==0)
			{
				
				
				if(*prevdir==NULL)
				{
					printf("%s\n","cd: OLDPWD not set");
				}

				else
				{
					newprev=strdup(inpwd());
					chdir(prevdir);
					prevdir=newprev;
				}	
					
			}
			
			else
			{
				
				newprev=strdup(inpwd());
				int ret=chdir(parameters[1]);
				if(ret!=0)
					printf("cd: %s: No such file or directory\n",parameters[1]);
				else
					prevdir=newprev;
			}

		}



		else if(strcmp(command, "pwd")==0)		//-L???
		{
			char *temp=inpwd();
			printf("%s\n",temp);
		}



		else if(strcmp(command, "history")==0)	
		{
			inhistory(historyarr, hac);
		}


		else if(strcmp(command, "date")==0 || strcmp(command, "cat")==0 || strcmp(command, "ls")==0 || strcmp(command, "mkdir")==0 || strcmp(command, "rm")==0)
		{
			pid_t pid=fork();		

			if(pid==0)
			{	
				printf("inhere");

				if(strcmp(command, "date")==0)
					execve("/home/surabhi/Desktop/date", parameters, NULL);
				else if(strcmp(command, "cat")==0)
					execve("/home/surabhi/Desktop/cat", parameters, NULL);
				else if(strcmp(command, "ls")==0)
					execve("/home/surabhi/Desktop/ls", parameters, NULL);
				else if(strcmp(command, "mkdir")==0)
					execve("/home/surabhi/Desktop/mkdir", parameters, NULL);
				else if(strcmp(command, "rm")==0)
					execve("/home/surabhi/Desktop/rm", parameters, NULL);

			}

			else
			{
				pid=wait(NULL);
			}	
		}

		else
		{
			if(strcmp(str,"")!=0)
				printf("%s: command not found\n",command);
		}

	}


	return 0;
}
