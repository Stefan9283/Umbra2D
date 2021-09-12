#include "FileExplorer.h"
#include "Texture.h"
#include "Gui.h"

// Private members
std::string Umbra2D::FileExplorer::formatPath(const std::string& path) {
	std::string formattedPath;

	for (int i = 0; i < path.size(); i++) {
		if (path[i] == '\\')
			formattedPath += "/";
		else
			formattedPath += path[i];
	}

	return formattedPath;
}

void Umbra2D::FileExplorer::getAllPaths(const std::string& path) {
	paths.erase(paths.begin(), paths.end());

	for (const auto& file : std::filesystem::directory_iterator(path)) {
		std::string iconType = "EmptyFolderIcon.png";

		if (!file.is_directory())
			iconType = "FolderIcon.png";
		else if (std::filesystem::is_empty(file))
			iconType = "FileIcon.png";

		paths.push_back({formatPath(file.path().string()), iconType});
	}
}

std::string Umbra2D::FileExplorer::truncatePath(const std::string& path) {
	for (size_t i = path.size(); i >= 0; i--)
		if (path[i] == '/')
			return std::string(path, i + 1);

	return std::string();
}

bool Umbra2D::FileExplorer::isATexture(const std::string& path) {
	std::string extension;

	for (size_t i = path.size(); i >= 0; i--)
		if (path[i] == '.') {
			extension = std::string(path, i + 1);
			break;
		}

	return extensions.find(extension) != extensions.end();
}

void Umbra2D::FileExplorer::loadTextures() {
	for (auto& it : textures)
		delete it.second;

	textures.erase(textures.begin(), textures.end());

	for (const auto& pair : paths)
		if (isATexture(pair.first))
			textures[truncatePath(pair.first)] = new Umbra2D::Assets::Texture(pair.first, truncatePath(pair.first));
}

void Umbra2D::FileExplorer::showChoiceList() {
	if (ImGui::BeginCombo("Current directory", currentDirectory.back().c_str())) {
		if (ImGui::Selectable(".")) {
			if (currentDirectory.size() > 1) {
				while (currentDirectory.size() != 1)
					currentDirectory.pop_back();

				getAllPaths(currentDirectory.back());
				loadTextures();
			}
		}

		if (ImGui::Selectable("<-")) {
			if (currentDirectory.size() > 1) {
				currentDirectory.pop_back();
				getAllPaths(currentDirectory.back());
				loadTextures();
			}
		}

		for (const auto& pair : paths)
			if (std::filesystem::is_directory(pair.first))
				if (ImGui::Selectable(truncatePath(pair.first).c_str())) {
					currentDirectory.push_back(pair.first);

					getAllPaths(currentDirectory.back());
					loadTextures();
					break;
				}

		ImGui::EndCombo();
	}
}

void Umbra2D::FileExplorer::showFiles(const glm::vec2& fileSize, const int& gridSize) {
	if (paths.size()) {
		int i = 0;

		std::sort(paths.begin(), paths.end(), [&](const auto& pair1, const auto& pair2) {
			return truncatePath(pair1.first).compare(truncatePath(pair2.first)) < 0;
		});

		if (ImGui::BeginTable("Files", gridSize)) {
			ImGui::TableNextRow();
		
			for (const auto& pair : paths) {
				ImGui::TableSetColumnIndex(i);

				if (isATexture(pair.first)) {
					Umbra2D::Gui::showTexture(textures[truncatePath(pair.first)], fileSize);
					ImGui::SameLine();
					ImGui::Selectable(truncatePath(pair.first).c_str());

					// Drag and drop for textures
					if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
						char buffer[MAX_LEN]{};

						strcpy(buffer, pair.first.c_str());
						ImGui::SetDragDropPayload("TEXTURE", &buffer, strlen(buffer) * sizeof(char));
						ImGui::EndDragDropSource();
					}

					if (ImGui::BeginDragDropTarget()) {
						if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TEXTURE"))
							std::cout << (char*)payload->Data << "\n";

						ImGui::EndDragDropTarget();
					}
				} else {
					Umbra2D::Gui::showTexture(icons[pair.second], fileSize);
					ImGui::SameLine();
					ImGui::Text(truncatePath(pair.first).c_str());
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

// Public members
Umbra2D::FileExplorer::FileExplorer(std::string path) {
	currentDirectory.push_back(path);
	getAllPaths("Dependencies\\Assets\\Textures\\Files");

	for (const auto& pair : paths)
		icons[truncatePath(pair.first)] = new Umbra2D::Assets::Texture(pair.first, truncatePath(pair.first));

	getAllPaths(path);
	loadTextures();
}

Umbra2D::FileExplorer::~FileExplorer() {
	for (auto& it : textures)
		delete it.second;

	for (auto& it : icons)
		delete it.second;
}

void Umbra2D::FileExplorer::showFileExplorer(const glm::vec2& windowSize, const glm::vec2& fileSize,
										     const float& fontSize, const int& gridSize) {
	ImGui::Begin("FileExplorer");
	ImGui::SetWindowFontScale(fontSize);
	ImGui::SetWindowSize(ImVec2(windowSize.x, windowSize.y));
	showChoiceList();
	showFiles(fileSize, gridSize);
	ImGui::End();
}
