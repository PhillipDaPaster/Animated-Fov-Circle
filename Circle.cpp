#define M_PI 3.14159265358979323846

void Anim_circle(float radius) {
	ImGuiIO& io = ImGui::GetIO();
	ImVec2 center(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f);
	ImDrawList* drawList = ImGui::GetForegroundDrawList();

	float timeFactor = fmod(ImGui::GetTime(), 5.0f) / 5.0f;

	for (int i = 0; i < sides; ++i) {
		ImVec2 pos(center.x, center.y);
		ImU32 currentColor = ImGui::ColorConvertFloat4ToU32(ImColor::HSV((timeFactor - i / static_cast<float>(sides)) + 1.0f, 0.5f, 1.0f));

		float angle = (i / static_cast<float>(sides)) * 2 * M_PI;
		ImVec2 lastPos(pos.x + cos(angle) * radius, pos.y + sin(angle) * radius);
		ImVec2 nextPos(pos.x + cos(angle + 2 * M_PI / sides) * radius, pos.y + sin(angle + 2 * M_PI / sides) * radius);

		drawList->AddLine(lastPos, nextPos, IM_COL32(0, 0, 0, 255), 4.f);//outline | очертание

		drawList->AddLine(lastPos, nextPos, currentColor, 2.f); //main | главный
	}
}

//example | пример
Anim_circle(90.f);
