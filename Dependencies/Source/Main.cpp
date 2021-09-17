// Umbra2D headers
#define STB_IMAGE_IMPLEMENTATION

#include <cstdio>

#include <Engine.h>
#include "Common.h"
#include "AssetLibrary.h"
#include "Window.h"
#include "Camera.h"
#include "Entity.h"
#include "Texture.h"
#include "Shader.h"
#include "Gui.h"
#include "Colliders.h"
#include "Fonts.h"
#include "FrameBuffer.h"
#include "FileExplorer.h"
//#include "AudioPlayer.h"

Umbra2D::Engine *umbra;
Umbra2D::Shader *colliderShader;

//
///*int main()
//{
//    PaStream* stream;
//    PaError error;
//    myWav current_wav;
//
//    current_wav.wav = sf_open("C:\\Users\\soulv\\Documents\\GitHub\\Umbra2D\\Dependencies\\Source\\test.wav", SFM_READ, &current_wav.info);
//    if (sf_error(current_wav.wav) != SF_ERR_NO_ERROR)
//    {
//        fprintf(stderr, "%s\n", sf_strerror(current_wav.wav));
//        fprintf(stderr, "File: %s\n", "test.wav");
//        return 1;
//    }
//
//    error = Pa_Initialize();
//    if (error != paNoError)
//    {
//        fprintf(stderr, "Problem initializing\n");
//        return 1;
//    }
//
//    error = Pa_OpenDefaultStream(&stream
//        , 0
//        , current_wav.info.channels
//        , paFloat32
//        , current_wav.info.samplerate
//        , FRAMES_PER_BUFFER
//        , callback
//        , &current_wav);
//    if (error != paNoError)
//    {
//        fprintf(stderr, "Problem opening Default Stream\n");
//        return 1;
//    }
//
//    error = Pa_StartStream(stream);
//    if (error != paNoError)
//    {
//        fprintf(stderr, "Problem opening starting Stream\n");
//        return 1;
//    }
//
//    while (Pa_IsStreamActive(stream))
//    {
//        Pa_Sleep(100);
//    }
//
//    error = Pa_StopStream(stream);
//    if (error != paNoError)
//    {
//        fprintf(stderr, "Problem closing stream\n");
//        return 1;
//    }
//
//    error = Pa_Terminate();
//    if (error != paNoError)
//    {
//        fprintf(stderr, "Problem terminating\n");
//        return 1;
//    }
//
//    sf_close(current_wav.wav);
//
//    return 0;
//}*/
//
int main()
{
   umbra = new Umbra2D::Engine();
   umbra->loadProject();

   Umbra2D::FileExplorer fe;

   colliderShader = new Umbra2D::Shader("Dependencies/Shader/collider/vert.glsl", "Dependencies/Shader/collider/frag.glsl");
   Umbra2D::Shader spriteShader("Dependencies/Shader/sprite/vert.glsl", "Dependencies/Shader/sprite/frag.glsl");
   Umbra2D::Shader textShader("Dependencies/Shader/text/vert.glsl", "Dependencies/Shader/text/frag.glsl");

   textShader.setMat4("model", glm::mat4(1));

   Umbra2D::Camera editorCamera(WINDOW);

   Umbra2D::Dynamic character;
   character.setSpriteSheet("Dependencies/Assets/Textures/Adventurer/adventurer-Sheet.png");
   character.transform.scale = 15.f * glm::vec2(43, 37);
   character.transform.layer = 1;

   Umbra2D::Static bg;
   bg.setTexture("Dependencies/Assets/Textures/UndertaleFin.png");
   bg.transform.scale = glm::vec2(10000, 10000);
   bg.transform.layer = 2;

   auto* rectangle = new Umbra2D::Colliders::Rectangle(200, 100);
   auto* circle = new Umbra2D::Colliders::Circle(200);
   auto* line = new Umbra2D::Colliders::Line(100, glm::vec2(1, 1));
   auto* line2 = new Umbra2D::Colliders::Line(100, glm::vec2(1, 1));

   Umbra2D::Text::Font f("Dependencies/Assets/Fonts/Minecraft.ttf");

   std::string renderedString = "Bruh";

   std::vector<int> numbers{1, 2, 3};
   std::vector<int> numbers2{4, 5};

   Umbra2D::FrameBuffer frbuf(GL_RGBA, {1920, 1080});

   ImGui::GetIO().ConfigWindowsResizeFromEdges = true;

   //auto audioPlayer = new Umbra2D::AudioPlayer();

   int colliderDepth = 0;
   while (!WINDOW->shouldClose()) {
       WINDOW->startFrame();

       static bool use_work_area = true;
       ImGuiWindowFlags rootFlags =
                   ImGuiWindowFlags_NoMove
                   | ImGuiWindowFlags_NoCollapse
                   | ImGuiWindowFlags_NoDocking
                   | ImGuiWindowFlags_NoResize
                   | ImGuiWindowFlags_NoTitleBar
                   | ImGuiWindowFlags_MenuBar
                   | ImGuiWindowFlags_NoBringToFrontOnFocus;

       const ImGuiViewport *viewport = ImGui::GetMainViewport();
       ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
       ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);

       ImGui::Begin("RootWindow", (bool*)use_work_area, rootFlags);
       ImGui::DockSpace(ImGui::GetID("MainWindow"));
       {   // WRITE YOUR CODE INSIDE OF THESE BRACKETS

           fe.showFileExplorer();
/*
           // DRAG AND DROP
           {
               if (ImGui::Begin("Drag-N-Drop 1")) {
                   if (ImGui::BeginDragDropTarget()) {
                       if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("NUMAR_MISTO")) {
                           int payload_n = *(const int *) payload->Data;
                           std::cout << payload_n << "\n";
                           numbers2.push_back(payload_n);
                       }
                       ImGui::EndDragDropTarget();
                   }
                   for (auto n : numbers2) {
                       ImGui::Button(std::to_string(n).c_str());
                       if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
                           // Set payload to carry the index of our item (could be anything)
                           ImGui::SetDragDropPayload("NUMAR_MISTO", &n, sizeof(int));
                           ImGui::EndDragDropSource();
                       }
                       if (ImGui::BeginDragDropTarget()) {
                           if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("NUMAR_MISTO")) {
                               int payload_n = *(const int *) payload->Data;
                               std::cout << payload_n << "\n";
                               numbers2.push_back(payload_n);
                           }
                           ImGui::EndDragDropTarget();
                       }
                   }
               }
               ImGui::End();

               if (ImGui::Begin("Drag-N-Drop 2")) {
                   for (auto n : numbers) {
                       ImGui::Button(std::to_string(n).c_str());
                       if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
                           // Set payload to carry the index of our item (could be anything)
                           ImGui::SetDragDropPayload("NUMAR_MISTO", &n, sizeof(int));
                           ImGui::EndDragDropSource();
                       }
                       if (ImGui::BeginDragDropTarget()) {
                           if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("NUMAR_MISTO")) {
                               int payload_n = *(const int *) payload->Data;
                               std::cout << payload_n << "\n";
                               numbers.push_back(payload_n);
                           }
                           ImGui::EndDragDropTarget();
                       }
                   }
               }
               ImGui::End();

           }
           // DRAG AND DROP END


           // THEME COLORS
           if(ImGui::Begin("Color")) {
               ImGuiStyle& style = ImGui::GetStyle();

               static ImGuiColorEditFlags alpha_flags = 0;
               if (ImGui::RadioButton("Opaque", alpha_flags == ImGuiColorEditFlags_None))             { alpha_flags = ImGuiColorEditFlags_None; } ImGui::SameLine();
               if (ImGui::RadioButton("Alpha",  alpha_flags == ImGuiColorEditFlags_AlphaPreview))     { alpha_flags = ImGuiColorEditFlags_AlphaPreview; } ImGui::SameLine();
               if (ImGui::RadioButton("Both",   alpha_flags == ImGuiColorEditFlags_AlphaPreviewHalf)) { alpha_flags = ImGuiColorEditFlags_AlphaPreviewHalf; } ImGui::SameLine();

               Umbra2D::Gui::HelpMarker(
                       "In the color list:\n"
                       "Left-click on color square to open color picker,\n"
                       "Right-click to open edit options menu.");

               static ImGuiTextFilter filter;
               filter.Draw("Filter colors", ImGui::GetFontSize() * 16);

               for (int i = 0; i < ImGuiCol_COUNT; i++) {
                   const char* name = ImGui::GetStyleColorName(i);
                   ImGui::ColorEdit4((name + std::to_string(i)).c_str(), (float*)&style.Colors[i], ImGuiColorEditFlags_AlphaBar | alpha_flags);
               }
           }
           ImGui::End();
*/
        //    if (ImGui::Begin("Plang"))
        //        if (ImGui::Button("Play")) {
        //            audioPlayer->listOutputDevices();
        //            if(audioPlayer->canPlayAudio())
        //                printf("DA\n");
        //            audioPlayer->addAudio(R"(Dependencies\Source\test.wav)", "k");
        //            audioPlayer->playAudio("k", 5);
        //        }
         //  ImGui::End();

           // check out what this function does for more ImGui examples
           ImGui::ShowDemoWindow();


           if(ImGui::Begin("Utils")) {
               LIBRARY->gui();

               // ENTITIES
               if (ImGui::TreeNode("bg")) {
                   bg.gui();
                   ImGui::TreePop();
               }
               if (ImGui::TreeNode("character")) {
                   character.gui();
                   ImGui::TreePop();
               }

               // COLLIDERS
               if (ImGui::TreeNode("colliders")) {
                   if (ImGui::TreeNode("line")) {
                       line->gui();
                       ImGui::Text("Line2 collision: %d\nRectangle collision:%d\nCircle collision: %d", line->checkCollision(line2), line->checkCollision(rectangle), line->checkCollision(circle));
                       ImGui::TreePop();
                   }
                   if (ImGui::TreeNode("line2")) {
                       line2->gui();
                       //ImGui::Text("Line2 collision: %d\nRectangle collision:%d\nCircle collision: %d", line->checkCollision(line2), line->checkCollision(rectangle), line->checkCollision(circle));
                       ImGui::TreePop();
                   }
                   if (ImGui::TreeNode("circle")) {
                       circle->gui();
                       ImGui::Text("Rectangle collision: %d", circle->checkCollision(rectangle));
                       ImGui::TreePop();
                   }
                   if (ImGui::TreeNode("rectangle")) {
                       rectangle->gui();
                       ImGui::TreePop();
                   }
                   ImGui::SliderInt("colliders depth", &colliderDepth, 0, 1000);
                   ImGui::TreePop();
               }
               ImGui::InputText("Rendered Text ", &renderedString);
           }
           ImGui::End();



           // ACTUAL RENDERING TO FRAMEBUFFER
           frbuf.bind();
           glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

           editorCamera.UpdateProjMatrix();
           glm::mat4
                   proj = editorCamera.getProj(),
                   view = editorCamera.getView();

           // ENTITIES RENDERING
           spriteShader.setMat4("view", &view);
           spriteShader.setMat4("proj", &proj);

           bg.draw(&spriteShader);
           character.draw(&spriteShader);

           // TEXT RENDERING
           textShader.setMat4("view", &view);
           textShader.setMat4("proj", &proj);
           f.RenderText(&textShader, renderedString, 0, 0, 1.0f,glm::vec4(0.5, 0.8f, 0.2f, 1.f), 0);

           colliderShader->setMat4("view", &view);
           colliderShader->setMat4("proj", &proj);
           colliderShader->setFloat("depth", colliderDepth);

           circle->draw();
           line->draw();
           line2->draw();
           rectangle->draw();

           frbuf.unbind();


           // DRAW GAME FRAMEBUFFER AS IMGUI TEXTURE
           if (ImGui::Begin("Game")) {
//                ImVec2 vMin = ImGui::GetWindowContentRegionMin();
//                ImVec2 vMax = ImGui::GetWindowContentRegionMax();
               ImVec2 last_tooltip_size = ImGui::GetWindowSize();
               Umbra2D::Gui::showTexture(frbuf.getTexture(), glm::vec2(last_tooltip_size.x - 2, last_tooltip_size.y - 37));
           }
           ImGui::End();


           // CAMERA INPUTS VIA WINDOW INSTANCE
           if (WINDOW->wasKeyPressed(GLFW_KEY_ESCAPE))
               break;
           if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_RootAndChildWindows)) {
               float unitsPerFrame = 5;
               if (WINDOW->wasKeyPressed(GLFW_KEY_D))
                   editorCamera.MoveHorizontally(-unitsPerFrame);
               if (WINDOW->wasKeyPressed(GLFW_KEY_A))
                   editorCamera.MoveHorizontally(unitsPerFrame);
               if (WINDOW->wasKeyPressed(GLFW_KEY_W))
                   editorCamera.MoveVertically(unitsPerFrame);
               if (WINDOW->wasKeyPressed(GLFW_KEY_S))
                   editorCamera.MoveVertically(-unitsPerFrame);
               if (WINDOW->wasKeyPressed(GLFW_KEY_LEFT_CONTROL))
                   editorCamera.Zoom(0.01f);
               if (WINDOW->wasKeyPressed(GLFW_KEY_LEFT_ALT))
                   editorCamera.Zoom(-0.01f);
           }
       } // WRITE YOUR CODE INSIDE OF THESE BRACKETS


       ImGui::End();
       WINDOW->endFrame();
   }
   delete colliderShader;
   //delete audioPlayer;
   umbra->saveProject();
   delete umbra;

   return 0;
}
