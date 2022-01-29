#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zoomrecs.h"

int main(int argc, char *argv[]) {
	
	FILE *inputfile = fopen(argv[1], "rt");
	
	// Creating variables
	char line[200];
	struct ZoomRecord* head = NULL;
	
	// Skipping the first line
	fgets(line, 200, inputfile);
	
	// Looping through each line of file until reaching the end
	while (fgets(line, 200, inputfile)) {
		
		struct ZoomRecord* student = (struct ZoomRecord*) malloc(sizeof(struct ZoomRecord));		

		char* token = strtok(line,",");

		// Assigning each variable to its field
		strcpy(student->email,token);
		token = strtok(NULL,",");

		strcpy(student->name,token);
		token = strtok(NULL,",");

		char lab = token[0];
		int position = lab-'A';
		token = strtok(NULL,",");
				
		student->durations[position] = atoi(token);
		token = strtok(NULL,",");
		
		// Adding the student into the linked list	
		addZoomRecord(&head, student, position);
	}
	
	fclose(inputfile);

	FILE *outputfile = fopen(argv[2], "wt");

	// Creating the outputfile with the linked list
	generateAttendance(&head, outputfile);

	fclose(outputfile);

	// Free the linked list's nodes
	struct ZoomRecord* freeZoomNode = head;
	while (head != NULL) {
		freeZoomNode = head;
		head = head->next;
		free(freeZoomNode);
	}

}

