#include "gui/leftPanel.hpp"

#include <imgui/imgui.h>

LeftPanel::LeftPanel(Scene& scene, const glm::ivec2& viewportSize) :
	m_scene{scene},
	m_viewportSize{viewportSize}
{ }

void LeftPanel::update()
{
	ImGui::SetNextWindowPos({0, 0}, ImGuiCond_Always);
	ImGui::SetNextWindowSize({width, static_cast<float>(m_viewportSize.y)}, ImGuiCond_Always);
	ImGui::SetNextWindowBgAlpha(0.5f);
	ImGui::Begin("leftPanel", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
	ImGui::PushItemWidth(100);

	static const std::string suffix = "##leftPanel";

	static constexpr float stepPrecision = 0.1f;
	static const std::string format = "%.1f";

	float cameraRadius = m_scene.getRadiusCamera();
	float prevCameraRadius = cameraRadius;

	ImGui::InputFloat(("distance" + suffix).c_str(), &cameraRadius, stepPrecision, stepPrecision,
		format.c_str());

	if (cameraRadius != prevCameraRadius && cameraRadius > 0)
	{
		m_scene.setRadiusCamera(cameraRadius);
	}

	separator();

	float blackHoleMass = m_scene.getBlackHoleMass();
	float prevBlackHoleMass = blackHoleMass;

	ImGui::InputFloat(("mass" + suffix).c_str(), &blackHoleMass, stepPrecision, stepPrecision,
		format.c_str());

	if (blackHoleMass != prevBlackHoleMass && blackHoleMass > 0)
	{
		m_scene.setBlackHoleMass(blackHoleMass);
	}

	ImGui::PopItemWidth();
	ImGui::End();
}

void LeftPanel::separator()
{
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();
}
