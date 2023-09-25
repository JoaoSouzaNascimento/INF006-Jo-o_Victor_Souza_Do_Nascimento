#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_LINE_FILE 500

// declaração dos tipos de dados a serem trabalhados
typedef struct {
  char **names;
  float *floats;
  int *integers;
  float **points;
  int key_names, key_floats, key_integers, key_points;
} Ldata;

// estrutura utilizada para flexibilizar a utilização de funções
typedef struct{
  float *floatarray;
  int *intarray;
  char **strarray;
  float **pointarray;
}Datatype;

// função que realiza a troca entre dois elementos
void troca(Datatype vet, int i, int j, char option)
{
  if(option=='0')
  {
  	int aux = vet.intarray[i];
  	vet.intarray[i] = vet.intarray[j];
  	vet.intarray[j] = aux;
  } else if (option == '1')
  {
    float aux = vet.floatarray[i];
  	vet.floatarray[i] = vet.floatarray[j];
  	vet.floatarray[j] = aux;
  } else if (option == '2')
  {
    char *aux;
    aux=(char*)malloc((strlen(vet.strarray[i])+1)*sizeof(char));
    
    strcpy(aux, vet.strarray[i]);
    
    vet.strarray[i]=(char*)realloc(vet.strarray[i],( strlen(vet.strarray[j])+1)*sizeof(char));

    strcpy(vet.strarray[i], vet.strarray[j]);

    vet.strarray[j]=(char*)realloc(vet.strarray[j],(strlen(aux)+1)*sizeof(char));

    strcpy(vet.strarray[j], aux);

    free(aux); 
  } else if (option == '3')
  {
    float *aux = vet.pointarray[i];
  	vet.pointarray[i] = vet.pointarray[j];
  	vet.pointarray[j] = aux;
  }
}

// particiona e retorna o índice do pivô
int particiona(Datatype vet, int inicio, int fim,  char option)
{
	int pivo_indice, i;
  float pivo;
  char *strpivo=NULL;
  
	if(option=='0')
  {
    pivo = vet.intarray[fim]; // o pivô é sempre o último elemento
  } else if(option=='1')
  {
    pivo = vet.floatarray[fim]; // o pivô é sempre o último elemento
  }  else if(option=='2')
  {
    strpivo=(char*)malloc((strlen(vet.strarray[fim])+1)*sizeof(char));
    strcpy(strpivo, vet.strarray[fim]); // o pivô é sempre o último elemento
  } else if(option=='3')
  {
    pivo = vet.pointarray[fim][2]; // o pivô é sempre o último elemento
  }
  
	pivo_indice = inicio;
	
	for(i = inicio; i < fim; i++)
	{
		// verifica se o elemento é <= ao pivô
		if(option=='0' && vet.intarray[i] <= pivo)
		{
			// realiza a troca
			troca(vet, i, pivo_indice,option);
			// incrementa o pivo_indice
			pivo_indice++;
		} else if(option=='1' && vet.floatarray[i] <= pivo)
		{
			// realiza a troca
			troca(vet, i, pivo_indice,option);
			// incrementa o pivo_indice
			pivo_indice++;
		} else if(option=='2' && strcmp(vet.strarray[i], strpivo) <= 0)
		{
			// realiza a troca
			troca(vet, i, pivo_indice,option);
			// incrementa o pivo_indice
			pivo_indice++;
		} else if(option=='3' && vet.pointarray[i][2] <= pivo)
		{
			// realiza a troca
			troca(vet, i, pivo_indice,option);
			// incrementa o pivo_indice
			pivo_indice++;
		}
	}

  free(strpivo);
	// troca o pivô
	troca(vet, pivo_indice, fim,option);
	// retorna o índice do pivô
	return pivo_indice;
}

// escolhe um pivô aleatório para evitar o pior caso do quicksort
int particiona_random(Datatype vet, int inicio, int fim, char option)
{
	// seleciona um número entre fim (inclusive) e inicio (inclusive)
	int pivo_indice = (rand() % (fim - inicio + 1)) + inicio;
	
	// faz a troca para colocar o pivô no fim
	troca(vet, pivo_indice, fim, option);
	// chama a particiona
	return particiona(vet, inicio, fim, option);
}

void quick_sort(Datatype vet, int inicio, int fim, char option)
{
  
	if(inicio < fim)
	{
		// função particionar retorna o índice do pivô
		int pivo_indice = particiona_random(vet, inicio, fim, option);
		
		// chamadas recursivas quick_sort
		quick_sort(vet, inicio, pivo_indice - 1, option);
		quick_sort(vet, pivo_indice + 1, fim, option);
	}
}

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

