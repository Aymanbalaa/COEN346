#include<sys/wait.h>
#include<unistd.h>
#include <stdio.h>
int main()
{
int num,n,m,fact=1,sum=0;
printf("Enter a number:");
scanf("%d",&num);
n = fork();
if(n==0)
{
for(int i=1;i<=num;i++)
{
sum=sum+i;
}
printf("The sum of numbers is %d\n", sum);
printf("The identifier of first child process is %d\n",getpid());
}
else
{
m = fork();
if(m==0)
{
for(int i=1;i<=num;i++)
{
fact=fact*i;
}
printf("The factorial of numbers is %d\n", fact);
printf("The identifier of second child process is %d\n",getpid());
}
else
{
wait(NULL);
printf("Done\n");
printf("The identifier of parent process is %d\n",getppid());
}
}
return 0;
}
