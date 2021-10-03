#ifndef UMBRA2D_ONETYPEVOIDPASS_H
#define UMBRA2D_ONETYPEVOIDPASS_H

#include "RenderPass.h"

extern Umbra2D::Umbra2DEngine* umbra;

template<typename T>
void drawType(Umbra2D::Scene* scene, Umbra2D::Graphics::Shader* shader) {
    // TODO optimize for instanced rendering
    auto view = scene->registry.view<T>();
    for (auto ent : view)
        scene->registry.get<T>(ent).draw(shader);
}

namespace Umbra2D::Graphics {
    template<typename T>
    class OneTypeVoidPass : public RenderPass {
    public:
        OneTypeVoidPass();
        void render(Umbra2D::Components::Camera *cam, Scene* s) override;
    };

    template<typename T>
    OneTypeVoidPass<T>::OneTypeVoidPass() : RenderPass(Void) {}

    template<typename T>
    void OneTypeVoidPass<T>::render(Umbra2D::Components::Camera* cam, Scene* s) {
        auto pFrameBuffer = getFrameBuffer();
        if (!pFrameBuffer) return;
        pFrameBuffer->bind();
        glm::vec4 color = umbra->getThemeColor();
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto pShader = getShader();
        if (pShader) {
            pShader->bind();
            pShader->setMat4("view", cam->getView());
            pShader->setMat4("proj", cam->getProj());
            drawType<T>(s, pShader);
            pShader->unbind();
        }
        pFrameBuffer->unbind();
    }
}

#endif //UMBRA2D_ONETYPEVOIDPASS_H
