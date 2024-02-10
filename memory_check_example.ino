#include "src/SecuredLinkedList.h"
#include <Arduino.h>

void dumpMemory(String label) {
  Serial.print("## "+label+" > ");
  // Get the free heap memory
  uint32_t freeHeap = ESP.getFreeHeap();
  // Get the total heap
  uint32_t totalHeap = ESP.getHeapSize();

  // Calculate the used memory (heap)
  uint32_t heapUsed = totalHeap - freeHeap;
  // Calculate the percentage of used memory
  float heapUsagePercent = ((float)heapUsed / totalHeap) * 100.0;

  // Print memory information
  Serial.print("Heap: ");
  Serial.print(heapUsed);
  Serial.print("/");
  Serial.print(totalHeap);
  Serial.print(" [");
  Serial.print(heapUsagePercent);
  Serial.print("%]\r\n");
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  Serial.println("_____________");
  
  dumpMemory("On startup.        ");

  SecuredLinkedList<int> list = SecuredLinkedList<int>();
  dumpMemory("After instantiation");

  // REMOVE
  Serial.println("# REMOVE");
  for(int i = 1; i <= 100; i++) {
    list.push(i);
  }
  dumpMemory("Before             ");
  for(int i = 1; i <= 100; i++) {
    list.remove(0);
  }
  dumpMemory("After              ");

  // POP
  Serial.println("# POP");
  for(int i = 1; i <= 100; i++) {
    list.push(i);
  }
  dumpMemory("Before             ");
  for(int i = 1; i <= 100; i++) {
    list.pop();
  }
  dumpMemory("After              ");

  // Shift
  Serial.println("# SHIFT");
  for(int i = 1; i <= 100; i++) {
    list.push(i);
  }
  dumpMemory("Before             ");
  for(int i = 1; i <= 100; i++) {
    list.shift();
  }
  dumpMemory("After              ");

  // CLEAR
  Serial.println("# CLEAR");
  for(int i = 1; i <= 100; i++) {
    list.push(i);
  }
  dumpMemory("Before             ");
  list.clear();
  dumpMemory("After              ");
}

void loop() {}