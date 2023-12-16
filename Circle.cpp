#define M_PI 3.14159265358979323846

static float radius = 200.f;
static bool fill = false;
static bool Rainbow = false;
static bool toMouse = false;

void Anim_circle(float r, bool filled, bool rainbow, bool toMouse) {
	auto& io = ImGui::GetIO();

	ImVec2 center = toMouse ? ImVec2(io.MousePos.x, io.MousePos.y) : ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f);
	auto drawList = ImGui::GetBackgroundDrawList();

	for (int i = 0; i < sides; ++i) {
		auto pos = center;
		float angle = (i / static_cast<float>(sides)) * 2 * M_PI;
		auto lastPos = ImVec2(pos.x + cos(angle) * r, pos.y + sin(angle) * r);
		auto nextPos = ImVec2(pos.x + cos(angle + 2 * M_PI / sides) * r, pos.y + sin(angle + 2 * M_PI / sides) * r);

		ImU32 currentColor = rainbow ? ImGui::ColorConvertFloat4ToU32(ImColor::HSV((fmod(ImGui::GetTime(), 5.0f) / 5.0f - i / static_cast<float>(sides)) + 1.0f, 0.5f, 1.0f)): IM_COL32(255, 255, 255, 255);

		ImU32 fillCol = filled ? ImGui::ColorConvertFloat4ToU32({ ImGui::ColorConvertU32ToFloat4(currentColor).x, ImGui::ColorConvertU32ToFloat4(currentColor).y, ImGui::ColorConvertU32ToFloat4(currentColor).z, 0.2f }): 0; // 0.2f = fill opacity

		if (filled) {
			ImVec2 triangle[3] = { lastPos, nextPos, center };
			drawList->AddConvexPolyFilled(triangle, 3, fillCol); // fill
		}

		drawList->AddLine(lastPos, nextPos, IM_COL32(0, 0, 0, 255), 4.f); // outline | очертание
		drawList->AddLine(lastPos, nextPos, currentColor, 2.f); // main | главный
	}
}

//example | пример
Anim_circle(radius, fill, Rainbow, toMouse);
Anim_circle(200.f, false, false, false);
