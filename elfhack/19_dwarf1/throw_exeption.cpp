#include <cstdio>
#include <cstring>
char buf[100];

void ReadAndThrow(){
  printf("enter expression to clculate: ");
  fgets(buf, sizeof(buf), stdin);

  char* nlp = strchr(buf, '\n');
  if(nlp)  *nlp = '\0';

  throw(const char*) buf;
}
int main(){
  try {
    ReadAndThrow();
  } catch (const char* msg) {
    printf("Exception occured!: ");
    puts(msg);
  }
}


