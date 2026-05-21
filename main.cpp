#include <cctype>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>

void procList() {
  DIR *dir = opendir("/proc");

  if (dir == NULL) {
    perror("Could not open /proc");
    return;
  }

  struct dirent *entry;
  std::string pid, statusFilePath, word, VmRSS, procName;
  double kb, byt, mb, gb, tb, pb;

  while ((entry = readdir(dir)) != NULL) {
    if (isdigit(entry->d_name[0])) {
      pid = entry->d_name;
      statusFilePath = "/proc/" + pid + "/status";

      std::ifstream statusFile(statusFilePath);
      if (!statusFile.is_open())
        continue;

      VmRSS = "0";
      procName = "Unknown";

      while (statusFile >> word) {
        if (word == "Name:") {
          statusFile >> procName;
        } else if (word == "VmRSS:") {
          statusFile >> VmRSS;
          break;
        }
      }

      try {
        kb = stod(VmRSS);
      } catch (const std::invalid_argument &e) {
        kb = 0;
      }

      if (kb >= 1099511627776.0) {
        pb = kb / 1099511627776.0;
        std::cout << "PID: " << pid << " \t Name: " << procName
                  << " \t RAM: " << pb << " PB" << std::endl;
      } else if (kb >= 1073741824.0) {
        tb = kb / 1073741824.0;
        std::cout << "PID: " << pid << " \t Name: " << procName
                  << " \t RAM: " << tb << " TB" << std::endl;
      } else if (kb >= 1048576.0) {
        gb = kb / 1048576.0;
        std::cout << "PID: " << pid << " \t Name: " << procName
                  << " \t RAM: " << gb << " GB" << std::endl;
      } else if (kb >= 1024.0) {
        mb = kb / 1024.0;
        std::cout << "PID: " << pid << " \t Name: " << procName
                  << " \t RAM: " << mb << " MB" << std::endl;
      } else if (kb >= 1.0) {
        std::cout << "PID: " << pid << " \t Name: " << procName
                  << " \t RAM: " << kb << " kB" << std::endl;
      } else {
        byt = kb * 1024.0;
        std::cout << "PID: " << pid << " \t Name: " << procName
                  << " \t RAM: " << byt << " Byte" << std::endl;
      }

      statusFile.close();
    }
  }
  closedir(dir);
}

int main() {
  int choice, procK;
  while (true) {
    system("clear");
    procList();

    std::cout << "Enter a choice (1 Refresh,2 Kill process,3 Exit):";
    std::cin >> choice;

    if (choice == 1) {
      system("clear");
      continue;
    } else if (choice == 2) {
      std::cout << "Select process PID you want to kill: ";
      std::cin >> procK;
      if (kill(procK, SIGKILL) == 0) {
        std::cout << "Process killed" << std::endl;
      } else {
        perror("Error Killing the process!");
      }
    } else if (choice == 3) {
      break;
    }
  }
  return 0;
}
