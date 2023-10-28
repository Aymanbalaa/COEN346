#include<sys/wait.h>
#include<unistd.h>
#include <stdio.h>
int main()
{

int input;
int n;
int sum=0;
printf("Enter a number:");
scanf("%d",&input);
n = fork();
if(n==0)
{
for(int i=1;i<=input;i++)
{
sum=sum+i;
}
printf("[ID = " getpid() +"]" + "Sum of positive integers up to " + input +" is %d\n", sum);

}


int m;
int factorial=1;
else
{
m = fork();
if(m==0)
{
for(int i=1;i<=input;i++)
{
factorial=factorial*i;
}

printf("[ID = " getpid() +"]"+ "factorialorial of " + input + " is %d\n", factorial);
}
else
{
wait(NULL);
printf("Done\n");
printf("[ID = " getppid() +"]"+"Done\n");
}
}
return 0;
}
