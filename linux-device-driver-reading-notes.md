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


**All code and api resides in kernel source tree include folder.**

Typical code snipet of device initialization and cleanup code.
key word **__init**, **__exit** and macro **module_init**, **module_exit**.
```C
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

## Differences between user-space driver and kernel-space driver
User-space driver has full C library linked, but kernel space program has only limited library.
User-space driver hang, just kill it. Kernel-space driver hang, system crash.
User-space memory is swappable, unlike kernel-space memory.

Infrastructure of user-space driver is server-client mode. The driver runs as server program and client communicate with server using IPC mechanism.

Interrupts are not available in user-space driver.
Direct access to memory is not availabe in user-space driver.
Response time slower in user-space driver.
Some most import device cannot be helded in user-space, like networking device and blocking device. And some(libusb) may use user-space driver.

![user-space and kernel-space](https://image.slidesharecdn.com/linux-kernel-development-22001/95/linux-kernel-development-26-728.jpg?cb=1170880820)

## character device
1. register/allocate device node with major/minor device number
register_chrdev_region/alloc_chrdev_region
```C
if (scull_major) {
  dev = MKDEV(scull_major, scull_minor);
  result = register_chrdev_region(dev, scull_nr_devs, "scull");
} else {
  result = alloc_chrdev_region(&dev, scull_minor, scull_nr_devs,
  "scull");
  scull_major = MAJOR(dev);
}
if (result < 0) {
  printk(KERN_WARNING "scull: can't get major %d\n", scull_major);
  return result;
}
```
2. connect device node with file operation.
File operations include open/release/read/write/lseek/aio_read/aio_write/readdir/poll/ioctl/mmap/flush/fsync/fasync/aio_fsync/lock/...
```C
struct file_operations scull_fops = {
  .owner = THIS_MODULE,
  .llseek = scull_llseek,
  .read = scull_read,
  .write = scull_write,
  .ioctl = scull_ioctl,
  .open = scull_open,
  .release = scull_release,
};
```
![file operation](http://www.srinivasbt.com/linux/drivers/image002.jpg)

3. file structure and inode structure
file structure in kernel-space is party to FILE* in user-space.

4. Char device registration and un-registration.
```C
struct scull_dev {
  struct scull_qset *data; /* Pointer to first quantum set */
  int quantum; /* the current quantum size */
  int qset; /* the current array size */
  unsigned long size; /* amount of data stored here */
  unsigned int access_key; /* used by sculluid and scullpriv */
  struct semaphore sem; /* mutual exclusion semaphore */
  struct cdev cdev; /* Char device structure */
};
static void scull_setup_cdev(struct scull_dev *dev, int index)
{
  int err, devno = MKDEV(scull_major, scull_minor + index);
  cdev_init(&dev->cdev, &scull_fops);
  dev->cdev.owner = THIS_MODULE;
  dev->cdev.ops = &scull_fops;
  err = cdev_add (&dev->cdev, devno, 1);
  /* Fail gracefully if need be */
  if (err)
    printk(KERN_NOTICE "Error %d adding scull%d", err, index);
}
```

## Concurrency and Race condition

Semaphores are a well-understood concept in computer science. At its core, a semaphore is a single integer value combined with a pair of functions that are typically
called P and V. A process wishing to enter a critical section will call P on the relevant
semaphore; if the semaphore’s value is greater than zero, that value is decremented
by one and the process continues. If, instead, the semaphore’s value is 0 (or less), the
process must wait until somebody else releases the semaphore. Unlocking a semaphore is accomplished by calling V; this function increments the value of the semaphore and, if necessary, wakes up processes that are waiting.

When semaphores are used for mutual exclusion—keeping multiple processes from
running within a critical section simultaneously—their value will be initially set to 1.
Such a semaphore can be held only by a single process or thread at any given time. A
semaphore used in this mode is sometimes called a mutex, which is, of course, an
abbreviation for “mutual exclusion.” Almost all semaphores found in the Linux kernel are used for mutual exclusion.

### Read/write Semophore
An rwsem allows either one writer or an unlimited number of readers to hold the
semaphore. Writers get priority; as soon as a writer tries to enter the critical section,
no readers will be allowed in until all writers have completed their work. This implementation can lead to reader starvation—where readers are denied access for a long
time—if you have a large number of writers contending for the semaphore. For this
reason, rwsems are best used when write access is required only rarely, and writer
access is held for short periods of time.

## Spinlock

Spinlocks are, by their nature, intended for use on multiprocessor systems, although
a uniprocessor workstation running a preemptive kernel behaves like SMP, as far as
concurrency is concerned. If a nonpreemptive uniprocessor system ever went into a
spin on a lock, it would spin forever; no other thread would ever be able to obtain
the CPU to release the lock. For this reason, spinlock operations on uniprocessor systems without preemption enabled are optimized to do nothing, with the exception of
the ones that change the IRQ masking status. Because of preemption, even if you
never expect your code to run on an SMP system, you still need to implement proper
locking.
