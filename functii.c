#include "biblioteca.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define NMAX 1000

void eliminare_trailing(char s[NMAX][NMAX], int line) {
  int i, n, space = 0;
  n = strlen(s[line]) - 1;
  for (i = n-1; i >= 0; i--) {
    if (s[line][i] == ' ' || s[line][i] == '\t') {
      space++;
    } else {
      break;
    }
  }
  if(space > 0) {
    memmove(s[line] + n - space , s[line] + n, strlen(s[line]));
  }
}

void eliminare_starting(char s[NMAX][NMAX], int line) {
  int i, space = 0, n;
  n =  strlen(s[line]) - 1;
  for (i = 0; i < n; i++) {
    if (s[line][i] == ' ' || s[line][i] == '\t') {
      space++;
    } else {
      break;
    }
  }
  if(space > 0)
    memmove(s[line], s[line] + space, strlen(s[line]));
}

void align_left(char original[NMAX][NMAX], int original_line_count,
 int start_line, int end_line) {
  int i;

  for (i = start_line; i <= end_line; i++) {
    eliminare_starting(original, i);
  }

  for (i = 0; i < original_line_count; i++) {
    eliminare_trailing(original, i);
  }
}

void align_right(char original[NMAX][NMAX], int original_line_count,
 int start_line, int end_line) {
  int i, max = 0, lg_linie, j;

  for (i = 0; i < original_line_count; i++) {
    eliminare_trailing(original, i);
  }

  for (i = 0; i <= original_line_count; i++) {
    lg_linie = strlen(original[i]);
    if (lg_linie > max) max = lg_linie;
  }

  for (i = start_line; i <= end_line; i++) {
    lg_linie = strlen(original[i]);
    if (lg_linie != max && original[i][0] != '\n') {
      // mut linia pana devine aliniata la dreapta
      memmove(original[i] + (max - lg_linie), original[i], strlen(original[i]));
      for (j = 0; j < max - lg_linie; j++) {
        // completez cu spatii
        original[i][j] = ' ';
      }
    }
  }
}

void center(char original[NMAX][NMAX], int original_line_count,
 int start_line, int end_line) {
  int i, max = 0, lungime_linie, j, nr_spatii;

  for(i = 0; i < original_line_count; i++) {
    eliminare_trailing(original, i);
  }

  for (i = 0; i < original_line_count; i++) {
    lungime_linie = strlen(original[i]);
    if (lungime_linie > max) max = lungime_linie;
  }
  for(i = start_line; i <= end_line; i++) {
    lungime_linie = strlen(original[i]);
    if(lungime_linie != max && original[i][0] != '\n') {
      if ((max - lungime_linie) % 2 == 0) {
        nr_spatii = (max - lungime_linie) / 2;
      } else {
        nr_spatii = (max - lungime_linie) / 2 + 1;
      }
      memmove(original[i] + nr_spatii, original[i], strlen(original[i]));
      for (j = 0; j < nr_spatii; j++) {
        original[i][j] = ' ';
      }
    }
  }
}

void paragraf(char original[NMAX][NMAX], int original_line_count,
 int indent_length, int start_line, int end_line) {
  int i;
  for (i = 0; i < original_line_count; i++) {
    eliminare_trailing(original, i);
  }

  int j, p = 0;
  if (start_line == 0) {
    // caz separat pentru prima linie din fisier
    memmove(original[0] + indent_length, original[0], strlen(original[0]));
    for (j = 0; j < indent_length; j++) {
      original[0][j] = ' ';
    }
  }

  for (i = start_line - 1; i <= end_line; i++) {
    p = 0;
    if (original[i][0] == '\n') {
      // caut unde am inceput de paragraf
      while (original[i][0] == '\n' && i <= end_line) {
        p++;
        i++;
      }
    }
    if (p >= 1) {
      // mut linia cu indent_length la dreapta si completez cu spatii
      memmove(original[i] + indent_length, original[i], strlen(original[i]));
      for (j = 0; j < indent_length; j++) {
        original[i][j] = ' ';
      }
    }
  }
}

