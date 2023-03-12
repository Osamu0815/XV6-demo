#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int prime(int num)
{
    int i;
    for(i = 2;i<num/2;i++)
    {
        if(num %i == 0) break;
    }
    if(i == num) return(0);
    return(1);
}

void main(int args, char* argv[])
{
    int p[2];
    int num;
    int pid;
    
    if(pipe(p)<0)
    {
        fprintf(2,"error:unable to build pipes \n");
    }

    for(int i = 2;i <= 35;i ++)
    {
        write(p[1],i,sizeof(i));
    }

    pid = fork();

    while (1)
    {
        if(pid > 0)
        {
            wait((int*)0);
            break;
        }else if (pid == 0)
        {
            while(1)
            {
                if(read(p[0],num,sizeof(num)))
                {
                    num = -1;
                    break;
                }
                if(prime(num))
                {
                    fprintf(1,"prime %d \n",num);
                }else if (num < 0)
                {
                    break;
                }
                
            }
        }else{
            fprintf(2,"error:fork failed \n"); 
            break;
        }
        
    }
    exit(0);
    
}