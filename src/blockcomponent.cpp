#include "blockcomponent.h"
#include <madd.h>

ComponentType BlockComponent::cType = Madd::GetNewComponentType();
ComponentType BlockComponent::Type(){ return cType; }
