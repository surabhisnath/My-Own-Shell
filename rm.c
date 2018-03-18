#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <error.h>




int main(int argc, char *argv[])
{	
   	struct stat s;
   	int vflag=0;
   	int dflag=0;

   	int save=-1;
   	for(int i=1; i<argc; i++)
   	{
   
   		if(argv[i][0]=='-')
   		{
   		
   			if(strcmp(argv[i],"-v")==0)
   				vflag=1;
   			else if(strcmp(argv[i],"-d")==0)
   				dflag=1;
   			else if(strcmp(argv[i],"-vd")==0 || strcmp(argv[i],"-dv")==0)
   			{
   					dflag=1;
   					vflag=1;
   			}

   			else
          	{
            	printf("rm: invalid option -- '%s'\n",argv[i]);
            	return 0;
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

	else
	{
	//	printf("in0");
		for(int j=save; j<argc; j++)
		{
			if(stat(argv[j],&s)<0)
	    	{
    	    	printf("rm: cannot remove '%s': No such file or directory\n",argv[j]);
        		return 0;
    		}

	    	if(S_ISREG(s.st_mode))
	    	{
	    		//printf("in1");
	        	remove(argv[j]);
	        	if(vflag==1)
	        		printf("removed %s\n",argv[j]);
	    	}

	    	else if(S_ISDIR(s.st_mode) && dflag==0)
	    	{
	    		//printf("in2");
	    		printf("rm: cannot remove '%s': Is a directory\n",argv[1]);
	    	}

	    	else if(S_ISDIR(s.st_mode) && dflag==1)
	    	{
	    		//printf("%llu", (unsigned long long)s.st_size);
	    		int n = 0;
			  	struct dirent *d;
			  	DIR *dir = opendir(argv[j]);
			  	while ((d = readdir(dir)) != NULL) 
			  	{
			    	if(++n > 2)
			      	break;
			  	}

			  	closedir(dir);
		
	    		if(n>2)
	    		{
	    			//printf("in4");
	        		printf("rm: cannot remove '%s': Directory not empty\n",argv[j]);	
	        	}

	        	else
	        	{
	        		//printf("in3");
	    			rmdir(argv[j]);
	        		if(vflag==1)
	        			printf("removed %s\n",argv[j]);
	        	}
	    	}

	    	else
	    	{
	    		//printf("why am I in else\n");
	    	}
		}
	}

	return 0;
}