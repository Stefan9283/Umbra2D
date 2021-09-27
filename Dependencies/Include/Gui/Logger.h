#pragma once

#include "Common.h"

namespace Umbra2D::Gui {
	class Logger {
	private:
		std::unordered_map<std::string, ImVec4> flagColors;
		std::vector<std::pair<std::string, std::string>> logs;
	public:
		Logger();

		void addFlag(const std::string& flag, ImVec4 color);

		/*
		 * adds another log to the logger
		 * default flag options are:
		 * - status
		 * - success
		 * - warning
		 * - error
		 */
		void addLog(std::string flag, const std::string& log);

		void gui();
	};
}
