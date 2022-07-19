#include <iostream>
#include <Windows.h>
#include <commctrl.h>
#include <vector>
#include <map>
#include <d3d11.h>
#pragma comment(lib, "comctl32.lib")

#include "../imgui/imgui.h"
#include "../imgui/imgui_stdlib.h"
#include "../imgui/imgui_impl_dx11.h"
#include "../imgui/imgui_impl_win32.h"

#include "Buffer.h"

#define int64 unsigned long long int
#define fn_export extern "C" __declspec(dllexport)

// Global Variables
Buffer* ext_buffer = nullptr;
std::map<std::string, ID3D11ShaderResourceView*> ext_loaded_image_map;

fn_export double _extension_setup(void* buffer_ptr, double buffer_size) {
	ext_buffer = new Buffer(buffer_ptr, buffer_size);

	return 0.0;
}

fn_export double _extension_cleanup() {
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

//-----------------------------------------------------------------------------
// [SECTION] Dear ImGui end-user API functions
//-----------------------------------------------------------------------------

// Main
fn_export double _imgui_setup(char* hwnd, char* device, char* device_context) {

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

fn_export double _imgui_cleanup(char* hwnd) {

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
	bool _open = open;
	ImGui::ShowDemoWindow(&_open);
	return _open;
}

fn_export double imgui_show_about_window(double open) {
	bool _open = open;
	ImGui::ShowAboutWindow(&_open);
	return _open;
}

fn_export double imgui_show_metrics_window(double open) {
	bool _open = open;
	ImGui::ShowMetricsWindow(&_open);
	return _open;
}

fn_export double imgui_show_style_editor() {
	ImGui::ShowStyleEditor();
	return 0.0;
}

fn_export double imgui_show_style_selector(const char* label) {
	return ImGui::ShowStyleSelector(label);
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

// returns { expanded, open }
fn_export double _imgui_begin(const char* name) {
	ext_buffer->seek(0);
	float fvalue = ext_buffer->read_float();
	ImGuiWindowFlags flags = ext_buffer->read_float();

	bool _open = fvalue;
	bool expanded = ImGui::Begin(name, fvalue < 0 ? NULL : &_open, flags);

	ext_buffer->seek(0);
	ext_buffer->write(expanded);
	ext_buffer->write(_open);

	return 0.0;
}

fn_export double imgui_end() {
	ImGui::End();
	return 0.0;
}


//-----------------------------------------------------------------------------
// [SECTION] ImGuiStyle
//-----------------------------------------------------------------------------


// Getter Functions
fn_export double imgui_get_style() {
	ImGuiStyle& style = ImGui::GetStyle();
	return reinterpret_cast<int64>(&style);
}

fn_export double imgui_style_get_alpha(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	return style_ptr->Alpha;
}

fn_export double imgui_style_get_disabled_alpha(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	return style_ptr->DisabledAlpha;
}

// returns ImVec2
fn_export double _imgui_style_get_window_padding(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ImVec2 padding = style_ptr->WindowPadding;
	ext_buffer->seek(0);
	ext_buffer->write(padding.x);
	ext_buffer->write(padding.y);
	return 0.0;
}

fn_export double imgui_style_get_window_rounding(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	return style_ptr->WindowRounding;
}

fn_export double imgui_style_get_window_border_size(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	return style_ptr->WindowBorderSize;
}

// returns ImVec2
fn_export double _imgui_style_get_window_min_size(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ImVec2 min_size = style_ptr->WindowMinSize;
	ext_buffer->seek(0);
	ext_buffer->write(min_size.x);
	ext_buffer->write(min_size.y);
	return 0.0;
}

// returns ImVec2
fn_export double _imgui_style_get_window_title_align(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ImVec2 title_align = style_ptr->WindowTitleAlign;
	ext_buffer->seek(0);
	ext_buffer->write(title_align.x);
	ext_buffer->write(title_align.y);
	return 0.0;
}

// returns ImGuiDir
fn_export double imgui_style_get_window_menu_button_position(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	return style_ptr->WindowMenuButtonPosition;
}

fn_export double imgui_style_get_child_rounding(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	return style_ptr->ChildRounding;
}

fn_export double imgui_style_get_child_border_size(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	return style_ptr->ChildBorderSize;
}

fn_export double imgui_style_get_popup_rounding(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	return style_ptr->PopupRounding;
}

fn_export double imgui_style_get_popup_border_size(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	return style_ptr->PopupBorderSize;
}

// returns ImVec2
fn_export double _imgui_style_get_frame_padding(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ImVec2 padding = style_ptr->FramePadding;
	ext_buffer->seek(0);
	ext_buffer->write(padding.x);
	ext_buffer->write(padding.y);
	return 0.0;
}

fn_export double imgui_style_get_frame_rounding(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	return style_ptr->FrameRounding;
}

fn_export double imgui_style_get_frame_border_size(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	return style_ptr->FrameBorderSize;
}

// returns ImVec2
fn_export double _imgui_style_get_item_spacing(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ImVec2 spacing = style_ptr->ItemSpacing;
	ext_buffer->seek(0);
	ext_buffer->write(spacing.x);
	ext_buffer->write(spacing.y);
	return 0.0;
}

// returns ImVec2
fn_export double _imgui_style_get_item_inner_spacing(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ImVec2 spacing = style_ptr->ItemInnerSpacing;
	ext_buffer->seek(0);
	ext_buffer->write(spacing.x);
	ext_buffer->write(spacing.y);
	return 0.0;
}

// returns ImVec2
fn_export double _imgui_style_get_cell_padding(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ImVec2 padding = style_ptr->CellPadding;
	ext_buffer->seek(0);
	ext_buffer->write(padding.x);
	ext_buffer->write(padding.y);
	return 0.0;
}

fn_export double imgui_style_get_indent_spacing(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	return style_ptr->IndentSpacing;
}

fn_export double imgui_style_get_columns_min_spacing(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	return style_ptr->ColumnsMinSpacing;
}

fn_export double imgui_style_get_scrollbar_size(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	return style_ptr->ScrollbarSize;
}

fn_export double imgui_style_get_scrollbar_rounding(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	return style_ptr->ScrollbarRounding;
}

fn_export double imgui_style_get_grab_min_size(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	return style_ptr->GrabMinSize;
}

fn_export double imgui_style_get_grab_rounding(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	return style_ptr->GrabRounding;
}

fn_export double imgui_style_get_log_slider_deadzone(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	return style_ptr->LogSliderDeadzone;
}

fn_export double imgui_style_get_tab_rounding(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	return style_ptr->TabRounding;
}

fn_export double imgui_style_get_tab_border_size(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	return style_ptr->TabBorderSize;
}

fn_export double imgui_style_get_tab_min_width_for_close_button(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	return style_ptr->TabMinWidthForCloseButton;
}

// returns ImGuiDir
fn_export double imgui_style_get_color_button_position(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	return style_ptr->ColorButtonPosition;
}

// returns ImVec2
fn_export double _imgui_style_get_button_text_align(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ImVec2 text_align = style_ptr->ButtonTextAlign;
	ext_buffer->seek(0);
	ext_buffer->write(text_align.x);
	ext_buffer->write(text_align.y);
	return 0.0;
}

// returns ImVec2
fn_export double _imgui_style_get_selectable_text_align(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ImVec2 text_align = style_ptr->SelectableTextAlign;
	ext_buffer->seek(0);
	ext_buffer->write(text_align.x);
	ext_buffer->write(text_align.y);
	return 0.0;
}

// returns ImVec2
fn_export double _imgui_style_get_display_window_padding(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ImVec2 padding = style_ptr->DisplayWindowPadding;
	ext_buffer->seek(0);
	ext_buffer->write(padding.x);
	ext_buffer->write(padding.y);
	return 0.0;
}

// returns ImVec2
fn_export double _imgui_style_get_display_safe_area_padding(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ImVec2 padding = style_ptr->DisplaySafeAreaPadding;
	ext_buffer->seek(0);
	ext_buffer->write(padding.x);
	ext_buffer->write(padding.y);
	return 0.0;
}

fn_export double imgui_style_get_mouse_cursor_scale(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	return style_ptr->MouseCursorScale;
}

fn_export double imgui_style_get_aa_lines(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	return style_ptr->AntiAliasedLines;
}

fn_export double imgui_style_get_aa_lines_use_tex(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	return style_ptr->AntiAliasedLinesUseTex;
}

fn_export double imgui_style_get_aa_fill(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	return style_ptr->AntiAliasedFill;
}

fn_export double imgui_style_get_curve_tessellation_tolerance(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	return style_ptr->CurveTessellationTol;
}

fn_export double imgui_style_get_circle_tessellation_max_error(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	return style_ptr->CircleTessellationMaxError;
}

fn_export double imgui_style_get_color(double style, double index) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ImVec4 color = style_ptr->Colors[(ImGuiCol)index];
	
	ext_buffer->seek(0);
	ext_buffer->write(color.x);
	ext_buffer->write(color.y);
	ext_buffer->write(color.z);
	ext_buffer->write(color.w);
	
	return 0.0;
}

// Setter Functions
fn_export double imgui_style_set_alpha(double style, double value) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	style_ptr->Alpha = value;
	return 0.0;
}

fn_export double imgui_style_set_disabled_alpha(double style, double value) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	style_ptr->DisabledAlpha = value;
	return 0.0;
}

