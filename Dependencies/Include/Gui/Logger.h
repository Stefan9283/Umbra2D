#pragma once

#include "Common.h"

namespace Umbra2D::Gui {
	class Logger {
	private:
		std::unordered_map<std::string, ImVec4> flagColors;
		std::vector<std::pair<std::string, std::string>> logs;
	public:
		Logger();

		void addFlag(std::string flag, ImVec4 color);

		void addLog(std::string flag, std::string log);

		void gui();
	};
}
