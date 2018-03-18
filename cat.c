#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char *argv[])
{
       int f=0,n;
       char l[80];
       struct stat s;
       int indicator=0;


       int eflag=0;
      int nflag=0;

      int save=-1;
      for(int i=1; i<argc; i++)
      {
     
        if(argv[i][0]=='-')
        {
        
          if(strcmp(argv[i],"-E")==0)
            eflag=1;
          else if(strcmp(argv[i],"-n")==0)
            nflag=1;
          else if(strcmp(argv[i],"-nE")==0 || strcmp(argv[i],"-En")==0)
          {
              eflag=1;
              nflag=1;
          }

          else
          {
            printf("cat: invalid option -- '%s'\n",argv[i]);
            return 0;
          }
        }

        else
        {
          save=i;
          break;
        } 

      }

       if(argc<2)
       {
               printf("Mismatch argument\n");
               exit(1);
       }

       for(int j=save; j<argc; j++)
       {
             if(stat(argv[j],&s)<0)
             {
                     printf("cat: %s: No such file or directory\n",argv[j]);
                     return 0;
             }

             if(S_ISDIR(s.st_mode))
             {
                     printf("cat: %s: Is a directory\n",argv[j]);
                     return 0;
             }
       

            FILE * fp;
            char * line = NULL;
            size_t len = 0;
            ssize_t read;


            fp = fopen(argv[j],"r"); 
             
                
            if(eflag==1)
            {

              if(nflag==1)
              {
                  int cnt=1;
                  while ((read = getline(&line, &len, fp)) != -1) 
                  {
                      printf("%d ",cnt);
                      cnt++;

                      for(int h=0; line[h+1]!='\0'; h++)
                      {
                          printf("%c",line[h]);
                      }

                      printf("$\n");
                  }
              }

              else
              {
                  while ((read = getline(&line, &len, fp)) != -1) 
                  {
                  
                      for(int h=0; line[h+1]!='\0'; h++)
                      {
                          printf("%c",line[h]);
                      }

                      printf("$\n");
                  } 
              }
                
            }

            else if(nflag==1)
            {
                int cnt=1;
                while ((read = getline(&line, &len, fp)) != -1) 
                {
                    printf("%d %s",cnt,line);
                    cnt++;
                }

                printf("\n");          
            }

             


             else
             {
                  while ((read = getline(&line, &len, fp)) != -1) 
                  {
                    printf("%s", line);
                  }

                    printf("\n");
             }
        

             fclose(fp); 
       }


       
}
