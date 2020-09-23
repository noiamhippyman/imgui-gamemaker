#include <Windows.h>
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx11.h"
#include "../imgui/imgui_impl_win32.h"

#define fn_export extern "C" __declspec(dllexport)

float* gm_vec_buffer; // used to return vec2/vec3/vec4
unsigned char* gm_bool_buffer; // used to return booleans

bool gm_double_to_bool(double d) {
	return (d > 0.0);
}

double gm_bool_to_double(bool b) {
	return b ? 1.0 : 0.0;
}


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK ImGuiGMSSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam,
	LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData) {

	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) {
		return true;
	}

	return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}


// Main
fn_export double imgui_send_buffers(void* vec_buffer, void* bool_buffer) {
	gm_vec_buffer = (float*)vec_buffer;
	gm_bool_buffer = (unsigned char*)bool_buffer;
	return 0.0;
}

fn_export double imgui_setup(char* hwnd, char* device, char* device_context) {

	// setup context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	
	// Enable keyboard navigation, docking, and viewports
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	// setup style
	ImGui::StyleColorsDark();

	// tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 0.0f;
	style.Colors[ImGuiCol_WindowBg].w = 1.0f;

	// setup platform/renderer bindings
	ImGui_ImplWin32_Init((void*)hwnd);
	ImGui_ImplDX11_Init((ID3D11Device*)device, (ID3D11DeviceContext*)device_context);

	// Subclass GM window to update keyboard/mouse/etc events
	SetWindowSubclass((HWND)hwnd, ImGuiGMSSubclassProc, 1, 1);

	return 0.0;
}

fn_export double imgui_cleanup(char* hwnd) {

	RemoveWindowSubclass((HWND)hwnd, ImGuiGMSSubclassProc, 1);

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	return 0.0;
}

fn_export double imgui_newframe() {

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	return 0.0;
}

fn_export double imgui_render() {

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}

	return 0.0;

}

// Demo, Debug, Information
fn_export double imgui_show_demo_window(double open) {
	bool _open = gm_double_to_bool(open);
	ImGui::ShowDemoWindow((bool*)&_open);
	return gm_bool_to_double(_open);
}

fn_export double imgui_show_about_window(double open) {
	bool _open = gm_double_to_bool(open);
	ImGui::ShowAboutWindow((bool*)&_open);
	return gm_bool_to_double(_open);
}

fn_export double imgui_show_metrics_window(double open) {
	bool _open = gm_double_to_bool(open);
	ImGui::ShowMetricsWindow((bool*)&_open);
	return gm_bool_to_double(_open);
}

fn_export double imgui_show_style_editor() {
	ImGui::ShowStyleEditor();
	return 0.0;
}

fn_export double imgui_show_style_selector(const char* label) {
	return gm_bool_to_double(ImGui::ShowStyleSelector(label));
}

fn_export double imgui_show_font_selector(const char* label) {
	ImGui::ShowFontSelector(label);
	return 0.0;
}

fn_export double imgui_show_user_guide() {
	ImGui::ShowUserGuide();
	return 0.0;
}

fn_export const char* imgui_get_version() {
	return ImGui::GetVersion();
}


// Styles
fn_export double imgui_style_colors_dark() {
	ImGui::StyleColorsDark();
	return 0.0;
}

fn_export double imgui_style_colors_classic() {
	ImGui::StyleColorsClassic();
	return 0.0;
}

fn_export double imgui_style_colors_light() {
	ImGui::StyleColorsLight();
	return 0.0;
}


// Windows
fn_export double imgui_begin(const char* name, double open, double flags) {
	bool _open = gm_double_to_bool(open);
	bool expanded = ImGui::Begin(name,&_open,(ImGuiWindowFlags)flags);
	
	//bool* b = (bool*)gm_bool_buffer;
	//b[0] = expanded;
	//b[1] = _open;
	gm_bool_buffer[0] = expanded;
	gm_bool_buffer[1] = _open;
	
	return 0.0;
}

fn_export double imgui_end() {
	ImGui::End();
	return 0.0;
}


// Child Windows
fn_export double imgui_begin_child(double id, double width, double height, double border, double flags) {
	ImVec2 size(width, height);

	bool expanded = ImGui::BeginChild((ImGuiID)id, size, border, (ImGuiWindowFlags)flags);

	return gm_bool_to_double(expanded);
}

fn_export double imgui_end_child() {
	ImGui::EndChild();
	return 0.0;
}


