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

# Prgm2: sox_open_read and sox_format_t, dereferencing pointers and sox_close()
```
#include "sox.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
int main(int argc, char **argv)
{
int ret = sox_init();
    if (ret == 0) {
	sox_format_t *handle = sox_open_read(argv[1], NULL, NULL, NULL);
	printf("%s", handle->filename);
	printf("%d", handle->encoding.encoding);
	sox_close(handle);
    }
}
```
> If 'ret' has the value '0' which means sox library has been initialised, then create a pointer of `sox_format_t`.</br>
> `sox_format_t` is actually a structure with various fields like filename, signal, encoding etc. and they are all of different data types. </br>
> We are passing `argv[1]` to the function `sox_open_read` and `NULL` for the rest. `argv[1]` points to the filename which we pass as argument</br>.
> `sox_open_read` expects 4 arguments: path, signal, encoding and filetype.Returns handle for the new session, or null on failure. </br>
> We are just printing filename which we passed as argument during execution by using `handle->filename`. We are dereferencing the pointer.
> Then we are printing values in an enumerator by using `handle->encoding.encoding`. Inside `sox_format_t`, there is another structure (nested structure) called `sox_encodinginfo_t` and in which `encoding` is another field of data type `enum`. </br>
> If you execute `./a.out <filename>.mp3`, output will be 22, since mp3 files are associated with the value '22' inside the enum.</br>
> `sox_close` closes an encoding/decoding sessions. Basically, freeing the pointer. It returns SOX_SUCCESS if successful.</br>

# Prgm3: sox_signal_info_t and sox_open_write
```
# include "sox.h"
# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
int main(int argc, char **argv)
{
	sox_format_t *in, *out;
	assert(sox_init() == SOX_SUCCESS);
	sox_signalinfo_t *sig_info;
	assert(argc==3);
	sig_info->rate=48000;
	sig_info->channels=1;
	sig_info->precision=16;
	assert(in=sox_open_read(argv[1],sig_info,NULL,NULL));
	assert(out=sox_open_write(argv[2],sig_info,NULL,NULL,NULL,NULL));
	sox_close(out);
	sox_close(in);
}
```
> `sox_signalinfo_t` contains fields like rate, channels, precision etc. </br>
> We want both input and output files to have same characteristics. Therefore making a common variable `sig_info` and giving values to its fields by dereferencing the pointers.</br>
> We are passing `sig_info` as 2nd parameter in both read and write functions.</br>
> `sox_open_write` accepts six parameters: path(required), signal(required), encoding, filetype, out of band and overwrite__permitted.</br>
