#include "building.h"


Building::~Building(){
    printf("Destroying The Plane\n");
    delete m_pDecl;
	wolf::BufferManager::DestroyBuffer(m_pVB);
}