#include "Umbra2D.h"

// Private members
namespace Umbra2D::Gui {
    std::string FileExplorer::formatPath(const std::string &path) {
        std::string formattedPath;

        for (char i : path) {
            if (i == '\\')
                formattedPath += "/";
            else
                formattedPath += i;
        }

        return formattedPath;
    }

    std::string FileExplorer::truncatePath(const std::string &path) {
        return std::string(path.substr(path.find_last_of('/') + 1));
    }

    void FileExplorer::getAllPaths(const std::string &path) {
        paths.erase(paths.begin(), paths.end());

        for (const auto &file : std::filesystem::directory_iterator(path))
            paths.emplace_back(getFileType(file.path().string()), formatPath(file.path().string()));
    }

    std::vector<std::string> FileExplorer::getAllSubpaths(std::string path) {
        std::vector<std::string> subpaths;
        int prev = 0;

        path += "/";

        for (int i = 0; i < path.size(); i++)
            if (path[i] == '/') {
                if (!subpaths.empty())
                    subpaths.push_back(subpaths.back() + "/" + std::string(path.begin() + prev, path.begin() + i));
                else
                    subpaths.emplace_back(path.begin() + prev, path.begin() + i);

                prev = i + 1;
            }

        return subpaths;
    }

    std::string FileExplorer::enumToString(FileType fileType) {
        if (fileType == EmptyFolder)
            return std::string("EmptyFolder.png");

        if (fileType == Folder)
            return std::string("Folder.png");

        if (fileType == File)
            return std::string("File.png");

        if (fileType == Texture)
            return std::string("Texture.png");

        if (fileType == Audio)
            return std::string("Audio.png");

        if (fileType == Script)
            return std::string("Script.png");

        return std::string("Shader.png");
    }

    FileExplorer::FileType FileExplorer::getFileType(const std::string &path) {
        if (std::filesystem::is_directory(path)) {
            if (std::filesystem::is_empty(path))
                return EmptyFolder;

            return Folder;
        }

        std::string extension;

        for (size_t i = path.size(); i >= 0; i--)
            if (path[i] == '.') {
                extension = std::string(path, i + 1);
                break;
            }

        if (textureExtensions.find(extension) != textureExtensions.end())
            return Texture;

        if (audioExtensions.find(extension) != audioExtensions.end())
            return Audio;

        if (scriptExtensions.find(extension) != scriptExtensions.end())
            return Script;

        if (shaderExtensions.find(extension) != shaderExtensions.end())
            return Shader;

        return File;
    }

    void FileExplorer::loadTextures() {
        for (auto &it : textures)
            delete it.second;

        textures.erase(textures.begin(), textures.end());

        for (const auto &pair : paths)
            if (pair.first == Texture)
                textures[truncatePath(pair.second)] = (new TEXTURE)->setTexture(pair.second, truncatePath(pair.second));
    }

    bool FileExplorer::isValid(const std::string &path) {
        if (!std::filesystem::exists(path))
            return false;

        for (int i = 0; i < (int) path.size() - 1; i++)
            if (path[i] == '.' && path[i] == path[i + 1])
                return false;

        return true;
    }

    void FileExplorer::showChoiceList() {
        if (ImGui::BeginPopup("Files")) {
            if (ImGui::Selectable("."))
                if (currentDirectory.size() > 1)
                    buffer = currentDirectory[0];

            if (ImGui::Selectable("<-"))
                if (currentDirectory.size() > 1)
                    buffer = currentDirectory[currentDirectory.size() - 2];

            for (const auto &pair : paths)
                if (pair.first == Folder || pair.first == EmptyFolder)
                    if (ImGui::Selectable(truncatePath(pair.second).c_str())) {
                        buffer = pair.second;
                        break;
                    }

            ImGui::EndPopup();
        }
    }

