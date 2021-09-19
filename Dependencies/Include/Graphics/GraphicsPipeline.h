#ifndef UMBRA2D_GRAPHICSPIPELINE_H
#define UMBRA2D_GRAPHICSPIPELINE_H

#include "Common.h"

namespace Umbra2D::Graphics {
    struct RenderNode {
        RenderPass* rp;
        int index = -1;
        RenderPass* fst = nullptr, *snd = nullptr;
        /* at first fst and snd are null
         * at runtime based on renderpasstype
         * the following pointers should be null
         * - void  - fst = snd = null
         * - FrBuf - snd = null
         * - Adder - fst != null && snd != null
        */
        void gui();
    };
    class GraphicsPipeline {
        std::vector<RenderNode*> renderNodes;
    public:
        // TODO should use ImNodes
        void gui();
        
    };
}

#endif //UMBRA2D_GRAPHICSPIPELINE_H
