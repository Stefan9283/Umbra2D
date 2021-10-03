#ifndef UMBRA2D_GRAPHICSPIPELINE_H
#define UMBRA2D_GRAPHICSPIPELINE_H

#include "Common.h"

namespace Umbra2D::Graphics {
    struct RenderNode {
        RenderPass* rp; // attrib 0
        RenderPass* fst = nullptr, // attrib 1
                    *snd = nullptr; // attrib 2
        /* at first fst and snd are null
         * at runtime based on renderpasstype
         * the following pointers should be null
         * - void  - fst = snd = null
         * - Filter - snd = null
         * - Adder - fst != null && snd != null
        */
        RenderNode(RenderPass* rp);
        void gui(int index) const;
    };
    class GraphicsPipeline {
        std::vector<RenderNode*> renderNodes;
        std::vector<glm::ivec2> links;
    public:
        ~GraphicsPipeline();
        void gui();
        void addRenderPass(RenderPass* rp);
        void linkRenderPasses(int fromNode, int toNode, int inputAttrib);
        int getAttribID(int node, int attrib);
        FrameBuffer* getDrawnFrameBuffer(Umbra2D::Components::Camera* cam, Scene* s);
    };
}

#endif //UMBRA2D_GRAPHICSPIPELINE_H

