#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  int vector[10] = {0};
  // Condicion de filas
  for (int i = 0 ; i < 9 ; i++){
    for (int j = 0 ; j < 9 ; j++){
      int num = n->sudo[i][j];
      if (num == 0) continue; // Si se topa con un 0 sigue recorriendo la matriz
      if (vector[num]) return 0; // Si el número ya está en el vector, no es válido
      vector[num] = 1;
    }
  }
  // Condicion de columnas
  for (int j = 0 ; j < 9 ; j++){
    for (int i = 0 ; i < 9 ; i++){
      int num = n->sudo[i][j];
      if (num == 0) continue; // Si se topa con un 0 sigue recorriendo la matriz
      if (vector[num]) return 0; // Si el número ya está en el vector, no es válido
      vector[num] = 1;
    }
  }
  return 1;
}


List* get_adj_nodes(Node* n){
  List* adj_list=createList();

  // Recorrer la matriz para encontrar la primera celda vacia
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      if(n->sudo[i][j] == 0){ // Primera celda vacia encontrada
        for (int k = 1 ; k <= 9 ; k++){
          Node* new_node = copy(n);
          new_node->sudo[i][j] = k;
          pushBack(adj_list, new_node);
        }
        return adj_list;  // Para no seguir buscando celdas
      }
    }
  }
  return adj_list;  // Si no hay CELDAS vacias, devuelve la LISTA vacia
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}
*/