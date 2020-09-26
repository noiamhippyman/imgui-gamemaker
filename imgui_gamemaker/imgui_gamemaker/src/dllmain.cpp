#include <Windows.h>
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx11.h"
#include "../imgui/imgui_impl_win32.h"

#define fn_export extern "C" __declspec(dllexport)


float* gm_send_buffer; // used to send arrays of data from GM to C++
float* gm_return_buffer; // used to return arrays of data from C++ to GM


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK ImGuiGMSSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam,
	LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData) {

	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) {
		return true;
	}

	return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}


// Main
fn_export double imgui_send_buffers(void* send_buffer, void* return_buffer) {
	gm_send_buffer = (float*)send_buffer;
	gm_return_buffer = (float*)return_buffer;
	
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
	bool _open = (bool)open;
	ImGui::ShowDemoWindow((bool*)&_open);
	return (double)(_open);
}

fn_export double imgui_show_about_window(double open) {
	bool _open = (bool)open;
	ImGui::ShowAboutWindow((bool*)&_open);
	return (double)(_open);
}

fn_export double imgui_show_metrics_window(double open) {
	bool _open = (bool)open;
	ImGui::ShowMetricsWindow((bool*)&_open);
	return (double)(_open);
}

fn_export double imgui_show_style_editor() {
	ImGui::ShowStyleEditor();
	return 0.0;
}

fn_export double imgui_show_style_selector(const char* label) {
	return (double)(ImGui::ShowStyleSelector(label));
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
	bool _open = (bool)open;
	bool expanded = ImGui::Begin(name,&_open,(ImGuiWindowFlags)flags);

	gm_return_buffer[0] = (float)expanded;
	gm_return_buffer[1] = (float)_open;
	
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

	return (double)(expanded);
}

fn_export double imgui_end_child() {
	ImGui::EndChild();
	return 0.0;
}


// Windows Utilities
fn_export double imgui_is_window_appearing() {
	return (double)(ImGui::IsWindowAppearing());
}

fn_export double imgui_is_window_collapsed() {
	return (double)(ImGui::IsWindowCollapsed());
}

fn_export double imgui_is_window_focused(double flags) {
	return (double)(ImGui::IsWindowFocused((ImGuiFocusedFlags)flags));
}

fn_export double imgui_is_window_hovered(double flags) {
	return (double)(ImGui::IsWindowHovered((ImGuiHoveredFlags)flags));
}

fn_export double imgui_get_window_dpi_scale() {
	return ImGui::GetWindowDpiScale();
}

fn_export double imgui_get_window_pos() {
	ImVec2 pos = ImGui::GetWindowPos();

	gm_return_buffer[0] = pos.x;
	gm_return_buffer[1] = pos.y;

	return 0.0;
}

fn_export double imgui_get_window_size() {
	ImVec2 size = ImGui::GetWindowSize();

	gm_return_buffer[0] = size.x;
	gm_return_buffer[1] = size.y;

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
	bool col = (bool)collapsed;
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
	bool col = (bool)collapsed;
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
	bool col = (bool)collapsed;
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

	gm_return_buffer[0] = region.x;
	gm_return_buffer[1] = region.y;

	return 0.0;
}

fn_export double imgui_get_content_region_avail() {
	ImVec2 region = ImGui::GetContentRegionAvail();

	gm_return_buffer[0] = region.x;
	gm_return_buffer[1] = region.y;

	return 0.0;
}

fn_export double imgui_get_window_content_region_min() {
	ImVec2 region = ImGui::GetWindowContentRegionMin();

	gm_return_buffer[0] = region.x;
	gm_return_buffer[1] = region.y;

	return 0.0;
}

