#include <iostream>
#include <Windows.h>
#include <commctrl.h>
#include <vector>
#pragma comment(lib, "comctl32.lib")

#include "../imgui/imgui.h"
#include "../imgui/imgui_stdlib.h"
#include "../imgui/imgui_impl_dx11.h"
#include "../imgui/imgui_impl_win32.h"

#include "Buffer.h"

#define fn_export extern "C" __declspec(dllexport)

Buffer* ext_buffer = nullptr;

fn_export double extension_setup(void* buffer_ptr, double buffer_size) {
	ext_buffer = new Buffer(buffer_ptr, buffer_size);
	return 0.0;
}

fn_export double extension_cleanup() {
	delete ext_buffer;
	ext_buffer = nullptr;
	return 0.0;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK ImGuiGMSSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam,
	LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData) {

	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) {
		return true;
	}

	return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}



// IO Config
// TODO: Start adding functons to GMS extension
fn_export double imgui_io_set_config_flags(double flags) {
	ImGui::GetIO().ConfigFlags = (ImGuiConfigFlags)flags;
	return 0.0;
}

fn_export double imgui_io_get_config_flags() {
	return ImGui::GetIO().ConfigFlags;
}

fn_export double imgui_io_set_font_global_scale(double scale) {
	ImGui::GetIO().FontGlobalScale = scale;
	return 0.0;
}

fn_export double imgui_io_get_font_global_scale() {
	return ImGui::GetIO().FontGlobalScale;
}

fn_export double imgui_io_set_font_allow_user_scaling(double enable) {
	ImGui::GetIO().FontAllowUserScaling = enable;
	return 0.0;
}

fn_export double imgui_io_get_font_allow_user_scaling() {
	return ImGui::GetIO().FontAllowUserScaling;
}

fn_export double imgui_io_set_config_docking_no_split(double enable) {
	ImGui::GetIO().ConfigDockingNoSplit = enable;
	return 0.0;
}

fn_export double imgui_io_get_config_docking_no_split() {
	return ImGui::GetIO().ConfigDockingNoSplit;
}

fn_export double imgui_io_set_config_docking_with_shift(double enable) {
	ImGui::GetIO().ConfigDockingWithShift = enable;
	return 0.0;
}

fn_export double imgui_io_get_config_docking_with_shift() {
	return ImGui::GetIO().ConfigDockingWithShift;
}

fn_export double imgui_io_set_config_docking_always_tab_bar(double enable) {
	ImGui::GetIO().ConfigDockingAlwaysTabBar = enable;
	return 0.0;
}

fn_export double imgui_io_get_config_docking_always_tab_bar() {
	return ImGui::GetIO().ConfigDockingAlwaysTabBar;
}

fn_export double imgui_io_set_config_docking_transparent_payload(double enable) {
	ImGui::GetIO().ConfigDockingTransparentPayload = enable;
	return 0.0;
}

fn_export double imgui_io_get_config_docking_transparent_payload() {
	return ImGui::GetIO().ConfigDockingTransparentPayload;
}

fn_export double imgui_io_set_config_viewports_no_automerge(double enable) {
	ImGui::GetIO().ConfigViewportsNoAutoMerge = enable;
	return 0.0;
}

fn_export double imgui_io_get_config_viewports_no_automerge() {
	return ImGui::GetIO().ConfigViewportsNoAutoMerge;
}

fn_export double imgui_io_set_config_viewports_no_task_bar_icon(double enable) {
	ImGui::GetIO().ConfigViewportsNoTaskBarIcon = enable;
	return 0.0;
}

fn_export double imgui_io_get_config_viewports_no_task_bar_icon() {
	return ImGui::GetIO().ConfigViewportsNoTaskBarIcon;
}

fn_export double imgui_io_set_config_viewports_no_decoration(double enable) {
	ImGui::GetIO().ConfigViewportsNoDecoration = enable;
	return 0.0;
}

fn_export double imgui_io_get_config_viewports_no_decoration() {
	return ImGui::GetIO().ConfigViewportsNoDecoration;
}

fn_export double imgui_io_set_config_viewports_no_default_parent(double enable) {
	ImGui::GetIO().ConfigViewportsNoDefaultParent = enable;
	return 0.0;
}

fn_export double imgui_io_get_config_viewports_no_default_parent() {
	return ImGui::GetIO().ConfigViewportsNoDefaultParent;
}

fn_export double imgui_io_set_config_input_text_cursor_blink(double enable) {
	ImGui::GetIO().ConfigInputTextCursorBlink = enable;
	return 0.0;
}

fn_export double imgui_io_get_config_input_text_cursor_blink() {
	return ImGui::GetIO().ConfigInputTextCursorBlink;
}

fn_export double imgui_io_set_config_windows_resize_from_edges(double enable) {
	ImGui::GetIO().ConfigWindowsResizeFromEdges = enable;
	return 0.0;
}

fn_export double imgui_io_get_config_windows_resize_from_edges() {
	return ImGui::GetIO().ConfigWindowsResizeFromEdges;
}

fn_export double imgui_io_set_config_windows_move_from_title_bar_only(double enable) {
	ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly = enable;
	return 0.0;
}

fn_export double imgui_io_get_config_windows_move_from_title_bar_only() {
	return ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly;
}


// Style Config
fn_export double imgui_style_set_alpha(double alpha) {
	ImGui::GetStyle().Alpha = alpha;
	return 0.0;
}

fn_export double imgui_style_get_alpha() {
	return ImGui::GetStyle().Alpha;
}

fn_export double imgui_style_set_window_padding(double padx, double pady) {
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowPadding.x = padx;
	style.WindowPadding.y = pady;
	return 0.0;
}

fn_export double imgui_style_get_window_padding() {
	ImGuiStyle& style = ImGui::GetStyle();
	ext_buffer->seek(0);
	ext_buffer->write(style.WindowPadding.x);
	ext_buffer->write(style.WindowPadding.y);
	return 0.0;
}

fn_export double imgui_style_set_window_rounding(double rounding) {
	ImGui::GetStyle().WindowRounding = rounding;
	return 0.0;
}

fn_export double imgui_style_get_window_rounding() {
	return ImGui::GetStyle().WindowRounding;
}

fn_export double imgui_style_set_window_border_size(double border_size) {
	ImGui::GetStyle().WindowBorderSize = border_size;
	return 0.0;
}

fn_export double imgui_style_get_window_border_size() {
	return ImGui::GetStyle().WindowBorderSize;
}

fn_export double imgui_style_set_window_min_size(double minx, double miny) {
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowMinSize.x = minx;
	style.WindowMinSize.y = miny;
	return 0.0;
}

fn_export double imgui_style_get_window_min_size() {
	ImGuiStyle& style = ImGui::GetStyle();
	ext_buffer->seek(0);
	ext_buffer->write(style.WindowMinSize.x);
	ext_buffer->write(style.WindowMinSize.y);
	return 0.0;
}

fn_export double imgui_style_set_window_title_align(double alignx, double aligny) {
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowTitleAlign.x = alignx;
	style.WindowTitleAlign.y = aligny;
	return 0.0;
}

fn_export double imgui_style_get_window_title_align() {
	ImGuiStyle& style = ImGui::GetStyle();
	ext_buffer->seek(0);
	ext_buffer->write(style.WindowTitleAlign.x);
	ext_buffer->write(style.WindowTitleAlign.y);
	return 0.0;
}

fn_export double imgui_style_set_window_menu_button_position(double position) {
	ImGui::GetStyle().WindowMenuButtonPosition = position;
	return 0.0;
}

