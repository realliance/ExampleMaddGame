#include "worldcomponent.h"
#include <madd.h>

ComponentType WorldComponent::cType = Madd::GetNewComponentType();
ComponentType WorldComponent::Type(){ return cType; }
