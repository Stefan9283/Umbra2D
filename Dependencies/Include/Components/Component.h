#include "Common.h"

#ifndef UMBRA2D_COMPONENTS_H
#define UMBRA2D_COMPONENTS_H

namespace Umbra2D::Components {
    class Component {
        Entity *parentEntity;
        void setParent(Entity* e);
    };
}

#endif //UMBRA2D_COMPONENTS_H
