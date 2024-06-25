//IMPLEMENTAÇÃO FILA VETOR CIRCULAR
//MARIA RITA PIEKAS
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

void fila_remove(Fila self, void *pdado)  {
  if(self->n_elem < self->tamanho * 0.35) {
      if(self->n_elem < MIN_ELEMENTOS) {
      }
      else if(self->pos_i >= self->tamanho / 2) {
      void *pos_if = calcula_ponteiro(self, 0);
      void *pos_d = calcula_ponteiro(self, self->tamanho - self->pos_i - 1);
      memmove(pos_d, pos_if, self->tam_dado * self->tamanho - self->pos_i - 1);
      void *p_i = calcula_ponteiro(self, self->pos_i);
      memmove(pos_if, p_i, self->tam_dado * self->tamanho - self->pos_i - 1);
      self->espaco = realloc(self->espaco, (self->tamanho / 2) * self->tam_dado);
      self->tamanho = self->tamanho / 2;
      self->pos_i = 0;
    } else {
      void *pos_ii = calcula_ponteiro(self, 0);
      void *p_i = calcula_ponteiro(self, self->pos_i);
      memmove(pos_ii, p_i, self->tam_dado * self->n_elem);
      self->espaco = realloc(self->espaco, (self->tamanho / 2) * self->tam_dado);
      self->tamanho = self->tamanho / 2;
      self->pos_i = 0;
    }
  }

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
  assert(self->n_elem <= self->tamanho);
  if(self->n_elem == self->tamanho) {
    int tam_antigo = self->tamanho;
    int pos_i_antiga = self->pos_i;
    assert(self->espaco != NULL);
    self->espaco = realloc(self->espaco, (self->tamanho * 2) * (self->tam_dado));
    assert(self->espaco != NULL);
    self->tamanho = self->tamanho * 2;
    void *pontr_i = calcula_ponteiro(self,0 );
    assert(pontr_i != NULL);
    void *pontr_f = calcula_ponteiro(self, tam_antigo-1);
    assert(pontr_f != NULL);
    self->pos_i = pos_i_antiga;
}
  self->n_elem++;
  void *ptr = calcula_ponteiro(self, self->n_elem-1);
  memmove(ptr, pdado, self->tam_dado);
}

void fila_inicia_percurso(Fila self, int pos_inicial)
{
  self->pos_percurso = pos_inicial;
}


bool fila_proximo(Fila self, void *pdado)
{
  void *ptr = calcula_ponteiro(self, self->pos_percurso);
  if (ptr == NULL) return false;
  if (pdado != NULL) {
    memmove(pdado, ptr, self->tam_dado);
  }
  if (self->pos_percurso < 0) {
    self->pos_percurso--;
  } else {
    self->pos_percurso++;
  }
  return true;
}

