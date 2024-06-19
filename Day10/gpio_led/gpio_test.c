#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main(int argc,char *argv)
{
   int fd;
   char str[4]="";
   if(argc!=2)
   {
      printf("Invalid usage\n");
	  return -1;
   }

   fd=open("/dev/bbb_gpio0",O_RDWR);
   if(strcmp(argv[1],"ON")==0)
   {
       write(fd,"1",1);
	   printf("Led ON\n");
   }
   else if(strcmp(argv[1],"OFF")==0)
   {  
       write(fd,"0",1);
	   printf("Led OFF\n");
   }
   else if(strcmp(argv[1],"state")==0)
   {
       read(fd,str,1);
	   printf("Led state=%c\n",str[1]);
   }
   else
   {
     printf("Invalid Usage\n");
	 return -1;
   }
   return 0;
}
