#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "biblioteca.h"
#define NMAX 1000

int main(int argc, char *argv[]) {
  char buf[NMAX],               // buffer used for reading from the file
      original[NMAX][NMAX],     // original text, line by line
      result[NMAX][NMAX];       // text obtained after applying operations
  int original_line_count = 0,  // number of lines in the input file
      result_line_count = 0,    // number of lines in the output file
      i;

  if (argc != 4) {  // invalid number of arguments
    fprintf(stderr,
            "Usage: %s operations_string input_file output_file\n",
            argv[0]);
    return -1;
  }

  // Open input file for reading
  FILE *input_file = fopen(argv[2], "r");

  if (input_file == NULL) {
    fprintf(stderr, "File \"%s\" not found\n", argv[2]);
    return -2;
  }

  // Read data in file line by line
  while (fgets(buf, NMAX, input_file)) {
    strcpy(original[original_line_count], buf);
    original_line_count++;
  }

  fclose(input_file);

  char *comanda, list_type, special_character, ordering, str[] = "WCLRJPIOwclrjpio", *cuvant;
  int arg1 = 0, arg2 = 0, indent_length, poz, nr, j;
  char copie1[NMAX][NMAX], cmd2[NMAX];
  char tip_lista[] = "nabA";
  char v[NMAX][NMAX], copie2[NMAX][NMAX];
  int k = 0, go = 1, go2 = 1, contor = 0, max_line_length = 0;

  for (i = 0; i < original_line_count; i++) {
    strcpy(copie1[i], original[i]);
    strcpy(copie2[i], original[i]);
  }
  int copie_line_count = original_line_count;
 
  strcpy(cmd2, argv[1]);
  
  int max = - 1, lg;

  comanda = strtok(cmd2, ",");
 	while (comanda) {
  	strcpy(v[k], comanda);
  	k++;
    comanda = strtok(NULL, ",");
 	}
  v[k][strlen(v[k])] = '\0';
 	for (i = 0; i < k; i++) {
 		eliminare_starting(v, i);	
  }

  char a[NMAX];
  for (i = 0; i < k; i++) {
    if (k > 10) {
      printf("Too many operations! Only the first 10 will be applied.\n");
      k = 10;
    }
  	strcpy(a, v[i]); 
    if (strchr(str, a[0]) == 0) {
      go = 0;
      break;
    }
    contor = 0;
    strcpy(a, v[i]);
    if (strlen(a) == strlen(argv[1])) {
      for (j = 0; j < strlen(a); j++) {
        if (strchr(str, a[j])) {
          contor++;
        }
        if (contor > 1) {
          go = 0;
          break;
        }
      }   
    }
    if (go == 0) {
      break;
    }

    nr = 0;
    for (j = 0; j < strlen(v[i]); j++) {
      if (v[i][j] != ' ') {
        if (v[i][j+1] == ' ' || v[i][j+1] == '\0') {
          nr++;
        }
      }
    }

  	if (v[i][0] == 'W' || v[i][0] == 'w') {   
      if (nr == 1 || nr > 2) {
        go = 0;
        break;
      }
      max_line_length = 0;
  		for (j = 2; j < strlen(v[i]); j++) {
  			if (v[i][j] != ' ') {
  				max_line_length = max_line_length * 10 + (v[i][j] - '0');
  			}
  		}
      max = -1;
      for (j = 0; j < original_line_count; j++) {
        cuvant = strtok(copie1[j], " .,"); // determin cel mai lung cuvant
        while (cuvant) {
          lg = strlen(cuvant);
          if (lg > max) max = lg;
          if (max_line_length < max) {
            go2 = 0;
            break;
          }
          cuvant = strtok(NULL, " .,");
        }
      }
      if (go2 == 0) {
        go = 0;
        break;
      } else {
  			wrap(original, &original_line_count, max_line_length);
  			for (j = 0; j < original_line_count; j++) {
  				eliminare_trailing(original, j);
  			}
  		}
    }
  	//Align Left
  	if (v[i][0] == 'L' || v[i][0] == 'l') {
      if (nr > 3) {
        go = 0;
        break;
      }
  		parametrii(v, i, original_line_count, &arg1, &arg2);
      if (arg1 == -2 || arg2 == -2) {
        go = 0;
        break;
      }
  		align_left(original, original_line_count, arg1, arg2);
  	}
  	//Align Right
  	if (v[i][0] == 'R' || v[i][0] == 'r') {
      if (nr > 3) {
        go = 0;
        break;
      }
  		parametrii(v, i, original_line_count, &arg1, &arg2);
      if (arg1 == -2 || arg2 == -2) {
        go = 0;
        break;
      }
  		align_right(original, original_line_count, arg1, arg2);
  	}
  	//Center
  	if (v[i][0] == 'C' || v[i][0] == 'c') {
      if (nr > 3) {
        go = 0;
        break;
      }
  		parametrii(v, i, original_line_count, &arg1, &arg2);
      if (arg1 == -2 || arg2 == -2) {
        go = 0;
        break;
      }
  		center(original, original_line_count, arg1, arg2);
  	}
  	//Paragrafe
  	if (v[i][0] == 'P' || v[i][0] == 'p') {
      if (nr < 2 || nr > 4) {
        go = 0;
        break;
      }
  		for (j = 2; j < strlen(v[i]); j++) {
  			if (v[i][j] != ' ') { // aflu indent_length
  				indent_length = v[i][j] - '0';
  				poz = j;
  				break;
  			}
  		}
  		strcpy(v[i] + 1, v[i] + poz + 1); // sterg din comanda indent_length
  		parametrii(v, i, original_line_count, &arg1, &arg2);
      if (arg1 == -2 || arg2 == -2) {
        go = 0;
        break;
      }
  		paragraf(original, original_line_count, indent_length, arg1, arg2);
  	}
  	//Justify
  	if (v[i][0] == 'J' || v[i][0] == 'j') {
      if (nr > 3) {
        go = 0;
        break;
      }
  		parametrii(v, i, original_line_count, &arg1, &arg2);
      if (arg1 == -2 || arg2 == -2) {
        go = 0;
        break;
      }
  		justify(original, original_line_count, arg1, arg2);
  	}
  	//Liste
  	if (v[i][0] == 'I' || v[i][0] == 'i') {
      if (nr > 5 || nr < 3) {
        go = 0;
        break;
      }
      int ok = 0;
      for (j = 2; j < strlen(v[i]); j++) {
        if (v[i][j] != ' ' && ok == 0) {
          list_type = v[i][j];
          ok = 1;
          continue;
        }
        if (v[i][j] != ' ' && ok == 1) {
          special_character = v[i][j];
          poz = j;
          break;
        }
      }
      if (strchr(tip_lista, list_type) == 0) {
        go = 0;
        break;
      }
      strcpy(v[i] + 1, v[i] + poz + 1); // sterg list type si special character
      parametrii(v, i, original_line_count, &arg1, &arg2);
      if (arg1 == -2 || arg2 == -2) {
        go = 0;
        break;
      }
      for (j = 0; j < original_line_count; j++) {
        eliminare_trailing(original, j);
      }
      lists(original, original_line_count, list_type,
       special_character, arg1, arg2);
      for (j = 0; j < original_line_count; j++) {
        eliminare_trailing(original, j);
      }
    }
    //Liste ordonate
    if (v[i][0] == 'O' || v[i][0] == 'o') {
      if (nr > 6 || nr < 4) {
        go = 0;
          break;
      }
      int ok = 0, ok2 = 0;
      for (j = 2; j < strlen(v[i]); j++) {
        if (v[i][j] != ' ' && ok == 0) {
          list_type = v[i][j];
          ok = 1;
          j++; 
        }
        if (v[i][j] != ' ' && ok == 1 && ok2 == 0) {
          special_character = v[i][j];
          ok2 = 1;
          j++;
        }
        if (v[i][j] != ' ' && ok == 1 && ok2 == 1) {
          ordering = v[i][j];
          poz = j;
          break;
        }
      }
      if (strchr(tip_lista, list_type) == 0) {
        go = 0;
        break;
      }
      if (ordering != 'a' && ordering != 'z') {
        go = 0;
        break;
      }
      strcpy(v[i] + 1, v[i] + poz + 1);
      parametrii(v, i, original_line_count, &arg1, &arg2);
      if (arg1 == -2 || arg2 == -2) {
        go = 0;
        break;
      }
      sort(original, arg1, arg2, ordering);
      lists(original, original_line_count, list_type,
       special_character, arg1, arg2);
      for (j = 0; j < original_line_count; j++) {
        eliminare_trailing(original, j);
      }
    }

  }

  if (go2 == 0) {
    printf("Cannot wrap!\n");
    for (i = 0; i < copie_line_count; i++) {
      strcpy(original[i], copie2[i]);
    }
    original_line_count = copie_line_count;
  }
  else
  if (go == 0) {
    printf("Invalid operation!\n");
    for (i = 0; i < copie_line_count; i++) {
      strcpy(original[i], copie2[i]);
    }
    original_line_count = copie_line_count;
  }
  
  for (i = 0; i < original_line_count; i++) {
    strcpy(result[i], original[i]);
  }
  result_line_count = original_line_count;

  // Open output file for writing
  FILE *output_file = fopen(argv[3], "w");

  if (output_file == NULL) {
    fprintf(stderr, "Could not open or create file \"%s\"\n", argv[3]);
    return -2;
  }

  // Write result in output file
  for (i = 0; i < result_line_count; i++) {
    fputs(result[i], output_file);
  }

  fclose(output_file);

  return 0;
}

