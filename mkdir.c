#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char *argv[])
{


	struct stat s;
   	int vflag=0;
   	int mflag=0;

   	int save=-1;
   	for(int i=1; i<argc; i++)
   	{
   
   		if(argv[i][0]=='-')
   		{
   		
   			if(strcmp(argv[i],"-v")==0)
   				vflag=1;
   			else if(strcmp(argv[i],"-m")==0)
   				mflag=1;
   			else
          	{
            	printf("mkdir: invalid option -- '%s'\n",argv[i]);
          	}
   		}

   		else
   		{
   			save=i;
   			break;
   		}	

   	}

   	//printf("save is %d\n",save);


   	if(argc<2)
    {
        printf("Mismatch argument\n");
        return 0;
    }


	if(mflag==1)
	{
    if(argc==2)
    {
          printf("Error: too less parameters\n");
          return 0;
    }
    
    else
    {
        umask(0);
        if(mkdir(argv[argc-1],argv[argc-2])!=0)
        {
          printf("mkdir: cannot create directory ‘%s’: File exists",argv[argc-1]);
          umask(022);
          return 0;
        }

        umask(022);  
    }
	}

  else
  {
    if(mkdir(argv[argc-1],S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH)!=0)
    {
        printf("mkdir: cannot create directory '%s': File exists\n",argv[argc-1]);
        return 0;
    }   
    
    if(strcmp(argv[1],"-v")==0)
    {
      if(argc==2)
        printf("Error: too less parameters\n");
      else if(argc==3)
        printf("mkdir: created directory '%s'\n",argv[argc-1]);
    }  
  }

	return 0;
}