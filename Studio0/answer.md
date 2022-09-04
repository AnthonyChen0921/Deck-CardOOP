1. Yunlai Chen, Anthony Chen

2. Hostname: linuxlab002

   ```bash
   [c.yunlai@linuxlab002 studio_0] which g++
   /project /compute/compilers/gcc-8.3.0/bin/g++
   ```

3. ```bash
   [c.yunlai@linuxlab002 studio_0] g++ -v
   Using built-in specs.
   COLLECT_GCC=g++
   COLLECT_LTO_WRAPPER=/project/engineering/compilers/gcc-8.3.0/bin/../libexec/gcc/x86_64-pc-linux-gnu/8.3.0/lto-wrapper
   Target: x86_64-pc-linux-gnu
   Configured with: ../gcc-8.3.0/configure --prefix=/project/compute/compilers/gcc-8.3.0 --enable-languages=c,c++,fortran,go --disable-multilib
   Thread model: posix
   gcc version 8.3.0 (GCC) 
   ```

4. ```bash
   [c.yunlai@linuxlab002 studio_0]$ ./studio0 
   usage: studio <arg1> [<arg2> ...]
   [c.yunlai@linuxlab002 studio_0]$ echo $?
   1
   [c.yunlai@linuxlab002 studio_0]$ ./studio0 1
   hello, world!
   [c.yunlai@linuxlab002 studio_0]$ echo $?
   0
   ```

5.  Use '1' as the file name, check the content and return value:

   ```bash
   [c.yunlai@linuxlab002 studio_0]$ ./studio0 1
   [c.yunlai@linuxlab002 studio_0]$ cat 1
   hello, world!
   [c.yunlai@linuxlab002 studio_0]$ echo $?
   0
   ```

6. Change the file '1' to read-only mode, and the return value is 2 (FAIL_OPEN_FILE)

   ```bash
   [c.yunlai@linuxlab002 studio_0]$ chmod a-w 1
   [c.yunlai@linuxlab002 studio_0]$ ./studio0 1
   [c.yunlai@linuxlab002 studio_0]$ echo $?
   2
   ```

   