void justify(char original[NMAX][NMAX], int original_line_count,
 int start_line, int end_line) {
  int i, j, lungime_linie, max = 0, ok = 1;
  for (i = 0; i < original_line_count; i++) {
    eliminare_trailing(original, i);
  }
 
  for (i = 0; i < original_line_count; i++) {
    lungime_linie = strlen(original[i]);
    if (lungime_linie > max) max = lungime_linie;
  }
 
  for (i = start_line; i <= end_line; i++) {
    eliminare_starting(original, i);
  }

  for (i = start_line; i < end_line; i++) {
    lungime_linie = strlen(original[i]);
    ok = 1;
    if (original[i][0] != '\n' && original[i+1][0] == '\n') {
      // daca este sfarsit de paragraf sa nu faca justify
      continue;
    }
    if (original[i][0] == '\n') {
      // daca este linia goala sa nu faca justify
      continue;
    }
    if (lungime_linie != max) {
      while (ok != 0 && strlen(original[i]) != max) {
        // parcurg fiecare linie de mai multe ori adaugand cate
        // un spatiu intre 2 cuvinte
        // pana cand lungimea devine egala cu cea a liniei de referinta
        j = 0;
        for (j = 0; j < strlen(original[i])-1; j++) {
          if (original[i][j] != ' ' && original[i][j+1] == ' ') {
            // verific unde este spatiu si mai adaug cate unul
            memmove(original[i] + j+2, original[i] + j+1, strlen(original[i]));
            original[i][j+1] = ' ';
          }
          // daca linia este completata trece la urmatoarea linie din fisier
          if (strlen(original[i]) == max) {
            break;
            ok = 0;
          } 
        }
      }
    }
  }

}

void lists(char original[NMAX][NMAX], int original_line_count,
  char list_type, char special_character,
  int start_line, int end_line) {

  int i, n = 1;
  char copie[NMAX][NMAX], c;
  for (i = 0; i < original_line_count; i++) {
    eliminare_trailing(original, i);
  }

  for (i = start_line; i <= end_line; i++) {
  	eliminare_starting(original, i);
  }

  if (list_type == 'n') {
    for (i = start_line; i <= end_line; i++) {
      memcpy(copie[i], original[i], strlen(original[i]) + 1);
      sprintf(original[i], "%d%c ", n, special_character);
      strcat(original[i], copie[i]);
      n++;
    }
  }
  if (list_type == 'a' || list_type == 'A') {
    if (list_type == 'a') {
      c = 'a';
    } else {
      c = 'A';
    }
    for (i = start_line; i <= end_line; i++) {
      memcpy(copie[i], original[i], strlen(original[i]) + 1);
      sprintf(original[i], "%c%c ", c, special_character);
      strcat(original[i], copie[i]);
      c++;
    }
  }
  if (list_type == 'b') {
    for (i = start_line; i <= end_line; i++) {
      memcpy(copie[i], original[i], strlen(original[i]) + 1);
      sprintf(original[i], "%c ", special_character);
      strcat(original[i], copie[i]);
    }
  }

}

int compare(const void * a ,const void * b) {
  return strcmp((char*) a ,(char*) b);
}

void sort(char original[NMAX][NMAX], int start_line,
 int end_line, char ordering) {
  int i, k = 0, aux_line_count;
  char aux[NMAX][NMAX];
  for (i = start_line; i <= end_line; i++) {
    // copiez intr-o matrice auxiliara liniile din original
    // de la start_line pana la end_line
  	strcpy(aux[k], original[i]);
  	k++;
  }
  aux_line_count = end_line - start_line + 1;
  // sortez matricea aux
  qsort(aux[0], aux_line_count, sizeof(aux[0]), compare);
  
  k = 0;
  // copiez liniile in original
  if (ordering == 'a') {
  	for (i = start_line; i <= end_line; i++) {
  		strcpy(original[i], aux[k++]);
  	}
  } else if (ordering == 'z') {
  	for (i = end_line; i >= start_line; i--) {
  		strcpy(original[i], aux[k++]);
  	}
  }
}

void parametrii(char v[NMAX][NMAX], int i, int lines, int *arg1, int *arg2) {
  // functie care imi determina parametrii unei comenzi
  // pentru "L 2 4" => arg1 = 2, arg2 = 4
  int ok, ok2, j;
  char cif[] = "0123456789";
  *arg1 = *arg2 = 0; // arg1 = start_line; arg2 = end_line;

    if (strlen(v[i]) > 1) {
      // daca am start_line si end_line pentru o comanda.
      // merge si pt cele care pe langa start line si end line
      // mai au alti parametrii deoarece pe acestia din urma 
      // ii sterg din comanda dupa ce ii determin (vezi in main
      // la comenzile de acest tip)
      ok = 1;
      ok2 = 1;
      for (j = 2; j < strlen(v[i]); j++) {
        if ((v[i][j] != ' ') && (ok == 1)) {
          if (strchr(cif, v[i][j]) == 0) { // pt erori daca nu sunt cifre
            *arg1 = -2; // -2 pentru erori
            *arg2 = -2;
            ok = 0;
            break;
          }
          *arg1 = (*arg1) * 10 + (v[i][j] - '0');
          ok2 = 0;
        } else if (v[i][j] == ' ' && ok2 == 0) {
          ok = 0; // inseamna ca am terminat cu start_line
        } else if ((v[i][j] != ' ') && (ok == 0)) {
            if (strchr(cif, v[i][j]) == 0) {
              *arg1 = -2;
              *arg2 = -2;
              break;
            }
            *arg2 = (*arg2) * 10 + (v[i][j] - '0');        
        }
      }
      if (ok == 1) 
        *arg2 = -1; // -1 daca nu este precizat end_line
    } else if(strlen(v[i]) == 1) { // comanda fara parametrii specificati
        *arg1 = *arg2 = -1; // -1 pt ca nu sunt precizati
    }

    if (ok == 1) *arg2 = -1;

    if (*arg1 == -1 && *arg2 == -1) { // daca nu sunt precizati
      *arg1 = 0; // start_line = prima linie din fisier
      *arg2 = lines - 1; // end_line = ultima linie din fisier
    }
    if (*arg1 != 0 && *arg2 == -1) { // end_line nu e precizat
      *arg2 = lines - 1; // ia valoarea numarului de linii din fisier
    }
    if (*arg2 > lines) {
      *arg2 = lines - 1; 
    }
    if (*arg1 > *arg2) {
      *arg1 = -2;
      *arg2 = -2;
    }
}

