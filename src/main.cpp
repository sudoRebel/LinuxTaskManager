#include "process_manager.h"
#include <cctype>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <dirent.h>
#include <ios>
#include <iostream>
#include <limits>
#include <sys/types.h>
#include <unistd.h>

int main() {
  while (true) {
    system("clear");
    procList();
    int choice;
    std::cout << "Enter a choice (1: Refresh, 2: Kill Process, 3: Exit): ";

    if (!(std::cin >> choice)) {
      std::cout << "\nError: Invalid input. Please enter a number";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      usleep(3000000);
      continue;
    }

    if (choice == 1) {
      system("clear");
      continue;
    } else if (choice == 2) {
      int targetPid;
      std::cout << "Select process PID you want to kill: ";

      if (!(std::cin >> targetPid)) {
        std::cout << "\nError: Invalid. Please enter PID id";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        usleep(3000000);
        continue;
      }

      if (kill(targetPid, SIGKILL) == 0) {
        std::cout << "\nProcess killed";
        continue;
      } else {
        perror("\nError: can't kill the process");
        usleep(3000000);
        continue;
      }
    } else if (choice == 3) {
      break;
    } else {
      std::cout << "\nError: Invalid option. Please choose 1, 2, or 3.";
      usleep(3000000);
    }
  }

  return 0;
}
