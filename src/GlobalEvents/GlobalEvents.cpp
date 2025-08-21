#include "GlobalEvents.h"

GlobalEvent::GlobalEvent(){}
GlobalEvent::~GlobalEvent(){}

EventPool::EventPool(){}

EventPool::~EventPool(){
    for ( GlobalEvent * item : event_vector ){
        if (item != nullptr){
            delete item;
            item = nullptr;
        }
    }
}


