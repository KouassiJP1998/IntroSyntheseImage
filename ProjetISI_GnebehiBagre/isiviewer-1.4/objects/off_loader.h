#ifndef OFF_LOADER_H
#define OFF_LOADER_H

#include <iostream>
#include <ctime>
#include <fstream>
#include <string.h>
#include "triMesh.h"
#include <math.h>


class off_loader : public TriMesh {

public:
    off_loader(std::string cheminAcces);

};

#endif // OFF_LOADER_H