fn_export double imgui_style_get_window_menu_button_position() {
	return ImGui::GetStyle().WindowMenuButtonPosition;
}

fn_export double imgui_style_set_child_rounding(double rounding) {
	ImGui::GetStyle().ChildRounding = rounding;
	return 0.0;
}

fn_export double imgui_style_get_child_rounding() {
	return ImGui::GetStyle().ChildRounding;
}

fn_export double imgui_style_set_child_border_size(double border_size) {
	ImGui::GetStyle().ChildBorderSize = border_size;
	return 0.0;
}

fn_export double imgui_style_get_child_border_size() {
	return ImGui::GetStyle().ChildBorderSize;
}

fn_export double imgui_style_set_popup_rounding(double rounding) {
	ImGui::GetStyle().PopupRounding = rounding;
	return 0.0;
}

fn_export double imgui_style_get_popup_rounding() {
	return ImGui::GetStyle().PopupRounding;
}

fn_export double imgui_style_set_popup_border_size(double border_size) {
	ImGui::GetStyle().PopupBorderSize = border_size;
	return 0.0;
}

fn_export double imgui_style_get_popup_border_size() {
	return ImGui::GetStyle().PopupBorderSize;
}

fn_export double imgui_style_set_frame_padding(double padx, double pady) {
	ImGuiStyle& style = ImGui::GetStyle();
	style.FramePadding.x = padx;
	style.FramePadding.y = pady;
	return 0.0;
}

fn_export double imgui_style_get_frame_padding() {
	ImGuiStyle& style = ImGui::GetStyle();
	ext_buffer->seek(0);
	ext_buffer->write(style.FramePadding.x);
	ext_buffer->write(style.FramePadding.y);
	return 0.0;
}

fn_export double imgui_style_set_frame_rounding(double rounding) {
	ImGui::GetStyle().FrameRounding = rounding;
	return 0.0;
}

fn_export double imgui_style_get_frame_rounding() {
	return ImGui::GetStyle().FrameRounding;
}

fn_export double imgui_style_set_frame_border_size(double border_size) {
	ImGui::GetStyle().FrameBorderSize = border_size;
	return 0.0;
}

fn_export double imgui_style_get_frame_border_size() {
	return ImGui::GetStyle().FrameBorderSize;
}

fn_export double imgui_style_set_item_spacing(double spacex, double spacey) {
	ImGuiStyle& style = ImGui::GetStyle();
	style.ItemSpacing.x = spacex;
	style.ItemSpacing.y = spacey;
	return 0.0;
}

fn_export double imgui_style_get_item_spacing() {
	ImGuiStyle& style = ImGui::GetStyle();
	ext_buffer->seek(0);
	ext_buffer->write(style.ItemSpacing.x);
	ext_buffer->write(style.ItemSpacing.y);
	return 0.0;
}

fn_export double imgui_style_set_item_inner_spacing(double spacex, double spacey) {
	ImGuiStyle& style = ImGui::GetStyle();
	style.ItemInnerSpacing.x = spacex;
	style.ItemInnerSpacing.y = spacey;
	return 0.0;
}

fn_export double imgui_style_get_item_inner_spacing() {
	ImGuiStyle& style = ImGui::GetStyle();
	ext_buffer->seek(0);
	ext_buffer->write(style.ItemInnerSpacing.x);
	ext_buffer->write(style.ItemInnerSpacing.y);
	return 0.0;
}

fn_export double imgui_style_set_indent_spacing(double spacing) {
	ImGui::GetStyle().IndentSpacing = spacing;
	return 0.0;
}

fn_export double imgui_style_get_indent_spacing() {
	return ImGui::GetStyle().IndentSpacing;
}

fn_export double imgui_style_set_columns_min_spacing(double spacing) {
	ImGui::GetStyle().ColumnsMinSpacing = spacing;
	return 0.0;
}

fn_export double imgui_style_get_columns_min_spacing() {
	return ImGui::GetStyle().ColumnsMinSpacing;
}

fn_export double imgui_style_set_scrollbar_size(double size) {
	ImGui::GetStyle().ScrollbarSize = size;
	return 0.0;
}

fn_export double imgui_style_get_scrollbar_size() {
	return ImGui::GetStyle().ScrollbarSize;
}

fn_export double imgui_style_set_scrollbar_rounding(double rounding) {
	ImGui::GetStyle().ScrollbarRounding = rounding;
	return 0.0;
}

fn_export double imgui_style_get_scrollbar_rounding() {
	return ImGui::GetStyle().ScrollbarRounding;
}

fn_export double imgui_style_set_grab_min_size(double size) {
	ImGui::GetStyle().GrabMinSize = size;
	return 0.0;
}

fn_export double imgui_style_get_grab_min_size() {
	return ImGui::GetStyle().GrabMinSize;
}

fn_export double imgui_style_set_grab_rounding(double rounding) {
	ImGui::GetStyle().GrabRounding = rounding;
	return 0.0;
}

fn_export double imgui_style_get_grab_rounding() {
	return ImGui::GetStyle().GrabRounding;
}

fn_export double imgui_style_set_log_slider_deadzone(double deadzone) {
	ImGui::GetStyle().LogSliderDeadzone = deadzone;
	return 0.0;
}

fn_export double imgui_style_get_log_slider_deadzone() {
	return ImGui::GetStyle().LogSliderDeadzone;
}

fn_export double imgui_style_set_tab_rounding(double rounding) {
	ImGui::GetStyle().TabRounding = rounding;
	return 0.0;
}

fn_export double imgui_style_get_tab_rounding() {
	return ImGui::GetStyle().TabRounding;
}

fn_export double imgui_style_set_tab_border_size(double border_size) {
	ImGui::GetStyle().TabBorderSize = border_size;
	return 0.0;
}

fn_export double imgui_style_get_tab_border_size() {
	return ImGui::GetStyle().TabBorderSize;
}

fn_export double imgui_style_set_tab_min_width_for_unselected_close_button(double width) {
	ImGui::GetStyle().TabMinWidthForUnselectedCloseButton = width;
	return 0.0;
}

fn_export double imgui_style_get_tab_min_width_for_unselected_close_button() {
	return ImGui::GetStyle().TabMinWidthForUnselectedCloseButton;
}

fn_export double imgui_style_set_color_button_position(double position) {
	ImGui::GetStyle().ColorButtonPosition = position;
	return 0.0;
}

fn_export double imgui_style_get_color_button_position() {
	return ImGui::GetStyle().ColorButtonPosition;
}

fn_export double imgui_style_set_button_text_align(double alignx, double aligny) {
	ImGuiStyle& style = ImGui::GetStyle();
	style.ButtonTextAlign.x = alignx;
	style.ButtonTextAlign.y = aligny;
	return 0.0;
}

fn_export double imgui_style_get_button_text_align() {
	ImGuiStyle& style = ImGui::GetStyle();
	ext_buffer->seek(0);
	ext_buffer->write(style.ButtonTextAlign.x);
	ext_buffer->write(style.ButtonTextAlign.y);
	return 0.0;
}

fn_export double imgui_style_set_selectable_text_align(double alignx, double aligny) {
	ImGuiStyle& style = ImGui::GetStyle();
	style.SelectableTextAlign.x = alignx;
	style.SelectableTextAlign.y = aligny;
	return 0.0;
}

fn_export double imgui_style_get_selectable_text_align() {
	ImGuiStyle& style = ImGui::GetStyle();
	ext_buffer->seek(0);
	ext_buffer->write(style.SelectableTextAlign.x);
	ext_buffer->write(style.SelectableTextAlign.y);
	return 0.0;
}

