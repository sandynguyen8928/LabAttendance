#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zoomrecs.h"

void addZoomRecord(struct ZoomRecord** head, struct ZoomRecord* student, int position) {
	
	struct ZoomRecord* pointer = *head;
	int already = 0;

	// For loop looking for an existing ZoomRecord
	while (pointer != NULL) {

		if (strcmp(pointer->email, student->email) == 0) {
			already = 1;
			break;
		}
		else {
			pointer = pointer->next;
		}	

	}
	
	// If the student is already in the linked list
	if (already == 1) {
		
		// Adding the lab duration
		pointer->durations[position] += student->durations[position];
	}

	// If the student is not in the linked list
	else {	

		// If it's the first student or the student's email should be the first one
		if (*head == NULL || strcmp((*head)->email, student->email) >= 0) {
			student->next = *head;
			*head = student;
		}
		
		// If it's not the first student
		else {
			struct ZoomRecord* ptr = *head;

			// Looping through the linked list
			while (ptr->next != NULL && strcmp(ptr->next->email, student->email) < 0) {
				ptr = ptr->next;
			}
		
			// Adding the student in the linked list
			student->next = ptr->next;
			ptr->next = student;
		}
	}
}

void generateAttendance(struct ZoomRecord** head, FILE* outputfile) {

	fputs("User Email,Name (Original Name),A,B,C,D,E,F,G,H,I,Attendance (Percentage)\n", outputfile);

	struct ZoomRecord* pointer = *head;
	
	// Looping through the linked list
	while (pointer != NULL) {
		
		int attendance = 0;

		fprintf(outputfile, "%s,", pointer->email);
		fprintf(outputfile, "%s,", pointer->name);

		for (int i=0; i<9; i++) {
			fprintf(outputfile, "%d,", pointer->durations[i]);
			
			if (pointer->durations[i] >= 45) {
				attendance++;
			}
		}

		float percentage = ((float)attendance / 9) * 100;

		fprintf(outputfile, "%2.2f\n", percentage);
		pointer = pointer->next;
	}
}
