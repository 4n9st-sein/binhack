#include <dlfcn.h>
#include <stdio.h>
int main(void) {
  //load libhello.so
  void *lib = dlopen("./libhello.so", RTLD_LAZY);
  if (lib == NULL) {
    printf("dlopen failed: %s\n", dlerror());
    return 1;
    }

    int (*hello)(void);
    hello = dlsym(lib, "hello");
    if (hello == NULL){
      printf("dlsym failed : %s\n", dlerror());
      return 1;
    }
    //call hello() which is defined in libhello.so
    hello();

    int ret = dlclose(lib);
    if (ret != 0) {
      printf("dlclose failed: %s\n", dlerror());
      return 1;
    }
    return 0;
}

