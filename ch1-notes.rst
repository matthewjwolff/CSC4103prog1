Chapter 1: Introduction
=======================

An Operating System is a program that manages a computer's hardware

**Figure 1.1** Different users use different programs on the same system. The Operating system coordinates the execution of these programs to ensure that each user can use the hardware fairly and efficiently.

1.1 What Operating Systems Do
-----------------------------

An computer system can be divided into four parts

* Hardware (including CPU, Memory, IO devices)
* Operating System (Controls hardware)
* Application Programs (use resources to solve problems for users)
* Users

1.1.1 User view
_______________

Systems are made in various ways for the user

* Personal machine (optimized for ease of use and resource monopolization)
* Terminal connected to Mainframe or Minicomputer (optimized for resource sharing)
* Workstation connected to other workstations and servers (a compromise of the above)
* Mobile computers (touch screen and battery constraints)
* Embedded systems (little or no user view)

1.1.2 System View
_________________

Operating systems can operate as:

* Resource allocator (decides how resources are used and what user gets to use them when)
* Control program (manages execution of user programs to prevent errors and improper use of the computer)

1.1.3 Defining Operating Systems
________________________________

Moore's Law predicted that transistors would double every 18 months; this law shows the growing complexity of operating systems.
What of this complexity can be classified as the "operating system"?

* Simple viewpoint: everything a vendor ships (Windows, OSX non power-users)
* More accurate: the single program running at all times: the kernel (Linux)
* Often an *operating system* also includes the **system programs**: utilities useful to most application software
* Mobile OSs also include **middleware** which provide software frameworks to application developers (iOS, Android)

1.2 Computer-System Organization
--------------------------------

The structure of a system

1.2.1 Computer-System Operation
_______________________________

**Figure 1.2:** Computers contain many devices connected together by buses

How a computer boots

1) **Bootstrap Program** Stored in **ROM** **EEPROM** (**firmware**): Initializes devices and finds **bootloader** in predetermined place on disk (in the MBR or EFI Partition)
2) **Bootloader** Boots the operating system (some allow users to choose from installed OSs), decompresses chosen kernel and loads it.
3) Kernel then loads **system processes** and **system daemons** that provide basic operating system functionality.

Now that the Operating System has booted, what does it do?

* Handles **interrupts** which signal the occurrence of an important event from hardware or software
* Exposes **system calls** to software for software to generate interrupts
* When the CPU finds an interrupt, it transfers control to a OS service determined by the **interrupt table**

**Figure 1.3** When a user requests a file to be written, the I/O device begins writing. Upon completion, the I/O device triggers an interrupt, which causes the CPU to trigger the event handler for that event. Then the CPU returns control to the user's process.

1.2.2. Storage Structure
_______________________

Computer storage is organized by speed, capacity and expense. For instance, memory is very fast, but expensive to make and a few GB large. Your hard disk is possibly TB large, but is very slow.

**Figure 1.4** Registers are the smallest form of memory, and are bytes large and built into the processor. Each level thereafter is slightly slower, larger, further away from the processor, and less expensive. The lower levels are used for persistent **secondary storage** while higher levels contain information currently in use.

Main memory and above are **volatile**: they lose their contents when unpowered. Main memory and above can also contain active processes.

1.2.3. I/O Structure
____________________

A device controller provides access to a physical device connected to a system.

A **device driver** allows the operating system to communicate with the device controller and therefore operate the device

**Direct Memory Access** allows memory (normally controlled by a device controller that must be interacted by the CPU) to directly write without instruction from the CPU. This reduces interrupts and improves performance.

1.3 Computer-System Architecture
--------------------------------

**Figure 1.5** A CPU communicates with many devices (including memory for loading/storing instructions/data). DMA allows other devices to directly access memory without interaction from the CPU

1.3.1 Single Processor Systems
______________________________

Most systems contain a single main processor that contains a general-purpose instruction set. Devices can also have sub-processors that handles their own specific tasks (like storage scheduling and keystroke code generation)

1.3.2 Multiprocessor Systems
____________________________

Other systems contain multiple discrete processors. They are cost efficient (sharing resources), reliable (fault tolerant), and more powerful (more throughput).
The processors will share memory, and possibly the same physical die (a **multicore system** with a shared L2 cache)

**Figure 1.6** 3 CPUS in a multiprocessing setup share the same memory

**Figure 1.7** A single CPU with 2 logical CPU cores have discrete L1 cache, a shared L2 cache (not shown), and shared memory

1.3.3. Clustered Systems
________________________

Much like multiple processors can be combined to form one machine, multiple systems can be combined to create a **clustered system**.
Each **node** (individual computer) of the cluster is connected and they work in parallel.

**Figure 1.8** 3 nodes (computers) are connected and share a data store

