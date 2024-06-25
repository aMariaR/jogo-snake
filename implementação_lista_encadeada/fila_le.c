//l2-t2-maria
//Programa que implementa fila com lista encadeada
//mariaritapiekas@gmail.com

#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include <assert.h>
#include <string.h>

struct no {
  void *dado;
  struct no *prox;
};

struct _fila {
  No lista;
  No fim;
  int tam_dado;
  int pos_percurso;
};


Fila fila_cria(int tamanho_dado)
{
  Fila self =(Fila ) malloc(sizeof(struct _fila));
  assert(self != NULL);
  self->tam_dado = tamanho_dado;
  self->lista = NULL;
  return self;
}


void fila_destroi(Fila self)
{
  No p = self->lista;
  while( p != NULL) {
    No a = p->prox;
    free(p->dado);
    p = a;
    free(p);
  }
  free(self);
}


bool fila_vazia(Fila self)
{
  return(self->lista == NULL);
}


void fila_remove(Fila self, void *pdado)
{
  if(!fila_vazia(self)) {
    No p = self->lista;
    self->lista = self->lista->prox;
    free(p->dado);
    free(p);
  }
}


void fila_insere(Fila self, void *pdado)
{
  No p = (No )malloc(sizeof(struct no));
  assert(p != NULL);
  p->dado = (No)malloc(self->tam_dado);
  assert(p->dado != NULL);
  memmove(p->dado, pdado, self->tam_dado);
  p->prox = NULL;

  if(fila_vazia(self)) {
    self->lista = p;

  } else {
    No a = self->lista;
    while(a->prox != NULL) {
      a = a->prox;
    }
    a->prox = p;
  }
}


void fila_inicia_percurso(Fila self, int pos_inicial) {
    if (pos_inicial < 0) {
        fprintf(stderr, "Sem suporte a percurso invertido na fila.\n");
        No a = self->lista;
        int contador = 0;
        while (a != NULL && contador < self->pos_percurso) {
           a = a->prox;
           contador++;
        }
        self->pos_percurso = contador;
        return;
    }

    self->pos_percurso = pos_inicial;
}


bool fila_proximo(Fila self, void *pdado) {
  No a = self->lista;
  int contador = 0;

    // Encontrar o nó correspondente à posição atual do percurso
  while (a != NULL && contador < self->pos_percurso) {
      a = a->prox;
      contador++;
  }

  if (a == NULL) {
      return false; // Percurso terminado
  }
  self->pos_percurso++;
  memmove(pdado, a->dado, self->tam_dado);
  return true;
}