void wrap (char original[NMAX][NMAX], int *original_line_count,
 int max_line_length) {
  char *p, s[NMAX][NMAX], b[NMAX][NMAX], copie[NMAX][NMAX];
  int i, copie_line_count = *original_line_count, current_line = 0, k = 0, j, n;
  for (i = 0; i < *original_line_count; i++) {
    eliminare_trailing(original, i);
  }
  
  for ( i = 0; i < *original_line_count; i++) {
    strcpy(copie[i], original[i]);
  }

  for (i = 1; i < copie_line_count; i++) {
  	if (copie[i-1][0] =='\n' && copie[i][0] != '\n') {
  		continue;
  	} else {
  		eliminare_starting(copie, i);
  	}
  }
  for (i = 0; i < copie_line_count; i++) {
    n = strlen(copie[i]);
    if (copie[i][0] == '\n') {
      strcat(s[k++], "\n");
    } 
    if (n > 1) {
      for (j = 0; j < n; j++) {
        if (j != n - 1) {
          strncat(s[k], copie[i] + j, 1);
        } else if(copie[i+1][0] == '\n'){
          strcat(s[k++], "\n");
        } else if(copie[i+1][0] != '\n' && i != copie_line_count - 1) {
          strcat(s[k], " ");
        }
      }
    }  
  } // s e o matrice care are pe fiecare linie cate un paragraf din original

 for (i = 0; i <= k; i++) {
    strcpy(original[i], s[i]);
  }
  *original_line_count = k + 1;
  
  for (j = 0; j < strlen(original[0]); j++) {
    if (original[0][j] == ' ') { // daca este spatiu pe prima linie
      strcat(b[current_line], " "); // il bag in noua matrice
    } else {
      break;
    }
  }
  // in b construiesc textul cu wrap
  for (i = 0; i <= k; i++) {
    if (original[i - 1][0] == '\n' && original[i][0] != '\n' && i > 0) {
      for (j = 0; j < strlen(original[i]); j++) {
        if (original[i][j] == ' ') {
          if (strlen(b[current_line]) <= max_line_length - 1) {// daca este 
            strcat(b[current_line], " "); //spatiu la inceput de paragraf
          } else {
            strcat(b[current_line], "\n");
            current_line++;
          }
        } else {
          break;
        }
      }
    }
    p = strtok(s[i], " "); // iau fiecare cuvant din fisier
    while (p) {
      if (strlen(b[current_line]) + strlen(p) <= max_line_length && p[0] != '\n') {
        strcat(b[current_line], p); // il adaug pe linia curenta
        strcat(b[current_line], " "); // pun spatiu dupa el
      } else if (strlen(b[current_line]) + strlen(p) > max_line_length
       && p[0] != '\n' ) { // daca depaseste nr de caractere permis
        memmove(b[current_line] + strlen(b[current_line]) - 1,
         b[current_line] + strlen(b[current_line]) , strlen(b[current_line]));
        strcat(b[current_line], "\n"); // sterg ultimul spatiu si adaug \n
        current_line++; // trec pe linia urmatoarea
        strcat(b[current_line], p); // adaug cuvantul
        strcat(b[current_line], " "); // pun spatiu dupa el
      } else if (p[0] == '\n') { // daca este o linie goala
        memmove(b[current_line] + strlen(b[current_line]) - 1,
         b[current_line] + strlen(b[current_line]) , strlen(b[current_line]));
        current_line++; // o adaug
        strcat(b[current_line], "\n"); //adaug \n
        current_line++; // trec pe linia urmatoare
      }
      p = strtok(NULL, " ");
    }
  }
  //sterg ultimul spatiu pus
  memmove(b[current_line] + strlen(b[current_line]) - 1,
   b[current_line] + strlen(b[current_line]) , strlen(b[current_line]));

  b[current_line][strlen(b[current_line])] = '\n';
  for (i = 0; i <= current_line; i++) {
    strcpy(original[i], b[i]);
  }
  *original_line_count = current_line + 1;
}