// Windows Utilities
fn_export double imgui_is_window_appearing() {
	return gm_bool_to_double(ImGui::IsWindowAppearing());
}

fn_export double imgui_is_window_collapsed() {
	return gm_bool_to_double(ImGui::IsWindowCollapsed());
}

fn_export double imgui_is_window_focused(double flags) {
	return gm_bool_to_double(ImGui::IsWindowFocused((ImGuiFocusedFlags)flags));
}

fn_export double imgui_is_window_hovered(double flags) {
	return gm_bool_to_double(ImGui::IsWindowHovered((ImGuiHoveredFlags)flags));
}

fn_export double imgui_get_window_dpi_scale() {
	return ImGui::GetWindowDpiScale();
}

fn_export double imgui_get_window_pos() {
	ImVec2 pos = ImGui::GetWindowPos();

	gm_vec_buffer[0] = pos.x;
	gm_vec_buffer[1] = pos.y;

	return 0.0;
}

fn_export double imgui_get_window_size() {
	ImVec2 size = ImGui::GetWindowSize();

	gm_vec_buffer[0] = size.x;
	gm_vec_buffer[1] = size.y;

	return 0.0;
}

fn_export double imgui_get_window_width() {
	return ImGui::GetWindowWidth();
}

fn_export double imgui_get_window_height() {
	return ImGui::GetWindowHeight();
}

fn_export double imgui_set_next_window_pos(double x, double y, double cond, double pivot_x, double pivot_y) {
	ImVec2 pos(x, y);
	ImVec2 pivot(pivot_x, pivot_y);
	ImGui::SetNextWindowPos(pos, (ImGuiCond)cond, pivot);
	return 0.0;
}

fn_export double imgui_set_next_window_size(double width, double height, double cond) {
	ImVec2 size(width, height);
	ImGui::SetNextWindowSize(size, (ImGuiCond)cond);
	return 0.0;
}

fn_export double imgui_set_next_window_content_size(double width, double height) {
	ImVec2 size(width, height);
	ImGui::SetNextWindowContentSize(size);
	return 0.0;
}

fn_export double imgui_set_next_window_collapsed(double collapsed, double cond) {
	bool col = gm_double_to_bool(collapsed);
	ImGui::SetNextWindowCollapsed(col, cond);
	return 0.0;
}

fn_export double imgui_set_next_window_focus() {
	ImGui::SetNextWindowFocus();
	return 0.0;
}

fn_export double imgui_set_next_window_bg_alpha(double alpha) {
	ImGui::SetNextWindowBgAlpha(alpha);
	return 0.0;
}

fn_export double imgui_set_next_window_viewport(double id) {
	ImGui::SetNextWindowViewport((ImGuiID)id);
	return 0.0;
}

fn_export double imgui_set_window_pos(double x, double y, double cond) {
	ImVec2 pos(x, y);
	ImGui::SetWindowPos(pos, (ImGuiCond)cond);
	return 0.0;
}

fn_export double imgui_set_window_size(double width, double height, double cond) {
	ImVec2 size(width, height);
	ImGui::SetWindowSize(size, (ImGuiCond)cond);
	return 0.0;
}

fn_export double imgui_set_window_collapsed(double collapsed, double cond) {
	bool col = gm_double_to_bool(collapsed);
	ImGui::SetWindowCollapsed(col, (ImGuiCond)cond);
	return 0.0;
}

fn_export double imgui_set_window_focus() {
	ImGui::SetWindowFocus();
	return 0.0;
}

fn_export double imgui_set_window_font_scale(double scale) {
	ImGui::SetWindowFontScale(scale);
	return 0.0;
}

fn_export double imgui_set_window_pos_named(const char* name, double x, double y, double cond) {
	ImVec2 pos(x, y);
	ImGui::SetWindowPos(name, pos, (ImGuiCond)cond);
	return 0.0;
}

fn_export double imgui_set_window_size_named(const char* name, double width, double height, double cond) {
	ImVec2 size(width, height);
	ImGui::SetWindowSize(name, size, (ImGuiCond)cond);
	return 0.0;
}

fn_export double imgui_set_window_collapsed_named(const char* name, double collapsed, double cond) {
	bool col = gm_double_to_bool(collapsed);
	ImGui::SetWindowCollapsed(name, col, (ImGuiCond)cond);
	return 0.0;
}

fn_export double imgui_set_window_focus_named(const char* name) {
	ImGui::SetWindowFocus(name);
	return 0.0;
}


