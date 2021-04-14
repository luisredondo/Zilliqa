#include "MemoryStats.h"
#include "libUtils/Logger.h"
#include "sys/types.h"
#include "sys/sysinfo.h"

int parseLine(char* line) {
  // This assumes that a digit will be found and the line ends in " Kb".
  int i = strlen(line);
  const char* p = line;
  while (*p < '0' || *p > '9') p++;
  line[i - 3] = '\0';
  i = atoi(p);
  return i;
}

int GetProcessPhysicalMemoryStats() {  // Note: this value is in KB!
  FILE* file = fopen("/proc/self/status", "r");
  int result = -1;
  char line[128];

  while (fgets(line, 128, file) != NULL) {
    if (strncmp(line, "VmRSS:", 6) == 0) {
      result = parseLine(line);
      break;
    }
  }
  fclose(file);
  return result;
}

int GetProcessVirtualMemoryStats() {  // Note: this value is in KB!
  FILE* file = fopen("/proc/self/status", "r");
  int result = -1;
  char line[128];

  while (fgets(line, 128, file) != NULL) {
    if (strncmp(line, "VmSize:", 7) == 0) {
      result = parseLine(line);
      break;
    }
  }
  fclose(file);
  return result;
}

void DisplayVirtualMemoryStats() {
  struct sysinfo memInfo;
  sysinfo(&memInfo);
  long long totalVirtualMem = memInfo.totalram;
  // Add other values in next statement to avoid int overflow on right hand
  // side...
  totalVirtualMem += memInfo.totalswap;
  totalVirtualMem *= memInfo.mem_unit;
  long long virtualMemUsed = memInfo.totalram - memInfo.freeram;
  // Add other values in next statement to avoid int overflow on right hand
  // side...
  virtualMemUsed += memInfo.totalswap - memInfo.freeswap;
  virtualMemUsed *= memInfo.mem_unit;
  int processVirtualMemUsed = GetProcessVirtualMemoryStats(); 
  LOG_GENERAL(INFO,"Total virtual memory = "<<totalVirtualMem <<" bytes");
  LOG_GENERAL(INFO,"Total virtual memory used = "<<virtualMemUsed<<" bytes");
  LOG_GENERAL(INFO,"Total virtual memory used by process = "<<processVirtualMemUsed<<" kb's");
}

void DisplayPhysicalMemoryStats() {
  struct sysinfo memInfo;
  sysinfo(&memInfo);
  long long totalPhysMem = memInfo.totalram;
  // Multiply in next statement to avoid int overflow on right hand side...
  totalPhysMem *= memInfo.mem_unit;
  long long physMemUsed = memInfo.totalram - memInfo.freeram;
  // Multiply in next statement to avoid int overflow on right hand side...
  physMemUsed *= memInfo.mem_unit;
  int processPhysMemUsed = GetProcessPhysicalMemoryStats();
  LOG_GENERAL(INFO, "Total physical memory = " << totalPhysMem<<" bytes");
  LOG_GENERAL(INFO, "Total physical memory used = " << physMemUsed<<" bytes");
  LOG_GENERAL(
      INFO, "Total physical  memory used by process = " << processPhysMemUsed<<" kb's");
}