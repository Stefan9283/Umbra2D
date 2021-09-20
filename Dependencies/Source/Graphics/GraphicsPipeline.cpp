#include "Graphics/GraphicsPipeline.h"
#include "Graphics/RenderPass.h"

namespace Umbra2D::Graphics {
    // TODO should use ImNodes
    void RenderNode::gui(int index) const {
        ImNodes::BeginNode(index);
        ImNodes::PushAttributeFlag(ImNodesAttributeFlags_EnableLinkDetachWithDragClick);
        ImGui::PushID(index);
        rp->gui();
        switch (rp->getType()) {
            case Adder:
                ImNodes::BeginInputAttribute(index + 2);
                ImGui::Text("frbuf in2");
                ImNodes::EndInputAttribute();
            case FrBuf:
                ImNodes::BeginInputAttribute(index + 1);
                ImGui::Text("frbuf in1");
                ImNodes::EndInputAttribute();
            case Void:
                break;
        }
        ImGui::PopID();
//        ImGui::SameLine();
        ImNodes::BeginOutputAttribute(index + 0);
        ImGui::Text("output");
        ImNodes::EndOutputAttribute();
        ImNodes::PopAttributeFlag();
        ImNodes::EndNode();
    }

    RenderNode::RenderNode(RenderPass* rp) { this->rp = rp; }

    void GraphicsPipeline::gui() {
        if (ImGui::Begin("Pipeline")) {
            ImNodes::BeginNodeEditor();

            int nodeIndex = 0;
            for (auto node : renderNodes) {
                node->gui(nodeIndex);
                nodeIndex += 3;
            }

            int linkIndex = 0;
            for (auto link : links)
                ImNodes::Link(linkIndex++, link.x, link.y);

            ImNodes::EndNodeEditor();


            int start_attr, end_attr;
            if (ImNodes::IsLinkCreated(&start_attr, &end_attr)) {
                int
                    node1 = start_attr / 3,
                    node2 = end_attr / 3,
                    attr1 = start_attr % 3,
                    attr2 = end_attr % 3;
//                std::cout << "Link (node: " << node1 << ", attrib: " << attr1
//                        << ") -> (node: " << node2 << ", attrib: " << attr2
//                        << ") should have been created\n";
                linkRenderPasses(node1, node2, attr2);
                links.emplace_back(start_attr, end_attr);
                // TODO topsort here
            }

            if (ImNodes::IsLinkDestroyed(&linkIndex)) {
//                std::cout << linkIndex << "\n";
//                std::cout << glm::to_string(links[linkIndex]) << "\n";
//                std::cout << links[linkIndex][0] << " " << links[linkIndex][1] << "\n";
                int
                    node1 = links[linkIndex][0] / 3,
                    node2 = links[linkIndex][1] / 3,
                    attr1 = links[linkIndex][0] % 3,
                    attr2 = links[linkIndex][1] % 3;

                switch (attr2) {
                    case 0:
                        assert(false);
                    case 1:
                        renderNodes[node2]->fst = nullptr;
                        break;
                    case 2:
                        renderNodes[node2]->snd = nullptr;
                        break;
                }
                links.erase(links.begin() + linkIndex);
            }
        }

        ImGui::End();
    }

    void GraphicsPipeline::addRenderPass(RenderPass* rp) { renderNodes.push_back(new RenderNode(rp)); }

    void GraphicsPipeline::linkRenderPasses(int fromNode, int toNode, int inputAttrib) {
        auto newInput = this->renderNodes[fromNode]->rp;
        auto destNode = this->renderNodes[toNode];
        switch (inputAttrib) {
            case 1:
                destNode->fst = newInput;
                break;
            case 2:
                destNode->snd = newInput;
                break;
            default:
                // shouldn't get to this branch
                assert(false);
                break;
        }
    }

    int GraphicsPipeline::getAttribID(int node, int attrib) {
        return node * 3 + attrib;
    }
}