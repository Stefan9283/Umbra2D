#include "..\..\Include\Gui\Logger.h"

Umbra2D::Gui::Logger::Logger() {
	addFlag("status", {106, 192, 180, 1});
	addFlag("success", {0, 255, 0, 1});
	addFlag("warning", {238, 237, 0, 1});
	addFlag("error", {255, 0, 0, 1});
}

void Umbra2D::Gui::Logger::addFlag(std::string flag, ImVec4 color) {
	flagColors[flag] = color;
}

void Umbra2D::Gui::Logger::addLog(std::string flag, std::string log) {
	if (logs.size() > MAX_LEN)
		logs.erase(logs.begin());

	auto currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::stringstream ss;

	ss << std::put_time(std::localtime(&currentTime), "%X");
	logs.push_back({ "[" + ss.str() + "] " + log, flag});
}

void Umbra2D::Gui::Logger::gui() {
	ImGui::Begin("Logger");

	for (const auto& log : logs)
		ImGui::TextColored(flagColors[log.second], log.first.c_str());
	
	ImGui::End();
}
