#include "qtctrlcollection.h"

#include "SDL/ctrlcollection.h"

QtCtrlCollection::QtCtrlCollection(){
}

QtCtrlCollection::QtCtrlCollection(int num_mappings)
{
    this->actual = new QtSDLCtrlCollection(num_mappings);
}


int QtCtrlCollection::numGamepads(){
    return this->actual->numGamepads();
}
