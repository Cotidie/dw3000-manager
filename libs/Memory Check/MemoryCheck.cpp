#include "MemoryCheck.h"

void printFreeStack() {
  // Get the stack high water mark (minimum remaining stack) in words
  UBaseType_t stackHighWaterMark = uxTaskGetStackHighWaterMark(NULL); // NULL = current task

  // Convert to bytes (each word is 4 bytes on ESP32)
  uint32_t stackFreeBytes = stackHighWaterMark * sizeof(StackType_t);
  float stackFreeKB = (float) stackFreeBytes / 1024;
  Serial.print("Free stack for current task: ");
  Serial.print(stackFreeBytes/1000);
  Serial.println(" KB");
}

void printFreeHeap() {
  // Get current free heap size in bytes
  uint32_t freeHeap = ESP.getFreeHeap();
  float freeHeapKB = (float) freeHeap / 1024;

  // Print free heap size
  Serial.print("Free heap: ");
  Serial.print(freeHeapKB);
  Serial.println(" KB");
}