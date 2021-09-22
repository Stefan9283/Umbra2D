#pragma once

#include "Common.h"

namespace Umbra2D::Gui {
	class FileExplorer {
	private:
		enum FileType{EmptyFolder, Folder, File, Texture, Audio, Script, Shader};

		std::string buffer;

		std::vector<std::string> currentDirectory;
		std::vector<std::pair<FileType, std::string>> paths;

		std::unordered_map<std::string, Umbra2D::Assets::Texture*> textures;
		std::unordered_map<std::string, Umbra2D::Assets::Texture*> icons;

		std::unordered_set<std::string> textureExtensions{"png", "jpg", "jpeg", "gif"};
		std::unordered_set<std::string> audioExtensions{"wav", "mp3", "flac", "ogg"};
		std::unordered_set<std::string> scriptExtensions{"py", "lua", "chai"};
		std::unordered_set<std::string> shaderExtensions{"glsl"};

		std::string formatPath(const std::string& path);

		std::string truncatePath(const std::string& path);

		void getAllPaths(const std::string& path);

		std::vector<std::string> getAllSubpaths(std::string path);

		std::string enumToString(FileType fileType);

		FileType getFileType(const std::string& path);

		void loadTextures();

		bool isValid(const std::string& path);

		void showChoiceList();

		void showFiles();

		void showChoiceListAndFiles();

	public:
		glm::vec2 fileSize = {20, 20};
		float fontSize = 1;
		int gridSize = 3;

		FileExplorer(std::string path = ".");

		~FileExplorer();

		void gui();
	};
}
