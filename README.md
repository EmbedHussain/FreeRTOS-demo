# Simple FreeRTOS CMake Project (Linux)

## Overview
Minimal FreeRTOS example using POSIX port.

### Concepts
- Semaphore (ISR → Task)
- Queue (Task → Task)
- Mutex (resource protection)

---

## Build & Run

```bash
sudo apt install build-essential cmake git

mkdir build
cd build
cmake ..
make
./demo
```

---

## Flow
ISR → Sensor → Control → Communication

---

## Interview Explanation
"A simulated interrupt gives a semaphore to a task. That task reads data and sends via queue. Another task processes and outputs result."
