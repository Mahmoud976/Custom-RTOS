# Custom RTOS Kernel for ARM Cortex-M3

A lightweight Real-Time Operating System (RTOS) developed from scratch for ARM Cortex-M3.

This project demonstrates the internal concepts of RTOS design including:

* Task Management
* Context Switching
* Priority Scheduling
* Round Robin Scheduling
* Task Waiting / Delay
* Mutex Synchronization
* FIFO Communication

---

# Project Architecture

```mermaid
graph TD

APP[Application Examples]

KERNEL[MY_RTOS Kernel]

SCHED[Scheduler]
TASK[Task Management]
MUTEX[Mutex]
FIFO[FIFO Queue]

PORT[Cortex-M3 Port Layer]

MCAL[MCAL Drivers]

HW[STM32 Hardware]

APP --> KERNEL

KERNEL --> SCHED
KERNEL --> TASK
KERNEL --> MUTEX
KERNEL --> FIFO

KERNEL --> PORT
PORT --> MCAL
MCAL --> HW
```

---

# Kernel Features

## Task Management

The RTOS supports creating multiple tasks with:

* Independent stack
* Priority level
* Task state management
* Scheduler integration

Task Flow:

```mermaid
stateDiagram-v2

[*] --> Suspend

Suspend --> Ready: Activate Task

Ready --> Running: Scheduler Select

Running --> Suspend: Terminate

Running --> Waiting: Delay / Mutex

Waiting --> Ready: Event Complete
```

---

# Context Switching

The RTOS uses ARM Cortex-M exception mechanisms:

* PendSV for context switching
* SVC for kernel services
* PSP for task stack handling

Context Switching:

```mermaid
sequenceDiagram

CPU->>PendSV: Trigger Switch

PendSV->>Task: Save Context

PendSV->>Scheduler: Select Next Task

Scheduler->>PendSV: New Task

PendSV->>CPU: Restore Context
```

---

# Examples

All RTOS features are tested through separated examples.

```
Examples

├── Priority Example
├── Priority Preemption Example
├── RoundRobin Example
├── TaskWaiting Example
├── Mutex Example
└── FIFO Example
```

---

# Priority Example

Demonstrates basic priority based scheduling.

Higher priority tasks are selected first.

Example:

```
Priority 1  -> Low Task
Priority 3  -> Medium Task
Priority 5  -> High Task
```

Scheduler selects the smallest priority value first according to the kernel implementation.

---

# Priority Preemption Example

Demonstrates preemption when a higher priority task becomes ready.

Flow:

```mermaid
sequenceDiagram

Low Priority Task->>Scheduler: Running

High Priority Task->>Scheduler: Activated

Scheduler->>Low Priority Task: Preempt

Scheduler->>High Priority Task: Execute
```

---

# Round Robin Example

Demonstrates CPU sharing between tasks having the same priority.

Example:

```
Task A
Task B
Task C


Execution:

A -> B -> C -> A -> B -> C
```

---

# Task Waiting Example

Uses:

```c
MY_RTOS_Task_Wait()
```

Allows tasks to sleep for a specific number of OS ticks.

Flow:

```mermaid
flowchart LR

Task --> Delay
Delay --> Waiting
Waiting --> SysTick
SysTick --> Ready
Ready --> Scheduler
```

---

# Mutex Example

Demonstrates resource protection between multiple tasks.

Used to prevent multiple tasks accessing the same resource simultaneously.

Mutex Flow:

```mermaid
flowchart TD

Task --> Acquire_Mutex

Acquire_Mutex --> Critical_Section

Critical_Section --> Release_Mutex

Release_Mutex --> Next_Task
```

---

# FIFO Example

Standalone FIFO driver implementation.

Features:

* Enqueue
* Dequeue
* Full detection
* Empty detection
* Circular buffer handling

Structure:

```
+----+----+----+----+
|    |    |    |    |
+----+----+----+----+

 ^
 Head

 ^
 Tail
```

---

# Project Structure

```
STM32

├── Kernel
│
│   ├── Src
│   │   ├── scheduler.c
│   │   └── RTOS_FIFO.c
│   │
│   └── inc
│       ├── scheduler.h
│       └── RTOS_FIFO.h
│

├── Port
│   ├── CortexMx_OS_Porting.c
│   └── CortexMx_OS_Porting.h
│

├── MCAL
│   ├── GPIO Driver
│   └── Interrupt Driver
│

├── Examples
│   ├── Priority Example
│   ├── Priority Preemption Example
│   ├── RoundRobin Example
│   ├── TaskWaiting Example
│   ├── Mutex Example
│   └── FIFO Example
│

└── main.c
```

---

# Hardware

Target MCU:

* STM32F103C6
* ARM Cortex-M3

Development Tools:

* STM32CubeIDE
* GNU Arm Embedded Toolchain

---

# Future Improvements

Planned features:

* Priority Inheritance for Mutex
* Message Queue
* Event Flags
* Dynamic Memory Management
* Support for more Cortex-M devices

---

# Author

Mahmoud Saleh

Embedded Systems Engineer
