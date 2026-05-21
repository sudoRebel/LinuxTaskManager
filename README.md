# 🖥️ Linux Task Manager (CLI)

A lightweight, interactive, high-performance Linux Command-Line Task Manager written in standard C++. It interacts directly with the Linux Kernel via the `/proc` pseudo-filesystem to monitor active processes and manage them using POSIX system signals.

---

# ✨ Features
* **Zero-Dependency**: Standard C++ library only.
* **Kernel Direct-Access**: Reads directly from the `/proc` filesystem.
* **PID Mapping**: Identifies active processes.
* **Interactive CLI Interface**: Real-time process monitoring with custom action loops (Refresh/Exit).
* **Process Management**: Send kernel signals (`SIGKILL`) to terminate any task instantly via PID.
* **Smart Memory Auto-Scaling**: Displays memory consumption dynamically in Bytes, kB, MB, GB, TB, or PB based on real usage.
* **Crash Resilience**: Built-in exception handling to survive dynamic kernel thread shifts.

# 💡 How it works
1. **Discovery**: Scans the `/proc` directory for PID-named folders using `dirent.h`.
2. **Filtering**: Uses `isdigit()` to isolate system processes.
3. **Extraction**: Parses `/proc/[PID]/status` to retrieve the process name and RAM usage (`VmRSS`).
4. **Interactivity**: Captures user input to safely dispatch POSIX signals or trigger dynamic terminal redraws using `system("clear")`.

# 🖥️ UI Preview
When you run the application, you will interact with a clean terminal layout:

+---------------------Terminal---------------------+
| ---------- Linux Task Manager ----------         |
| PID: 1       Name: systemd        RAM: 12.4 MB   |
| PID: 532     Name: Xorg           RAM: 145.2 MB  |
| PID: 2134    Name: g++            RAM: 45.8 MB   |
|                                                  |
| Enter a choice (1 Refresh, 2 Kill process, 3 Exit):|
+--------------------------------------------------+

# 🐧 System Requirements
* **OS**: Linux-based operating systems (Tested on Arch Linux).
* **Compiler**: GCC/G++ or Clang with C++11 support or higher.

# 🛠️ Installation & Run Guide
```bash
# Clone the repository
git clone https://github.com/sudoRebel/LinuxTaskManager

# Compile with G++
g++ -o TaskManager main.cpp

# Run the app
./LinuxTaskManager
