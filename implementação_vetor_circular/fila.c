//IMPLEMENTAÇÃO FILA COM VETOR CIRCULAR
//POR MARIA RITA PIEKAS
//mariaritapiekas@gmail.com


#include "fila.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_ELEMENTOS 10

struct _fila {
  int n_elem;
  int tamanho;
  int pos_i;
  int tam_dado;
  int pos_percurso;
  void *espaco;
};

// funções que implementam as operações básicas de uma fila

// cria uma fila vazia que suporta dados do tamanho fornecido (em bytes)
Fila fila_cria(int tam_do_dado) {
  Fila self = malloc(sizeof(struct _fila));
  if (self != NULL) {
    self->espaco = malloc(MIN_ELEMENTOS * tam_do_dado);
    if (self->espaco != NULL) {
      self->n_elem = 0;
      self->tam_dado = tam_do_dado;
      self->pos_i = 0;
      self->tamanho = MIN_ELEMENTOS;
    } else {
      free(self);
      self = NULL;
    }
  }
  return self;
}


void fila_destroi(Fila self) {
  free(self->espaco);
  free(self);
}

bool fila_vazia(Fila self) {
  return self->n_elem == 0;
}

// calcula o valor do ponteiro para o elemento na posição pos da fila
static void *calcula_ponteiro(Fila self, int pos)
{
  // TODO: suporte a pos negativa
  if (pos < 0 || pos >= self->n_elem) return NULL;
  void *ptr = (char *)self->espaco + ((self->pos_i + pos) % self->tamanho) * self->tam_dado;
  return ptr;
}

void fila_remove(Fila self, void *pdado) {
  void *ptr = calcula_ponteiro(self, 0);
  assert(ptr != NULL);
  if (pdado != NULL) {
    memmove(pdado, ptr, self->tam_dado);
  }
  ptr = calcula_ponteiro(self, 1);
  self->n_elem--;
  self->pos_i++;
}


void fila_insere(Fila self, void *pdado) {
  assert(self->n_elem < self->tamanho);
  if(self->n_elem == self->tamanho) {
    self->tamanho = self->tamanho * 1.5;
    self->espaco = realloc(self->espaco, self->tamanho);
    assert(self->espaco != NULL);
    void *pontr_i = calcula_ponteiro(self, 0);
    void *pontr_f = calcula_ponteiro(self, self->n_elem);
    memmove(pontr_f, pontr_i, self->pos_i * self->tam_dado);
  }
  self->n_elem++;
  void *ptr = calcula_ponteiro(self, self->n_elem-1);
  memmove(ptr, pdado, self->tam_dado);
}

void fila_inicia_percurso(Fila self, int pos_inicial)
{
  pos_inicial =  self->pos_i;
  self->pos_percurso = pos_inicial;
}

bool fila_proximo(Fila self, void *pdado) {  
  void *ptr = calcula_ponteiro(self, self->pos_percurso);
  if (ptr == NULL) return false;
  memmove(pdado, ptr, self->tam_dado);
  if (self->pos_percurso < 0) {
    self->pos_percurso--;
  } else {
    self->pos_percurso++;
  }
  return true;
}

