# Building Source in a Chroot

A common issue on Unix-like operating systems is a mismatch between libraries on different systems. I myself ran into this issue when building this project on my main PC (which uses Manjaro, which is based on Arch), and on my CI server (which uses debian). 

A solution to this is building/running the game inside of a chroot environment. Personally, I use schroot in order to easily manage chroot environments. The schroot tool is available on any Linux distro for the most part.  
In order to setup the chroot, I used debootstrap, which is a tool provided by the Debian project. You can use it to setup a custom chroot that uses Debian, which is your best choice if you want to build this reliably. 

Optionally, you can also use the sysroots provided by Valve, called the Steam Runtime. Unfortunately, these sysroots use pretty old tools, so you will need to be content with using GCC-4.8 or GCC-5 if you go this route.

Building in a chroot of your choice can be done like this: 

```bash
schroot -c build-chroot -d /path/to/your/source/work/dir/

[ -d build ] && rm -rf build 
mkdir build && cd build

cmake ../ -DCMAKE_C_FLAGS=-m32 -DCMAKE_CXX_FLAGS=-m32

make -j4 && make install
```

I find that running software built inside of a relatively modern chroot works well. Otherwise, you can run it inside the chroot.

As for distributing the compiled products, I've yet to come up with a good solution. The best solution is probably to use the Steam Runtime's sysroots for building, as those are generally used by many Linux users anyways.

Another solution might be to just wing the fuck out of it! Source seems to have pretty easy dependencies to meet, so you don't need to worry about users needing some obscure version of boost or something. Afaik, Source just depends on curl, ssl, and SDL2, all of which it ships with itself. 

The final solution is not exactly ideal for some teams, but I think it works too: Provide the source code and have users build it themselves. Linux users are generally going to be knowledgeable about this stuff, so most will probably be able to build it themselves.

For me, I think the first option is best. Source should run fine on any system pretty much, since everyone should have libc and SDL2!
