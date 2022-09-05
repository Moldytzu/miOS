# Codename: miOS

## Attention!
This project depends on the cross-compiler built with the script from https://github.com/Moldytzu/cross-compiler-builder.

### Milestones:
##### [x] Hello World:
   	- configure project [x]
    - configure Limine [x]
    - use the terminal to display some text [x]
    - enable simd [x]
##### [] Userspace:
    - set up basic serial communication [x]
    - set up a GDT [x]
    - create a physical and virtual memory manager [x]
    - create a heap [x]
    - set up a TSS [x]
    - set up an IDT [x]    
    - set up sysret/syscall [x]
    - jump in userspace []
    - create one test syscall []
##### [] Multiprocessing:
    - set up the lapic intrerrupt controller and timer []
    - boot up the cores []
    - make the cores jump in long mode []
    - locks []
    - test serial communication in parallel []
##### [] Scheduling:
    - set up a preemptive scheduler for a core []
    - make it work for all of them []
##### [] RAM filesystem:
    - read a filesystem into memory using Limine []
    - read files from it []
##### [] Framebuffer:
    - get framebuffer information []
    - read a screen font from the ram filesystem []
    - use it to draw text on the screen []
##### [] ELF:
    - read and execute a static ELF executable []
    - load shared objects []
##### [] VFS:
    - basic structure []
    - map the RAM filesystem []
    - expose as syscall []
##### [] Subsystems:
    - sockets []
    - virtual terminals []
##### [] Drivers:
    - driver system []
##### [] Userland:
    - init system []
    - shell []
    - libc []
    - window manager []
    - desktop []