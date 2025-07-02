#include<stdio.h>
#include<math.h>
int gcd(int a,int b){
int t;
while(b!=0){
t=b;
b=b%a;
a=t;
}
return a;
}
int modInverse(int e,int phi){
int d=1;
while((e*d)%phi!=1)
{
d++;
}
return d;
}
int modPower(int exp21,int base,int mod){
int result=1;
for(int i=0;i<base;i++)
result =(result*exp21)%mod;
return result;
}
int main()
{
int p,q,n,phi,e,d;
int message,encrypted,decrypted;
printf("enter two prime numbers");
scanf("%d%d",&p,&q);
n=p*q;
phi=(p-1)*(q-1);
for(e=2;e<phi;e++)
if(gcd(e,phi)==1)
break;
d=modInverse(e,phi);
printf("\n public key(e,n): (%d,%d)",e,n);
printf("\n private key(d,n): (%d,%d)",d,n);
printf("\n enter the message to be encripted");
scanf("%d",&message);
encrypted=modPower(message,e,n);
printf("\n encrypted message is:%d",encrypted);
decrypted=modPower(encrypted,d,n);
printf("\n decrypted message is:%d",decrypted);
return 0;
}
