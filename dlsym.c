#include  <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
int fun(){
    printf("test");
}

typedef struct
{
  __const char *dli_fname;  /* File name of defining object.  */
  void *dli_fbase;      /* Load address of that object.  */
  __const char *dli_sname;  /* Name of nearest symbol.  */
  void *dli_saddr;      /* Exact value of nearest symbol.  */
} Dl_info;

int main(){
    char fname[] = "fun";
    void * handle = dlopen("./trace.o", RTLD_LAZY );
    // you could do RTLD_NOW as well.  shouldn't matter
    if(!handle) {
        fprintf(stderr, "Dynamic linking on main module : %s\n", dlerror() );
        exit(1);
    }

    void * addr = dlsym(handle, fname);
    fprintf(stderr, "%s is at %p\n", fname, addr);
    Dl_info info;
    int rc = dladdr(addr, &info);
    printf("fname=%s, fbase=%x, sname=%s, saddr=%x\n", info.dli_fname, info.dli_fbase, info.dli_sname, info.dli_saddr);
}
