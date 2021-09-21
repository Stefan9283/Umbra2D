#include "Umbra2D.h"

extern Umbra2D::Umbra2DEngine* umbra;

bool Umbra2D::AbstractRenderer::isActive() { return render; }
void Umbra2D::AbstractRenderer::toggle() { render = !render; }

template<typename T>
void drawType(Umbra2D::Scene* scene, Umbra2D::Graphics::Shader* shader) {
    auto view_circle = scene->registry.view<T>();
    for (auto ent : view_circle)
        scene->registry.get<T>(ent).draw(shader);
}

/*
 *

template<typename T>
void drawType(Umbra2D::Scene* scene) {
    auto view_circle = scene->registry.view<T>();
    for (auto ent : view_circle)
        scene->registry.get<T>(ent).draw();
}

void Umbra2D::Renderer::onUpdate(Scene *scene, Shader* shader) {
    if (!isActive()) return;
    shader->bind();
    drawType<STATIC>(scene, shader);
    drawType<DYNAMIC>(scene, shader);
    shader->unbind();
}

void Umbra2D::CollidersRenderer::onUpdate(Umbra2D::Scene *scene, Umbra2D::Graphics::Shader *shader) {
    if (!isActive()) return;
    shader->bind();
    drawType<CIRCLE>(scene);
    drawType<RECTANGLE>(scene);
    drawType<LINE>(scene);
    shader->unbind();
}
 *
 */

void Umbra2D::Renderer::onUpdate(Scene *scene, Graphics::Shader* shader) {
    if (!isActive()) return;
    shader->bind();
    drawType<STATIC>(scene, shader);
    drawType<DYNAMIC>(scene, shader);
    shader->unbind();
}

void Umbra2D::CollidersRenderer::onUpdate(Umbra2D::Scene *scene, Graphics::Shader *shader) {
    if (!isActive()) return;
    shader->bind();
    drawType<CIRCLE>(scene, shader);
    drawType<LINE>(scene, shader);
    drawType<AARECTANGLE>(scene, shader);
    drawType<RECTANGLE>(scene, shader);
    shader->unbind();
}
