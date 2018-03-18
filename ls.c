#include <sys/types.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int alphasort();


int temp()
{
    return 1;
}

int main(int argc, char *argv[])
{

    int rflag=0;
    int aflag=0;

    int save=-1;
    for(int i=1; i<argc; i++)
    {
       
        if(argv[i][0]=='-')
        {
            //printf("here1");
            if(strcmp(argv[i],"-r")==0)
                rflag=1;
            else if(strcmp(argv[i],"-a")==0)
                aflag=1;
            else if(strcmp(argv[i],"-ra")==0 || strcmp(argv[i],"-ar")==0)
            {
                rflag=1;
                aflag=1;
            }

            else
            {
                printf("ls: invalid option -- '%s'\n",argv[i]);
                return 0;
            }
        }

        else
        {
            save=i;
            break;
        }   

    }

    //printf("%d",save);
    //printf("%d",argc);


    if(save==-1)
    {
        int numfiles;
        struct direct **files;
        char pathname[100000];

        if(!getcwd(pathname, sizeof(pathname)))
        {
                printf("Error getting pathname\n");
                return 0;
        }


        numfiles = scandir(pathname, &files, temp, alphasort);

        if(numfiles<=0)
            printf("%s\n","No files in this directory");

        else
        {
            
            if(rflag==1)
            {
                //printf("here");
                for (int i=numfiles-1; i>=0; i--)
                {
                    char *temp=files[i]->d_name;
                    
                    if(aflag==0)
                    {
                        if(strcmp(temp,".")==0 || strcmp(temp,"..")==0 || temp[0]=='.')
                        continue;    
                    }

                    printf("%s  ",files[i]->d_name);
                }   
                printf("\n");
            }

            else if(aflag==1)
            {
                for (int i=0; i<numfiles; i++)
                    printf("%s  ",files[i]->d_name);
                printf("\n");                    
            }

            else
            {
                for (int i=0; i<numfiles; i++)
                {
                    char *temp=files[i]->d_name;
                    
                    if(aflag==0)
                    {
                        if(strcmp(temp,".")==0 || strcmp(temp,"..")==0 || temp[0]=='.')
                        continue;    
                    }

                    printf("%s  ",files[i]->d_name);
                }   
                printf("\n");
            }
        }
    }

    
    else
    {
        for(int j=save; j<argc; j++)
        {
            int numfiles;
            struct direct **files;
            char pathname[100000];

        
            int ret=chdir(argv[j]);
            if(ret!=0)
                printf("ls: cannot access '%s': No such file or directory\n",argv[j]);
            

            else
            {
                getcwd(pathname, sizeof(pathname));
                numfiles = scandir(pathname, &files, temp, alphasort);

                if(numfiles<=0)
                    printf("%s\n","No files in this directory");

                if(rflag==1)
                {
                    for (int i=numfiles-1; i>=0; i--)
                    {
                        char *temp=files[i]->d_name;
                        
                        if(aflag==0)
                        {
                            if(strcmp(temp,".")==0 || strcmp(temp,"..")==0 || temp[0]=='.')
                            continue;    
                        }

                        printf("%s  ",files[i]->d_name);
                    }   
                    printf("\n");
                }

                else if(aflag==1)
                {
                    for (int i=0; i<numfiles; i++)
                        printf("%s  ",files[i]->d_name);
                    printf("\n");                    
                }

                else
                {
                    for (int i=0; i<numfiles; i++)
                    {
                        char *temp=files[i]->d_name;
                        
                        if(aflag==0)
                        {
                            if(strcmp(temp,".")==0 || strcmp(temp,"..")==0 || temp[0]=='.')
                            continue;    
                        }

                        printf("%s  ",files[i]->d_name);
                    }   
                    printf("\n");
                }
            }
               
           
        }
        
    }
    
    return 0;
}
