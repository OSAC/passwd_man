#include "passman.h"

int main(int argc, char** argv)
{
char site[200],comm[200];
if(argc <2 )
	{
	printf("Usage %s -i              Initialize only for first time use.\n",argv[0]);
	printf("%s -s \'site\'           Store password for site named \'site\'\n",argv[0]);
	printf("%s -g \'site\'           Get password for site named \'site\'\n",argv[0]);
	
	return 1;
}
else if( (argc == 2) && (strcmp(argv[1],"-i") ==0) )
	{
	initialize(argv[0]);
	return 0;
}
else if((argc == 3) && (strcmp(argv[1],"-s")==0))
	{
	strcpy(site,argv[2]);
	store(argv[0],site);
	return 0;
}
else if((argc == 3) && (strcmp(argv[1],"-g") == 0) )
	{
	strcpy(site,argv[2]);
	get(argv[0],site);
	return 0;
}
else 
	sprintf(comm,"info %s",argv[0]);
	system(comm);
return 1;
}
