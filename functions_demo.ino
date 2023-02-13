// Created by Steven Cybinski
// GitHub: https://github.com/StevenCyb/SecuredLinkedListNode

#include "src/SecuredLinkedList.h"

SecuredLinkedList<String> stringList = SecuredLinkedList<String>();
SecuredLinkedList<int> *intList = new SecuredLinkedList<int>();

void setup() {
  Serial.begin(115200);
  while(!Serial){}

  for(int i = 2; i <= 5; i++) {
    stringList.push("Test" + String(i));
    intList->push(i);
  }
  // stringList = ["Test2", "Test3", "Test4", "Test5"]
  // stringList = [2, 3, 4, 5]

  Serial.println(stringList.size()); // -> 4
  Serial.println(intList->size());   // -> 4
  // stringList = ["Test2", "Test3", "Test4", "Test5"]
  // stringList = [2, 3, 4, 5]

  stringList.unshift("Test1");
  intList->unshift(1);
  // stringList = ["Test1", "Test2", "Test3", "Test4", "Test5"]
  // stringList = [1, 2, 3, 4, 5]

  Serial.println(stringList.shift()); // -> Test1
  Serial.println(intList->shift());   // -> 1
  // stringList = ["Test2", "Test3", "Test4", "Test5"]
  // stringList = [2, 3, 4, 5]

  Serial.println(stringList.pop()); // -> Test5
  Serial.println(intList->pop());   // -> 5
  // stringList = ["Test2", "Test3", "Test4"]
  // stringList = [2, 3, 4]

  stringList.add(0, "Test1");
  intList->add(0, 1);
  stringList.add(2, "Middle");
  intList->add(2, -5);
  // stringList = ["Test1", "Test2", "Middle", "Test3", "Test4"]
  // stringList = [1, 2, -5, 3, 4]

  int size = stringList.size();
  for(int i = 0; i < size; i++) {
    Serial.println(String(i) + " = " + stringList.get(i));
  }
  //  OUTPUT
  /*
  0 = Test1
  1 = Test2
  2 = Middle
  3 = Test3
  4 = Test4
  */
  // stringList = ["Test1", "Test2", "Middle", "Test3", "Test4"]
  
  size = intList->size();
  for(int i = 0; i < size; i++) {
    Serial.println(String(i) + " = " + intList->get(i));
  }
  //  OUTPUT
  /*
  0 = 1
  1 = 2
  2 = -5
  3 = 3
  4 = 4
  */
  // stringList = [1, 2, -5, 3, 4]
  
  intList->remove(0);
  intList->remove(3);
  intList->remove(1);
  size = intList->size();
  for(int i = 0; i < size; i++) {
    Serial.println(String(i) + " = " + intList->get(i));
  }
  //  OUTPUT
  /*
  0 = 2
  1 = 3
  */
  // stringList = [2, 3]
  
  stringList.remove(0);
  stringList.remove(3);
  stringList.remove(1);
  size = stringList.size();
  for(int i = 0; i < size; i++) {
    Serial.println(String(i) + " = " + stringList.get(i));
  }
  //  OUTPUT
  /*
  0 = Test2
  1 = Test3
  */
  // stringList = ["Test2", "Test3"]

  stringList.clear();
  intList->clear();
  Serial.println(stringList.size());  // -> 0
  Serial.println(intList->size());    // -> 0
  // stringList = []
  // stringList = []
}

void loop() {}
