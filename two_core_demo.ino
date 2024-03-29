// Created by Steven Cybinski
// GitHub: https://github.com/StevenCyb/SecuredLinkedListNode

#include "src/SecuredLinkedList.h"

SecuredLinkedList<int> dataList = SecuredLinkedList<int>();

TaskHandle_t generatorTask;
TaskHandle_t destroyerTask;

void setup() {
  Serial.begin(115200);
  while(!Serial){}

  xTaskCreatePinnedToCore(  // Serial task definition on core 0
    generatorTaskRoutine,   //Task function
    "Generator",            //Name of task
    4000,                   //Stack size of task
    NULL,                   //Parameter of the task
    5,                      //Priority of task
    &generatorTask,         //ask handle to keep track of created task
    0                       //Pin task to core 1
  );
  xTaskCreatePinnedToCore(  // Broker task definition on core 1
    destroyerTaskRoutine,   //Task function
    "Destroyer",            //Name of task
    4000,                   //Stack size of task
    NULL,                   //Parameter of the task
    5,                      //Priority of task
    &destroyerTask,         //ask handle to keep track of created task
    1                       //Pin task to core 1
  );
}

void generatorTaskRoutine( void * pvParameters ){
  Serial.println("Generator running on core " + String(xPortGetCoreID()));
  while(true) {
    if(dataList.size() > 0) {
      Serial.println("Pop: " + String(dataList.pop()));
    }
    delay(10);
    yield();
  }
}

void destroyerTaskRoutine( void * pvParameters ){
  Serial.println("Destroyer running on core " + String(xPortGetCoreID()));
  unsigned int counter = 0;
  while(true) {
    Serial.println("Unshift: " + String(counter));
    dataList.unshift(counter);
    counter += 1;
    delay(10);
    yield();
  }
}

void loop() {}

// OUTPUT
/*
  ⸮ ⸮          ⸮ ⸮  ⸮ ⸮
Generator running on core 0
Destroyer running on core 1
Unshift: 0
Pop: 0
Unshift: 1
Pop: 1
Unshift: 2
Pop: 2
Unshift: 3
Pop: 3
Unshift: 4
Pop: 4
Unshift: 5
Pop: 5
Unshift: 6
Pop: 6
Unshift: 7
Pop: 7
Unshift: 8
Pop: 8
Unshift: 9
Pop: 9
Unshift: 10
Pop: 10
...
*/
