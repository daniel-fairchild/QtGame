#include "qtctrlcollection.h"

#include "SDL/ctrlcollection.h"

QtCtrlCollection *QtCtrlCollection::factory(int num_mappings)
{
    return new QtSDLCtrlCollection(num_mappings);
}

QtCtrlCollection::QtCtrlCollection(){
}
