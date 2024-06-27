#include "framework/Object.h"
#include "framework/Core.h"

namespace ly{
unsigned int Object::uniqueIDCounter = 0;
Object::Object()
  :mIsPendingDestory{false},
    mUniqueID{ GetNextAvaliableID() } {

}

Object::~Object(){
  LOG("Object Destoryred");
}

void Object::Destory(){
    onDestory.Broadcast(this);
  mIsPendingDestory = true;
}

weak<Object> Object::GetWeakRef()
{
    return weak_from_this();
}

weak<const Object> Object::GetWeakRef() const
{
    return weak_from_this();
}

unsigned int Object::GetNextAvaliableID() {
    return uniqueIDCounter++;
 }

}
