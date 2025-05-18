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

void reiniciar_vector(int *vector){
  for (int i = 0 ; i < 10 ; i++){
    vector[i] = 0 ;
  }
}

int is_valid(Node* n){
  int vector[10];
  // Condicion de filas
  // Recorre matriz
  for (int i = 0 ; i < 9 ; i++){
    reiniciar_vector(vector);
    for (int j = 0 ; j < 9 ; j++){
      int num = n->sudo[i][j];
      if (num == 0) continue; // Si se topa con un 0 sigue recorriendo la matriz
      if (vector[num]) return 0; // Si el número ya está en el vector (marcado como 1), no es válido
      vector[num] = 1;  // Si no está en el vector, lo marca como 1
    }
  }
  // Condicion de columnas
  // Hace el mismo proceso pero para las columnas
  for (int j = 0 ; j < 9 ; j++){
    reiniciar_vector(vector);
    for (int i = 0 ; i < 9 ; i++){
      int num = n->sudo[i][j];
      if (num == 0) continue; 
      if (vector[num]) return 0;
      vector[num] = 1;
    }
  }

  // Condicion de submatrices
  for (int k = 0 ; k < 9 ; k++){
    reiniciar_vector(vector);
    for (int l = 0 ; l < 9 ; l++){
      // Definir las submatrices
      int i = 3 * (k / 3) + (l / 3);
      int j = 3 * (k % 3) + (l % 3);
      int num = n->sudo[i][j];
      // Mismas condiciones
      if (num == 0) continue;
      if (vector[num]) return 0;
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
          // Verificar si cumple las condiciones de la funcion is_valid
          if (is_valid(new_node)){
            // Si asi, se agrega a la lista de nodos adyacentes
            pushBack(adj_list, new_node);
          } else {
            free(new_node);
          }
        }
        return adj_list;  // Para no seguir buscando celdas
      }
    }
  }
  return adj_list;  // Si no hay CELDAS vacias, devuelve la LISTA vacia
}

int is_final(Node* n){
  for (int i = 0 ; i < 9 ; i++){
    for (int j = 0 ; j < 9 ; j++){
      // Si hay una celda = 0, no es el resultado final
      if (n->sudo[i][j] == 0) return 0;
    }
  }
  return 1; // Si no hay ceros, es el estado final
}

Node* DFS(Node* initial, int* cont){
  Stack *pila = createStack();
  push(pila, initial); // Agregar el nodo 0
  // Recorrer la pila
  while (top(pila) != NULL){
    Node *current = top(stack);
    pop(pila); // Elimina el nodo procesado
    if (is_final(current)){ // Si es el estado final
      return current; // Se retorna
    }
    List *adj_list = get_adj_nodes(current); // Vemos los nodos adyacentes
    Node *vecino;
    while ((vecino = popFront(adj_list)) != NULL){
      push(pila, vecino); // Agregar el vecino a la pila
    }
  }
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