fn_export double imgui_style_set_window_padding(double style, double pad_x, double pad_y) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ImVec2 padding;
	padding.x = pad_x;
	padding.y = pad_y;
	style_ptr->WindowPadding = padding;
	return 0.0;
}

fn_export double imgui_style_set_window_rounding(double style, double value) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	style_ptr->WindowRounding = value;
	return 0.0;
}

fn_export double imgui_style_set_window_border_size(double style, double value) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	style_ptr->WindowBorderSize = value;
	return 0.0;
}

fn_export double imgui_style_set_window_min_size(double style, double width, double height) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ImVec2 size;
	size.x = width;
	size.y = height;
	style_ptr->WindowMinSize = size;
	return 0.0;
}

fn_export double imgui_style_set_window_title_align(double style, double align_x, double align_y) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ImVec2 align;
	align.x = align_x;
	align.y = align_y;
	style_ptr->WindowTitleAlign = align;
	return 0.0;
}

fn_export double imgui_style_set_window_menu_button_position(double style, double value) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	style_ptr->WindowMenuButtonPosition = (ImGuiDir)value;
	return 0.0;
}

fn_export double imgui_style_set_child_rounding(double style, double value) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	style_ptr->ChildRounding = value;
	return 0.0;
}

fn_export double imgui_style_set_child_border_size(double style, double value) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	style_ptr->ChildBorderSize = value;
	return 0.0;
}