fn_export double imgui_style_set_display_window_padding(double padx, double pady) {
	ImGuiStyle& style = ImGui::GetStyle();
	style.DisplayWindowPadding.x = padx;
	style.DisplayWindowPadding.y = pady;
	return 0.0;
}

fn_export double imgui_style_get_display_window_padding() {
	ImGuiStyle& style = ImGui::GetStyle();
	ext_buffer->seek(0);
	ext_buffer->write(style.DisplayWindowPadding.x);
	ext_buffer->write(style.DisplayWindowPadding.y);
	return 0.0;
}

fn_export double imgui_style_set_display_safe_area_padding(double padx, double pady) {
	ImGuiStyle& style = ImGui::GetStyle();
	style.DisplaySafeAreaPadding.x = padx;
	style.DisplaySafeAreaPadding.y = pady;
	return 0.0;
}

fn_export double imgui_style_get_display_safe_area_padding() {
	ImGuiStyle& style = ImGui::GetStyle();
	ext_buffer->seek(0);
	ext_buffer->write(style.DisplaySafeAreaPadding.x);
	ext_buffer->write(style.DisplaySafeAreaPadding.y);
	return 0.0;
}

fn_export double imgui_style_set_mouse_cursor_scale(double scale) {
	ImGui::GetStyle().MouseCursorScale = scale;
	return 0.0;
}

fn_export double imgui_style_get_mouse_cursor_scale() {
	return ImGui::GetStyle().MouseCursorScale;
}

fn_export double imgui_style_set_antialiased_lines(double enable) {
	ImGui::GetStyle().AntiAliasedLines = enable;
	return 0.0;
}

fn_export double imgui_style_get_antialiased_lines() {
	return ImGui::GetStyle().AntiAliasedLines;
}

fn_export double imgui_style_set_antialiased_fill(double enable) {
	ImGui::GetStyle().AntiAliasedFill = enable;
	return 0.0;
}

fn_export double imgui_style_get_antialiased_fill() {
	return ImGui::GetStyle().AntiAliasedFill;
}

fn_export double imgui_style_set_curve_tessellation_tol(double tolerance) {
	ImGui::GetStyle().CurveTessellationTol = tolerance;
	return 0.0;
}

fn_export double imgui_style_get_curve_tessellation_tol() {
	return ImGui::GetStyle().CurveTessellationTol;
}

fn_export double imgui_style_set_circle_segment_max_error(double max_error) {
	ImGui::GetStyle().CircleSegmentMaxError = max_error;
	return 0.0;
}

fn_export double imgui_style_get_circle_segment_max_error() {
	return ImGui::GetStyle().CircleSegmentMaxError;
}

fn_export double imgui_style_set_color(double idx, double r, double g, double b, double a) {
	ImGuiStyle& style = ImGui::GetStyle();
	ImVec4 col = style.Colors[(ImGuiCol)idx];
	col.x = r;
	col.y = g;
	col.z = b;
	col.w = a;
	return 0.0;
}

fn_export double imgui_style_get_color(double idx) {
	ImGuiStyle& style = ImGui::GetStyle();
	ImVec4 col = style.Colors[(ImGuiCol)idx];
	ext_buffer->seek(0);
	ext_buffer->write(col.x);
	ext_buffer->write(col.y);
	ext_buffer->write(col.z);
	ext_buffer->write(col.w);
	return 0.0;
}


// Main
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
	ImGui::ShowDemoWindow(&_open);
	return (double)_open;
}

fn_export double imgui_show_about_window(double open) {
	bool _open = (bool)open;
	ImGui::ShowAboutWindow(&_open);
	return (double)_open;
}

fn_export double imgui_show_metrics_window(double open) {
	bool _open = (bool)open;
	ImGui::ShowMetricsWindow(&_open);
	return (double)_open;
}

fn_export double imgui_show_style_editor() {
	ImGui::ShowStyleEditor();
	return 0.0;
}

fn_export double imgui_show_style_selector(const char* label) {
	return (double)ImGui::ShowStyleSelector(label);
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

	ext_buffer->seek(0);
	ext_buffer->write((float)expanded);
	ext_buffer->write((float)_open);
	
	return 0.0;
}

fn_export double imgui_end() {
	ImGui::End();
	return 0.0;
}


// Child Windows
fn_export double imgui_begin_child(double id, double width, double height, double border, double flags) {
	ImVec2 size;
	size.x = width;
	size.y = height;

	bool expanded = ImGui::BeginChild((ImGuiID)id, size, border, (ImGuiWindowFlags)flags);

	return (double)expanded;
}

fn_export double imgui_end_child() {
	ImGui::EndChild();
	return 0.0;
}


// Windows Utilities
fn_export double imgui_is_window_appearing() {
	return (double)ImGui::IsWindowAppearing();
}

fn_export double imgui_is_window_collapsed() {
	return (double)ImGui::IsWindowCollapsed();
}

fn_export double imgui_is_window_focused(double flags) {
	return (double)ImGui::IsWindowFocused((ImGuiFocusedFlags)flags);
}

fn_export double imgui_is_window_hovered(double flags) {
	return (double)ImGui::IsWindowHovered((ImGuiHoveredFlags)flags);
}

fn_export double imgui_get_window_dpi_scale() {
	return ImGui::GetWindowDpiScale();
}

fn_export double imgui_get_window_pos() {
	ImVec2 pos = ImGui::GetWindowPos();

	ext_buffer->seek(0);
	ext_buffer->write(pos.x);
	ext_buffer->write(pos.y);

	return 0.0;
}

fn_export double imgui_get_window_size() {
	ImVec2 size = ImGui::GetWindowSize();
	
	ext_buffer->seek(0);
	ext_buffer->write(size.x);
	ext_buffer->write(size.y);

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
	ImVec2 size;
	size.x = width;
	size.y = height;
	ImGui::SetNextWindowSize(size, (ImGuiCond)cond);
	return 0.0;
}

fn_export double imgui_set_next_window_content_size(double width, double height) {
	ImVec2 size;
	size.x = width;
	size.y = height;
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
	ImVec2 size;
	size.x = width;
	size.y = height;
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
	ImVec2 size;
	size.x = width;
	size.y = height;
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

	ext_buffer->seek(0);
	ext_buffer->write(region.x);
	ext_buffer->write(region.y);

	return 0.0;
}

fn_export double imgui_get_content_region_avail() {
	ImVec2 region = ImGui::GetContentRegionAvail();

	ext_buffer->seek(0);
	ext_buffer->write(region.x);
	ext_buffer->write(region.y);

	return 0.0;
}

fn_export double imgui_get_window_content_region_min() {
	ImVec2 region = ImGui::GetWindowContentRegionMin();

	ext_buffer->seek(0);
	ext_buffer->write(region.x);
	ext_buffer->write(region.y);

	return 0.0;
}

fn_export double imgui_get_window_content_region_max() {
	ImVec2 region = ImGui::GetWindowContentRegionMax();

	ext_buffer->seek(0);
	ext_buffer->write(region.x);
	ext_buffer->write(region.y);

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
	ImVec4 col;
	col.x = r;
	col.y = g;
	col.z = b;
	col.w = a;
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

	ext_buffer->seek(0);
	ext_buffer->write(color.x);
	ext_buffer->write(color.y);
	ext_buffer->write(color.z);
	ext_buffer->write(color.w);

	return 0.0;
}

fn_export double imgui_get_font_size() {
	return ImGui::GetFontSize();
}

