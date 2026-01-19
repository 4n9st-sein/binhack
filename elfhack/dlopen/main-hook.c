#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
//save pointer to special malloc()
//initiallize when first mallc is called
 int (*real_main)(int, char **, char **) = NULL;

//wrapper function of malloc()
int wrapped_main(int argc, char **argv, char **envp ) {
  puts("hello from wrapped_main()");
  return real_main(argc, argv, envp);
}
int __libc_start_main(int (*main)(int, char **, char **), int argc, char **ubp_av, void (*init)(void), void (*fini)(void), void(*rtld_fini)(void), void(*stack_end)){
  //declare pointer to __libc_start_main
  
int (*real_libc_start_main)(int (*)(int, char **, char **), int , char **, void (*)(void), void (*)(void), void(*)(void), void(*));
        real_libc_start_main  = dlsym(RTLD_NEXT, "__libc_start_main");
      if (real_libc_start_main == NULL) {
        fprintf(stderr, "dlsym error: %s\n", dlerror());
        exit(1);
      }
  real_main = main;  
    return real_libc_start_main(wrapped_main, argc, ubp_av, init, fini, rtld_fini, stack_end);
    
  }