fn_export double imgui_style_set_popup_rounding(double style, double value) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	style_ptr->PopupRounding = value;
	return 0.0;
}

fn_export double imgui_style_set_popup_border_size(double style, double value) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	style_ptr->PopupBorderSize = value;
	return 0.0;
}

fn_export double imgui_style_set_frame_padding(double style, double pad_x, double pad_y) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ImVec2 padding;
	padding.x = pad_x;
	padding.y = pad_y;
	style_ptr->FramePadding = padding;
	return 0.0;
}

fn_export double imgui_style_set_frame_rounding(double style, double value) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	style_ptr->FrameRounding = value;
	return 0.0;
}

fn_export double imgui_style_set_frame_border_size(double style, double value) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	style_ptr->FrameBorderSize = value;
	return 0.0;
}

fn_export double imgui_style_set_item_spacing(double style, double space_x, double space_y) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ImVec2 spacing;
	spacing.x = space_x;
	spacing.y = space_y;
	style_ptr->ItemSpacing = spacing;
	return 0.0;
}

fn_export double imgui_style_set_item_inner_spacing(double style, double space_x, double space_y) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ImVec2 spacing;
	spacing.x = space_x;
	spacing.y = space_y;
	style_ptr->ItemInnerSpacing = spacing;
	return 0.0;
}

fn_export double imgui_style_set_cell_padding(double style, double pad_x, double pad_y) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ImVec2 padding;
	padding.x = pad_x;
	padding.y = pad_y;
	style_ptr->CellPadding = padding;
	return 0.0;
}

fn_export double imgui_style_set_indent_spacing(double style, double value) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	style_ptr->IndentSpacing = value;
	return 0.0;
}

fn_export double imgui_style_set_columns_min_spacing(double style, double value) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	style_ptr->ColumnsMinSpacing = value;
	return 0.0;
}

fn_export double imgui_style_set_scrollbar_size(double style, double value) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	style_ptr->ScrollbarSize = value;
	return 0.0;
}

fn_export double imgui_style_set_scrollbar_rounding(double style, double value) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	style_ptr->ScrollbarRounding = value;
	return 0.0;
}

