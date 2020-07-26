iflags is a simple C programs which enumerates the canonical ioctl flags of all
net interfaces on Linux.

I made this in about 15 minutes, out of frustration for the lack of a simple
way to just enumerate the damn flags. (iproute2 does some processing,
/sys/class/net/*/flags exposes something that is surely not the raw flags).

This would probably not work well in BSD, as it works under the assumption that
getifaddrs() returns one AF_PACKET struct for each interface. However,
adapting it to work should be quite trivial.

To compile and run:
```
meson build
cd build
meson compile
./iflags
```

Or if you're one for simple things:
```
gcc iflags.c
./a.out
```

The project doesn't have a license. Do what the hell you want with it. Give
credits if it was useful to you!

