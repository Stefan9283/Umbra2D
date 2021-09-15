#include "Graphics/Shader.h"
#include "Engines/Renderer.h"
#include "Components/Renderable.h"
#include "Scene.h"

extern Umbra2D::Umbra2DEngine* umbra;

void Umbra2D::Renderer::onUpdate(Scene *scene, Shader* shader) {
    if (!render) return;

    shader->bind();

    auto view_st = scene->registry.view<STATIC>();
    for (auto ent : view_st)
        scene->registry.get<STATIC>(ent).draw(shader);

    auto view_dyn = scene->registry.view<DYNAMIC>();
    for (auto ent : view_dyn)
        scene->registry.get<DYNAMIC>(ent).draw(shader);

    shader->unbind();
}
bool Umbra2D::Renderer::isActive() { return render; }
void Umbra2D::Renderer::toggle() { render = !render; }