fn_export double imgui_style_set_grab_min_size(double style, double value) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	style_ptr->GrabMinSize = value;
	return 0.0;
}

fn_export double imgui_style_set_grab_rounding(double style, double value) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	style_ptr->GrabRounding = value;
	return 0.0;
}

fn_export double imgui_style_set_log_slider_deadzone(double style, double value) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	style_ptr->LogSliderDeadzone = value;
	return 0.0;
}

fn_export double imgui_style_set_tab_rounding(double style, double value) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	style_ptr->TabRounding = value;
	return 0.0;
}

fn_export double imgui_style_set_tab_border_size(double style, double value) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	style_ptr->TabBorderSize = value;
	return 0.0;
}

fn_export double imgui_style_set_tab_min_width_for_close_button(double style, double value) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	style_ptr->TabMinWidthForCloseButton = value;
	return 0.0;
}

fn_export double imgui_style_set_color_button_position(double style, double value) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	style_ptr->ColorButtonPosition = (ImGuiDir)value;
	return 0.0;
}

fn_export double imgui_style_set_button_text_align(double style, double align_x, double align_y) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ImVec2 align;
	align.x = align_x;
	align.y = align_y;
	style_ptr->ButtonTextAlign = align;
	return 0.0;
}

fn_export double imgui_style_set_selectable_text_align(double style, double align_x, double align_y) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ImVec2 align;
	align.x = align_x;
	align.y = align_y;
	style_ptr->SelectableTextAlign = align;
	return 0.0;
}

fn_export double imgui_style_set_display_window_padding(double style, double pad_x, double pad_y) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ImVec2 padding;
	padding.x = pad_x;
	padding.y = pad_y;
	style_ptr->DisplayWindowPadding = padding;
	return 0.0;
}

fn_export double imgui_style_set_display_safe_area_padding(double style, double pad_x, double pad_y) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ImVec2 padding;
	padding.x = pad_x;
	padding.y = pad_y;
	style_ptr->DisplaySafeAreaPadding = padding;
	return 0.0;
}

fn_export double imgui_style_set_mouse_cursor_scale(double style, double value) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	style_ptr->MouseCursorScale = value;
	return 0.0;
}

fn_export double imgui_style_set_aa_lines(double style, double value) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	style_ptr->AntiAliasedLines = value;
	return 0.0;
}

fn_export double imgui_style_set_aa_lines_use_tex(double style, double value) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	style_ptr->AntiAliasedLinesUseTex = value;
	return 0.0;
}

fn_export double imgui_style_set_aa_fill(double style, double value) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	style_ptr->AntiAliasedFill = value;
	return 0.0;
}

fn_export double imgui_style_set_curve_tessellation_tolerance(double style, double value) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	style_ptr->CurveTessellationTol = value;
	return 0.0;
}

fn_export double imgui_style_set_circle_tessellation_max_error(double style, double value) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	style_ptr->CircleTessellationMaxError = value;
	return 0.0;
}

fn_export double imgui_style_set_color(double style, double index, double r, double g, double b, double a) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ImVec4 color;
	color.x = r;
	color.y = g;
	color.z = b;
	color.w = a;
	style_ptr->Colors[(ImGuiCol)index] = color;
	return 0.0;
}



//-----------------------------------------------------------------------------
// [SECTION] ImGuiIO
//-----------------------------------------------------------------------------

fn_export double imgui_get_io() {
	ImGuiIO& io = ImGui::GetIO();
	return reinterpret_cast<int64>(&io);
}

fn_export double imgui_io_get_config_flags(double io) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	return io_ptr->ConfigFlags;
}

fn_export double imgui_io_set_config_flags(double io, double flags) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	io_ptr->ConfigFlags = flags;
	return 0.0;
}

// returns ImVec2
fn_export double _imgui_io_get_display_size(double io) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	ImVec2 size = io_ptr->DisplaySize;
	
	ext_buffer->seek(0);
	ext_buffer->write(size.x);
	ext_buffer->write(size.y);
	
	return 0.0;
}

fn_export double imgui_io_get_delta_time(double io) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	return io_ptr->DeltaTime;
}

fn_export double imgui_io_get_ini_saving_rate(double io) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	return io_ptr->IniSavingRate;
}

fn_export double imgui_io_set_ini_saving_rate(double io, double seconds) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	io_ptr->IniSavingRate = seconds;
	return 0.0;
}

