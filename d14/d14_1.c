#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <openssl/evp.h>

char candidate(char* md5)
{
  while(md5[0] != '\0') {
    if(md5[1] == md5[0] && md5[2] == md5[0]) {
     return md5[0];
    }
    md5++;
  }
  return 0;
}

int has_five(char *md5, char c)
{
  while(md5[0] != 0) {
    if (md5[0] == c && md5[1] == c && md5[2] == c
      && md5[3] == c && md5[4] == c) {
      return 1;
    }
    md5++;
  }
  return 0;
}

typedef struct _node{
  char c;
  int seq;
  char *md5;
  struct _node *next;
} Node;

Node *create_node(int seq, char c, char *md5)
{
  Node *n = (Node *)malloc(sizeof(Node));
  char *value = (char *)malloc(2*EVP_MAX_MD_SIZE+1);
  strcpy(value, md5);
  n->seq = seq;
  n->c = c;
  n->md5 = value;
  n->next = NULL;
}

void free_node(Node *n)
{
  free(n->md5);
  free(n);
}

void free_list(Node **head, Node **tail) {
  Node *h = *head, *tmp;
  while (h != NULL) {
    tmp = h;
    h = h->next;
    free_node(tmp);
  }
  *head = NULL;
  *tail = NULL;
}

Node *shift(Node **head, Node **tail)
{
  if (*head == NULL) return NULL;
  Node *h = *head;
  *head = h->next;
  if (h == *tail) *tail = NULL;
  return h;
}

void push(Node **head, Node **tail, Node *n)
{
  if (*head == NULL) {
    *head = n;
    *tail = n;
  }
  (*tail)->next = n;
  *tail = n;
}

int is_empty(Node *head)
{
  return head == NULL;
}

char HEX[] = "0123456789abcdef";

void calc_md5(EVP_MD_CTX *mdctx, char* msg, unsigned char *md_value, int *md_len)
{
  EVP_DigestInit_ex(mdctx, EVP_md5(), NULL);
  EVP_DigestUpdate(mdctx, msg, strlen(msg));
  EVP_DigestFinal_ex(mdctx, md_value, md_len);
  int i = *md_len * 2 - 1, val;
  unsigned char chr;
  while (i >= 0) {
    chr = md_value[i/2];
    md_value[i--] = HEX[chr & 0xf];
    md_value[i--] = HEX[chr >> 4];
  }
  md_value[*md_len * 2] = '\0';
}

int traverse(Node *head, Node *tail, char chr)
{
  while(head != NULL) {
    if (has_five(head->md5, chr)) {
      return 1;
    }
    head = head->next;
  }
  return 0;
}

int main(int argc, char *argv[])
{
  EVP_MD_CTX *mdctx;
  char id[] = "ihaygndm";
  char msg[100];
  unsigned char md_value[2*EVP_MAX_MD_SIZE+1];
  int md_len, i, j, count = 0;
  char candi, chr;
  char *md5;
  Node *head = NULL, *tail = NULL, *tmp;

  mdctx = EVP_MD_CTX_create();

  for (i = 0; count < 64; i++) {
    if ((tmp = shift(&head, &tail)) == NULL) {
      sprintf(msg, "%s%d", id, i);
      calc_md5(mdctx, msg, md_value, &md_len);
      if ((candi = candidate(md_value)) == 0) {
        continue;
      }
    } else {
      candi = tmp->c;
      i = tmp->seq;
      free_node(tmp);
      tmp = NULL;
    }

    if (!is_empty(head) && traverse(head, tail, candi)) {
      count++;
      continue;
    }
    else if (!is_empty(head)) {
      j = tail->seq + 1;
    }
    else {
      j = i + 1;
    }
    for (; j <= i+1000; j++) {
      sprintf(msg, "%s%d", id, j);
      calc_md5(mdctx, msg, md_value, &md_len);
      if ((chr = candidate(md_value)) == 0) {
        continue;
      }
      push(&head, &tail, create_node(j, chr, md_value));
      if (has_five(md_value, candi)) {
        count++;
        break;
      }
    }
  }
  printf("result: %d\n", i-1);
  free_list(&head, &tail);

  EVP_MD_CTX_destroy(mdctx);
}
