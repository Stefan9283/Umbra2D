#ifndef UMBRA2D_COMPONENTS_H
#define UMBRA2D_COMPONENTS_H

#include "Common.h"

namespace Umbra2D::Components {
    class Component {
        Entity *parentEntity;
        void setParent(Entity* e);
    };
}

#endif //UMBRA2D_COMPONENTS_H
