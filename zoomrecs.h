#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ZoomRecord {
  char email[60];
  char name[60];
  int durations[9];
  struct ZoomRecord *next;
};

void addZoomRecord(struct ZoomRecord** head, struct ZoomRecord* student, int position);
void generateAttendance(struct ZoomRecord** head, FILE* outputfile);
