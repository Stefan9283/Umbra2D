#pragma once

#include "Common.h"

namespace Umbra2D {
	class FileExplorer {
	private:
		std::vector<std::string> currentDirectory;
		std::vector<std::pair<std::string, std::string>> paths;

		std::unordered_map<std::string, Umbra2D::Assets::Texture*> textures;
		std::unordered_map<std::string, Umbra2D::Assets::Texture*> icons;
		std::unordered_set<std::string> extensions{"png", "jpg", "jpeg", "gif"};

		std::string formatPath(const std::string& path);

		void getAllPaths(const std::string& path);

		std::string truncatePath(const std::string& path);

		bool isATexture(const std::string& path);

		void loadTextures();

		void showChoiceList();

		void showFiles(const glm::vec2& fileSize, const int& gridSize);

	public:
		FileExplorer(std::string path = ".");

		~FileExplorer();

		void showFileExplorer(const glm::vec2& windowSize = {750, 500},
							  const glm::vec2& fileSize = {20, 20},
							  const float& fontSize = 1,
							  const int& gridSize = 3);
	};
}
