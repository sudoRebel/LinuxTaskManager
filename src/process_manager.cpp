#include "process_manager.h"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <dirent.h>
#include <fstream>
#include <iomanip>
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

  while ((entry = readdir(dir)) != NULL) {
    double kiloByte;

    if (isdigit(entry->d_name[0])) {
      std::string pid = entry->d_name;
      std::string statusFilePath = "/proc/" + pid + "/status";

      std::ifstream statusFile(statusFilePath);

      if (!statusFile.is_open()) {
        continue;
      }

      std::string vmRss = "0";
      std::string procName = "Unknown";
      std::string line;

      while (getline(statusFile, line)) {
        size_t charIndexForName = line.find("Name:");

        if (charIndexForName != std::string::npos) {
          std::string rawName = line.substr(charIndexForName + 5);
          size_t firstChar = rawName.find_first_not_of(" \t\r\n");
          size_t lastChar = rawName.find_last_not_of(" \t\r\n");

          if (firstChar != std::string::npos && lastChar != std::string::npos) {
            procName = rawName.substr(firstChar, lastChar - (firstChar - 1));
          }
        }

        size_t charIndexForVmRSS = line.find("VmRSS:");

        if (charIndexForVmRSS != std::string::npos) {
          std::string rawName = line.substr(charIndexForVmRSS + 6);
          size_t firstChar = rawName.find_first_not_of(" \t\r\n");
          size_t lastChar = rawName.find_last_not_of(" \t\r\n");

          if (firstChar != std::string::npos && lastChar != std::string::npos) {
            vmRss = rawName.substr(firstChar, lastChar - (firstChar - 1));
          }
        }
      }
      statusFile.close();

      try {
        kiloByte = stod(vmRss);
      } catch (const std::invalid_argument &e) {
        kiloByte = 0;
      }

      std::cout << std::left << "PID: " << std::setw(10) << pid
                << " Name: " << std::setw(35) << procName << " RAM: ";

      if (kiloByte >= 1099511627776.0) {
        double petaByte = kiloByte / 1099511627776.0;
        std::cout << petaByte << " PB\n";
      } else if (kiloByte >= 1073741824.0) {
        double teraByte = kiloByte / 1073741824.0;
        std::cout << teraByte << " TB\n";
      } else if (kiloByte >= 1048576.0) {
        double gigaByte = kiloByte / 1048576.0;
        std::cout << gigaByte << " GB\n";
      } else if (kiloByte >= 1024.0) {
        double megaByte = kiloByte / 1024.0;
        std::cout << megaByte << " MB\n";
      } else if (kiloByte >= 1.0) {
        std::cout << kiloByte << " kB\n";
      } else {
        double bytes = kiloByte * 1024.0;
        std::cout << bytes << " Byte\n";
      }
    }
  }
  closedir(dir);
}
