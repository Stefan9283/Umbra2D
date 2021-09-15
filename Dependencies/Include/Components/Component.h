#ifndef UMBRA2D_COMPONENTS_H
#define UMBRA2D_COMPONENTS_H

#include "Common.h"

namespace Umbra2D::Components {
    class Component {
        Entity *parentEntity = nullptr;
    public:
        void setParent(Entity* e);
        Entity* getParent();
        virtual void gui()  = 0;
    };
}

#endif //UMBRA2D_COMPONENTS_H
