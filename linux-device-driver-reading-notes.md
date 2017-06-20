# Linux Device Driver

## Policy and mechanism
The distinction between mechanism and policy is one of the best ideas behind the
Unix design. Most programming problems can indeed be split into two parts: “what
capabilities are to be provided” (the mechanism) and “how those capabilities can be
used” (the policy). If the two issues are addressed by different parts of the program,
or even by different programs altogether, the software package is much easier to
develop and to adapt to particular needs.

[Separation of mechanism and policy](https://en.wikipedia.org/wiki/Separation_of_mechanism_and_policy)

[Policy vs mechanism](https://sites.google.com/site/mylokesh/policyvsmechanism)

## Splitting the Kernel
* Process Management
* Memory Management
* Filesystem
* Device control
* Networking

![A split view of kernel](http://www.xml.com/ldd/chapter/book/figs/ldr2_0101.gif)

character device, block device, networking device

Typical code snipet of device initialization and cleanup code.
key word **__init**, **__exit** and macro **module_init**, **module_exit**.
```
static int __init initialization_function(void)
{
/* Initialization code here */
}
module_init(initialization_function);

static void __exit cleanup_function(void)
{
/* Cleanup code here */
}
module_exit(cleanup_function);
```

User-space driver has full C library linked, but kernel space program has only limited library.
User-space driver hang, just kill it. Kernel-space driver hang, system crash.
User-space memory is swappable, unlike kernel-space memory.

Infrastructure of user-space driver is server-client mode. The driver runs as server program and client communicate with server using IPC mechanism.

Interrupts are not available in user-space driver.
Direct access to memory is not availabe in user-space driver.
Response time slower in user-space driver.
Some most import device cannot be helded in user-space, like networking device and blocking device. And some(libusb) may use user-space driver.
