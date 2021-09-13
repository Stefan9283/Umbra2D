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

std::string Umbra2D::FileExplorer::truncatePath(const std::string& path) {
	for (int i = path.size(); i >= 0; i--)
		if (path[i] == '/')
			return std::string(path, i + 1);

	return std::string();
}

void Umbra2D::FileExplorer::getAllPaths(const std::string& path) {
	paths.erase(paths.begin(), paths.end());

	for (const auto& file : std::filesystem::directory_iterator(path))
		paths.push_back({getFileType(file.path().string()), formatPath(file.path().string())});
}

std::vector<std::string> Umbra2D::FileExplorer::getAllSubpaths(std::string path) {
	std::vector<std::string> subpaths;
	int prev = 0;

	path += "/";

	for (int i = 0; i < path.size(); i++)
		if (path[i] == '/') {
			if (subpaths.size())
				subpaths.push_back(subpaths.back() + "/" + std::string(path.begin() + prev, path.begin() + i));
			else
				subpaths.push_back(std::string(path.begin() + prev, path.begin() + i));

			prev = i + 1;
		}

	return subpaths;
}

std::string Umbra2D::FileExplorer::enumToString(FileType fileType) {
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

	return std::string("Script.png");
}

Umbra2D::FileExplorer::FileType Umbra2D::FileExplorer::getFileType(const std::string& path) {
	if (std::filesystem::is_directory(path)) {
		if (std::filesystem::is_empty(path))
			return EmptyFolder;

		return Folder;
	}

	std::string extension;

	for (int i = path.size(); i >= 0; i--)
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

	return File;
}

void Umbra2D::FileExplorer::loadTextures() {
	for (auto& it : textures)
		delete it.second;

	textures.erase(textures.begin(), textures.end());

	for (const auto& pair : paths)
		if (pair.first == Texture)
			textures[truncatePath(pair.second)] = new Umbra2D::Assets::Texture(pair.second, truncatePath(pair.second));
}

void Umbra2D::FileExplorer::showChoiceList() {
	if (ImGui::BeginPopup("Files")) {
		if (ImGui::Selectable("."))
			if (currentDirectory.size() > 1)
				buffer = currentDirectory[0];

		if (ImGui::Selectable("<-"))
			if (currentDirectory.size() > 1)
				buffer = currentDirectory[currentDirectory.size() - 2];

		for (const auto& pair : paths)
			if (pair.first == Folder || pair.first == EmptyFolder)
				if (ImGui::Selectable(truncatePath(pair.second).c_str())) {
					buffer = pair.second;
					break;
				}

		ImGui::EndPopup();
	}
}

void Umbra2D::FileExplorer::showFiles(const glm::vec2& fileSize, const int& gridSize) {
	if (paths.size()) {
		int i = 0, id = 0;

		std::sort(paths.begin(), paths.end(), [&](const auto& pair1, const auto& pair2) {
			return truncatePath(pair1.second).compare(truncatePath(pair2.second)) < 0;
		});

		if (ImGui::BeginTable("Files", gridSize)) {
			ImGui::TableNextRow();
		
			for (const auto& pair : paths) {
				ImGui::TableSetColumnIndex(i);

				if (pair.first == Texture) {
					Umbra2D::Gui::showTexture(textures[truncatePath(pair.second)], fileSize);
					ImGui::SameLine();
					ImGui::Selectable(truncatePath(pair.second).c_str());
				} else if (pair.first == EmptyFolder || pair.first == Folder) {
					ImGui::PushID(id);
					ImGui::PushStyleColor(ImGuiCol_Button, {0, 0, 0, 0});

					if (ImGui::ImageButton((ImTextureID)icons[enumToString(pair.first)]->getID(),
										   {fileSize.x, fileSize.y}, {0, 1}, {1, 0}, 0, {0, 0, 0, 0}, {1, 1, 1, 1}))
						buffer = pair.second;
					else
						id++;

					ImGui::PopStyleColor();
					ImGui::PopID();
					ImGui::SameLine(0, 5);
					ImGui::PushStyleColor(ImGuiCol_Button, {0, 0, 0, 0});

					if (ImGui::Button(truncatePath(pair.second).c_str())) {
						buffer = pair.second;
						ImGui::PopStyleColor();
						ImGui::EndTable();
						return;
					}

					ImGui::PopStyleColor();
				} else {
					Umbra2D::Gui::showTexture(icons[enumToString(pair.first)], fileSize);
					ImGui::SameLine();

					if (pair.first == Audio || pair.first == Script)
						ImGui::Selectable(truncatePath(pair.second).c_str());
					else
						ImGui::Text(truncatePath(pair.second).c_str());
				}

				// Drag and drop
				if (pair.first == Texture || pair.first == Audio || pair.first == Script) {
					std::string type = pair.first == Texture ? "TEXTURE_PATH" : (pair.first == Audio ? "AUDIO_PATH" : "SCRIPT_PATH");

					if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
						char buffer[MAX_LEN]{};

						strcpy(buffer, pair.second.c_str());
						ImGui::SetDragDropPayload(type.c_str(), &buffer, strlen(buffer) * sizeof(char));
						ImGui::EndDragDropSource();
					}
				}

				if (ImGui::BeginDragDropTarget()) {
					if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TEXTURE_PATH"))
						std::cout << "Texture\n";
					else if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("AUDIO_PATH"))
						std::cout << "Audio\n";
					else if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("SCRIPT_PATH"))
						std::cout << "Script\n";

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

void Umbra2D::FileExplorer::showChoiceListAndFiles(const glm::vec2& fileSize, const int& gridSize) {
	ImGui::InputText("##input", &buffer);
	ImGui::SameLine(0, 0);

	ImVec2 pos = ImGui::GetItemRectMin();
	ImVec2 size = ImGui::GetItemRectSize();

	if (ImGui::ArrowButton("##combo", ImGuiDir_Down))
		ImGui::OpenPopup("Files");

	ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y + size.y));
	ImGui::SetNextWindowSize(ImVec2(size.x + 19, size.y * 10));

	if (std::filesystem::exists(buffer)) {
		bool wasChanged = buffer != currentDirectory.back();

		currentDirectory.erase(currentDirectory.begin(), currentDirectory.end());
		paths.erase(paths.begin(), paths.end());

		for (const auto& subpath : getAllSubpaths(buffer))
			currentDirectory.push_back(subpath);

		getAllPaths(currentDirectory.back());
		showChoiceList();
		ImGui::SameLine();
		ImGui::Text("Current directory");

		if (wasChanged)
			loadTextures();

		showFiles(fileSize, gridSize);
	} else {
		ImGui::SameLine();
		ImGui::Text("Current directory");
	}
}

// Public members
Umbra2D::FileExplorer::FileExplorer(std::string path) {
	currentDirectory.push_back(path);
	getAllPaths("Dependencies/Assets/Textures/Files");

	for (const auto& pair : paths)
		icons[truncatePath(pair.second)] = new Umbra2D::Assets::Texture(pair.second, truncatePath(pair.second));

	buffer = path;
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
	ImGui::Begin("File explorer");
	ImGui::SetWindowFontScale(fontSize);
	ImGui::SetWindowSize(ImVec2(windowSize.x, windowSize.y));
	showChoiceListAndFiles(fileSize, gridSize);
	ImGui::End();
}