fn_export double imgui_get_font_tex_uv_white_pixel() {
	ImVec2 ret = ImGui::GetFontTexUvWhitePixel();

	ext_buffer->seek(0);
	ext_buffer->write(ret.x);
	ext_buffer->write(ret.y);

	return 0.0;
}

fn_export double imgui_get_color_u32_id(double id, double alpha_mul) {
	return ImGui::GetColorU32((ImGuiCol)id, alpha_mul);
}

fn_export double imgui_get_color_u32_f4(double r, double g, double b, double a) {
	ImVec4 col;
	col.x = r;
	col.y = g;
	col.z = b;
	col.w = a;
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
	ImVec2 size;
	size.x = width;
	size.y = height;
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

	ext_buffer->seek(0);
	ext_buffer->write(pos.x);
	ext_buffer->write(pos.y);

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

	ext_buffer->seek(0);
	ext_buffer->write(pos.x);
	ext_buffer->write(pos.y);

	return 0.0;
}

fn_export double imgui_get_cursor_screen_pos() {
	ImVec2 pos = ImGui::GetCursorScreenPos();

	ext_buffer->seek(0);
	ext_buffer->write(pos.x);
	ext_buffer->write(pos.y);

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
	ImVec2 size;
	size.x = width;
	size.y = height;
	return (double)(ImGui::Button(label,size));
}

fn_export double imgui_small_button(const char* label) {
	return (double)(ImGui::SmallButton(label));
}

fn_export double imgui_invisible_button(const char* str_id, double width, double height, double flags) {
	ImVec2 size;
	size.x = width;
	size.y = height;
	return (double)(ImGui::InvisibleButton(str_id, size, (ImGuiButtonFlags)flags));
}

fn_export double imgui_checkbox(const char* label, double checked) {
	bool v = (bool)checked;
	bool changed = ImGui::Checkbox(label, &v);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write((float)v);

	return 0.0;
}

fn_export double imgui_checkbox_flags(const char* label, double flags, double flags_value) {
	unsigned int _flags = (unsigned int)flags;
	bool changed = ImGui::CheckboxFlags(label, &_flags, flags_value);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write((float)_flags);

	return 0.0;
}

fn_export double imgui_radio_button(const char* label, double active) {
	bool _active = (bool)active;
	return (double)ImGui::RadioButton(label, _active);
}

fn_export double imgui_radio_button_int(const char* label, double v, double v_button) {
	int iv = (int)v;
	int iv_button = (int)v_button;
	bool changed = ImGui::RadioButton(label, &iv, iv_button);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write((float)iv);

	return 0.0;
}

