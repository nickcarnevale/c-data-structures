#include "linkedlist.h"
#include <stdlib.h> 
#include <stdio.h>

//file to test lib.c by reading in the test file
int main() {

	FILE *textfile;
    char line[1000];
	int test_counter = 0;
     
    textfile = fopen("tests", "r");
    if(textfile == NULL)
        return 1;
    
    while(fgets(line, 1000, textfile)){
		if(line[0] == 'H' || line[0] == 'T'){
			int counter = 0;
			int completed = 0;
			List* list = malloc(sizeof(List));
			initList(list); 
			test_counter++;
			printf("\nTEST %d\n", test_counter);
			printf(line);
			int* arr = command(line, list, counter);
			int c = counter;
			counter += arr[0];
			completed += arr[1];
			if(arr[1] == 0){
					printf("Command %c Completed Successfully\n",line[c]);
				}else{
					printf("Command:%c Not Completed Successfully\n",line[c]);
				}
			free(arr);
			while(line[counter] != 'X'){
				int* arr = command(line, list, counter);
				int c = counter;
				counter += arr[0]; 
				completed += arr[1];
				if(arr[1] == 0){
					printf("Command %c Completed Successfully\n",line[c]);
				}else{
					printf("Command:%c Not Completed Successfully\n",line[c]);
				}
				free(arr);
			}
			if(completed == 0){
				printf("Test was Successful\n");
				printList(list);

			}else{
				printf("Test was not Successful\n");
				printList(list);

			}
			freeList(list);
		}
    }
    fclose(textfile);
	return 0;
}