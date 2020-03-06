#include "simplexcomponent.h"
#include <madd.h>

ComponentType SimplexComponent::cType = Madd::GetNewComponentType();
ComponentType SimplexComponent::Type(){ return cType; }