// Content Region
fn_export double imgui_get_content_region_max() {
	ImVec2 region = ImGui::GetContentRegionMax();

	gm_vec_buffer[0] = region.x;
	gm_vec_buffer[1] = region.y;

	return 0.0;
}

fn_export double imgui_get_content_region_avail() {
	ImVec2 region = ImGui::GetContentRegionAvail();

	gm_vec_buffer[0] = region.x;
	gm_vec_buffer[1] = region.y;

	return 0.0;
}

fn_export double imgui_get_window_content_region_min() {
	ImVec2 region = ImGui::GetWindowContentRegionMin();

	gm_vec_buffer[0] = region.x;
	gm_vec_buffer[1] = region.y;

	return 0.0;
}

fn_export double imgui_get_window_content_region_max() {
	ImVec2 region = ImGui::GetWindowContentRegionMax();

	gm_vec_buffer[0] = region.x;
	gm_vec_buffer[1] = region.y;

	return 0.0;
}

fn_export double imgui_get_window_content_region_width() {
	return ImGui::GetWindowContentRegionWidth();
}


// Windows Scrolling
fn_export double imgui_get_scroll_x() {
	return ImGui::GetScrollX();
}

fn_export double imgui_get_scroll_y() {
	return ImGui::GetScrollY();
}

fn_export double imgui_get_scroll_max_x() {
	return ImGui::GetScrollMaxX();
}

fn_export double imgui_get_scroll_max_y() {
	return ImGui::GetScrollMaxY();
}

fn_export double imgui_set_scroll_x(double scroll_x) {
	ImGui::SetScrollX(scroll_x);
	return 0.0;
}

fn_export double imgui_set_scroll_y(double scroll_y) {
	ImGui::SetScrollY(scroll_y);
	return 0.0;
}

fn_export double imgui_set_scroll_here_x(double center_x_ratio) {
	ImGui::SetScrollHereX(center_x_ratio);
	return 0.0;
}

fn_export double imgui_set_scroll_here_y(double center_y_ratio) {
	ImGui::SetScrollHereY(center_y_ratio);
	return 0.0;
}

fn_export double imgui_set_scroll_from_pos_x(double local_x, double center_x_ratio) {
	ImGui::SetScrollFromPosX(local_x, center_x_ratio);
	return 0.0;
}

fn_export double imgui_set_scroll_from_pos_y(double local_y, double center_y_ratio) {
	ImGui::SetScrollFromPosY(local_y, center_y_ratio);
	return 0.0;
}


// Parameter Stacks (Shared)

// Parameter Stacks (Current Window)

// Cursor / Layout
// - By "cursor" we mean the current output position.
// - The typical widget behavior is to output themselves at the current cursor position, then move the cursor one line down.
// - You can call SameLine() between widgets to undo the last carriage return and output at the right of the preceding widget.
// - Attention! We currently have inconsistencies between window-local and absolute positions we will aim to fix with future API:
//    Window-local coordinates:   SameLine(), GetCursorPos(), SetCursorPos(), GetCursorStartPos(), GetContentRegionMax(), GetWindowContentRegion*(), PushTextWrapPos()
//    Absolute coordinate:        GetCursorScreenPos(), SetCursorScreenPos(), all ImDrawList:: functions.

fn_export double imgui_text(const char* text) {
	ImGui::Text(text);
	return 0.0;
}

fn_export double imgui_button(const char* label, double width, double height) {
	ImVec2 size(width, height);
	return (double)ImGui::Button(label,size);
}

//fn_export double buffer_fiddle(void* buffer) {
//	float* _b = (float*)buffer;
//	_b[0] = 100.1;
//	_b[1] = 1000.01;
//	_b[2] = 10000.001;
//	_b[3] = 100000.0001;
//	_b[4] = 1000000.00001;
//
//	return 0.0;
//}

BOOL WINAPI DllMain(
	HINSTANCE hinstDLL,  // handle to DLL module
	DWORD fdwReason,     // reason for calling function
	LPVOID lpReserved)  // reserved
{
	// Perform actions based on the reason for calling.
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		// Initialize once for each new process.
		// Return FALSE to fail DLL load.
		// Somehow hook into WndProc message handler. Still reading shit. 
		break;

	case DLL_THREAD_ATTACH:
		// Do thread-specific initialization.
		break;

	case DLL_THREAD_DETACH:
		// Do thread-specific cleanup.
		break;

	case DLL_PROCESS_DETACH:
		// Perform any necessary cleanup.
		break;
	}
	return TRUE;  // Successful DLL_PROCESS_ATTACH.
}