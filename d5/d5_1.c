#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <openssl/evp.h>

int main(int argc, char *argv[])
{
  EVP_MD_CTX *mdctx;
  char id[] = "ojvtpuvg";
  char msg[100];
  unsigned char md_value[EVP_MAX_MD_SIZE];
  int md_len, i, count = 0;

  mdctx = EVP_MD_CTX_create();
  for (i = 0; count < 8; i++) {
    EVP_DigestInit_ex(mdctx, EVP_md5(), NULL);
    sprintf(msg, "%s%d", id, i);
    EVP_DigestUpdate(mdctx, msg, strlen(msg));
    EVP_DigestFinal_ex(mdctx, md_value, &md_len);
    if (md_value[0] == 0 && md_value[1] == 0 &&
        (md_value[2] >> 4) == 0) {
      printf("%x", md_value[2] & 15);
      count++;
    }
  }
  printf("\n");

  EVP_MD_CTX_destroy(mdctx);
}