1.4 Operating-System Structure
------------------------------

Users never use one program exclusively, many processes run at once for a user to use a machine.

**Multiprogramming** describes the strategy of process layout in memory and CPU usage among multiple jobs in a **job pool**

**Time sharing** allows the CPU to switch among the jobs to let them all have a turn getting executed

A **process** is a program loaded into memory and executing. The need to run the process creates a job, the OS must choose in what order to load the jobs created by users. This is **job scheduling**
When jobs are chosen to be loaded, they will wait to be executed. The OS must use **CPU scheduling** to decide when a job gets executed

1.5 Operating-System Operations
------------------------------

Operating systems provide a layer of safety between untrusted user programs and the system. Interrupts and traps are used to handle errors and corral bad behavior to the offending process

1.5.1 Dual-Mode and Multimode operation
_______________________________________

The **mode bit** is added to hardware to distinguish between to modes of operation:

1) **User mode** contains the process running and using system calls to trigger functionality in the kernel
2) **Kernel mode** has direct access to hardware and executes system calls from the user process

**Privileged instructions** are only handled by kernel mode operations, shielded by safe and predictable system calls. Only those system calls are exposed to user-mode processes

1.5.2 Timer
___________

Regularly timed interrupts generated by a **timer** (combination of hardware clock and software parameters) add additional security functions.
For example, an operating system can choose to respond to a timer interrupt by terminating a program that is taking too long or is unresponsive.

1.6 Process Management
----------------------

A program is a passive entity, stored on disk. A process is active. It has a **program counter** that points to the next instruction to executes. Systems consider processes the main unit of work. A program can have multiple processes.
A system has to manage processes by scheduling them, creating and deleting them, synchronizing them, communication between them, and suspending and resuming them.

1.7 Memory Management
---------------------

Programs need memory to operate, and must know how to address their memory. Many processes must be executed at once, so giving exclusive access to a process is not an option.
Virtual memory allows the operating system to map parts of memory to certain programs, move unused parts of processes to disk, and make programs believe that they have complete access to memory.

1.8 Storage Management
----------------------

Filesystems were developed to organize the large amount of secondary storage available. The single unit of data is called a **file**.

1.8.1 File-System Management
____________________________

The operating system is responsible for

* Creating and deleting files
* Creating and deleting directories to organize files
* Supporting primitives for manipulating files and directories
* Mapping files onto secondary storage
* Backing up files on stable (nonvolatile) storage media

1.8.2 Mass-Storage Management
_____________________________

The Operating System must also manage the storage devices themselves with

* Free-space management
* Storage allocation
* Disk scheduling

1.8.3 Caching
_____________

When a part of slower storage is used many times, an operating system can utilize **caching** and move those parts of storage to faster storage to improve performance.
This faster storage is smaller, so **cache management** must be used to determine how the more valuable cach space is used

**Figure 1.11** A comparison of various storage media shows how much performance can be gained with caching. Each column can be interpreted as a cache for the column to its right.
**Figure 1.12** As an integer is used more, it is progressively moved from magnetic disk (hard drive) to a register in hardware

When multiple copies of data are made with a caching system, **cache coherency** must be maintained so that a value is kept consistent. This becomes even more important in a multiprocessor system where multiple copies of data might be operated upon simultaneously.

1.8.4 I/O Systems
_________________

The buffer between hardware and user created by an Operating System can also be used to standardize the way a program interacts with hardware.
An **I/O subsytem** accomplishes this task by

* A memory-management component that includes buffering, caching, and
spooling
* A general device-driver interface
* Drivers for specific hardware devices

1.9 Protection and Security
---------------------------

An operating system must regulate access to data to protect processes from stealing information from other processes.
UNIX uses **user identifiers** and **group identifiers** to protect data. Processes started by a user contain that user's id. Processes and files can belong to sets of users with groups.
**Escalating privileges** allows a user to gain extra permissions temporarily.

1.10 Kernel Data Structures
---------------------------

An kernel has various ways of manipulating data

1.10.1 Lists, Stacks, and Queues
________________________________

Arrays are limited by a fixed size and a fixed element size. A **list** allows more freedom by using pointers instead of memory proximity.

**Figure 1.13** A singly linked list contains the data and an additional pointer to the next item in the list. The last item points to NULL.

**Figure 1.14** A doubly linked list contains the data and two pointers, one to the previous item and one to the next item. The first item's previous pointer points to NULL; the last item's next pointer points to NULL.

**Figure 1.15** A circularly linked list contains the data and a pointer to the next item. The last item contains a pointer to the first item.

These lists can be specialized based on their intended access order. A **stack** follows Last-In-First-Out (LIFO), the last item pushed in is the first item to leave the stack.
A **queue** follows First-In-First-Out (FIFO) where items leave the queue in the order they entered.