fn_export const char* imgui_io_get_ini_filename(double io) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	return io_ptr->IniFilename;
}

fn_export double imgui_io_set_ini_filename(double io, const char* filename) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	io_ptr->IniFilename = filename;
	return 0.0;
}

fn_export const char* imgui_io_get_log_filename(double io) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	return io_ptr->LogFilename;
}

fn_export double imgui_io_set_log_filename(double io, const char* filename) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	io_ptr->LogFilename = filename;
	return 0.0;
}

fn_export double imgui_io_get_mouse_double_click_time(double io) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	return io_ptr->MouseDoubleClickTime;
}

fn_export double imgui_io_set_mouse_double_click_time(double io, double seconds) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	io_ptr->MouseDoubleClickTime = seconds;
	return 0.0;
}

fn_export double imgui_io_get_mouse_double_click_max_dist(double io) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	return io_ptr->MouseDoubleClickMaxDist;
}

fn_export double imgui_io_set_mouse_double_click_max_dist(double io, double distance) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	io_ptr->MouseDoubleClickMaxDist = distance;
	return 0.0;
}

fn_export double imgui_io_get_mouse_drag_threshold(double io) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	return io_ptr->MouseDragThreshold;
}

fn_export double imgui_io_set_mouse_drag_threshold(double io, double distance) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	io_ptr->MouseDragThreshold = distance;
	return 0.0;
}

fn_export double imgui_io_get_key_repeat_delay(double io) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	return io_ptr->KeyRepeatDelay;
}

fn_export double imgui_io_set_key_repeat_delay(double io, double seconds) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	io_ptr->KeyRepeatDelay = seconds;
	return 0.0;
}

fn_export double imgui_io_get_key_repeat_rate(double io) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	return io_ptr->KeyRepeatRate;
}

fn_export double imgui_io_set_key_repeat_rate(double io, double seconds) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	io_ptr->KeyRepeatRate = seconds;
	return 0.0;
}

fn_export double imgui_io_get_font_global_scale(double io) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	return io_ptr->FontGlobalScale;
}

fn_export double imgui_io_set_font_global_scale(double io, double scale) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	io_ptr->FontGlobalScale = scale;
	return 0.0;
}

fn_export double imgui_io_get_font_allow_user_scaling(double io) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	return io_ptr->FontAllowUserScaling;
}

fn_export double imgui_io_set_font_allow_user_scaling(double io, double enable) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	io_ptr->FontAllowUserScaling = enable;
	return 0.0;
}

fn_export double imgui_io_get_config_docking_no_split(double io) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	return io_ptr->ConfigDockingNoSplit;
}

fn_export double imgui_io_set_config_docking_no_split(double io, double enable) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	io_ptr->ConfigDockingNoSplit = enable;
	return 0.0;
}

fn_export double imgui_io_get_config_docking_with_shift(double io) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	return io_ptr->ConfigDockingWithShift;
}

fn_export double imgui_io_set_config_docking_with_shift(double io, double enable) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	io_ptr->ConfigDockingWithShift = enable;
	return 0.0;
}

fn_export double imgui_io_get_config_viewports_no_auto_merge(double io) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	return io_ptr->ConfigViewportsNoAutoMerge;
}

fn_export double imgui_io_set_config_viewports_no_auto_merge(double io, double enable) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	io_ptr->ConfigViewportsNoAutoMerge = enable;
	return 0.0;
}

fn_export double imgui_io_get_config_viewports_no_taskbar_icon(double io) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	return io_ptr->ConfigViewportsNoTaskBarIcon;
}

fn_export double imgui_io_set_config_viewports_no_taskbar_icon(double io, double enable) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	io_ptr->ConfigViewportsNoTaskBarIcon = enable;
	return 0.0;
}

fn_export double imgui_io_get_config_viewports_no_decoration(double io) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	return io_ptr->ConfigViewportsNoDecoration;
}

fn_export double imgui_io_set_config_viewports_no_decoration(double io, double enable) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	io_ptr->ConfigViewportsNoDecoration = enable;
	return 0.0;
}

fn_export double imgui_io_get_config_viewports_no_default_parent(double io) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	return io_ptr->ConfigViewportsNoDefaultParent;
}

fn_export double imgui_io_set_config_viewports_no_default_parent(double io, double enable) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	io_ptr->ConfigViewportsNoDefaultParent = enable;
	return 0.0;
}