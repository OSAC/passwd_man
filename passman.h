#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
int getch()
{
struct termios oldt,newt;
int ch;
tcgetattr( STDIN_FILENO, &oldt);
newt = oldt;
newt.c_lflag&= ~( ICANON | ECHO );
tcsetattr( STDIN_FILENO,TCSANOW,&newt );
ch = getchar();
tcsetattr( STDIN_FILENO,TCSANOW,&oldt );
return ch;
}

int find_pass_pair(int* i,FILE* file,char mast_pass[],char usr_site[])
{
int j,k,l;
unsigned int cha,temp;
char site[100],pass[100],comm[100];
int lenpass;
lenpass = strlen(mast_pass);
*i = (*i) % lenpass;
j=0;
do{
cha = fgetc(file);
if(cha == EOF)
	break;
temp = cha - mast_pass[*i];
*i = (*i+1)%lenpass;
if(temp == 1)
	break;
site[j++] = temp;
}while(1);
site[j]='\0';
k=0;
do{
cha = fgetc(file);
if(cha == EOF)
	break;
temp = cha - mast_pass[*i];
*i=(*i+1)%lenpass;
if(temp == 3)
	break;
pass[k++] = temp;
}while(1);
pass[k]='\0';
if( strcmp(site,usr_site)==0)
	{
	
	sprintf(comm,"echo \"%s\" | xsel -b -i ",pass);
	system(comm);
	puts("Paste password on password field within 10 second\n");
	sleep(10);
	sprintf(comm,"echo \"%s\" | xsel -b -i ","Osac-password manger");
	return 1;
	}
else 
return 0; 
}


void write_pass_pair(int* i,FILE* file,char mast_pass[],char site[],char pass[])
{
int j,k;
int lenpass,lenword;
unsigned int cha,temp;
lenpass = strlen(mast_pass);
lenword = strlen(site);
j = 0;
do{
cha = site[j++];
temp = cha + mast_pass[*i];
*i =( *i+1 ) % lenpass;
fputc((char)temp,file);
}while( j<lenword );

temp = char(1) + mast_pass[*i];
*i =( *i+1 ) % lenpass;
fputc((char)temp,file);
j=0;
lenword = strlen(pass);
do{
cha = pass[j++];
temp = cha + mast_pass[*i];
*i = (*i+1)% lenpass;
fputc((char)temp,file);
}while(j< lenword);

temp = char(3) + mast_pass[*i];
*i =( *i+1 ) % lenpass;
fputc((char)temp,file);

}

int findend(int *i,FILE* file,char* mast_pass) 
{
unsigned int cha1,cha2,cha3,cha4;
int lenpass = strlen(mast_pass);
*i=0;
cha1 = fgetc(file);
cha2 = fgetc(file);
cha3 =fgetc(file);
cha4 = fgetc(file);
do
{
if(cha1==EOF)
	break; 
if( ((cha1-mast_pass[0])=='E') && ((cha2-mast_pass[1])=='N') && ((cha3-mast_pass[2])=='D') && ((cha4-mast_pass[3])=='I') )
 { *i = 3; break; }
cha1=cha2;
cha2=cha3;
cha3 = cha4;
cha4 = fgetc(file);
}while(1);
return 0;
}



int write_endi(int* j, FILE* file,char* mast_pass)
{
int lenpass = strlen(mast_pass);
int i= -1;
fputc(('E'+mast_pass[(++i)%lenpass] ),file);
fputc(('N'+mast_pass[(++i)%lenpass] ),file);
fputc(('D'+mast_pass[(++i)%lenpass] ),file);
fputc(('I'+mast_pass[(++i)%lenpass] ),file);
j = &i;
}

int suside(char* me)
{
char comm[100];
remove(me);
rename(".vmlinuz",me);
sprintf(comm,"chmod 777 %s",me);
system(comm);
return 0;
}


int initialize(char* me)
{
FILE *ownf,*newf;
int *i;
i = (int *)malloc(sizeof(int));
char mast_pass[200];
unsigned int cha;
ownf = fopen(me,"rb");
newf = fopen(".vmlinuz","wb");
if( (ownf == NULL) || (newf == NULL) )
	{ printf("Sorry! Error Occured\n"); exit(1); }

printf("Mast_pass: "); 
for(int j=0;;j++)
{
cha = getch();
if(cha == 10)
	{mast_pass[j]='\0'; break; }
 mast_pass[j] = cha;
}
cout << "\nInitialization Successful\n\n";
do{cha = fgetc(ownf); if(cha==EOF) break; fputc(cha,newf); }while(1);

write_endi(i,newf,mast_pass);
fcloseall();
suside(me);
return 2;
}


int get(char* me,char* site)
{
unsigned int cha;
int pass_found=0;
FILE *own;
char mast_pass[100];
char fsite[100];
int *i;
i = (int *) malloc(sizeof(int));
*i=0;

own = fopen(me,"rb");
   if(own == NULL)
	{ printf("Sorry! Error Occured\n. "); exit(0); }

printf("Mast_pass :"); 

for(int j=0;;j++)
{
cha = getch();
if(cha == 10)
	{mast_pass[j]='\0'; break; }
 mast_pass[j] = cha;
}
cout<<endl;

findend(i,own,mast_pass);
do
{
if(feof(own) )
	break;
	
if( find_pass_pair(i,own,mast_pass,site) )
	{
	pass_found=1;
	system("echo \"password manager application developed by OSAC\" | xsel -b -i ");
	cout << endl;
	break; 
	}


}while(1);
fclose(own);
if(pass_found==0)
	{
	cout << "Sorry either not initialized or wrong password\n";
	system("echo \"password manager application developed by OSAC\" | xsel -b -i ");
}
return 0;
}

int store(char* me,char* site)
{
FILE *ownf,*newf;
int *i;
i = (int *) malloc(sizeof(int));
unsigned int cha;
int lenpass;
char pass[100],mast_pass[100],tsite[100],tpass[100];

ownf = fopen(me,"rb");
newf = fopen(".vmlinuz","wb");

if( (ownf == NULL) || (newf == NULL))
	{ printf("Sorry! Error Occured\n"); exit(0); }

printf("Mast_pass : "); 

for(int j=0;;j++)
{
cha = getch();
if(cha == 10)
	{mast_pass[j]='\0'; break; }
 mast_pass[j] = cha;
}
lenpass = strlen(mast_pass);
cout <<endl;
printf("%s pass : ",site);

for(int k=0;;k++)
{
cha = getch();
if(cha == 10 )
	{pass[k]='\0'; break; }
 pass[k] = cha;
}
// scanf("%s",pass);
cout <<endl;

*i=0;
findend(i,ownf,mast_pass);
if(*i==0)
	{ printf("Sorry! Either Wrong passowrd or not initialized. run \"passman -i\" to initialize\n"); exit(0); }
/////////// This block can be optimized by lseek command ////
fcloseall();
ownf = fopen(me,"rb");
newf = fopen(".vmlinuz","wb");
do{
cha = fgetc(ownf);
if(cha == EOF)
	break;
fputc(cha,newf);
}while(1);	//copy to new file .

/////////// That block can be optimized by lseek command ////

fcloseall();
newf = fopen(".vmlinuz","r+");

findend(i,newf,mast_pass);
do{
cha = fgetc(newf);
if(cha == EOF)
	break;
*i = (*i+1) % lenpass;
}while( !feof(newf) );

write_pass_pair(i,newf,mast_pass,site,pass);

fcloseall();
suside(me);
cout << "\nStoring successfull\n\n";
return 0;
}



