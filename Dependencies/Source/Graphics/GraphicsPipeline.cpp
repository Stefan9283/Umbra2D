
#include <Graphics/GraphicsPipeline.h>

#include "Umbra2D.h"

namespace Umbra2D::Graphics {
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
        ImGui::Text("%d", index / 3);
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
//                    attr1 = start_attr % 3,
                    attr2 = end_attr % 3;
//                std::cout << "Link (node: " << node1 << ", attrib: " << attr1
//                        << ") -> (node: " << node2 << ", attrib: " << attr2
//                        << ") should have been created\n";
                linkRenderPasses(node1, node2, attr2);
                links.emplace_back(start_attr, end_attr);

                // Topological sort(rule: output -> input)
                std::vector<std::vector<int>> v(renderNodes.size());

                for (const auto& link : links)
                    v[link.x / 3].push_back(link.y / 3);

                std::stack<int> stack;
                std::vector<bool> visited(renderNodes.size());
                std::vector<int> visitedin(renderNodes.size());

                std::function<void(int)> dfs = [&](int i) {
                    visited[i] = true;

                    for (int j : v[i])
                        if (!visited[j])
                            dfs(j);

                    stack.push(i);
                };

                for (int i = 0; i < renderNodes.size(); i++)
                    if (!visited[i])
                        dfs(i);

                std::unordered_map<int, int> newOrder;
                std::vector<RenderNode*> newRenderNodes;
                std::vector<glm::ivec2> newLinks;

                for (int i = 0; i < renderNodes.size(); i++) {
                    newRenderNodes.push_back(renderNodes[stack.top()]);
                    newOrder[stack.top()] = i;
                    stack.pop();
                }

                for (const auto& it : links)
                    newLinks.emplace_back(newOrder[it.x / 3] * 3 + it.x % 3, newOrder[it.y / 3] * 3 + it.y % 3);

                for (int i = 0; i < renderNodes.size(); i++)
                    renderNodes[i] = newRenderNodes[i];

                for (int i = 0; i < links.size(); i++)
                    links[i] = newLinks[i];
            }

            if (ImNodes::IsLinkDestroyed(&linkIndex)) {
//                std::cout << linkIndex << "\n";
//                std::cout << glm::to_string(links[linkIndex]) << "\n";
//                std::cout << links[linkIndex][0] << " " << links[linkIndex][1] << "\n";
                int
//                    node1 = links[linkIndex][0] / 3,
                    node2 = links[linkIndex][1] / 3,
//                    attr1 = links[linkIndex][0] % 3,
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

    GraphicsPipeline::~GraphicsPipeline() {
        for (auto& node : this->renderNodes) {
            delete node->rp;
            delete node;
        }
    }

    FrameBuffer* GraphicsPipeline::getDrawnFrameBuffer(Umbra2D::Components::Camera* cam, Scene* s) {
        RenderNode* last = nullptr;
        for (auto* node : renderNodes) {
            switch (node->rp->getType()) {
                case Void:
                    node->rp->render(cam, s);
                    last = node;
                    break;
                case FrBuf:
                    if (node->fst) {
                        node->rp->render(cam, s,
                            node->fst->getFrameBuffer());
                        last = node;
                    }
                    break;
                case Adder:
                    if (node->fst && node->snd) {
                        node->rp->render(cam, s,
                             node->fst->getFrameBuffer(),
                             node->snd->getFrameBuffer());
                        last = node;
                    }
                    break;
            }
        }
        if (!last) return nullptr;

        return last->rp->getFrameBuffer();
    }
}