    void FileExplorer::showFiles() {
        if (!paths.empty()) {
            int i = 0;

            std::sort(paths.begin(), paths.end(), [&](const auto &pair1, const auto &pair2) {
                return truncatePath(pair1.second).compare(truncatePath(pair2.second)) < 0;
            });

            if (ImGui::BeginTable("Files", gridSize)) {
                ImGui::TableNextRow();

                for (const auto &pair : paths) {
                    ImGui::TableSetColumnIndex(i);

                    if (pair.first == Texture) {
                        Umbra2D::Gui::showTexture(textures[truncatePath(pair.second)], fileSize);
                        ImGui::SameLine();
                        ImGui::Selectable(truncatePath(pair.second).c_str());
                    } else if (pair.first == EmptyFolder || pair.first == Folder) {
                        if (ImGui::BeginTable("##folderCell", 1)) {
                            ImVec2 min, max, pos;

                            ImGui::TableNextRow();
                            ImGui::TableSetColumnIndex(0);
                            Umbra2D::Gui::showTexture(icons[enumToString(pair.first)], fileSize);
                            min = ImGui::GetItemRectMin();
                            ImGui::SameLine();
                            ImGui::Text("%s", truncatePath(pair.second).c_str());
                            max = ImGui::GetItemRectMax();
                            pos = ImGui::GetMousePos();
                            max.x = ImGui::GetWindowPos().x + ImGui::GetWindowSize().x / gridSize * (i + 1);

                            if (pos.x >= min.x && pos.x <= max.x && pos.y >= min.y && pos.y <= max.y) {
                                ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, ImGui::GetColorU32(ImGui::GetStyle().Colors[ImGuiCol_Button]));

                                if (ImGui::IsMouseDoubleClicked(0))
                                    buffer = pair.second;
                            }

                            ImGui::EndTable();
                        }
                    } else {
                        Umbra2D::Gui::showTexture(icons[enumToString(pair.first)], fileSize);
                        ImGui::SameLine();

                        if (pair.first == Audio || pair.first == Script || pair.first == Shader)
                            ImGui::Selectable(truncatePath(pair.second).c_str());
                        else
                            ImGui::Text("%s", truncatePath(pair.second).c_str());
                    }

                    // Drag and drop
                    if (pair.first == Texture || pair.first == Audio || pair.first == Script || pair.first == Shader) {
                        std::string type;
                        
                        if (pair.first == Texture)
                            type = "TEXTURE_PATH";
                        else if (pair.first == Audio)
                            type = "AUDIO_PATH";
                        else if (pair.first == Script)
                            type = "SCRIPT_PATH";
                        else
                            type = "SHADER_PATH";

                        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
                            char path_buffer[MAX_LEN]{};
                            strcpy(path_buffer, pair.second.c_str() + 2);
                            ImGui::SetDragDropPayload(type.c_str(), &path_buffer, strlen(path_buffer) * sizeof(char) + 1);
                            ImGui::EndDragDropSource();
                        }
                    }

                    if (ImGui::BeginDragDropTarget()) {
                        if (const ImGuiPayload *payload1 = ImGui::AcceptDragDropPayload("TEXTURE_PATH"))
                            std::cout << "Texture\n";
                        else if (const ImGuiPayload *payload2 = ImGui::AcceptDragDropPayload("AUDIO_PATH"))
                            std::cout << "Audio\n";
                        else if (const ImGuiPayload *payload3 = ImGui::AcceptDragDropPayload("SCRIPT_PATH"))
                            std::cout << "Script\n";
                        else if (const ImGuiPayload* payload4 = ImGui::AcceptDragDropPayload("SHADER_PATH"))
                            std::cout << "Shader\n";

                        ImGui::EndDragDropTarget();
                    }

                    if (i + 1 < gridSize)
                        i++;
                    else {
                        i = 0;
                        ImGui::TableNextRow();
                    }
                }

                ImGui::EndTable();
            }
        }
    }

    void FileExplorer::showChoiceListAndFiles() {
        ImGui::InputText("##input", &buffer);
        ImGui::SameLine(0, 0);

        ImVec2 pos = ImGui::GetItemRectMin();
        ImVec2 size = ImGui::GetItemRectSize();

        if (ImGui::ArrowButton("##combo", ImGuiDir_Down))
            ImGui::OpenPopup("Files");

        ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y + size.y));
        ImGui::SetNextWindowSize(ImVec2(size.x + 19, size.y * 10));

        if (isValid(buffer)) {
            bool wasChanged = buffer != currentDirectory.back();

            currentDirectory.erase(currentDirectory.begin(), currentDirectory.end());
            paths.erase(paths.begin(), paths.end());

            for (const auto &subpath : getAllSubpaths(buffer))
                currentDirectory.push_back(subpath);

            getAllPaths(currentDirectory.back());
            showChoiceList();
            ImGui::SameLine();
            ImGui::Text("Current directory");

            if (wasChanged)
                loadTextures();

            showFiles();
        } else {
            ImGui::SameLine();
            ImGui::Text("Current directory");
            ImGui::PushStyleColor(ImGuiCol_FrameBg, {0, 0, 0, 0});

            if (ImGui::BeginListBox("##possibleFiles", {size.x + 19, size.y * 10})) {
                ImGui::PopStyleColor();

                std::string basePath = buffer.substr(0, buffer.find_last_of('/'));

                if (isValid(basePath)) {
                    getAllPaths(basePath);

                    for (const auto &path : paths)
                        if ((path.first == EmptyFolder || path.first == Folder) && path.second.starts_with(buffer))
                            if (ImGui::Selectable(truncatePath(path.second).c_str())) {
                                buffer = path.second;
                                break;
                            }
                }

                ImGui::EndListBox();
                return;
            }

            ImGui::PopStyleColor();
        }
    }

// Public members
    FileExplorer::FileExplorer(std::string path) {
        currentDirectory.push_back(path);
        getAllPaths("Dependencies/Assets/Textures/Files");

        for (const auto &pair : paths)
            icons[truncatePath(pair.second)] = (new TEXTURE)->setTexture(pair.second, truncatePath(pair.second));

        buffer = path;
        getAllPaths(path);
        loadTextures();
    }

    FileExplorer::~FileExplorer() {
        for (auto &it : textures)
            delete it.second;

        for (auto &it : icons)
            delete it.second;
    }

    void FileExplorer::gui() {
        ImGui::Begin("File explorer");
        ImGui::SetWindowFontScale(fontSize);

        if (ImGui::IsMouseClicked(1))
            if (currentDirectory.size() > 1)
                buffer = currentDirectory[currentDirectory.size() - 2];

        showChoiceListAndFiles();
        ImGui::End();
    }
}
