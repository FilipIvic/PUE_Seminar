#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>

//-----------------------------------------------------------------------------------------------

void shellFunkcija()
{

	int a, b, size = 15;

	printf("\n\n****************************************");
	printf("\n\n\n****MOJ SHELL****");
	printf("\n\n-KORIŠTENJE NA VLASTITU ODGOVORNOST-");
	printf("\n\n\n\n");

	for (a = size/2; a <= size; a = a+2) {
  
        	for (b = 1; b < size-a; b = b+2)         
            		printf(" ");
   
        	for (b = 1; b <= a; b++)
           		printf("A");
    
        	for (b = 1; b <= size-a; b++)
            		printf(" ");
           
        	for (b = 1; b <= a-1; b++)
            		printf("A");
  
        	printf("\n");
    	}
    
   	for (a = size; a >= 0; a--) {
   
        	for (b = a; b < size; b++)
            		printf(" ");
   
        	for (b = 1; b <= ((a * 2) - 1); b++)
            		printf("B");
  
        	printf("\n");   
    	} 	
	printf("\n\n****************************************");
	
	char* username = getenv("USER");
	printf("\n\n\nUSER is: @%s", username);
	printf("\n");
}

//-----------------------------------------------------------------------------------------------

int uzmiUlaz(char* str)
{
	char* buf;
  
	buf = readline("\n>>> ");
	if (strlen(buf) != 0) {
		add_history(buf);
        	strcpy(str, buf);
        	return 0;
	} else {
        	return 1;
	}
}

//-----------------------------------------------------------------------------------------------

void ispisiDirektorij()
{
	char path[100];
    	getcwd(path, 100);

    	printf("\nDir: %s", path);
}

//-----------------------------------------------------------------------------------------------

int parsirajRazmake(char* str, char** parsiranStr)
{
    	int i;
  
    	for (i = 0; i < 100; i++) {
        	parsiranStr[i] = strsep(&str, " ");
  
        	if (parsiranStr[i] == NULL)
           		break; 			
        	if (strlen(parsiranStr[i]) == 0)
            	i--;
    	}
	return i;
}

//-----------------------------------------------------------------------------------------------

void izvrsi( char** args)
{
	int pid;
	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid == 0){
		execvp(args[0], args);
		perror("execvp");
	} else {
		wait(NULL);
	}	
}

//-----------------------------------------------------------------------------------------------

int provjeriKomande(char** args, char** komande )
{
	int slucaj = 0;
	for (int i = 0; i < 4; i++) {
       		if (strcmp(args[0], komande[i]) == 0) {
          			//printf("\nKomanda!!!");
				slucaj = i + 1;
				break;
			}			
		}
		
		switch (slucaj) {
  		case 1:
    		printf("\nGoodbye\n");
        		exit(0);
    		case 2:
        		chdir(args[1]);
        		return 1;
    		case 3:
       	 		//openHelp();
        		return 1;
    		case 4:
        		printf("\nDodat cu\n");
        		return 1;
    		default:
        		break;
		}
return 0;
}

//-----------------------------------------------------------------------------------------------

int main()
{
	int n, status;
	char ulazniString[100];
	char *parsiraniString[100];
	char *komanda[3];
	komanda[0] = "exit";
   	komanda[1] = "cd";
    	komanda[2] = "help";
    	komanda[3] = "hello";

	shellFunkcija();
  
	while (1) {
		
		ispisiDirektorij();

		if (uzmiUlaz(ulazniString))
			continue;
		
		n = parsirajRazmake(ulazniString, parsiraniString);
		parsiraniString[n] = NULL;

		status = provjeriKomande(parsiraniString, komanda);
		if(status == 0 )		
			izvrsi(parsiraniString);

    }
    return 0;
}