fn_export double imgui_progress_bar(double fraction, double width, double height, const char* overlay) {
	ImVec2 size;
	size.x = width;
	size.y = height;
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

fn_export double imgui_combo(const char* label) {
	ext_buffer->seek(0);
	int popup_max_height_in_items = ext_buffer->read_float();
	int current_item = ext_buffer->read_float();
	int items_count = ext_buffer->read_float();
	std::vector<std::string> items;
	for (int i = 0; i < items_count; ++i) {
		items.push_back(ext_buffer->read_string());
	}
	
	bool changed = ImGui::Combo(label, &current_item, items, popup_max_height_in_items);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(current_item);

	return 0.0;
}

// Widgets: Drag Sliders
fn_export double imgui_drag_float(const char* label, const char* format, double flags) {
	ext_buffer->seek(0);
	float v = ext_buffer->read_float();
	float v_speed = ext_buffer->read_float();
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();

	bool changed = ImGui::DragFloat(label, &v, v_speed, v_min, v_max, format, (ImGuiSliderFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(v);

	return 0.0;
}

fn_export double imgui_drag_float2(const char* label, const char* format, double flags) {
	ext_buffer->seek(0);
	float v[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};
	float v_speed = ext_buffer->read_float();
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	bool changed = ImGui::DragFloat2(label, v, v_speed, v_min, v_max, format, (ImGuiSliderFlags)flags);


	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);

	return 0.0;
}

fn_export double imgui_drag_float3(const char* label, const char* format, double flags) {

	ext_buffer->seek(0);
	float v[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};
	float v_speed = ext_buffer->read_float();
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	bool changed = ImGui::DragFloat3(label, v, v_speed, v_min, v_max, format, (ImGuiSliderFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);
	ext_buffer->write(v[2]);

	return 0.0;
}

fn_export double imgui_drag_float4(const char* label, const char* format, double flags) {
	ext_buffer->seek(0);
	float v[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};
	float v_speed = ext_buffer->read_float();
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	bool changed = ImGui::DragFloat4(label, v, v_speed, v_min, v_max, format, (ImGuiSliderFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);
	ext_buffer->write(v[2]);
	ext_buffer->write(v[3]);

	return 0.0;
}

fn_export double imgui_drag_float_range2(const char* label, const char* format, const char* format_max, double flags) {
	ext_buffer->seek(0);
	float v_current_min = ext_buffer->read_float();
	float v_current_max = ext_buffer->read_float();
	float v_speed = ext_buffer->read_float();
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	bool changed = ImGui::DragFloatRange2(label, &v_current_min, &v_current_max, v_speed, v_min, v_max, format, format_max, (ImGuiSliderFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(v_current_min);
	ext_buffer->write(v_current_max);

	return 0.0;
}

fn_export double imgui_drag_int(const char* label, const char* format, double flags) {
	ext_buffer->seek(0);
	int v = (int)ext_buffer->read_float();
	float v_speed = ext_buffer->read_float();
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	
	bool changed = ImGui::DragInt(label, &v, v_speed, v_min, v_max, format, (ImGuiSliderFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(v);

	return 0.0;
}

fn_export double imgui_drag_int2(const char* label, const char* format, double flags) {
	ext_buffer->seek(0);
	int v[] = { 
		(int)ext_buffer->read_float(), 
		(int)ext_buffer->read_float() 
	};
	float v_speed = ext_buffer->read_float();
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();

	bool changed = ImGui::DragInt2(label, v, v_speed, v_min, v_max, format, (ImGuiSliderFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);

	return 0.0;
}

fn_export double imgui_drag_int3(const char* label, const char* format, double flags) {
	ext_buffer->seek(0);
	int v[] = { 
		(int)ext_buffer->read_float(),
		(int)ext_buffer->read_float(),
		(int)ext_buffer->read_float()
	};
	float v_speed = ext_buffer->read_float();
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	bool changed = ImGui::DragInt3(label, v, v_speed, v_min, v_max, format, (ImGuiSliderFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);
	ext_buffer->write(v[2]);

	return 0.0;
}

fn_export double imgui_drag_int4(const char* label, const char* format, double flags) {
	ext_buffer->seek(0);
	int v[] = {
		(int)ext_buffer->read_float(),
		(int)ext_buffer->read_float(),
		(int)ext_buffer->read_float(),
		(int)ext_buffer->read_float()
	};
	float v_speed = ext_buffer->read_float();
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	bool changed = ImGui::DragInt4(label, v, v_speed, v_min, v_max, format, (ImGuiSliderFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);
	ext_buffer->write(v[2]);
	ext_buffer->write(v[3]);

	return 0.0;
}

fn_export double imgui_drag_int_range2(const char* label, const char* format, const char* format_max, double flags) {
	ext_buffer->seek(0);
	int v_current_min = (int)ext_buffer->read_float();
	int v_current_max = (int)ext_buffer->read_float();
	float v_speed = ext_buffer->read_float();
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	bool changed = ImGui::DragIntRange2(label, &v_current_min, &v_current_max, v_speed, v_min, v_max, format, format_max, (ImGuiSliderFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(v_current_min);
	ext_buffer->write(v_current_max);

	return 0.0;
}


// Widgets: Regular Sliders
fn_export double imgui_slider_float(const char* label, const char* format, double flags) {
	ext_buffer->seek(0);
	float v = ext_buffer->read_float();
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	bool changed = ImGui::SliderFloat(label, &v, v_min, v_max, format, (ImGuiSliderFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(v);

	return 0.0;
}

fn_export double imgui_slider_float2(const char* label, const char* format, double flags) {
	ext_buffer->seek(0);
	float v[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	bool changed = ImGui::SliderFloat2(label, v, v_min, v_max, format, (ImGuiSliderFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);

	return 0.0;
}

fn_export double imgui_slider_float3(const char* label, const char* format, double flags) {
	ext_buffer->seek(0);
	float v[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	bool changed = ImGui::SliderFloat3(label, v, v_min, v_max, format, (ImGuiSliderFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);
	ext_buffer->write(v[2]);

	return 0.0;
}

fn_export double imgui_slider_float4(const char* label, const char* format, double flags) {

	ext_buffer->seek(0);
	float v[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();

	bool changed = ImGui::SliderFloat4(label, v, v_min, v_max, format, (ImGuiSliderFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);
	ext_buffer->write(v[2]);
	ext_buffer->write(v[3]);

	return 0.0;
}

fn_export double imgui_slider_angle(const char* label, const char* format, double flags) {
	
	ext_buffer->seek(0);
	float v_rad = ext_buffer->read_float();
	float v_degrees_min = ext_buffer->read_float();
	float v_degrees_max = ext_buffer->read_float();
	bool changed = ImGui::SliderAngle(label, &v_rad, v_degrees_min, v_degrees_max, format, (ImGuiSliderFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(v_rad);

	return 0.0;
}

fn_export double imgui_slider_int(const char* label, const char* format, double flags) {
	ext_buffer->seek(0);
	int v = (int)ext_buffer->read_float();
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	bool changed = ImGui::SliderInt(label, &v, v_min, v_max, format, (ImGuiSliderFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(v);

	return 0.0;
}

fn_export double imgui_slider_int2(const char* label, const char* format, double flags) {
	ext_buffer->seek(0);
	int v[] = { 
		(int)ext_buffer->read_float(), 
		(int)ext_buffer->read_float() 
	};
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	bool changed = ImGui::SliderInt2(label, v, v_min, v_max, format, (ImGuiSliderFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);

	return 0.0;
}

fn_export double imgui_slider_int3(const char* label, const char* format, double flags) {
	ext_buffer->seek(0);
	int v[] = {
		(int)ext_buffer->read_float(),
		(int)ext_buffer->read_float(),
		(int)ext_buffer->read_float()
	};
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	bool changed = ImGui::SliderInt3(label, v, v_min, v_max, format, (ImGuiSliderFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);
	ext_buffer->write(v[2]);

	return 0.0;
}

fn_export double imgui_slider_int4(const char* label, const char* format, double flags) {
	ext_buffer->seek(0);
	int v[] = {
		(int)ext_buffer->read_float(),
		(int)ext_buffer->read_float(),
		(int)ext_buffer->read_float(),
		(int)ext_buffer->read_float()
	};
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	bool changed = ImGui::SliderInt4(label, v, v_min, v_max, format, (ImGuiSliderFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);
	ext_buffer->write(v[2]);
	ext_buffer->write(v[3]);

	return 0.0;
}

fn_export double imgui_vslider_float(const char* label, const char* format, double flags) {
	ext_buffer->seek(0);
	ImVec2 size;
	size.x = ext_buffer->read_float();
	size.y = ext_buffer->read_float();
	float v = ext_buffer->read_float();
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();

	bool changed = ImGui::VSliderFloat(label, size, &v, v_min, v_max, format, (ImGuiSliderFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(v);

	return 0.0;
}

fn_export double imgui_vslider_int(const char* label, const char* format, double flags) {
	ext_buffer->seek(0);
	ImVec2 size;
	size.x = ext_buffer->read_float();
	size.y = ext_buffer->read_float();
	int v = (int)ext_buffer->read_float();
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	bool changed = ImGui::VSliderInt(label, size, &v, v_min, v_max, format, (ImGuiSliderFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(v);

	return 0.0;
}


// Widgets: Input with Keyboard
fn_export double imgui_input_text(const char* label, const char* text, double flags) {
	std::string str(text);
	bool changed = ImGui::InputText(label, &str, (ImGuiInputTextFlags)flags);// , (ImGuiInputTextCallback)0, (void*)0);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(str);

	return 0.0;
}

fn_export double imgui_input_text_multiline(const char* label, const char* text, double flags) {
	ext_buffer->seek(0);
	float width = ext_buffer->read_float();
	float height = ext_buffer->read_float();

	std::string str(text);
	ImVec2 size;
	size.x = width;
	size.y = height;
	bool changed = ImGui::InputTextMultiline(label, &str, size, (ImGuiInputTextFlags)flags);
	
	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(str);

	return 0.0;

}

fn_export double imgui_input_text_with_hint(const char* label, const char* hint, const char* text, double flags) {
	std::string str(text);
	bool changed = ImGui::InputTextWithHint(label, hint, &str, (ImGuiInputTextFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(str);

	return 0.0;
}

fn_export double imgui_input_float(const char* label, const char* format, double flags) {

	ext_buffer->seek(0);
	float v = ext_buffer->read_float();
	float step = ext_buffer->read_float();
	float step_fast = ext_buffer->read_float();
	//int decimal_precision = (int)ext_buffer->read_float();

	bool changed = ImGui::InputFloat(label, &v, step, step_fast, format, (ImGuiInputTextFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(v);

	return 0.0;
}

fn_export double imgui_input_float2(const char* label, const char* format, double flags) {

	ext_buffer->seek(0);
	float v[] = { 
		ext_buffer->read_float(), 
		ext_buffer->read_float() 
	};
	//int decimal_precision = (int)ext_buffer->read_float();

	bool changed = ImGui::InputFloat2(label, v, format, (ImGuiInputTextFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);

	return 0.0;
}

fn_export double imgui_input_float3(const char* label, const char* format, double flags) {

	ext_buffer->seek(0);
	float v[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};

	bool changed = ImGui::InputFloat3(label, v, format, (ImGuiInputTextFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);
	ext_buffer->write(v[2]);

	return 0.0;
}

fn_export double imgui_input_float4(const char* label, const char* format, double flags) {

	ext_buffer->seek(0);
	float v[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};

	bool changed = ImGui::InputFloat4(label, v, format, (ImGuiInputTextFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);
	ext_buffer->write(v[2]);
	ext_buffer->write(v[3]);

	return 0.0;
}

fn_export double imgui_input_int(const char* label, double flags) {

	ext_buffer->seek(0);
	int v = ext_buffer->read_float();
	int step = ext_buffer->read_float();
	int step_fast = ext_buffer->read_float();
	//int decimal_precision = (int)ext_buffer->read_float();

	bool changed = ImGui::InputInt(label, &v, step, step_fast, (ImGuiInputTextFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((int)changed);
	ext_buffer->write(v);

	return 0.0;
}

fn_export double imgui_input_int2(const char* label, double flags) {

	ext_buffer->seek(0);
	int v[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};
	//int decimal_precision = (int)ext_buffer->read_float();

	bool changed = ImGui::InputInt2(label, v, (ImGuiInputTextFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((int)changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);

	return 0.0;
}

fn_export double imgui_input_int3(const char* label, double flags) {

	ext_buffer->seek(0);
	int v[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};

	bool changed = ImGui::InputInt3(label, v, (ImGuiInputTextFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((int)changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);
	ext_buffer->write(v[2]);

	return 0.0;
}

fn_export double imgui_input_int4(const char* label, double flags) {

	ext_buffer->seek(0);
	int v[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};

	bool changed = ImGui::InputInt4(label, v, (ImGuiInputTextFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((int)changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);
	ext_buffer->write(v[2]);
	ext_buffer->write(v[3]);

	return 0.0;
}


// Widgets: Color Editor/Picker
fn_export double imgui_color_edit3(const char* label, double flags) {
	ext_buffer->seek(0);
	float c[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};
	bool changed = ImGui::ColorEdit3(label, c, (ImGuiColorEditFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(c[0]);
	ext_buffer->write(c[1]);
	ext_buffer->write(c[2]);

	return 0.0;
}

fn_export double imgui_color_edit4(const char* label, double flags) {
	ext_buffer->seek(0);
	float c[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};
	bool changed = ImGui::ColorEdit4(label, c, (ImGuiColorEditFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(c[0]);
	ext_buffer->write(c[1]);
	ext_buffer->write(c[2]);

	return 0.0;
}

fn_export double imgui_color_picker3(const char* label, double flags) {
	ext_buffer->seek(0);
	float c[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};
	bool changed = ImGui::ColorPicker3(label, c, (ImGuiColorEditFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(c[0]);
	ext_buffer->write(c[1]);
	ext_buffer->write(c[2]);

	return 0.0;
}

fn_export double imgui_color_picker4(const char* label, double flags) {
	ext_buffer->seek(0);
	float c[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};
	bool changed = ImGui::ColorPicker4(label, c, (ImGuiColorEditFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(c[0]);
	ext_buffer->write(c[1]);
	ext_buffer->write(c[2]);
	ext_buffer->write(c[3]);

	return 0.0;
}

fn_export double imgui_color_button(const char* desc_id, double flags) {
	ext_buffer->seek(0);
	ImVec4 c;
	c.x = ext_buffer->read_float();
	c.y = ext_buffer->read_float();
	c.z = ext_buffer->read_float();
	c.w = ext_buffer->read_float();

	ImVec2 size;
	size.x = ext_buffer->read_float();
	size.y = ext_buffer->read_float();
	
	return ImGui::ColorButton(desc_id, c, (ImGuiColorEditFlags)flags, size);
}

fn_export double imgui_set_color_edit_options(double flags) {
	ImGui::SetColorEditOptions((ImGuiColorEditFlags)flags);

	return 0.0;
}


// Widgets: Trees
fn_export double imgui_tree_node(const char* label) {
	return ImGui::TreeNode(label);
}

fn_export double imgui_tree_node_ex(const char* label, double flags) {
	return ImGui::TreeNodeEx(label, (ImGuiTreeNodeFlags)flags);
}

fn_export double imgui_tree_push(const char* str_id) {
	ImGui::TreePush(str_id);
	return 0.0;
}

fn_export double imgui_tree_pop() {
	ImGui::TreePop();
	return 0.0;
}

fn_export double imgui_get_tree_node_to_label_spacing() {
	return ImGui::GetTreeNodeToLabelSpacing();
}

fn_export double imgui_collapsing_header(const char* label, double  open, double flags) {
	bool is_null = open == -4;
	bool b = (bool)open;
	bool collapsed = ImGui::CollapsingHeader(label, is_null ? NULL : &b, (ImGuiTreeNodeFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((float)collapsed);
	ext_buffer->write(is_null ? -4.0 : (float)b);

	return 0.0;
}

fn_export double imgui_set_next_item_open(double is_open, double cond) {
	ImGui::SetNextItemOpen((bool)is_open, (ImGuiCond)cond);
	return 0.0;
}


// Widgets: Selectables
fn_export double imgui_selectable(const char* label, double selected, double flags) {
	ext_buffer->seek(0);
	ImVec2 size;
	size.x = ext_buffer->read_float();
	size.y = ext_buffer->read_float();
	return ImGui::Selectable(label, selected, (ImGuiSelectableFlags)flags, size);
}


// Widgets: List Boxes
fn_export double imgui_list_box(const char* label) {
	ext_buffer->seek(0);
	int height_in_items = ext_buffer->read_float();
	int current_item = ext_buffer->read_float();
	int item_count = ext_buffer->read_float();
	std::vector<std::string> items;
	for (int i = 0; i < item_count; ++i) {
		items.push_back(ext_buffer->read_string());
	}
	bool changed = ImGui::ListBox(label, &current_item, items, height_in_items);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(current_item);

	return 0.0;
}

fn_export double imgui_list_box_header(const char* label, double width, double height) {
	ImVec2 size;
	size.x = width;
	size.y = height;
	return ImGui::ListBoxHeader(label, size);
}

fn_export double imgui_list_box_footer() {
	ImGui::ListBoxFooter();
	return 0.0;
}


// Widgets: Data Plotting
fn_export double imgui_plot_lines(const char* label, const char* overlay_text) {

	ext_buffer->seek(0);
	int values_count = ext_buffer->read_float();
	std::vector<float> values;
	for (int i = 0; i < values_count; ++i) {
		values.push_back(ext_buffer->read_float());
	}
	int values_offset = ext_buffer->read_float();
	float scale_min = ext_buffer->read_float();
	float scale_max = ext_buffer->read_float();
	ImVec2 graph_size;
	graph_size.x = ext_buffer->read_float();
	graph_size.y = ext_buffer->read_float();

	ImGui::PlotLines(label, &values[0], values_count, values_offset, overlay_text, scale_min == -4 ? FLT_MAX : scale_min, scale_max == -4 ? FLT_MAX : scale_max, graph_size);

	return 0.0;

}

fn_export double imgui_plot_histogram(const char* label, const char* overlay_text) {

	ext_buffer->seek(0);
	int values_count = ext_buffer->read_float();
	std::vector<float> values;
	for (int i = 0; i < values_count; ++i) {
		values.push_back(ext_buffer->read_float());
	}
	int values_offset = ext_buffer->read_float();
	float scale_min = ext_buffer->read_float();
	float scale_max = ext_buffer->read_float();
	ImVec2 graph_size;
	graph_size.x = ext_buffer->read_float();
	graph_size.y = ext_buffer->read_float();
	
	ImGui::PlotHistogram(label, &values[0], values_count, values_offset, overlay_text, scale_min == -4 ? FLT_MAX : scale_min, scale_max == -4 ? FLT_MAX : scale_max, graph_size);

	return 0.0;

}


// Widgets: Value() Helpers
// do them yourself if you want. It's pointless to make this for GMS


// Widgets: Menus
fn_export double imgui_begin_menu_bar() {
	return ImGui::BeginMenuBar();
}

fn_export double imgui_end_menu_bar() {
	ImGui::EndMenuBar();
	return 0.0;
}

fn_export double imgui_begin_main_menu_bar() {
	return ImGui::BeginMainMenuBar();
}

fn_export double imgui_end_main_menu_bar() {
	ImGui::EndMainMenuBar();
	return 0.0;
}

fn_export double imgui_begin_menu(const char* label, double enabled) {
	return ImGui::BeginMenu(label, enabled);
}

fn_export double imgui_end_menu() {
	ImGui::EndMenu();
	return 0.0;
}

fn_export double imgui_menu_item(const char* label, const char* shortcut, double selected, double enabled) {
	bool _selected = (bool)selected;
	return ImGui::MenuItem(label, shortcut, &_selected, enabled);
}


// Tooltips
fn_export double imgui_begin_tooltip() {
	ImGui::BeginTooltip();
	return 0.0;
}

fn_export double imgui_end_tooltip() {
	ImGui::EndTooltip();
	return 0.0;
}

fn_export double imgui_set_tooltip(const char* fmt) {
	ImGui::SetTooltip(fmt);
	return 0.0;
}


// Popups, Modals
fn_export double imgui_begin_popup(const char* str_id, double flags) {
	return ImGui::BeginPopup(str_id, (ImGuiWindowFlags)flags);
}

fn_export double imgui_begin_popup_modal(const char* name, double open, double flags) {
	bool _open = (bool)open;
	bool opened = ImGui::BeginPopupModal(name, &_open, (ImGuiWindowFlags)flags);

	ext_buffer->seek(0);
	ext_buffer->write((float)opened);
	ext_buffer->write((float)_open);

	return 0.0;
}

fn_export double imgui_end_popup() {
	ImGui::EndPopup();
	return 0.0;
}

fn_export double imgui_open_popup(const char* str_id, double flags) {
	ImGui::OpenPopup(str_id, (ImGuiPopupFlags)flags);
	return 0.0;
}

fn_export double imgui_close_current_popup() {
	ImGui::CloseCurrentPopup();
	return 0.0;
}

fn_export double imgui_begin_popup_context_item(const char* str_id, double flags) {
	return ImGui::BeginPopupContextItem(str_id, (ImGuiPopupFlags)flags);
}

fn_export double imgui_begin_popup_context_window(const char* str_id, double flags) {
	return ImGui::BeginPopupContextWindow(str_id, (ImGuiPopupFlags)flags);
}

fn_export double imgui_begin_popup_context_void(const char* str_id, double flags) {
	return ImGui::BeginPopupContextVoid(str_id, (ImGuiPopupFlags)flags);
}

fn_export double imgui_is_popup_open(const char* str_id, double flags) {
	return ImGui::IsPopupOpen(str_id, (ImGuiPopupFlags)flags);
}


// Columns
fn_export double imgui_columns(double count, const char* id, double border) {
	ImGui::Columns(count, id, border);
	return 0.0;
}

fn_export double imgui_next_column() {
	ImGui::NextColumn();
	return 0.0;
}

fn_export double imgui_get_column_index() {
	return ImGui::GetColumnIndex();
}

fn_export double imgui_get_column_width(double column_index) {
	return ImGui::GetColumnWidth(column_index);
}

fn_export double imgui_set_column_width(double column_index, double width) {
	ImGui::SetColumnWidth(column_index, width);
	return 0.0;
}

fn_export double imgui_get_column_offset(double column_index) {
	return ImGui::GetColumnOffset(column_index);
}

fn_export double imgui_set_column_offset(double column_index, double offset) {
	ImGui::SetColumnOffset(column_index, offset);
	return 0.0;
}

fn_export double imgui_get_columns_count() {
	return ImGui::GetColumnsCount();
}


// Tab Bars, Tabs
fn_export double imgui_begin_tab_bar(const char* str_id, double flags) {
	return ImGui::BeginTabBar(str_id, (ImGuiTabBarFlags)flags);
}

fn_export double imgui_end_tab_bar() {
	ImGui::EndTabBar();
	return 0.0;
}

fn_export double imgui_begin_tab_item(const char* label, double open, double flags) {

	bool _open = (bool)open;
	bool selected = ImGui::BeginTabItem(label, open < 0.0 ? NULL : &_open, (ImGuiTabItemFlags)flags);
	
	ext_buffer->seek(0);
	ext_buffer->write(selected);
	ext_buffer->write(_open);

	return 0.0;
}

fn_export double imgui_end_tab_item() {
	ImGui::EndTabItem();
	return 0.0;
}

fn_export double imgui_set_tab_item_closed(const char* tab_or_docked_window_label) {
	ImGui::SetTabItemClosed(tab_or_docked_window_label);
	return 0.0;
}


// Docking
// TODO: Wrap these functions ya bum


// Logging/Capture
fn_export double imgui_log_to_tty(double auto_open_depth) {
	ImGui::LogToTTY(auto_open_depth);
	return 0.0;
}

fn_export double imgui_log_to_file(double auto_open_depth, const char* filename) {
	ImGui::LogToFile(auto_open_depth, filename);
	return 0.0;
}

fn_export double imgui_log_to_clipboard(double auto_open_depth) {
	ImGui::LogToClipboard(auto_open_depth);
	return 0.0;
}

fn_export double imgui_log_finish() {
	ImGui::LogFinish();
	return 0.0;
}

fn_export double imgui_log_buttons() {
	ImGui::LogButtons();
	return 0.0;
}

fn_export double imgui_log_text(const char* fmt) {
	ImGui::LogText(fmt);
	return 0.0;
}

// Drag and Drop
// TODO: Wrap these functions ya bum


// Clipping
fn_export double imgui_push_clip_rect(double min_x, double min_y, double max_x, double max_y, double intersect_with_current_clip_rect) {
	ImVec2 clip_rect_min;
	clip_rect_min.x = min_x;
	clip_rect_min.y = min_y;

	ImVec2 clip_rect_max;
	clip_rect_max.x = max_x;
	clip_rect_max.y = max_y;

	ImGui::PushClipRect(clip_rect_min, clip_rect_max, intersect_with_current_clip_rect);
	return 0.0;
}

fn_export double imgui_pop_clip_rect() {
	ImGui::PopClipRect();
	return 0.0;
}


// Focus, Activation
fn_export double imgui_set_item_default_focus() {
	ImGui::SetItemDefaultFocus();
	return 0.0;
}

fn_export double imgui_set_keyboard_focus_here(double offset) {
	ImGui::SetKeyboardFocusHere(offset);
	return 0.0;
}


// Item/Widgets Utilities
fn_export double imgui_is_item_hovered(double flags) {
	return ImGui::IsItemHovered((ImGuiHoveredFlags)flags);
}

fn_export double imgui_is_item_active() {
	return ImGui::IsItemActive();
}

fn_export double imgui_is_item_focused() {
	return ImGui::IsItemFocused();
}

fn_export double imgui_is_item_clicked(double mouse_button) {
	return ImGui::IsItemClicked((ImGuiMouseButton)mouse_button);
}

fn_export double imgui_is_item_visible() {
	return ImGui::IsItemVisible();
}

fn_export double imgui_is_item_edited() {
	return ImGui::IsItemEdited();
}

fn_export double imgui_is_item_activated() {
	return ImGui::IsItemActivated();
}

fn_export double imgui_is_item_deactivated() {
	return ImGui::IsItemDeactivated();
}

fn_export double imgui_is_item_deactivated_after_edit() {
	return ImGui::IsItemDeactivatedAfterEdit();
}

fn_export double imgui_is_item_toggled_open() {
	return ImGui::IsItemToggledOpen();
}

fn_export double imgui_is_any_item_hovered() {
	return ImGui::IsAnyItemHovered();
}

fn_export double imgui_is_any_item_active() {
	return ImGui::IsAnyItemActive();
}

fn_export double imgui_is_any_item_focused() {
	return ImGui::IsAnyItemFocused();
}

fn_export double imgui_get_item_rect_min() {
	ImVec2 rmin = ImGui::GetItemRectMin();
	ext_buffer->seek(0);
	ext_buffer->write(rmin.x);
	ext_buffer->write(rmin.y);
	return 0.0;
}

fn_export double imgui_get_item_rect_max() {
	ImVec2 rmax = ImGui::GetItemRectMax();
	ext_buffer->seek(0);
	ext_buffer->write(rmax.x);
	ext_buffer->write(rmax.y);
	return 0.0;
}

fn_export double imgui_get_item_rect_size() {
	ImVec2 rsize = ImGui::GetItemRectSize();
	ext_buffer->seek(0);
	ext_buffer->write(rsize.x);
	ext_buffer->write(rsize.y);
	return 0.0;
}

fn_export double imgui_set_item_allow_overlap() {
	ImGui::SetItemAllowOverlap();
	return 0.0;
}


// Miscellaneous Utilities
fn_export double imgui_is_rect_visible(double x1, double y1, double x2, double y2) {
	ImVec2 rect_min;
	rect_min.x = x1;
	rect_min.y = y1;

	ImVec2 rect_max;
	rect_min.x = x1;
	rect_min.y = y1;
	return ImGui::IsRectVisible(rect_min, rect_max);
}

fn_export double imgui_get_time() {
	return ImGui::GetTime();
}

fn_export double imgui_get_frame_count() {
	return ImGui::GetFrameCount();
}

fn_export const char* imgui_get_style_color_name(double idx) {
	return ImGui::GetStyleColorName((ImGuiCol)idx);
}

fn_export double imgui_begin_child_frame(double id, double width, double height, double flags) {
	ImVec2 size;
	size.x = width;
	size.y = height;
	return ImGui::BeginChildFrame((ImGuiID)id, size, (ImGuiWindowFlags)flags);
}

fn_export double imgui_end_child_frame() {
	ImGui::EndChildFrame();
	return 0.0;
}


// Text Utilities
fn_export double imgui_calc_text_size(const char* text, const char* text_end, double hide_text_after_double_hash, double wrap_width) {
	ImVec2 size = ImGui::CalcTextSize(text, text_end, hide_text_after_double_hash, wrap_width);
	ext_buffer->seek(0);
	ext_buffer->write(size.x);
	ext_buffer->write(size.y);

	return 0.0;
}


// Color Utilities
fn_export double imgui_color_convert_u32_to_float4(double in) {
	ImVec4 color = ImGui::ColorConvertU32ToFloat4((ImU32)in);
	ext_buffer->seek(0);
	ext_buffer->write(color.x);
	ext_buffer->write(color.y);
	ext_buffer->write(color.z);
	ext_buffer->write(color.w);

	return 0.0;
}

fn_export double imgui_color_convert_float4_to_u32(double r, double g, double b, double a) {
	ImVec4 in;
	in.x = r;
	in.y = g;
	in.z = b;
	in.w = a;
	return ImGui::ColorConvertFloat4ToU32(in);
}

fn_export double imgui_color_convert_rgb_to_hsv(double r, double g, double b) {
	float h, s, v;
	ImGui::ColorConvertRGBtoHSV(r, g, b, h, s, v);
	ext_buffer->seek(0);
	ext_buffer->write(h);
	ext_buffer->write(s);
	ext_buffer->write(v);
	return 0.0;
}

fn_export double imgui_color_convert_hsv_to_rgb(double h, double s, double v) {
	float r, g, b;
	ImGui::ColorConvertHSVtoRGB(h, s, v, r, g, b);
	ext_buffer->seek(0);
	ext_buffer->write(r);
	ext_buffer->write(g);
	ext_buffer->write(b);
	return 0.0;
}


// Input Utilities: Keyboard
fn_export double imgui_get_key_index(double imgui_key) {
	return ImGui::GetKeyIndex((ImGuiKey)imgui_key);
}

fn_export double imgui_is_key_down(double user_key_index) {
	return ImGui::IsKeyDown(user_key_index);
}

fn_export double imgui_is_key_pressed(double user_key_index, double repeat) {
	return ImGui::IsKeyPressed(user_key_index, repeat);
}

fn_export double imgui_is_key_released(double user_key_index) {
	return ImGui::IsKeyReleased(user_key_index);
}

fn_export double imgui_get_key_pressed_amount(double key_index, double repeat_delay, double rate) {
	return ImGui::GetKeyPressedAmount(key_index, repeat_delay, rate);
}


// Input Utilities: Mouse
fn_export double imgui_is_mouse_down(double button) {
	return ImGui::IsMouseDown((ImGuiMouseButton)button);
}

fn_export double imgui_is_mouse_clicked(double button, double repeat) {
	return ImGui::IsMouseClicked((ImGuiMouseButton)button, repeat);
}

fn_export double imgui_is_mouse_released(double button) {
	return ImGui::IsMouseReleased((ImGuiMouseButton)button);
}

fn_export double imgui_is_mouse_double_clicked(double button) {
	return ImGui::IsMouseDoubleClicked((ImGuiMouseButton)button);
}

fn_export double imgui_is_mouse_hovering_rect(double x1, double y1, double x2, double y2, double clip) {
	ImVec2 rmin; rmin.x = x1; rmin.y = y1;
	ImVec2 rmax; rmax.x = x1; rmax.y = y1;
	return ImGui::IsMouseHoveringRect(rmin, rmax, clip);
}

fn_export double imgui_is_mouse_pos_valid(double x, double y) {
	ImVec2 mouse_pos;
	mouse_pos.x = x;
	mouse_pos.y = y;
	return ImGui::IsMousePosValid(&mouse_pos);
}

fn_export double imgui_is_any_mouse_down() {
	return ImGui::IsAnyMouseDown();
}

fn_export double imgui_get_mouse_pos() {
	ImVec2 pos = ImGui::GetMousePos();
	ext_buffer->seek(0);
	ext_buffer->write(pos.x);
	ext_buffer->write(pos.y);
	return 0.0;
}

fn_export double imgui_get_mouse_pos_on_opening_current_popup() {
	ImVec2 pos = ImGui::GetMousePosOnOpeningCurrentPopup();
	ext_buffer->seek(0);
	ext_buffer->write(pos.x);
	ext_buffer->write(pos.y);
	return 0.0;
}

fn_export double imgui_is_mouse_dragging(double button, double lock_threshold) {
	return ImGui::IsMouseDragging((ImGuiMouseButton)button, lock_threshold);
}

fn_export double imgui_get_mouse_drag_delta(double button, double lock_threshold) {
	ImVec2 d = ImGui::GetMouseDragDelta((ImGuiMouseButton)button, lock_threshold);
	ext_buffer->seek(0);
	ext_buffer->write(d.x);
	ext_buffer->write(d.y);
	return 0.0;
}

fn_export double imgui_reset_mouse_drag_delta(double button) {
	ImGui::ResetMouseDragDelta((ImGuiMouseButton)button);
	return 0.0;
}

fn_export double imgui_get_mouse_cursor() {
	return ImGui::GetMouseCursor();
}

fn_export double imgui_set_mouse_cursor(double cursor_type) {
	ImGui::SetMouseCursor(cursor_type);
	return 0.0;
}


// Clipboard Utilities
fn_export const char* imgui_get_clipboard_text() {
	return ImGui::GetClipboardText();
}

fn_export double imgui_set_clipboard_text(const char* text) {
	ImGui::SetClipboardText(text);
	return 0.0;
}



// Settings/.INI Utilities
fn_export double imgui_load_ini_settings_from_disk(const char* ini_filename) {
	ImGui::LoadIniSettingsFromDisk(ini_filename);
	return 0.0;
}

fn_export double imgui_save_ini_settings_to_disk(const char* ini_filename) {
	ImGui::SaveIniSettingsToDisk(ini_filename);
	return 0.0;
}


// Pretty sure I don't need this.
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