#include "Gui/Logger.h"

Umbra2D::Gui::Logger::Logger() {
	addFlag("status", {106, 192, 180, 1});
	addFlag("success", {0, 255, 0, 1});
	addFlag("warning", {238, 237, 0, 1});
    addFlag("error", {255, 0, 0, 1});
}

void Umbra2D::Gui::Logger::addFlag(const std::string& flag, ImVec4 color) {
	flagColors[flag] = color;
}

void Umbra2D::Gui::Logger::addLog(std::string flag, const std::string& log) {
	if (logs.size() > MAX_LEN)
		logs.erase(logs.begin());

	auto currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::stringstream ss;

	ss << std::put_time(std::localtime(&currentTime), "%X");

	bool foundFlag = false;
	for (const auto& flagCol : flagColors) {
	    if (flag == flagCol.first) {
	        foundFlag = true;
	        break;
	    }
	}

	if (!foundFlag) {
        std::cout << "There is no flag by the name of " << flag << "\n Replacing with warning\n";
        flag = "warning";
    }

    logs.emplace_back( "[" + ss.str() + "] " + log, flag);
}

void Umbra2D::Gui::Logger::gui() {
	ImGui::Begin("Logger");

	for (const auto& log : logs)
		ImGui::TextColored(flagColors[log.second], "%s", log.first.c_str());
	
	ImGui::End();
}

