# Codename: miOS

### Milestones:
##### [x] Hello World:
   	- configure project [x]
    - configure Limine [x]
    - use the terminal to display some text [x]
    - enable simd [x]
##### [] Userspace:
    - set up basic serial communication [x]
    - set up a GDT []
    - create a physical and virtual memory manager []
    - create a heap []
    - set up a TSS []
    - set up an IDT []    
    - set up sysret/syscall []
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