fn_export double imgui_get_window_content_region_max() {
	ImVec2 region = ImGui::GetWindowContentRegionMax();

	gm_return_buffer[0] = region.x;
	gm_return_buffer[1] = region.y;

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
fn_export double imgui_push_style_color(double id, double r, double g, double b, double a) {
	ImVec4 col(r, g, b, a);
	ImGui::PushStyleColor((ImGuiCol)id, col);
	return 0.0;
}

fn_export double imgui_pop_style_color(double count) {
	ImGui::PopStyleColor(count);
	return 0.0;
}

fn_export double imgui_push_style_var_f(double id, double val) {
	ImGui::PushStyleVar((ImGuiCol)id, val);
	return 0.0;
}

fn_export double imgui_push_style_var_f2(double id, double x, double y) {
	ImVec2 val(x, y);
	ImGui::PushStyleVar((ImGuiCol)id, val);
	return 0.0;
}

fn_export double imgui_pop_style_var(double count) {
	ImGui::PopStyleVar(count);
	return 0.0;
}

fn_export double imgui_get_style_color_vec4(double id) {
	ImVec4 color = ImGui::GetStyleColorVec4((ImGuiCol)id);

	gm_return_buffer[0] = color.x;
	gm_return_buffer[1] = color.y;
	gm_return_buffer[2] = color.z;
	gm_return_buffer[3] = color.w;

	return 0.0;
}

fn_export double imgui_get_font_size() {
	return ImGui::GetFontSize();
}

fn_export double imgui_get_font_tex_uv_white_pixel() {
	ImVec2 ret = ImGui::GetFontTexUvWhitePixel();
	
	gm_return_buffer[0] = ret.x;
	gm_return_buffer[1] = ret.y;

	return 0.0;
}

fn_export double imgui_get_color_u32_id(double id, double alpha_mul) {
	return ImGui::GetColorU32((ImGuiCol)id, alpha_mul);
}

fn_export double imgui_get_color_u32_f4(double r, double g, double b, double a) {
	ImVec4 col(r, g, b, a);
	return ImGui::GetColorU32(col);
}


// Parameter Stacks (Current Window)
fn_export double imgui_push_item_width(double item_width) {
	ImGui::PushItemWidth(item_width);
	return 0.0;
}

fn_export double imput_pop_item_width() {
	ImGui::PopItemWidth();
	return 0.0;
}

fn_export double imgui_set_next_item_width(double item_width) {
	ImGui::SetNextItemWidth(item_width);
	return 0.0;
}

fn_export double imgui_calc_item_width() {
	return ImGui::CalcItemWidth();
}

fn_export double imgui_push_text_wrap_pos(double wrap_local_pos_x) {
	ImGui::PushTextWrapPos(wrap_local_pos_x);
	return 0.0;
}

fn_export double imgui_pop_text_wrap_pos() {
	ImGui::PopTextWrapPos();
	return 0.0;
}

fn_export double imgui_push_allow_keyboard_focus(double allow_keyboard_focus) {
	bool allow = (bool)allow_keyboard_focus;
	ImGui::PushAllowKeyboardFocus(allow);
	return 0.0;
}

fn_export double imgui_pop_allow_keyboard_focus() {
	ImGui::PopAllowKeyboardFocus();
	return 0.0;
}

fn_export double imgui_push_button_repeat(double repeat) {
	bool r = (bool)repeat;
	ImGui::PushButtonRepeat(r);
	return 0.0;
}

fn_export double imgui_pop_button_repeat() {
	ImGui::PopButtonRepeat();
	return 0.0;
}


// Cursor/Layout
fn_export double imgui_separator() {
	ImGui::Separator();
	return 0.0;
}

fn_export double imgui_same_line(double offset_from_start_x, double spacing) {
	ImGui::SameLine(offset_from_start_x, spacing);
	return 0.0;
}

fn_export double imgui_new_line() {
	ImGui::NewLine();
	return 0.0;
}

fn_export double imgui_spacing() {
	ImGui::Spacing();
	return 0.0;
}

fn_export double imgui_dummy(double width, double height) {
	ImVec2 size(width, height);
	ImGui::Dummy(size);
	return 0.0;
}

fn_export double imgui_indent(double indent_w) {
	ImGui::Indent(indent_w);
	return 0.0;
}

fn_export double imgui_unindent(double indent_w) {
	ImGui::Unindent(indent_w);
	return 0.0;
}

fn_export double imgui_begin_group() {
	ImGui::BeginGroup();
	return 0.0;
}

fn_export double imgui_end_group() {
	ImGui::EndGroup();
	return 0.0;
}

fn_export double imgui_get_cursor_pos() {
	ImVec2 pos = ImGui::GetCursorPos();

	gm_return_buffer[0] = pos.x;
	gm_return_buffer[0] = pos.y;

	return 0.0;
}

fn_export double imgui_get_cursor_pos_x() {
	return ImGui::GetCursorPosX();
}

fn_export double imgui_get_cursor_pos_y() {
	return ImGui::GetCursorPosY();
}

fn_export double imgui_set_cursor_pos(double x, double y) {
	ImVec2 pos(x, y);
	ImGui::SetCursorPos(pos);
	return 0.0;
}

fn_export double imgui_set_cursor_pos_x(double x) {
	ImGui::SetCursorPosX(x);
	return 0.0;
}

fn_export double imgui_set_cursor_pos_y(double y) {
	ImGui::SetCursorPosY(y);
	return 0.0;
}

fn_export double imgui_get_cursor_start_pos() {
	ImVec2 pos = ImGui::GetCursorStartPos();

	gm_return_buffer[0] = pos.x;
	gm_return_buffer[1] = pos.y;

	return 0.0;
}

fn_export double imgui_get_cursor_screen_pos() {
	ImVec2 pos = ImGui::GetCursorScreenPos();

	gm_return_buffer[0] = pos.x;
	gm_return_buffer[1] = pos.y;

	return 0.0;
}

fn_export double imgui_set_cursor_screen_pos(double x, double y) {
	ImVec2 pos(x, y);
	ImGui::SetCursorScreenPos(pos);
	return 0.0;
}

fn_export double imgui_align_text_to_frame_padding() {
	ImGui::AlignTextToFramePadding();
	return 0.0;
}

fn_export double imgui_get_text_line_height() {
	return ImGui::GetTextLineHeight();
}

fn_export double imgui_get_text_line_height_with_spacing() {
	return ImGui::GetTextLineHeightWithSpacing();
}

fn_export double imgui_get_frame_height() {
	return ImGui::GetFrameHeight();
}

fn_export double imgui_get_frame_height_with_spacing() {
	return ImGui::GetFrameHeightWithSpacing();
}


// ID stack/scopes
fn_export double imgui_push_id_str(const char* str_id) {
	ImGui::PushID(str_id);
	return 0.0;
}

fn_export double imgui_push_id_begin_end(const char* str_id_begin, const char* str_id_end) {
	ImGui::PushID(str_id_begin, str_id_end);
	return 0.0;
}

fn_export double imgui_push_id(double id) {
	ImGui::PushID(id);
	return 0.0;
}

fn_export double imgui_pop_id() {
	ImGui::PopID();
	return 0.0;
}

fn_export double imgui_get_id_str(const char* str_id) {
	return ImGui::GetID(str_id);
}

fn_export double imgui_get_id_begin_end(const char* str_id_begin, const char* str_id_end) {
	return ImGui::GetID(str_id_begin, str_id_end);
}


// Widgets: Text
fn_export double imgui_text_unformatted(const char* text) {
	ImGui::TextUnformatted(text, NULL);
	return 0.0;
}

fn_export double imgui_text(const char* text) {
	ImGui::Text(text);
	return 0.0;
}

fn_export double imgui_text_colored(double imu32_color, const char* text) {
	ImVec4 col = ImGui::ColorConvertU32ToFloat4((ImU32)imu32_color);
	ImGui::TextColored(col, text);
	return 0.0;
}

fn_export double imgui_text_disabled(const char* text) {
	ImGui::TextDisabled(text);
	return 0.0;
}

fn_export double imgui_text_wrapped(const char* text) {
	ImGui::TextWrapped(text);
	return 0.0;
}

fn_export double imgui_label_text(const char* label, const char* text) {
	ImGui::LabelText(label,text);
	return 0.0;
}

fn_export double imgui_bullet_text(const char* text) {
	ImGui::BulletText(text);
	return 0.0;
}


// Widgets: Main
fn_export double imgui_button(const char* label, double width, double height) {
	ImVec2 size(width, height);
	return (double)(ImGui::Button(label,size));
}

fn_export double imgui_small_button(const char* label) {
	return (double)(ImGui::SmallButton(label));
}

fn_export double imgui_invisible_button(const char* str_id, double width, double height, double flags) {
	ImVec2 size(width, height);
	return (double)(ImGui::InvisibleButton(str_id, size, (ImGuiButtonFlags)flags));
}

fn_export double imgui_checkbox(const char* label, double checked) {
	bool v = (bool)checked;
	bool changed = ImGui::Checkbox(label, &v);

	gm_return_buffer[0] = (float)changed;
	gm_return_buffer[1] = (float)v;

	return 0.0;
}

fn_export double imgui_checkbox_flags(const char* label, double flags, double flags_value) {
	unsigned int _flags = (unsigned int)flags;
	bool changed = ImGui::CheckboxFlags(label, &_flags, flags_value);

	gm_return_buffer[0] = (float)changed;
	gm_return_buffer[1] = (float)_flags;

	return 0.0;
}

fn_export double imgui_radio_button(const char* label, double active) {
	bool _active = (bool)active;
	return (double)(ImGui::RadioButton(label, _active));
}

fn_export double imgui_radio_button_int(const char* label, double v, double v_button) {
	int iv = (int)v;
	int iv_button = (int)v_button;
	bool changed = ImGui::RadioButton(label, &iv, iv_button);

	gm_return_buffer[0] = (float)changed;
	gm_return_buffer[1] = (float)iv;

	return 0.0;
}

fn_export double imgui_progress_bar(double fraction, double width, double height, const char* overlay = NULL) {
	ImVec2 size(width, height);
	ImGui::ProgressBar(fraction, size, overlay);
	return 0.0;
}

fn_export double imgui_bullet() {
	ImGui::Bullet();
	return 0.0;
}


// Widgets: Combo Box
fn_export double imgui_begin_combo(const char* label, const char* preview_value, double flags) {
	return (double)(ImGui::BeginCombo(label, preview_value, (ImGuiComboFlags)flags));
}

fn_export double imgui_end_combo() {
	ImGui::EndCombo();
	return 0.0;
}

//fn_export double imgui_combo(const char* label, double current_item, const char* items_separated_by_zeros, double popup_max_height_in_items) {
//	int i = (int)current_item;
//
//	bool changed = ImGui::Combo(label, &i, items_separated_by_zeros, (int)popup_max_height_in_items);
//
//	gm_return_buffer[0] = (float)changed;
//	gm_return_buffer[1] = (float)i;
//
//	return 0.0;
//}

// Widgets: Drag Sliders
fn_export double imgui_drag_float(const char* label, )


// Widgets: Regular Sliders


// Widgets: Input with Keyboard


// Widgets: Color Editor/Picker


// Widgets: Trees


// Widgets: Selectables


// Widgets: List Boxes


// Widgets: Data Plotting


// Widgets: Value() Helpers


// Widgets: Menus


// Tooltips


// Popups, Modals


// Columns


// Tab Bars, Tabs


// Logging/Capture


// Drag and Drop


// Clipping


// Focus, Activation


// Item/Widgets Utilities


// Miscellaneous Utilities


// Text Utilities


// Color Utilities


// Input Utilities: Keyboard


// Input Utilities: Mouse


// Clipboard Utilities


// Settings/.INI Utilities


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