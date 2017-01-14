#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <openssl/evp.h>

int main(int argc, char *argv[])
{
  EVP_MD_CTX *mdctx;
  char id[] = "ojvtpuvg";
  // char id[] = "abc";
  char msg[100];
  unsigned char md_value[EVP_MAX_MD_SIZE];
  int md_len, i, count = 0, pos;
  char res[] = "________";
  char chs[] = "0123456789abcdef";

  mdctx = EVP_MD_CTX_create();
  printf("%s", res);
  for (i = 0; count < 8; i++) {
    EVP_DigestInit_ex(mdctx, EVP_md5(), NULL);
    sprintf(msg, "%s%d", id, i);
    EVP_DigestUpdate(mdctx, msg, strlen(msg));
    EVP_DigestFinal_ex(mdctx, md_value, &md_len);
    if (md_value[0] == 0 && md_value[1] == 0 &&
        (md_value[2] >> 4) == 0 &&
        (pos = md_value[2] & 15) < 8 && res[pos] == '_') {
      res[pos] = chs[md_value[3] >> 4];
      printf("\r%s", res);
      count++;
    }
  }
  printf("\n");

  EVP_MD_CTX_destroy(mdctx);
}
