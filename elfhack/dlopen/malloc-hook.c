#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
//save pointer to special malloc()
//initiallize when first mallc is called
static void *(*real_malloc)(size_t) = NULL;

//wrapper function of malloc()
void *malloc(size_t size) {
  if (real_malloc == NULL) {
        //because of RTLD_NEXT, try to find malloc() which is loaded after this
        real_malloc = dlsym(RTLD_NEXT, "malloc");
      if (real_malloc == NULL) {
        fprintf(stderr, "dlsym error: %s\n", dlerror());
        exit(1);
      }
    }
    //output log to stderr
    //By the way, if this output is defined as stdout
    //possibly malloc() will be called and becomes infinite recursion
    fprintf(stderr, "malloc: size=%zu\n", size);
    return real_malloc(size);
  }


