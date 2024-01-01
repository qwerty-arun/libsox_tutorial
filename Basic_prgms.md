# Prgm1: understanding sox_init, argc and argv 
```
#include "sox.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
int main(int argc,char *argv[])
{
	printf("%d\n",argc);
	int i = sox_init();
	printf("%d",i);
	for(int i=0;i<argc;i++)
    {
		printf("%s ",argv[i]);
	}
}
```
> Compile the file using `gcc <filename.c> -lsox` command on terminal. Without the `-lsox`, and error: "undefined error to sox_init()" will be shown.</br>
`sox_init()` will return SOX_SUCCESS if successful. And value of SOX_SUCCESS is 0. Otherwise, SOX_EOF(End of file =-1) will be returned.</br>
> 'argc' is the number of arguments we pass while executing.</br> If we execute like `./a.out <filename.c>`, then `argc` will hold the value '2', because two arguments are passed.</br>
> 'argv' is a pointer to characters, in this case it is the arguments which we pass. The for loop is prints all the arguments which we pass.
> `**argv` instead of `*argv[]` is perfectly correct as array itself is a pointer.</br>