1.10.2 Trees
____________

Trees represent a hierarchy of data. By mandating certain properties onto a tree, common tasks can be improved drastically.

A **binary tree** mandates that each node have no more than two children. A **binary search tree** creates an order to the children and speeds up searching quadradicly.
A **balanced binary search tree** organizes child placement to restrict the height of the tree. Searching speeds up logarithmically.

**Figure 1.16** A binary search tree.

1.10.3 Hash Functions and maps
______________________________

A **hash function** maps data to an index in a hash table. Searching for an item in a hash table is extremely fast when one knows or can construct the key for the desired item.
A **hash map** is such a mapping

**Figure 1.17 A hash map takes a key, turns it into the index of the hash table, and then indexes that table to find the value.

1.10.4 Bitmaps
______________

A **bitmap** uses a string of *n* bits to represent *n* binary states, efficiently storing the state of those n items in a small space.

1.11 Computing Environments
---------------------------

1.11.1 Traditional Computing
____________________________

In earlier times, computers were limited and timesharing was employed to share the resources among many people.

The trend is now pushing to **portals** that expose a company subnet to the internet.
Home users have a similar portal setup called a **firewall**.

1.11.2 Mobile Computing
_______________________

Smaller form factor computers like **iOS** and **Android** provide a portable computing interface

1.11.3 Distributed Systems
__________________________

Computers can be connected together to form a **network**, and these networks can exchange resources.

1.11.4 Client-Server Computing
______________________________

A **server system** executes requests made by **client systems** to form a **client-server system**.
For example, a client may request a server to deliver email to the client.

**Figure 1.18** Various client systems communicate with a server through the network and submit requests to it.

1.11.5 Peer-To-Peer Computing
_____________________________

A peer to peer system allows computers to request and deliver upon services requested by other peers in the network.
This allows direct connection to peer computers without a server in the middle.

**Figure 1.19** A peer to peer network has no server. Each 'client' is connected to every other 'client' and they communicate directly.

1.11.6 Virtualization
_____________________

**Emulation** is performed by a program that executes in software the instruction set of a different hardware machine.
A program uses **interpretation** to execute a higher-level language at runtime. The code of the high-level language can be though of as executing inside a system created by the interpreting program.
**Virtualization** creates an Operating System within an Operating System that then executes native code separate from the host Operating System.

**Figure 1.20** The host machine on the left contains within the kernel functionality for virtualization. Inside the host machine are 3 virtual machines with their own processes and kernel.

1.11.7 Cloud Computing
______________________

**Cloud computing** is a type of computing that delivers computing, storage, and even applications as a service across a network.

**Figure 1.21** Requests for services are received from the internet, distributed among the cloud network, and the results are sent back over the internet to whatever client requested it.

1.11.8 Real-Time Embedded Systems
_________________________________

A **real time operating system** prioritizes the execution of code in real time and has strict time requirements for that execution.
This has implications on the scheduling concepts discussed earlier.

1.12 Open Source Operating Systems
----------------------------------

An **open source operating system** is an operating system whose source is publically available for viewing.
In contrast, Windows and OSX and **closed source** and are only distributed in compiled binary forms.

1.12.1 History
______________

As storage became cheap enough to distribute compiled executables, companies began charging for access to the executables, and closed their source so that no binaries could be generated except from them.
Richard Stallman created the GNU project to counter the closing of source code and formed the **Free Software Foundation** to do so.
One of the goals of FSF was to maintain the open nature of source code for transparency, user freedom, and education.
The FSF established "copyleft", which mandates those freedoms in a similar fashion as copyright mandates that no copies be made.
The **GNU General Public License** is such a license.

1.12.2 Linux
____________

The FSF was creating the free GNU operating system, and did not have a kernel ready for it.
Linus Torvalds wrote the Linux kernel at that time, and the GNU utility programs were combined with the Linux kernel to make the **GNU/Linux** operating system.

1.12.3 BSD UNIX
_______________

Just as the FSF was creating the GNU operating system, UC Berkeley was creating a UNIX like system called **BSD UNIX**.
Mac OSX is a descendent of BSD UNIX.

1.12.4 Solaris
______________

Sun Microsystems also made a UNIX like system called **Solaris**

1.12.5 Open-Source Systems as Learning Tools
____________________________________________

Free Software's open source creates the possibility for the study of their source code.

1.13 Summary
------------
An operating system manages hardware and provides an environment for applications to run.
The operating system has a kernel, which is the program that manages the hardware and exposes it to user programs.
Memory is organized by the operating system based on its physical configuration, with smaller, faster memory having precedence but storing more volatile information.
Operating Systems coordinate between many processes.
