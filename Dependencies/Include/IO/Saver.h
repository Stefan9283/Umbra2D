#pragma once

#include "Common.h"

namespace Umbra2D::IO {
	class Saver {
	private:
		std::string path;

		void saveTexture(std::ofstream& fout, TEXTURE* texture, int depth);

		void saveSpriteSize(std::ofstream& fout, SPRITE_SHEET* spriteSheet, int depth);

		void saveFrameDescription(std::ofstream& fout, std::string& description, int depth);

		void saveAnimationName(std::ofstream& fout, std::string& name, int depth);

		void saveKeyFrame(std::ofstream& fout, std::pair<int, float>& keyFrame, int depth);

		void saveKeyFrames(std::ofstream& fout, std::vector<std::pair<int, float>>& keyFrames, int depth);

		void saveAnimation(std::ofstream& fout, ANIMATION& animation, int depth);

		void saveAnimations(std::ofstream& fout, SPRITE_SHEET* spriteSheet, int depth);

		void saveFrameDescriptions(std::ofstream& fout, SPRITE_SHEET* spriteSheet, int depth);

		void saveSpriteSheet(std::ofstream& fout, SPRITE_SHEET* spriteSheet, int depth);

		void saveTextures(std::ofstream& fout, int depth);

		void saveSpriteSheets(std::ofstream& fout, int depth);

		void saveAssetLibrary(std::ofstream& fout, int depth);
	public:
		Saver(std::string path);

		void saveSettings();
	};
}