Ldata *organizer(Ldata *datas, char *line,int key_datas) {
  datas= (Ldata*)realloc(datas, (key_datas + 1) * sizeof(Ldata));
  if (datas == NULL) {
        // A alocação de memória falhou
          printf("Erro: Falha na alocação de memória.\n");
          exit(1); // Saia do programa ou tome as medidas apropriadas.
      }
  char *token;
  char *tok;
  char havfloat = '0';
  char havchar = '0';
  char havinteger = '0';
  char havpoints = '0';
  inicializer(&datas[key_datas]);

  
  for (token = strtok(line, " "); token != NULL ; token = strtok(NULL, " ")) {
    
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

      datas[key_datas].names =
          (char **)realloc(datas[key_datas].names, (datas[key_datas].key_names + 1) * sizeof(char *));

      if (datas[key_datas].names == NULL) {
        perror("Falha na alocação de memória");
        exit(1);
      }

      datas[key_datas].names[datas[key_datas].key_names] = (char *)malloc(strlen(token) + 1);

      if (datas[key_datas].names[datas[key_datas].key_names] == NULL) {
        perror("Falha na alocação de memória");
        exit(1);
      }

      strcpy(datas[key_datas].names[datas[key_datas].key_names], token);
      datas[key_datas].key_names++;
    }

    else if (havinteger == '1' && havpoints == '1') {
      datas[key_datas].points =
          (float **)realloc(datas[key_datas].points, (datas[key_datas].key_points + 1) * sizeof(float *));

      if (datas[key_datas].points == NULL) {
        perror("Falha na alocação de memória");
        exit(1);
      }

      datas[key_datas].points[datas[key_datas].key_points] = (float *)malloc(2*sizeof(float));

      if (datas[key_datas].points[datas[key_datas].key_points] == NULL) {
        perror("Falha na alocação de memória");
        exit(1);
      }

      sscanf(token, "%*c %f %*c %f %*c", &datas[key_datas].points[datas[key_datas].key_points][0],
             &datas[key_datas].points[datas[key_datas].key_points][1]);
      datas[key_datas].key_points++;
    }

    else if (havfloat == '1' && havinteger == '1') {
      datas[key_datas].floats =
          (float *)realloc(datas[key_datas].floats, (datas[key_datas].key_floats + 1) * sizeof(float));

      if (datas[key_datas].floats == NULL) {
        perror("Falha na alocação de memória");
        exit(1);
      }

      sscanf(token, "%f", &datas[key_datas].floats[datas[key_datas].key_floats]);

      datas[key_datas].key_floats++;
    }

    else if (havinteger == '1') {
      datas[key_datas].integers =
          (int *)realloc(datas[key_datas].integers, (datas[key_datas].key_integers + 1) * sizeof(int));

      if (datas[key_datas].integers == NULL) {
        perror("Falha na alocação de memória");
        exit(1);
      }

      sscanf(token, "%d", &datas[key_datas].integers[datas[key_datas].key_integers]);
      datas[key_datas].key_integers++;
    }
  }
  return datas;
}

Ldata *read(Ldata *datas, int *key_datas) {
  FILE *input;
  char*line = malloc(MAX_LINE_FILE*sizeof(char));
  
  if ((input = fopen("L0Q2.in", "r")) != NULL) {

    while (fgets(line, MAX_LINE_FILE, input)!=NULL) 
    {
      datas=organizer(datas, line, *key_datas);
    
      *key_datas+=1;
    }
  }
  free(line);
  fclose(input);
  return datas;
}

void DistancePointOrigin(Datatype vet, int key_points){

  for(int i = 0; i<key_points;i++)
  {
    vet.pointarray[i]=(float *)realloc(vet.pointarray[i],sizeof(vet.pointarray[i]) + sizeof(float ));
    
    vet.pointarray[i][2] = sqrt(((vet.pointarray[i][0]*vet.pointarray[i][0]) + (vet.pointarray[i][1]*vet.pointarray[i][1])));  
  }
}

void SortInt(Ldata *datas, int key_datas, char option) 
{
  Datatype vet;

  if(option=='0')
  {
    for(int i=0; i<key_datas;i++)
    { 
      vet.intarray=datas[i].integers;
      quick_sort(vet, 0, datas[i].key_integers-1,option);
    }
  } else if(option=='1')
  {
    for(int i=0; i<key_datas;i++)
    { 
      vet.floatarray=datas[i].floats;
      quick_sort(vet, 0, datas[i].key_floats-1,option);
    }
  } else if(option=='2')
  {
    for(int i=0; i<key_datas;i++)
    { 
      vet.strarray=datas[i].names;
      quick_sort(vet, 0, datas[i].key_names-1,option);
    }
  } else if(option=='3')
  {
    for(int i=0; i<key_datas;i++)
    { 
      vet.pointarray=datas[i].points;
      
      DistancePointOrigin(vet, datas[i].key_points);
      
      quick_sort(vet, 0, datas[i].key_points-1,option);
    }
  }
}

void save(Ldata *datas, int key_datas) 
{
  FILE *output;
  
  if ((output = fopen("L0Q2.out", "w")) != NULL) 
  {
    int j;
    for(int i=0;i<key_datas;i++)
    {
      fprintf(output, "str:");
      for(j=0;j<datas[i].key_names;j++)
      {
        fprintf(output, "%s", datas[i].names[j]);
        if(j<datas[i].key_names)
          fprintf(output, " ");
      }
      
      fprintf(output, "int:");
      for(j=0;j<datas[i].key_integers;j++)
      {
        fprintf(output, "%d", datas[i].integers[j]);
        if(j<datas[i].key_integers)
          fprintf(output, " ");
      }
      
      fprintf(output, "float:");
      for(j=0;j<datas[i].key_floats;j++)
      {
        fprintf(output, "%g", datas[i].floats[j]);
        if(j<datas[i].key_floats)
          fprintf(output, " ");
      }
      
      fprintf(output, "p:");
      for(j=0;j<datas[i].key_points;j++)
      {
        fprintf(output, "(%g,%g)", datas[i].points[j][0], datas[i].points[j][1]);
        if(j<datas[i].key_points-1)
          fprintf(output, " ");
      }
      if(i<key_datas-1)
        fprintf(output, "\n");
    }
  }

  fclose(output);
}

int main(void) {
  Ldata *datas;
  int key_datas=0;
  datas = NULL;
  
  datas=read(datas, &key_datas);
  
  SortInt(datas,key_datas,'0');
  SortInt(datas,key_datas,'1');
  SortInt(datas,key_datas,'2');
  SortInt(datas,key_datas,'3');
  
  save(datas,key_datas);
  
  return 0;
}


