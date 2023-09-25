#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_FILE 100

typedef struct {
  char **names;
  float *floats;
  int *integers;
  float **points;
  int key_names, key_floats, key_integers, key_points;
} Ldata;

void inicializer(Ldata *lista) {

  lista->names = NULL;
  lista->key_names = 0;

  lista->integers = NULL;
  lista->key_integers = 0;

  lista->points = NULL;
  lista->key_points = 0;

  lista->floats = NULL;
  lista->key_floats = 0;
}

Ldata organizer(Ldata *datas, char *line) {
  Ldata aux;
  char *token;
  char *tok;
  char havfloat = '0';
  char havchar = '0';
  char havinteger = '0';
  char havpoints = '0';
  inicializer(&aux);

  for (token = strtok(line, " "); token != NULL; token = strtok(NULL, " ")) {
    printf("TOKEN DA VEZ: %s", token);
    havfloat = '0';
    havchar = '0';
    havinteger = '0';
    havpoints = '0';

    for (int i = 0; token[i] != '\0'; i++) {
      if (token[i] >= 48 && token[i] <= 57) {
        havinteger = '1';
      }
      if (token[i] == 46) {
        havfloat = '1';
      }
      if (token[i] == '(' || token[i] == ',' || token[i] == ')') {
        havpoints = '1';
      }
      if (token[i] >= 'a' && token[i] <= 'z') {
        havchar = '1';
      }
    }

    if (havchar == '1') {

      aux.names =
          (char **)realloc(aux.names, (aux.key_names + 1) * sizeof(char *));

      if (aux.names == NULL) {
        perror("Falha na alocação de memória");
        exit(1);
      }

      aux.names[aux.key_names] = (char *)malloc(strlen(token) + 1);

      if (aux.names[aux.key_names] == NULL) {
        perror("Falha na alocação de memória");
        exit(1);
      }

      strcpy(aux.names[aux.key_names], token);
      printf("\n %s \n", aux.names[aux.key_names]);
      aux.key_names++;
    }

    else if (havinteger == '1' && havpoints == '1') {
      aux.points =
          (float **)realloc(aux.points, (aux.key_points + 1) * sizeof(float *));

      if (aux.points == NULL) {
        perror("Falha na alocação de memória");
        exit(1);
      }

      aux.points[aux.key_points] = (float *)malloc(2);

      if (aux.points[aux.key_points] == NULL) {
        perror("Falha na alocação de memória");
        exit(1);
      }

      sscanf(token, "%*c %f %*c %f %*c", &aux.points[aux.key_points][0],
             &aux.points[aux.key_points][1]);
      printf("\n (%.2f,%.2f) \n", aux.points[aux.key_points][0],
             aux.points[aux.key_points][1]);
      aux.key_points++;
    }

    else if (havfloat == '1' && havinteger == '1') {
      aux.floats =
          (float *)realloc(aux.floats, (aux.key_floats + 1) * sizeof(float *));

      if (aux.floats == NULL) {
        perror("Falha na alocação de memória");
        exit(1);
      }

      sscanf(token, "%f", &aux.floats[aux.key_floats]);
      printf("\n %.2f \n", aux.floats[aux.key_floats]);
      aux.key_floats++;
    }

    else if (havinteger == '1') {
      aux.integers =
          (int *)realloc(aux.integers, (aux.key_integers + 1) * sizeof(int *));

      if (aux.integers == NULL) {
        perror("Falha na alocação de memória");
        exit(1);
      }

      sscanf(token, "%d", &aux.integers[aux.key_integers]);
      printf("\n %d \n", aux.integers[aux.key_integers]);
      aux.key_integers++;
    }
  }
  return aux;
}

void read(Ldata *datas, int key_datas) {
  FILE *input;
  
  char line[MAX_LINE_FILE];

  if ((input = fopen("L0Q2in.txt", "r")) != NULL) {

    while (!feof(input)) {
      fgets(line, MAX_LINE_FILE, input);
      datas[key_datas]=organizer(datas, line);
      //printf("%f",datas[key_datas].floats[0]);
      key_datas++;
    }
  }
  fclose(input);
}

int main(void) {
  Ldata *datas;
  int key_datas = 0;

  read(datas, key_datas);

  printf("Hello World\n");
  return 0;
}