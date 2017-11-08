#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  NAME_ONLY = 0,
  MAJOR_AND_NAME = 1, 
  YEAR_AND_NAME = 2,
  YEARS_LEFT_AND_NAME = 3,
} Mode;

typedef struct {
  char *first_name;
  char *last_name;
  char *major;
  int year;
  int years_left;
} Student;

void print_student(Mode m, Student s) {
  switch (m) {
    case NAME_ONLY:
      printf("%s %s\n", s.first_name, s.last_name);
      break;
 	case MAJOR_AND_NAME:
	  printf("%s %s %s\n", s.major, s.first_name, s.last_name);
      break;
	case YEAR_AND_NAME:
	  printf("%d %s %s\n", s.year, s.first_name, s.last_name);
      break;
	case YEARS_LEFT_AND_NAME:
	  printf("%d %s %s\n", s.years_left, s.first_name, s.last_name);
      break;
  }
}

int main(int argc, char *argv[]) {  
  char *filename = argv[1];
  FILE *fp = fopen(filename, "r");
  char buffer[256];
  Student s[256];
  int m;
  int in;
  
  
  if (fp == NULL) {
    printf("Could not open %s\n", filename);
    return -1;
  }

  // read one line at a time
  char *ss;
  int i = 0;
  
  // First loop to process input file
  while ((ss = fgets(buffer, 255, fp)) != NULL) {
	size_t len = strlen(buffer);
	size_t len_bytes = (len + 1) * sizeof(char);
	char *new_string = malloc(len_bytes);
	
	memcpy(new_string, buffer, len_bytes);
	
	s[i].first_name = malloc(len_bytes);
	s[i].last_name = malloc(len_bytes);
	s[i].major = malloc(len_bytes);
	
	sscanf(new_string, "%s %s %s %d", s[i].first_name, s[i].last_name, s[i].major, &s[i].year);
	s[i].years_left = s[i].year - 2017;
	i++;
  }
  // Takes index and mode from user input, then prints	
		printf("Please input \"(index) (mode)\" to display student info:\n");
		while ( 1 > 0 ) {
		  scanf("%d %d", &in, &m);
		  print_student(m, s[in]);
		}
  
  // Clean up memory
  for (int j = 0; j < i; j++) {
	if (s[j].first_name != NULL) {
	  free(s[j].first_name);
	}
	if (s[j].last_name != NULL) {
	  free(s[j].last_name);
	}
	if (s[j].major != NULL) {
	  free(s[j].first_name);
	}
}
 
  fclose(fp);
  return 0;
}
