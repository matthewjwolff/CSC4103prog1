Chapter 1: Introduction
=======================

An Operating System is a program that manages a computer's hardware
** Figure 1.1** Different users use different programs on the same system. The Operating system coordinates the execution of these programs to ensure that each user can use the hardware fairly and efficiently.

1.1 What Operating Systems Do
-----------------------------

An computer system can be divided into four parts:
- Hardware (including CPU, Memory, IO devices)
- Operating System (Controls hardware)
- Application Programs (use resources to solve problems for users)
- Users

Viewpoints of a system

1.1.1 User view
_______________

Systems are made in various ways for the user
- Personal machine (optimized for ease of use and resource monopolization)
- Terminal connected to Mainframe or Minicomputer (optimized for resource sharing)
- Workstation connected to other workstations and servers (a compromise of the above)
- Mobile computers (touch screen and battery constraints)
- Embedded systems (little or no user view)

1.1.2 System View
_________________

Operating systems can operate as:
- Resource allocator (decides how resources are used and what user gets to use them when)
- Control program (manages execution of user programs to prevent errors and improper use of the computer)

1.1.3 Defining Operating Systems
________________________________

Moore's Law predicted that transistors would double every 18 months; this law shows the growing complexity of operating systems.
What of this complexity can be classified as the "operating system"?
- Simple viewpoint: everything a vendor ships (Windows, OSX non power-users)
- More accurate: the single program running at all times: the kernel (Linux)
- Often an *operating system* also includes the **system programs**: utilities useful to most application software
- Mobile OSs also include **middleware** which provide software frameworks to application developers (iOS, Android)

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
- Handles **interrupts** which signal the occurrence of an important event from hardware or software
- Exposes **system calls** to software for software to generate interrupts
- When the CPU finds an interrupt, it transfers control to a OS service determined by the **interrupt table**

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
