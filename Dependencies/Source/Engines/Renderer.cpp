#include "Graphics/Shader.h"
#include "Engines/Renderer.h"
#include "Components/Renderable.h"
#include "Components/Colliders.h"
#include "Scene.h"

extern Umbra2D::Umbra2DEngine* umbra;

bool Umbra2D::AbstractRenderer::isActive() { return render; }
void Umbra2D::AbstractRenderer::toggle() { render = !render; }

void Umbra2D::Renderer::onUpdate(Scene *scene, Shader* shader) {
    if (!isActive()) return;

    shader->bind();

    auto view_st = scene->registry.view<STATIC>();
    for (auto ent : view_st)
        scene->registry.get<STATIC>(ent).draw(shader);

    auto view_dyn = scene->registry.view<DYNAMIC>();
    for (auto ent : view_dyn)
        scene->registry.get<DYNAMIC>(ent).draw(shader);

    shader->unbind();
}

void Umbra2D::CollidersRenderer::onUpdate(Umbra2D::Scene *scene, Umbra2D::Shader *shader) {
    if (!isActive()) return;
    shader->bind();

    auto view_circle = scene->registry.view<CIRCLE>();
    for (auto ent : view_circle)
        scene->registry.get<CIRCLE>(ent).draw();

    auto view_rectangle = scene->registry.view<RECTANGLE>();
    for (auto ent : view_rectangle)
        scene->registry.get<RECTANGLE>(ent).draw();

    auto view_line = scene->registry.view<LINE>();
    for (auto ent : view_line)
        scene->registry.get<LINE>(ent).draw();

    shader->unbind();
}
