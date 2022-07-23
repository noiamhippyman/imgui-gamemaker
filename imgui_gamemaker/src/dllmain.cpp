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
//ImFontConfig ext_font_config;

fn_export void* imgui_null() {
	return (void*)0;
}

bool _imgui_is_image_loaded(const char* name) {
	return ext_loaded_image_map.count(name) > 0;
}

fn_export double imgui_load_image(const char* name, void* buffer_ptr, void* d3d_device) {
	if (_imgui_is_image_loaded(name)) return 0.0;

	unsigned char* image_data = (unsigned char*)buffer_ptr;
	ID3D11Device* device = (ID3D11Device*)d3d_device;

	ext_buffer->seek(0);
	int imgW = ext_buffer->read_float();
	int imgH = ext_buffer->read_float();

	// Create texture
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = imgW;
	desc.Height = imgH;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;

	ID3D11Texture2D* pTexture = nullptr;
	D3D11_SUBRESOURCE_DATA subResource;
	subResource.pSysMem = image_data;
	subResource.SysMemPitch = desc.Width * 4;
	subResource.SysMemSlicePitch = 0;
	device->CreateTexture2D(&desc, &subResource, &pTexture);

	// Create texture view
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ID3D11ShaderResourceView* texID;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = desc.MipLevels;
	srvDesc.Texture2D.MostDetailedMip = 0;
	device->CreateShaderResourceView(pTexture, &srvDesc, &texID);
	pTexture->Release();

	ext_loaded_image_map[name] = texID;

	return 0.0;
}

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


// Child Windows
fn_export double _imgui_begin_child(const char* name) {
	ImVec2 size = { ext_buffer->read_float(), ext_buffer->read_float() };
	bool border = ext_buffer->read_float();
	ImGuiWindowFlags flags = ext_buffer->read_float();

	return ImGui::BeginChild(name, size, border, flags);
}

fn_export double imgui_end_child() {
	ImGui::EndChild();
	return 0.0;
}


// Window Utilities
fn_export double imgui_is_window_appearing() {
	return ImGui::IsWindowAppearing();
}

fn_export double imgui_is_window_collapsed() {
	return ImGui::IsWindowCollapsed();
}

fn_export double _imgui_is_window_focused(double flags) {
	return ImGui::IsWindowFocused((ImGuiFocusedFlags)flags);
}

fn_export double _imgui_is_window_hovered(double flags) {
	return ImGui::IsWindowHovered((ImGuiHoveredFlags)flags);
}

fn_export double imgui_get_window_draw_list() {
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	return reinterpret_cast<int64>(draw_list);
}

fn_export double imgui_get_window_dpi_scale() {
	return ImGui::GetWindowDpiScale();
}

fn_export double _imgui_get_window_pos() {
	ImVec2 pos = ImGui::GetWindowPos();

	ext_buffer->seek(0);
	ext_buffer->write(pos.x);
	ext_buffer->write(pos.y);

	return 0.0;
}

fn_export double _imgui_get_window_size() {
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

// returns ImGuiViewport*
// I'm not sure if the end-user ever needs this. If somebody asks or I find a reason I'll put it back in
//fn_export double imgui_get_window_viewport() {
//	ImGuiViewport* viewport = ImGui::GetWindowViewport();
//	return reinterpret_cast<int64>(viewport);
//}


// Window Manipulation
fn_export double _imgui_set_next_window_pos() {
	ext_buffer->seek(0);

	ImVec2 pos(ext_buffer->read_float(), ext_buffer->read_float());
	ImGuiCond cond = ext_buffer->read_float();
	ImVec2 pivot(ext_buffer->read_float(), ext_buffer->read_float());

	ImGui::SetNextWindowPos(pos, cond, pivot);

	return 0.0;
}

fn_export double _imgui_set_next_window_size() {
	ext_buffer->seek(0);

	ImVec2 size(ext_buffer->read_float(), ext_buffer->read_float());
	ImGuiCond cond = ext_buffer->read_float();

	ImGui::SetNextWindowSize(size, cond);

	return 0.0;
}

fn_export double _imgui_set_next_window_size_constraints() {
	ext_buffer->seek(0);

	ImVec2 size_min(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 size_max(ext_buffer->read_float(), ext_buffer->read_float());

	// TODO: figure out how to do callbacks

	ImGui::SetNextWindowSizeConstraints(size_min, size_max, NULL, NULL);

	return 0.0;
}

fn_export double _imgui_set_next_window_content_size() {
	ext_buffer->seek(0);

	ImVec2 size(ext_buffer->read_float(), ext_buffer->read_float());

	ImGui::SetNextWindowContentSize(size);

	return 0.0;
}

fn_export double _imgui_set_next_window_collapsed() {
	ext_buffer->seek(0);

	bool collapsed = ext_buffer->read_float();
	ImGuiCond cond = ext_buffer->read_float();

	ImGui::SetNextWindowCollapsed(collapsed, cond);

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

fn_export double _imgui_set_window_pos() {
	ext_buffer->seek(0);
	ImVec2 pos(ext_buffer->read_float(), ext_buffer->read_float());
	ImGuiCond cond = ext_buffer->read_float();
	ImGui::SetWindowPos(pos, cond);
	return 0.0;
}

fn_export double _imgui_set_window_size() {
	ext_buffer->seek(0);
	ImVec2 size(ext_buffer->read_float(), ext_buffer->read_float());
	ImGuiCond cond = ext_buffer->read_float();
	ImGui::SetWindowSize(size, cond);
	return 0.0;
}

fn_export double _imgui_set_window_collapsed() {
	ext_buffer->seek(0);

	bool collapsed = ext_buffer->read_float();
	ImGuiCond cond = ext_buffer->read_float();

	ImGui::SetWindowCollapsed(collapsed, cond);

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


// Content region
fn_export double _imgui_get_content_region_avail() {
	ImVec2 region = ImGui::GetContentRegionAvail();

	ext_buffer->seek(0);
	ext_buffer->write(region.x);
	ext_buffer->write(region.y);

	return 0.0;
}

fn_export double _imgui_get_content_region_max() {
	ImVec2 region = ImGui::GetContentRegionMax();
	
	ext_buffer->seek(0);
	ext_buffer->write(region.x);
	ext_buffer->write(region.y);

	return 0.0;
}

fn_export double _imgui_get_window_content_region_min() {
	ImVec2 region = ImGui::GetWindowContentRegionMin();

	ext_buffer->seek(0);
	ext_buffer->write(region.x);
	ext_buffer->write(region.y);

	return 0.0;
}

fn_export double _imgui_get_window_content_region_max() {
	ImVec2 region = ImGui::GetWindowContentRegionMax();

	ext_buffer->seek(0);
	ext_buffer->write(region.x);
	ext_buffer->write(region.y);

	return 0.0;
}


// Windows Scrolling
fn_export double imgui_get_scroll_x() { return ImGui::GetScrollX(); }
fn_export double imgui_get_scroll_y() { return ImGui::GetScrollY(); }
fn_export double imgui_set_scroll_x(double value) { ImGui::SetScrollX(value); return 0.0; }
fn_export double imgui_set_scroll_y(double value) { ImGui::SetScrollY(value); return 0.0; }
fn_export double imgui_get_scroll_max_x() { return ImGui::GetScrollMaxX(); }
fn_export double imgui_get_scroll_max_y() { return ImGui::GetScrollMaxY(); }
fn_export double _imgui_set_scroll_here_x(double center_x_ratio) { ImGui::SetScrollHereX(center_x_ratio); return 0.0; }
fn_export double _imgui_set_scroll_here_y(double center_y_ratio) { ImGui::SetScrollHereY(center_y_ratio); return 0.0; }
fn_export double _imgui_set_scroll_from_pos_x(double local_x, double center_x_ratio) { ImGui::SetScrollFromPosX(local_x, center_x_ratio); return 0.0; }
fn_export double _imgui_set_scroll_from_pos_y(double local_y, double center_y_ratio) { ImGui::SetScrollFromPosY(local_y, center_y_ratio); return 0.0; }


// Parameters stacks (shared)
fn_export double imgui_push_font(double font) {
	ImFont* _font = reinterpret_cast<ImFont*>((int64)font);
	ImGui::PushFont(_font);
	return 0.0;
}

fn_export double imgui_pop_font() {
	ImGui::PopFont();
	return 0.0;
}

fn_export double _imgui_push_style_color() {
	ext_buffer->seek(0);
	ImGuiCol idx = ext_buffer->read_float();
	ImVec4 col( ext_buffer->read_float(), ext_buffer->read_float(), ext_buffer->read_float(), ext_buffer->read_float() );
	ImGui::PushStyleColor(idx, col);
	return 0.0;
}

fn_export double _imgui_pop_style_color(double count) {
	ImGui::PopStyleColor(count);
	return 0.0;
}

fn_export double imgui_push_style_var_f(double idx, double val) {
	ImGui::PushStyleVar(idx, val);
	return 0.0;
}

fn_export double _imgui_push_style_var_f2() {
	ext_buffer->seek(0);
	ImGuiCol idx = ext_buffer->read_float();
	ImVec2 val(ext_buffer->read_float(), ext_buffer->read_float());
	ImGui::PushStyleVar(idx, val);
	return 0.0;
}

fn_export double _imgui_pop_style_var(double count) {
	ImGui::PopStyleVar(count);
	return 0.0;
}

fn_export double imgui_push_allow_keyboard_focus(double allow) {
	ImGui::PushAllowKeyboardFocus(allow);
	return 0.0;
}

fn_export double imgui_pop_allow_keyboard_focus() {
	ImGui::PopAllowKeyboardFocus();
	return 0.0;
}

fn_export double imgui_push_button_repeat(double repeat) {
	ImGui::PushButtonRepeat(repeat);
	return 0.0;
}

fn_export double imgui_pop_button_repeat() {
	ImGui::PopButtonRepeat();
	return 0.0;
}


// Parameters stacks (current window)
fn_export double imgui_push_item_width(double width) {
	ImGui::PushItemWidth(width);
	return 0.0;
}

fn_export double imgui_pop_item_width() {
	ImGui::PopItemWidth();
	return 0.0;
}

fn_export double imgui_set_next_item_width(double width) {
	ImGui::SetNextItemWidth(width);
	return 0.0;
}

fn_export double imgui_calc_item_width() {
	return ImGui::CalcItemWidth();
}

fn_export double _imgui_push_text_wrap_pos(double wrap_local_pos_x) {
	ImGui::PushTextWrapPos(wrap_local_pos_x);
	return 0.0;
}

fn_export double imgui_pop_text_wrap_pos() {
	ImGui::PopTextWrapPos();
	return 0.0;
}


// Style read access
fn_export double imgui_get_font() {
	ImFont* font = ImGui::GetFont();
	return reinterpret_cast<int64>(font);
}

fn_export double imgui_get_font_size() {
	return ImGui::GetFontSize();
}

fn_export double _imgui_get_font_tex_uv_white_pixel() {
	ImVec2 uv = ImGui::GetFontTexUvWhitePixel();

	ext_buffer->seek(0);
	ext_buffer->write(uv.x);
	ext_buffer->write(uv.y);
	
	return 0.0;
}

fn_export double _imgui_get_style_color_u32() {
	ext_buffer->seek(0);
	ImGuiCol idx = ext_buffer->read_float();
	float alpha = ext_buffer->read_float();
	return ImGui::GetColorU32(idx, alpha);
}

fn_export double _imgui_get_color_u32() {
	ext_buffer->seek(0);
	ImVec4 col( ext_buffer->read_float(), ext_buffer->read_float(), ext_buffer->read_float(), ext_buffer->read_float() );
	return ImGui::GetColorU32(col);
}

fn_export double _imgui_get_style_color_vec4() {
	ext_buffer->seek(0);
	ImGuiCol idx = ext_buffer->read_float();
	ImVec4 color = ImGui::GetStyleColorVec4(idx);
	ext_buffer->seek(0);
	ext_buffer->write(color.x);
	ext_buffer->write(color.y);
	ext_buffer->write(color.z);
	ext_buffer->write(color.w);
	return 0.0;
}


// Cursor/Layout
fn_export double imgui_separator() {
	ImGui::Separator();
	return 0.0;
}

fn_export double _imgui_same_line(double offset_from_start_x, double spacing) {
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

fn_export double _imgui_dummy() {
	ext_buffer->seek(0);
	ImVec2 size(ext_buffer->read_float(), ext_buffer->read_float());
	ImGui::Dummy(size);
	return 0.0;
}

fn_export double _imgui_indent(double indent_w) {
	ImGui::Indent(indent_w);
	return 0.0;
}

fn_export double _imgui_unindent(double indent_w) {
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

fn_export double _imgui_get_cursor_pos() {
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

fn_export double _imgui_set_cursor_pos() {
	ext_buffer->seek(0);
	ImVec2 pos(ext_buffer->read_float(), ext_buffer->read_float());
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

fn_export double _imgui_get_cursor_start_pos() {
	ImVec2 pos = ImGui::GetCursorStartPos();

	ext_buffer->seek(0);
	ext_buffer->write(pos.x);
	ext_buffer->write(pos.y);

	return 0.0;
}

fn_export double _imgui_get_cursor_screen_pos() {
	ImVec2 pos = ImGui::GetCursorScreenPos();

	ext_buffer->seek(0);
	ext_buffer->write(pos.x);
	ext_buffer->write(pos.y);

	return 0.0;
}

fn_export double _imgui_set_cursor_screen_pos() {
	ext_buffer->seek(0);
	ImVec2 pos(ext_buffer->read_float(), ext_buffer->read_float());
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
fn_export double _imgui_text_unformatted(const char* text, const char* text_end) {
	ImGui::TextUnformatted(text,text_end);
	return 0.0;
}

fn_export double imgui_text(const char* text) {
	ImGui::Text(text);
	return 0.0;
}

fn_export double _imgui_text_colored(const char* text) {
	ext_buffer->seek(0);
	ImVec4 col( ext_buffer->read_float(), ext_buffer->read_float(), ext_buffer->read_float(), ext_buffer->read_float() );
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
	ImGui::LabelText(label, text);
	return 0.0;
}

fn_export double imgui_bullet_text(const char* text) {
	ImGui::BulletText(text);
	return 0.0;
}


// Widgets: Main
fn_export double _imgui_button(const char* label) {
	ext_buffer->seek(0);
	ImVec2 size(ext_buffer->read_float(), ext_buffer->read_float());
	return ImGui::Button(label, size);
}

fn_export double imgui_small_button(const char* label) {
	return ImGui::SmallButton(label);
}

fn_export double _imgui_invisible_button(const char* str_id) {
	ext_buffer->seek(0);
	ImVec2 size(ext_buffer->read_float(), ext_buffer->read_float());
	ImGuiButtonFlags flags = ext_buffer->read_float();
	return ImGui::InvisibleButton(str_id, size, flags);
}

fn_export double imgui_arrow_button(const char* str_id, double dir) {
	return ImGui::ArrowButton(str_id, dir);
}

fn_export double _imgui_image(const char* name) {

	ext_buffer->seek(0);
	ImVec2 size(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 uv0(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 uv1(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec4 tint_col(ext_buffer->read_float(), ext_buffer->read_float(), ext_buffer->read_float(), ext_buffer->read_float());
	ImVec4 border_col(ext_buffer->read_float(), ext_buffer->read_float(), ext_buffer->read_float(), ext_buffer->read_float());

	ID3D11ShaderResourceView* texID = nullptr;
	if (_imgui_is_image_loaded(name)) {
		texID = ext_loaded_image_map[name];
	}

	ImGui::Image(texID, size, uv0, uv1, tint_col, border_col);

	return 0.0;
}

fn_export double _imgui_image_button(const char* name) {

	ext_buffer->seek(0);
	ImVec2 size(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 uv0(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 uv1(ext_buffer->read_float(), ext_buffer->read_float());
	int frame_padding = ext_buffer->read_float();
	ImVec4 bg_col(ext_buffer->read_float(), ext_buffer->read_float(), ext_buffer->read_float(), ext_buffer->read_float());
	ImVec4 tint_col(ext_buffer->read_float(), ext_buffer->read_float(), ext_buffer->read_float(), ext_buffer->read_float());

	ID3D11ShaderResourceView* texID = nullptr;
	if (_imgui_is_image_loaded(name)) {
		texID = ext_loaded_image_map[name];
	}

	return ImGui::ImageButton(texID, size, uv0, uv1, frame_padding, bg_col, tint_col);
}

fn_export double _imgui_checkbox(const char* label, double checked) {
	bool v = checked;
	bool changed = ImGui::Checkbox(label, &v);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(v);

	return 0.0;
}

fn_export double _imgui_checkbox_flags(const char* label, double flags, double flags_value) {
	int _flags = flags;
	bool changed = ImGui::CheckboxFlags(label, &_flags, flags_value);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(_flags);

	return 0.0;
}

fn_export double imgui_radio_button(const char* label, double active) {
	return ImGui::RadioButton(label, active);
}

fn_export double _imgui_radio_button_int(const char* label, double v, double v_button) {
	int iv = v;
	int iv_button = v_button;
	bool changed = ImGui::RadioButton(label, &iv, iv_button);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(iv);

	return 0.0;
}

fn_export double _imgui_progress_bar(const char* overlay) {
	ext_buffer->seek(0);
	float fraction = ext_buffer->read_float();
	ImVec2 size(ext_buffer->read_float(), ext_buffer->read_float());
	ImGui::ProgressBar(fraction, size, overlay);
	return 0.0;
}

fn_export double imgui_bullet() {
	ImGui::Bullet();
	return 0.0;
}


// Widgets: Combo Box
fn_export double _imgui_begin_combo(const char* label, const char* preview_value, double flags) {
	return ImGui::BeginCombo(label, preview_value, flags);
}

fn_export double imgui_end_combo() {
	ImGui::EndCombo();
	return 0.0;
}

fn_export double _imgui_combo(const char* label) {
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
	ext_buffer->write(changed);
	ext_buffer->write(current_item);

	return 0.0;
}


// Widgets: Drag Sliders
fn_export double _imgui_drag_float(const char* label, const char* format) {
	ext_buffer->seek(0);
	float v = ext_buffer->read_float();
	float v_speed = ext_buffer->read_float();
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	ImGuiSliderFlags flags = ext_buffer->read_float();
	bool changed = ImGui::DragFloat(label, &v, v_speed, v_min, v_max, format, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(v);

	return 0.0;
}

fn_export double _imgui_drag_float2(const char* label, const char* format) {
	ext_buffer->seek(0);
	float v[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};
	float v_speed = ext_buffer->read_float();
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	ImGuiSliderFlags flags = ext_buffer->read_float();
	bool changed = ImGui::DragFloat2(label, v, v_speed, v_min, v_max, format, flags);


	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);

	return 0.0;
}

fn_export double _imgui_drag_float3(const char* label, const char* format) {

	ext_buffer->seek(0);
	float v[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};
	float v_speed = ext_buffer->read_float();
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	ImGuiSliderFlags flags = ext_buffer->read_float();
	bool changed = ImGui::DragFloat3(label, v, v_speed, v_min, v_max, format, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);
	ext_buffer->write(v[2]);

	return 0.0;
}

fn_export double _imgui_drag_float4(const char* label, const char* format) {
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
	ImGuiSliderFlags flags = ext_buffer->read_float();
	bool changed = ImGui::DragFloat4(label, v, v_speed, v_min, v_max, format, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);
	ext_buffer->write(v[2]);
	ext_buffer->write(v[3]);

	return 0.0;
}

fn_export double _imgui_drag_float_range2(const char* label, const char* format, const char* format_max) {
	ext_buffer->seek(0);
	float v_current_min = ext_buffer->read_float();
	float v_current_max = ext_buffer->read_float();
	float v_speed = ext_buffer->read_float();
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	ImGuiSliderFlags flags = ext_buffer->read_float();
	bool changed = ImGui::DragFloatRange2(label, &v_current_min, &v_current_max, v_speed, v_min, v_max, format, format_max, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(v_current_min);
	ext_buffer->write(v_current_max);

	return 0.0;
}

fn_export double _imgui_drag_int(const char* label, const char* format) {
	ext_buffer->seek(0);
	int v = ext_buffer->read_float();
	float v_speed = ext_buffer->read_float();
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	ImGuiSliderFlags flags = ext_buffer->read_float();
	bool changed = ImGui::DragInt(label, &v, v_speed, v_min, v_max, format, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(v);

	return 0.0;
}

fn_export double _imgui_drag_int2(const char* label, const char* format) {
	ext_buffer->seek(0);
	int v[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};
	float v_speed = ext_buffer->read_float();
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	ImGuiSliderFlags flags = ext_buffer->read_float();
	bool changed = ImGui::DragInt2(label, v, v_speed, v_min, v_max, format, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);

	return 0.0;
}

fn_export double _imgui_drag_int3(const char* label, const char* format) {
	ext_buffer->seek(0);
	int v[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};
	float v_speed = ext_buffer->read_float();
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	ImGuiSliderFlags flags = ext_buffer->read_float();
	bool changed = ImGui::DragInt3(label, v, v_speed, v_min, v_max, format, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);
	ext_buffer->write(v[2]);

	return 0.0;
}

fn_export double _imgui_drag_int4(const char* label, const char* format) {
	ext_buffer->seek(0);
	int v[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};
	float v_speed = ext_buffer->read_float();
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	ImGuiSliderFlags flags = ext_buffer->read_float();
	bool changed = ImGui::DragInt4(label, v, v_speed, v_min, v_max, format, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);
	ext_buffer->write(v[2]);
	ext_buffer->write(v[3]);

	return 0.0;
}

fn_export double _imgui_drag_int_range2(const char* label, const char* format, const char* format_max) {
	ext_buffer->seek(0);
	int v_current_min = ext_buffer->read_float();
	int v_current_max = ext_buffer->read_float();
	float v_speed = ext_buffer->read_float();
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	ImGuiSliderFlags flags = ext_buffer->read_float();
	bool changed = ImGui::DragIntRange2(label, &v_current_min, &v_current_max, v_speed, v_min, v_max, format, format_max, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(v_current_min);
	ext_buffer->write(v_current_max);

	return 0.0;
}

// kinda works but gets wiggy waggy when min and max aren't perfect. can't do reverse for some reason not sure why.
// gamemaker man. i'm excited for the future extension updates. I need them baaaaaad morty.
//fn_export double _imgui_drag_scalar_s8(const char* label, const char* format) {
//	ext_buffer->seek(0);
//	char p_data = ext_buffer->read_float();
//	float v_speed = ext_buffer->read_float();
//	char p_min = ext_buffer->read_float();
//	char p_max = ext_buffer->read_float();
//	ImGuiSliderFlags flags = ext_buffer->read_float();
//
//	bool changed = ImGui::DragScalar(label, ImGuiDataType_S8, &p_data, v_speed, &p_min, &p_max, format, flags);
//
//	ext_buffer->seek(0);
//	ext_buffer->write(changed);
//	ext_buffer->write(p_data);
//
//	return 0.0;
//}


// Widgets: Regular Sliders
fn_export double _imgui_slider_float(const char* label, const char* format) {
	ext_buffer->seek(0);
	float v = ext_buffer->read_float();
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	ImGuiSliderFlags flags = ext_buffer->read_float();
	bool changed = ImGui::SliderFloat(label, &v, v_min, v_max, format, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(v);

	return 0.0;
}

fn_export double _imgui_slider_float2(const char* label, const char* format) {
	ext_buffer->seek(0);
	float v[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	ImGuiSliderFlags flags = ext_buffer->read_float();
	bool changed = ImGui::SliderFloat2(label, v, v_min, v_max, format, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);

	return 0.0;
}

fn_export double _imgui_slider_float3(const char* label, const char* format) {
	ext_buffer->seek(0);
	float v[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	ImGuiSliderFlags flags = ext_buffer->read_float();
	bool changed = ImGui::SliderFloat3(label, v, v_min, v_max, format, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);
	ext_buffer->write(v[2]);

	return 0.0;
}

fn_export double _imgui_slider_float4(const char* label, const char* format) {

	ext_buffer->seek(0);
	float v[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	ImGuiSliderFlags flags = ext_buffer->read_float();

	bool changed = ImGui::SliderFloat4(label, v, v_min, v_max, format, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);
	ext_buffer->write(v[2]);
	ext_buffer->write(v[3]);

	return 0.0;
}

fn_export double _imgui_slider_angle(const char* label, const char* format) {

	ext_buffer->seek(0);
	float v_rad = ext_buffer->read_float();
	float v_degrees_min = ext_buffer->read_float();
	float v_degrees_max = ext_buffer->read_float();
	ImGuiSliderFlags flags = ext_buffer->read_float();
	bool changed = ImGui::SliderAngle(label, &v_rad, v_degrees_min, v_degrees_max, format, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(v_rad);

	return 0.0;
}

fn_export double _imgui_slider_int(const char* label, const char* format) {
	ext_buffer->seek(0);
	int v = ext_buffer->read_float();
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	ImGuiSliderFlags flags = ext_buffer->read_float();
	bool changed = ImGui::SliderInt(label, &v, v_min, v_max, format, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(v);

	return 0.0;
}

fn_export double _imgui_slider_int2(const char* label, const char* format) {
	ext_buffer->seek(0);
	int v[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	ImGuiSliderFlags flags = ext_buffer->read_float();
	bool changed = ImGui::SliderInt2(label, v, v_min, v_max, format, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);

	return 0.0;
}

fn_export double _imgui_slider_int3(const char* label, const char* format) {
	ext_buffer->seek(0);
	int v[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	ImGuiSliderFlags flags = ext_buffer->read_float();
	bool changed = ImGui::SliderInt3(label, v, v_min, v_max, format, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);
	ext_buffer->write(v[2]);

	return 0.0;
}

fn_export double _imgui_slider_int4(const char* label, const char* format) {
	ext_buffer->seek(0);
	int v[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	ImGuiSliderFlags flags = ext_buffer->read_float();
	bool changed = ImGui::SliderInt4(label, v, v_min, v_max, format, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);
	ext_buffer->write(v[2]);
	ext_buffer->write(v[3]);

	return 0.0;
}

fn_export double _imgui_vslider_float(const char* label, const char* format) {
	ext_buffer->seek(0);
	ImVec2 size(ext_buffer->read_float(), ext_buffer->read_float());
	float v = ext_buffer->read_float();
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	ImGuiSliderFlags flags = ext_buffer->read_float();

	bool changed = ImGui::VSliderFloat(label, size, &v, v_min, v_max, format, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(v);

	return 0.0;
}

fn_export double _imgui_vslider_int(const char* label, const char* format) {
	ext_buffer->seek(0);
	ImVec2 size(ext_buffer->read_float(), ext_buffer->read_float());
	int v = ext_buffer->read_float();
	float v_min = ext_buffer->read_float();
	float v_max = ext_buffer->read_float();
	ImGuiSliderFlags flags = ext_buffer->read_float();
	bool changed = ImGui::VSliderInt(label, size, &v, v_min, v_max, format, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(v);

	return 0.0;
}


// Widgets: Input w/ Keyboard
fn_export double _imgui_input_text(const char* label, const char* text) {
	std::string str(text);
	ext_buffer->seek(0);
	ImGuiInputTextFlags flags = ext_buffer->read_float();
	bool changed = ImGui::InputText(label, &str, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(str);

	return 0.0;
}

fn_export double _imgui_input_text_multiline(const char* label, const char* text) {
	ext_buffer->seek(0);
	ImVec2 size(ext_buffer->read_float(), ext_buffer->read_float());
	ImGuiInputTextFlags flags = ext_buffer->read_float();

	std::string str(text);
	bool changed = ImGui::InputTextMultiline(label, &str, size, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(str);

	return 0.0;

}

fn_export double _imgui_input_text_with_hint(const char* label, const char* hint, const char* text) {
	std::string str(text);
	ext_buffer->seek(0);
	ImGuiInputTextFlags flags = ext_buffer->read_float();
	bool changed = ImGui::InputTextWithHint(label, hint, &str, flags);

	ext_buffer->seek(0);
	ext_buffer->write((float)changed);
	ext_buffer->write(str);

	return 0.0;
}

fn_export double _imgui_input_float(const char* label, const char* format) {

	ext_buffer->seek(0);
	float v = ext_buffer->read_float();
	float step = ext_buffer->read_float();
	float step_fast = ext_buffer->read_float();
	ImGuiInputTextFlags flags = ext_buffer->read_float();

	bool changed = ImGui::InputFloat(label, &v, step, step_fast, format, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(v);

	return 0.0;
}

fn_export double _imgui_input_float2(const char* label, const char* format) {

	ext_buffer->seek(0);
	float v[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};

	ImGuiInputTextFlags flags = ext_buffer->read_float();

	bool changed = ImGui::InputFloat2(label, v, format, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);

	return 0.0;
}

fn_export double _imgui_input_float3(const char* label, const char* format) {

	ext_buffer->seek(0);
	float v[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};
	ImGuiInputTextFlags flags = ext_buffer->read_float();

	bool changed = ImGui::InputFloat3(label, v, format, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);
	ext_buffer->write(v[2]);

	return 0.0;
}

fn_export double _imgui_input_float4(const char* label, const char* format) {

	ext_buffer->seek(0);
	float v[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};

	ImGuiInputTextFlags flags = ext_buffer->read_float();

	bool changed = ImGui::InputFloat4(label, v, format, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);
	ext_buffer->write(v[2]);
	ext_buffer->write(v[3]);

	return 0.0;
}

fn_export double _imgui_input_int(const char* label) {

	ext_buffer->seek(0);
	int v = ext_buffer->read_float();
	int step = ext_buffer->read_float();
	int step_fast = ext_buffer->read_float();
	ImGuiInputTextFlags flags = ext_buffer->read_float();

	bool changed = ImGui::InputInt(label, &v, step, step_fast, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(v);

	return 0.0;
}

fn_export double _imgui_input_int2(const char* label) {

	ext_buffer->seek(0);
	int v[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};

	ImGuiInputTextFlags flags = ext_buffer->read_float();

	bool changed = ImGui::InputInt2(label, v, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);

	return 0.0;
}

fn_export double _imgui_input_int3(const char* label) {

	ext_buffer->seek(0);
	int v[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};

	ImGuiInputTextFlags flags = ext_buffer->read_float();

	bool changed = ImGui::InputInt3(label, v, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);
	ext_buffer->write(v[2]);

	return 0.0;
}

fn_export double _imgui_input_int4(const char* label) {

	ext_buffer->seek(0);
	int v[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};

	ImGuiInputTextFlags flags = ext_buffer->read_float();

	bool changed = ImGui::InputInt4(label, v, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(v[0]);
	ext_buffer->write(v[1]);
	ext_buffer->write(v[2]);
	ext_buffer->write(v[3]);

	return 0.0;
}

fn_export double _imgui_input_double(const char* label, const char* format) {
	ext_buffer->seek(0);
	double v = ext_buffer->read_double();
	double step = ext_buffer->read_double();
	double step_fast = ext_buffer->read_double();
	ImGuiInputTextFlags flags = ext_buffer->read_float();
	bool changed = ImGui::InputDouble(label, &v, step, step_fast, format, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(v);
	return 0.0;
}

// Widgets: Color Editor/Picker
fn_export double _imgui_color_edit3(const char* label) {
	ext_buffer->seek(0);
	float c[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};
	ImGuiColorEditFlags flags = ext_buffer->read_float();
	bool changed = ImGui::ColorEdit3(label, c, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(c[0]);
	ext_buffer->write(c[1]);
	ext_buffer->write(c[2]);

	return 0.0;
}

fn_export double _imgui_color_edit4(const char* label) {
	ext_buffer->seek(0);
	float c[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};
	ImGuiColorEditFlags flags = ext_buffer->read_float();
	bool changed = ImGui::ColorEdit4(label, c, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(c[0]);
	ext_buffer->write(c[1]);
	ext_buffer->write(c[2]);
	ext_buffer->write(c[3]);

	return 0.0;
}

fn_export double _imgui_color_picker3(const char* label) {
	ext_buffer->seek(0);
	float c[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};
	ImGuiColorEditFlags flags = ext_buffer->read_float();
	bool changed = ImGui::ColorPicker3(label, c, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(c[0]);
	ext_buffer->write(c[1]);
	ext_buffer->write(c[2]);

	return 0.0;
}

fn_export double _imgui_color_picker4(const char* label) {
	ext_buffer->seek(0);
	float c[] = {
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float(),
		ext_buffer->read_float()
	};
	ImGuiColorEditFlags flags = ext_buffer->read_float();
	bool changed = ImGui::ColorPicker4(label, c, flags);

	ext_buffer->seek(0);
	ext_buffer->write(changed);
	ext_buffer->write(c[0]);
	ext_buffer->write(c[1]);
	ext_buffer->write(c[2]);
	ext_buffer->write(c[3]);

	return 0.0;
}

fn_export double _imgui_color_button(const char* desc_id) {
	ext_buffer->seek(0);
	ImVec4 c(ext_buffer->read_float(), ext_buffer->read_float(), ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 size(ext_buffer->read_float(), ext_buffer->read_float());
	ImGuiColorEditFlags flags = ext_buffer->read_float();

	return ImGui::ColorButton(desc_id, c, flags, size);
}

fn_export double _imgui_set_color_edit_options(double flags) {
	ImGui::SetColorEditOptions(flags);

	return 0.0;
}


// Widgets: Trees
fn_export double imgui_tree_node(const char* label) {
	return ImGui::TreeNode(label);
}

fn_export double _imgui_tree_node_ex(const char* label, double flags) {
	return ImGui::TreeNodeEx(label, flags);
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

fn_export double _imgui_collapsing_header(const char* label) {
	ext_buffer->seek(0);
	float open = ext_buffer->read_float();
	ImGuiTreeNodeFlags flags = ext_buffer->read_float();
	bool is_null = open < 0;
	bool b = (bool)open;
	bool collapsed = ImGui::CollapsingHeader(label, is_null ? NULL : &b, flags);

	ext_buffer->seek(0);
	ext_buffer->write(collapsed);
	ext_buffer->write(is_null ? open : b);

	return 0.0;
}

fn_export double _imgui_set_next_item_open(double is_open, double cond) {
	ImGui::SetNextItemOpen(is_open, cond);
	return 0.0;
}


// Widgets: Selectables
fn_export double _imgui_selectable(const char* label) {
	ext_buffer->seek(0);
	bool selected = ext_buffer->read_float();
	ImGuiSelectableFlags flags = ext_buffer->read_float();
	ImVec2 size(ext_buffer->read_float(), ext_buffer->read_float());
	return ImGui::Selectable(label, selected, flags, size);
}


// Widgets: List Boxes
fn_export double _imgui_begin_list_box(const char* label) {
	ext_buffer->seek(0);
	ImVec2 size(ext_buffer->read_float(), ext_buffer->read_float());
	return ImGui::BeginListBox(label, size);
}

fn_export double imgui_end_list_box() {
	ImGui::EndListBox();
	return 0.0;
}

fn_export double _imgui_list_box(const char* label) {
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
	ext_buffer->write(changed);
	ext_buffer->write(current_item);

	return 0.0;
}


// Widgets: Data Plotting
fn_export double _imgui_plot_lines(const char* label, const char* overlay_text) {

	ext_buffer->seek(0);
	int values_count = ext_buffer->read_float();
	std::vector<float> values;
	for (int i = 0; i < values_count; ++i) {
		values.push_back(ext_buffer->read_float());
	}
	int values_offset = ext_buffer->read_float();
	float scale_min = ext_buffer->read_float();
	float scale_max = ext_buffer->read_float();
	ImVec2 graph_size(ext_buffer->read_float(), ext_buffer->read_float());

	ImGui::PlotLines(label, &values[0], values_count, values_offset, overlay_text, scale_min < 0 ? FLT_MAX : scale_min, scale_max < 0 ? FLT_MAX : scale_max, graph_size);

	return 0.0;

}

fn_export double _imgui_plot_histogram(const char* label, const char* overlay_text) {

	ext_buffer->seek(0);
	int values_count = ext_buffer->read_float();
	std::vector<float> values;
	for (int i = 0; i < values_count; ++i) {
		values.push_back(ext_buffer->read_float());
	}
	int values_offset = ext_buffer->read_float();
	float scale_min = ext_buffer->read_float();
	float scale_max = ext_buffer->read_float();
	ImVec2 graph_size(ext_buffer->read_float(), ext_buffer->read_float());

	ImGui::PlotHistogram(label, &values[0], values_count, values_offset, overlay_text, scale_min < 0 ? FLT_MAX : scale_min, scale_max < 0 ? FLT_MAX : scale_max, graph_size);

	return 0.0;

}


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

fn_export double _imgui_begin_menu(const char* label, double enabled) {
	return ImGui::BeginMenu(label, enabled);
}

fn_export double imgui_end_menu() {
	ImGui::EndMenu();
	return 0.0;
}

fn_export double _imgui_menu_item(const char* label, const char* shortcut) {
	ext_buffer->seek(0);
	bool selected = ext_buffer->read_float();
	bool enabled = ext_buffer->read_float();
	return ImGui::MenuItem(label, shortcut, selected, enabled);
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

fn_export double imgui_set_tooltip(const char* text) {
	ImGui::SetTooltip(text);
	return 0.0;
}


// Popups: Begin/End functions
fn_export double _imgui_begin_popup(const char* str_id, double flags) {
	return ImGui::BeginPopup(str_id, flags);
}

fn_export double _imgui_begin_popup_modal(const char* name) {
	ext_buffer->seek(0);
	float open = ext_buffer->read_float();
	bool _open = open;
	ImGuiPopupFlags flags = ext_buffer->read_float();

	bool was_opened = ImGui::BeginPopupModal(name, open < 0 ? (bool*)0 : &_open, flags);

	ext_buffer->seek(0);
	ext_buffer->write(was_opened);
	ext_buffer->write(_open);

	return 0.0;
}

fn_export double imgui_end_popup() {
	ImGui::EndPopup();
	return 0.0;
}


// Popups: Open/Close functions
fn_export double _imgui_open_popup(const char* str_id, double flags) {
	ImGui::OpenPopup(str_id, flags);
	return 0.0;
}

fn_export double _imgui_open_popup_on_item_click(const char* str_id, double flags) {
	ImGui::OpenPopupOnItemClick(str_id, flags);
	return 0.0;
}

fn_export double imgui_close_current_popup() {
	ImGui::CloseCurrentPopup();
	return 0.0;
}


// Popups: Open + Begin combined function helpers
fn_export double _imgui_begin_popup_context_item(const char* str_id, double flags) {
	return ImGui::BeginPopupContextItem(str_id, flags);
}

fn_export double _imgui_begin_popup_context_window(const char* str_id, double flags) {
	return ImGui::BeginPopupContextWindow(str_id, flags);
}

fn_export double _imgui_begin_popup_context_void(const char* str_id, double flags) {
	return ImGui::BeginPopupContextVoid(str_id, flags);
}


// Popups: Query Functions
fn_export double _imgui_is_popup_open(const char* str_id, double flags) {
	return ImGui::IsPopupOpen(str_id, flags);
}


// Tables
fn_export double _imgui_begin_table(const char* str_id) {
	ext_buffer->seek(0);
	int column = ext_buffer->read_float();
	ImGuiTableFlags flags = ext_buffer->read_float();
	ImVec2 outer_size(ext_buffer->read_float(), ext_buffer->read_float());
	float inner_width = ext_buffer->read_float();
	
	return ImGui::BeginTable(str_id, column, flags, outer_size, inner_width);
}

fn_export double imgui_end_table() {
	ImGui::EndTable();
	return 0.0;
}

fn_export double _imgui_table_next_row() {
	ext_buffer->seek(0);
	ImGuiTableRowFlags flags = ext_buffer->read_float();
	float min_row_height = ext_buffer->read_float();
	ImGui::TableNextRow(flags, min_row_height);
	return 0.0;
}

fn_export double imgui_table_next_column() {
	return ImGui::TableNextColumn();
}

fn_export double imgui_table_set_column_index(double column_n) {
	return ImGui::TableSetColumnIndex(column_n);
}


// Tables: Headers & Columns declaration
fn_export double _imgui_table_setup_column(const char* label) {
	ext_buffer->seek(0);
	ImGuiTableColumnFlags flags = ext_buffer->read_float();
	float init_width_or_weight = ext_buffer->read_float();
	ImGuiID user_id = ext_buffer->read_float();
	ImGui::TableSetupColumn(label, flags, init_width_or_weight, user_id);
	return 0.0;
}

fn_export double imgui_table_setup_scroll_freeze(double cols, double rows) {
	ImGui::TableSetupScrollFreeze(cols, rows);
	return 0.0;
}

fn_export double imgui_table_headers_row() {
	ImGui::TableHeadersRow();
	return 0.0;
}

fn_export double imgui_table_header(const char* label) {
	ImGui::TableHeader(label);
	return 0.0;
}


// Tables: Sorting & Misc functions
fn_export double imgui_table_get_sort_specs() {
	// TODO: access to specs
	ImGuiTableSortSpecs* specs = ImGui::TableGetSortSpecs();
	return reinterpret_cast<int64>(specs);
}

fn_export double imgui_table_get_column_count() {
	return ImGui::TableGetColumnCount();
}

fn_export double imgui_table_get_column_index() {
	return ImGui::TableGetColumnIndex();
}

fn_export double imgui_table_get_row_index() {
	return ImGui::TableGetRowIndex();
}

fn_export const char* _imgui_table_get_column_name(double column_n) {
	return ImGui::TableGetColumnName(column_n);
}

fn_export double _imgui_table_get_column_flags(double column_n) {
	return ImGui::TableGetColumnFlags(column_n);
}

fn_export double imgui_table_set_column_enabled(double column_n, double enabled) {
	ImGui::TableSetColumnEnabled(column_n, enabled);
	return 0.0;
}

fn_export double _imgui_table_set_bg_color() {
	ImGuiTableBgTarget target = ext_buffer->read_float();
	ImU32 color = ext_buffer->read_float();
	int column_n = ext_buffer->read_float();

	ImGui::TableSetBgColor(target, color, column_n);

	return 0.0;
}


// Legacy Columns API
fn_export double _imgui_columns(const char* id) {
	ext_buffer->seek(0);
	int count = ext_buffer->read_float();
	bool border = ext_buffer->read_float();
	ImGui::Columns(count, id, border);
	return 0.0;
}

fn_export double imgui_next_column() {
	ImGui::NextColumn();
	return 0.0;
}

fn_export double imgui_get_column_index() {
	ImGui::GetColumnIndex();
	return 0.0;
}

fn_export double _imgui_get_column_width(double column_index) {
	return ImGui::GetColumnWidth(column_index);
}

fn_export double imgui_set_column_width(double column_index, double width) {
	ImGui::SetColumnWidth(column_index, width);
	return 0.0;
}

fn_export double _imgui_get_column_offset(double column_index) {
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
fn_export double _imgui_begin_tab_bar(const char* str_id, double flags) {
	return ImGui::BeginTabBar(str_id, flags);
}

fn_export double imgui_end_tab_bar() {
	ImGui::EndTabBar();
	return 0.0;
}

fn_export double _imgui_begin_tab_item(const char* label) {
	ext_buffer->seek(0);
	float open = ext_buffer->read_float();
	bool _open = open;
	ImGuiTabItemFlags flags = ext_buffer->read_float();

	bool selected = ImGui::BeginTabItem(label, open < 0 ? (bool*)0 : &_open, flags);

	ext_buffer->seek(0);
	ext_buffer->write(selected);
	ext_buffer->write(_open);

	return 0.0;
}

fn_export double imgui_end_tab_item() {
	ImGui::EndTabItem();
	return 0.0;
}

fn_export double _imgui_tab_item_button(const char* label, double flags) {
	return ImGui::TabItemButton(label, flags);
}

fn_export double imgui_set_tab_item_closed(const char* tab_or_docked_window_label) {
	ImGui::SetTabItemClosed(tab_or_docked_window_label);
	return 0.0;
}


// Logging/Capture

fn_export double _imgui_log_to_TTY(double auto_open_depth) {
	ImGui::LogToTTY(auto_open_depth);
	return 0.0;
}

fn_export double _imgui_log_to_file(double auto_open_depth, const char* filename) {
	ImGui::LogToFile(auto_open_depth,filename);
	return 0.0;
}

fn_export double _imgui_log_to_clipboard(double auto_open_depth) {
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

fn_export double imgui_log_text(const char* text) {
	ImGui::LogText(text);
	return 0.0;
}


// Drag and Drop
fn_export double _imgui_begin_drag_drop_source(double flags) {
	return ImGui::BeginDragDropSource(flags);
}

fn_export double _imgui_set_drag_drop_payload(const char* type) {
	ext_buffer->seek(0);
	ImGuiCond cond = ext_buffer->read_float();
	int data_size = ext_buffer->read_float();
	if (data_size <= 0) {
		return ImGui::SetDragDropPayload(type, NULL, 0, cond);
	}
	else {
		std::vector<float> data;
		for (int i = 0; i < data_size; ++i) {
			data.push_back(ext_buffer->read_float());
		}

		return ImGui::SetDragDropPayload(type, &data, sizeof(float) * data_size, cond);
	}
}

fn_export double imgui_end_drag_drop_source() {
	ImGui::EndDragDropSource();
	return 0.0;
}

fn_export double imgui_begin_drag_drop_target() {
	return ImGui::BeginDragDropTarget();
}

fn_export double _imgui_accept_drag_drop_payload(const char* type, double flags) {
	const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(type, flags);

	float* data = (float*)payload->Data;

	ext_buffer->seek(0);
	ext_buffer->write(payload->DataSize);
	for (int i = 0; i < payload->DataSize; ++i) {
		ext_buffer->write(data[i]);
	}

	return 0.0;
}

fn_export double imgui_end_drag_drop_target() {
	ImGui::EndDragDropTarget();
	return 0.0;
}

fn_export double imgui_get_drag_drop_payload() {
	const ImGuiPayload* payload = ImGui::GetDragDropPayload();
	return reinterpret_cast<int64>(payload);
}


// ImGuiPayload access functions
fn_export double imgui_payload_is_data_type(double payload_id, const char* type) {
	const ImGuiPayload* payload = reinterpret_cast<const ImGuiPayload*>((int64)payload_id);
	return payload->IsDataType(type);
}

fn_export double imgui_payload_is_preview(double payload_id) {
	const ImGuiPayload* payload = reinterpret_cast<const ImGuiPayload*>((int64)payload_id);
	return payload->IsPreview();
}

fn_export double imgui_payload_is_delivery(double payload_id) {
	const ImGuiPayload* payload = reinterpret_cast<const ImGuiPayload*>((int64)payload_id);
	return payload->IsDelivery();
}

fn_export double _imgui_payload_get_data(double payload_id) {
	const ImGuiPayload* payload = reinterpret_cast<const ImGuiPayload*>((int64)payload_id);
	
	float* data = (float*)payload->Data;

	ext_buffer->seek(0);
	ext_buffer->write(payload->DataSize);
	for (int i = 0; i < payload->DataSize; ++i) {
		ext_buffer->write(data[i]);
	}
	
	return 0.0;
}

fn_export double imgui_payload_get_data_size(double payload_id) {
	const ImGuiPayload* payload = reinterpret_cast<const ImGuiPayload*>((int64)payload_id);
	return payload->DataSize;
}


// Disabling [BETA API]
fn_export double _imgui_begin_disabled(double disabled) {
	ImGui::BeginDisabled(disabled);
	return 0.0;
}

fn_export double imgui_end_disabled() {
	ImGui::EndDisabled();
	return 0.0;
}


// Clipping
fn_export double _imgui_push_clip_rect() {
	ext_buffer->seek(0);
	ImVec2 clip_rect_min(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 clip_rect_max(ext_buffer->read_float(), ext_buffer->read_float());
	bool intersect_with_current_clip_rect = ext_buffer->read_float();
	
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

fn_export double _imgui_set_keyboard_focus_here(double offset) {
	ImGui::SetKeyboardFocusHere(offset);
	return 0.0;
}


// Item/Widget Utilities and Query functions
fn_export double _imgui_is_item_hovered(double flags) {
	return ImGui::IsItemHovered(flags);
}

fn_export double imgui_is_item_active() {
	return ImGui::IsItemActive();
}

fn_export double imgui_is_item_focused() {
	return ImGui::IsItemFocused();
}

fn_export double _imgui_is_item_clicked(double mouse_button) {
	return ImGui::IsItemClicked(mouse_button);
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

fn_export double _imgui_get_item_rect_min() {
	ImVec2 size = ImGui::GetItemRectMin();
	ext_buffer->seek(0);
	ext_buffer->write(size.x);
	ext_buffer->write(size.y);
	return 0.0;
}

fn_export double _imgui_get_item_rect_max() {
	ImVec2 size = ImGui::GetItemRectMax();
	ext_buffer->seek(0);
	ext_buffer->write(size.x);
	ext_buffer->write(size.y);
	return 0.0;
}

fn_export double _imgui_get_item_rect_size() {
	ImVec2 size = ImGui::GetItemRectSize();
	ext_buffer->seek(0);
	ext_buffer->write(size.x);
	ext_buffer->write(size.y);
	return 0.0;
}

fn_export double imgui_set_item_allow_overlap() {
	ImGui::SetItemAllowOverlap();
	return 0.0;
}


// Background/Foreground draw lists
fn_export double imgui_get_background_drawlist() {
	ImDrawList* list = ImGui::GetBackgroundDrawList();
	return reinterpret_cast<int64>(list);
}

fn_export double imgui_get_foreground_drawlist() {
	ImDrawList* list = ImGui::GetForegroundDrawList();
	return reinterpret_cast<int64>(list);
}


// Misc. Utilities
fn_export double _imgui_is_rect_visible() {
	ext_buffer->seek(0);
	ImVec2 size(ext_buffer->read_float(), ext_buffer->read_float());
	return ImGui::IsRectVisible(size);
}

fn_export double _imgui_is_rect_visible_minmax() {
	ext_buffer->seek(0);
	ImVec2 rect_min(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 rect_max(ext_buffer->read_float(), ext_buffer->read_float());
	return ImGui::IsRectVisible(rect_min,rect_max);
}

fn_export double imgui_get_time() {
	return ImGui::GetTime();
}

fn_export double imgui_get_frame_count() {
	return ImGui::GetFrameCount();
}

fn_export double imgui_get_drawlist_shared_data() {
	ImDrawListSharedData* data = ImGui::GetDrawListSharedData();
	return reinterpret_cast<int64>(data);
}

fn_export const char* imgui_get_style_color_name(double idx) {
	return ImGui::GetStyleColorName(idx);
}

fn_export double _imgui_begin_child_frame() {
	ext_buffer->seek(0);
	ImGuiID id = ext_buffer->read_float();
	ImVec2 size(ext_buffer->read_float(), ext_buffer->read_float());
	ImGuiWindowFlags flags = ext_buffer->read_float();
	
	return ImGui::BeginChildFrame(id, size, flags);
}

fn_export double imgui_end_child_frame() {
	ImGui::EndChildFrame();
	return 0.0;
}


// Text Utilities
fn_export double _imgui_get_calc_text_size(const char* text, const char* text_end) {
	ext_buffer->seek(0);
	bool hide_text_after_double_hash = ext_buffer->read_float();
	float wrap_width = ext_buffer->read_float();

	ImVec2 size = ImGui::CalcTextSize(text, text_end, hide_text_after_double_hash, wrap_width);
	ext_buffer->seek(0);
	ext_buffer->write(size.x);
	ext_buffer->write(size.y);
	return 0.0;
}


// Color Utilities
fn_export double _imgui_color_convert_u32_to_float4(double colU32) {
	
	ImVec4 colF4 = ImGui::ColorConvertU32ToFloat4(colU32);

	ext_buffer->seek(0);
	ext_buffer->write(colF4.x);
	ext_buffer->write(colF4.y);
	ext_buffer->write(colF4.z);
	ext_buffer->write(colF4.w);

	return 0.0;
}

fn_export double _imgui_color_convert_float4_to_u32() {
	ext_buffer->seek(0);
	ImVec4 colF4(ext_buffer->read_float(), ext_buffer->read_float(), ext_buffer->read_float(), ext_buffer->read_float());
	return ImGui::ColorConvertFloat4ToU32(colF4);
}

fn_export double _imgui_color_convert_rgb_to_hsv() {
	ext_buffer->seek(0);
	float f[3] = { ext_buffer->read_float(), ext_buffer->read_float(), ext_buffer->read_float() };
	float hsv[3] = { 0.0, 0.0, 0.0 };
	ImGui::ColorConvertRGBtoHSV(f[0], f[1], f[2], hsv[0], hsv[1], hsv[2]);

	ext_buffer->seek(0);
	ext_buffer->write(hsv[0]);
	ext_buffer->write(hsv[1]);
	ext_buffer->write(hsv[2]);

	return 0.0;
}

fn_export double _imgui_color_convert_hsv_to_rgb() {
	ext_buffer->seek(0);
	float h = ext_buffer->read_float();
	float s = ext_buffer->read_float();
	float v = ext_buffer->read_float();
	float r, g, b;
	ImGui::ColorConvertHSVtoRGB(h, s, v, r, g, b);

	ext_buffer->seek(0);
	ext_buffer->write(r);
	ext_buffer->write(g);
	ext_buffer->write(b);

	return 0.0;
}


// Input Utilities: Keyboard
fn_export double imgui_is_key_down(double key) {
	return ImGui::IsKeyDown(key);
}

fn_export double _imgui_is_key_pressed(double key,double repeat) {
	return ImGui::IsKeyPressed(key,repeat);
}

fn_export double imgui_is_key_released(double key) {
	return ImGui::IsKeyReleased(key);
}

fn_export double imgui_get_key_pressed_amount(double key, double repeat_delay, double rate) {
	return ImGui::GetKeyPressedAmount(key, repeat_delay, rate);
}

fn_export const char* imgui_get_key_name(double key) {
	return ImGui::GetKeyName(key);
}

fn_export double imgui_set_next_frame_want_capture_keyboard(double want_capture) {
	ImGui::SetNextFrameWantCaptureKeyboard(want_capture);
	return 0.0;
}


// Input Utilities: Mouse
fn_export double imgui_is_mouse_down(double button) {
	return ImGui::IsMouseDown(button);
}

fn_export double _imgui_is_mouse_clicked(double button, double repeat) {
	return ImGui::IsMouseClicked(button, repeat);
}

fn_export double imgui_is_mouse_released(double button) {
	return ImGui::IsMouseReleased(button);
}

fn_export double imgui_is_mouse_double_clicked(double button) {
	return ImGui::IsMouseDoubleClicked(button);
}

fn_export double imgui_get_mouse_clicked_count(double button) {
	return ImGui::GetMouseClickedCount(button);
}

fn_export double _imgui_is_mouse_hovering_rect() {
	ext_buffer->seek(0);
	ImVec2 r_min(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 r_max(ext_buffer->read_float(), ext_buffer->read_float());
	bool clip = ext_buffer->read_float();
	return ImGui::IsMouseHoveringRect(r_min, r_max, clip);
}

fn_export double imgui_is_mouse_pos_valid() {
	return ImGui::IsMousePosValid();
}

fn_export double imgui_is_any_mouse_down() {
	return ImGui::IsAnyMouseDown();
}

fn_export double _imgui_get_mouse_pos() {
	ImVec2 pos = ImGui::GetMousePos();
	ext_buffer->seek(0);
	ext_buffer->write(pos.x);
	ext_buffer->write(pos.y);
	return 0.0;
}

fn_export double _imgui_get_mouse_pos_on_opening_current_popup() {
	ImVec2 pos = ImGui::GetMousePosOnOpeningCurrentPopup();
	ext_buffer->seek(0);
	ext_buffer->write(pos.x);
	ext_buffer->write(pos.y);
	return 0.0;
}

fn_export double _imgui_is_mouse_dragging(double button, double lock_threshold) {
	return ImGui::IsMouseDragging(button, lock_threshold);
}

fn_export double _imgui_get_mouse_drag_delta(double button, double lock_threshold) {

	ImVec2 delta = ImGui::GetMouseDragDelta(button, lock_threshold);

	ext_buffer->seek(0);
	ext_buffer->write(delta.x);
	ext_buffer->write(delta.y);

	return 0.0;

}

fn_export double _imgui_reset_mouse_drag_delta(double button) {
	ImGui::ResetMouseDragDelta(button);
	return 0.0;
}

fn_export double imgui_get_mouse_cursor() {
	return ImGui::GetMouseCursor();
}

fn_export double imgui_set_mouse_cursor(double cursor_type) {
	ImGui::SetMouseCursor(cursor_type);
	return 0.0;
}

fn_export double imgui_set_next_frame_want_capture_mouse(double want_capture) {
	ImGui::SetNextFrameWantCaptureMouse(want_capture);
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



//-----------------------------------------------------------------------------
// [SECTION] ImDrawList functions
//-----------------------------------------------------------------------------

// ImDrawList: Push/Pop functions
fn_export double _imgui_drawlist_push_clip_rect(double id) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);

	ext_buffer->seek(0);
	ImVec2 clip_rect_min(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 clip_rect_max(ext_buffer->read_float(), ext_buffer->read_float());
	bool intersect_with_current_clip_rect = ext_buffer->read_float();

	drawlist->PushClipRect(clip_rect_min, clip_rect_max, intersect_with_current_clip_rect);

	return 0.0;
}

fn_export double imgui_drawlist_push_clip_rect_fullscreen(double id) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);
	drawlist->PushClipRectFullScreen();
	return 0.0;
}

fn_export double imgui_drawlist_pop_clip_rect(double id) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);
	drawlist->PopClipRect();
	return 0.0;
}

fn_export double imgui_drawlist_push_texture_id(double id, const char* tex_name) {
	if (!_imgui_is_image_loaded(tex_name)) return -1.0;

	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);
	ImTextureID tex_id = ext_loaded_image_map[tex_name];
	drawlist->PushTextureID(tex_id);
	return 0.0;
}

fn_export double imgui_drawlist_pop_texture_id(double id) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);
	drawlist->PopTextureID();
	return 0.0;
}

fn_export double _imgui_drawlist_get_clip_rect_min(double id) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);
	ImVec2 v = drawlist->GetClipRectMin();
	ext_buffer->seek(0);
	ext_buffer->write(v.x);
	ext_buffer->write(v.y);
	return 0.0;
}

fn_export double _imgui_drawlist_get_clip_rect_max(double id) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);
	ImVec2 v = drawlist->GetClipRectMax();
	ext_buffer->seek(0);
	ext_buffer->write(v.x);
	ext_buffer->write(v.y);
	return 0.0;
}


// ImDrawList: Primitives
fn_export double _imgui_drawlist_add_line(double id) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);

	ext_buffer->seek(0);
	ImVec2 p1(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 p2(ext_buffer->read_float(), ext_buffer->read_float());
	ImU32 col = ext_buffer->read_float();
	float thickness = ext_buffer->read_float();
	drawlist->AddLine(p1, p2, col, thickness);

	return 0.0;
}

fn_export double _imgui_drawlist_add_rect(double id) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);

	ext_buffer->seek(0);
	ImVec2 p_min(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 p_max(ext_buffer->read_float(), ext_buffer->read_float());
	ImU32 col = ext_buffer->read_float();
	float rounding = ext_buffer->read_float();
	ImDrawFlags flags = ext_buffer->read_float();
	float thickness = ext_buffer->read_float();
	drawlist->AddRect(p_min,p_max,col,rounding,flags,thickness);

	return 0.0;
}

fn_export double _imgui_drawlist_add_rect_filled(double id) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);

	ext_buffer->seek(0);
	ImVec2 p_min(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 p_max(ext_buffer->read_float(), ext_buffer->read_float());
	ImU32 col = ext_buffer->read_float();
	float rounding = ext_buffer->read_float();
	ImDrawFlags flags = ext_buffer->read_float();
	drawlist->AddRectFilled(p_min, p_max, col, rounding, flags);

	return 0.0;
}

fn_export double _imgui_drawlist_add_rect_filled_multicolor(double id) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);

	ext_buffer->seek(0);
	ImVec2 p_min(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 p_max(ext_buffer->read_float(), ext_buffer->read_float());
	ImU32 col_upr_left = ext_buffer->read_float();
	ImU32 col_upr_right = ext_buffer->read_float();
	ImU32 col_bot_right = ext_buffer->read_float();
	ImU32 col_bot_left = ext_buffer->read_float();

	drawlist->AddRectFilledMultiColor(p_min, p_max, col_upr_left, col_upr_right, col_bot_right, col_bot_left);

	return 0.0;
}

fn_export double _imgui_drawlist_add_quad(double id) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);

	ext_buffer->seek(0);
	ImVec2 p1(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 p2(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 p3(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 p4(ext_buffer->read_float(), ext_buffer->read_float());
	ImU32 col = ext_buffer->read_float();
	float thickness = ext_buffer->read_float();
	drawlist->AddQuad(p1, p2, p3, p4, col, thickness);

	return 0.0;
}

fn_export double _imgui_drawlist_add_quad_filled(double id) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);

	ext_buffer->seek(0);
	ImVec2 p1(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 p2(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 p3(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 p4(ext_buffer->read_float(), ext_buffer->read_float());
	ImU32 col = ext_buffer->read_float();
	drawlist->AddQuadFilled(p1, p2, p3, p4, col);

	return 0.0;
}

fn_export double _imgui_drawlist_add_triangle(double id) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);

	ext_buffer->seek(0);
	ImVec2 p1(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 p2(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 p3(ext_buffer->read_float(), ext_buffer->read_float());
	ImU32 col = ext_buffer->read_float();
	float thickness = ext_buffer->read_float();
	drawlist->AddTriangle(p1, p2, p3, col, thickness);

	return 0.0;
}

fn_export double _imgui_drawlist_add_triangle_filled(double id) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);

	ext_buffer->seek(0);
	ImVec2 p1(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 p2(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 p3(ext_buffer->read_float(), ext_buffer->read_float());
	ImU32 col = ext_buffer->read_float();
	drawlist->AddTriangleFilled(p1, p2, p3, col);

	return 0.0;
}

fn_export double _imgui_drawlist_add_circle(double id) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);

	ext_buffer->seek(0);
	ImVec2 center(ext_buffer->read_float(), ext_buffer->read_float());
	float radius = ext_buffer->read_float();
	ImU32 col = ext_buffer->read_float();
	int num_segments = ext_buffer->read_float();
	float thickness = ext_buffer->read_float();

	drawlist->AddCircle(center, radius, col, num_segments, thickness);

	return 0.0;
}

fn_export double _imgui_drawlist_add_circle_filled(double id) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);

	ext_buffer->seek(0);
	ImVec2 center(ext_buffer->read_float(), ext_buffer->read_float());
	float radius = ext_buffer->read_float();
	ImU32 col = ext_buffer->read_float();
	int num_segments = ext_buffer->read_float();

	drawlist->AddCircleFilled(center, radius, col, num_segments);

	return 0.0;
}

fn_export double _imgui_drawlist_add_ngon(double id) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);

	ext_buffer->seek(0);
	ImVec2 center(ext_buffer->read_float(), ext_buffer->read_float());
	float radius = ext_buffer->read_float();
	ImU32 col = ext_buffer->read_float();
	int num_segments = ext_buffer->read_float();
	float thickness = ext_buffer->read_float();

	drawlist->AddNgon(center, radius, col, num_segments, thickness);

	return 0.0;
}

fn_export double _imgui_drawlist_add_ngon_filled(double id) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);

	ext_buffer->seek(0);
	ImVec2 center(ext_buffer->read_float(), ext_buffer->read_float());
	float radius = ext_buffer->read_float();
	ImU32 col = ext_buffer->read_float();
	int num_segments = ext_buffer->read_float();

	drawlist->AddNgonFilled(center, radius, col, num_segments);

	return 0.0;
}

fn_export double _imgui_drawlist_add_text(double id, const char* text_begin, const char* text_end) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);

	ext_buffer->seek(0);
	ImVec2 pos(ext_buffer->read_float(), ext_buffer->read_float());
	ImU32 col = ext_buffer->read_float();
	drawlist->AddText(pos, col, text_begin, text_end);

	return 0.0;
}

fn_export double _imgui_drawlist_add_font_text(double id, double font_id, const char* text_begin, const char* text_end) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);

	ImFont* font = reinterpret_cast<ImFont*>((int64)font_id);

	ext_buffer->seek(0);
	float font_size = ext_buffer->read_float();
	ImVec2 pos(ext_buffer->read_float(), ext_buffer->read_float());
	ImU32 col = ext_buffer->read_float();
	float wrap_width = ext_buffer->read_float();
	ImVec4 cpu_fine_clip_rect(ext_buffer->read_float(), ext_buffer->read_float(), ext_buffer->read_float(), ext_buffer->read_float());

	drawlist->AddText(font, font_size, pos, col, text_begin, text_end, wrap_width,&cpu_fine_clip_rect);

	return 0.0;
}

fn_export double _imgui_drawlist_add_polyline(double id) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);

	ext_buffer->seek(0);
	int num_points = ext_buffer->read_float();
	std::vector<ImVec2> points;
	for (int i = 0; i < num_points; ++i) {
		ImVec2 v(ext_buffer->read_float(), ext_buffer->read_float());
		points.push_back(v);
	}
	ImU32 col = ext_buffer->read_float();
	ImDrawFlags flags = ext_buffer->read_float();
	float thickness = ext_buffer->read_float();


	drawlist->AddPolyline(&points[0], num_points, col, flags, thickness);

	return 0.0;
}

fn_export double _imgui_drawlist_add_convex_poly_filled(double id) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);

	ext_buffer->seek(0);
	int num_points = ext_buffer->read_float();
	std::vector<ImVec2> points;
	for (int i = 0; i < num_points; ++i) {
		ImVec2 v(ext_buffer->read_float(), ext_buffer->read_float());
		points.push_back(v);
	}
	ImU32 col = ext_buffer->read_float();


	drawlist->AddConvexPolyFilled(&points[0], num_points, col);

	return 0.0;
}

fn_export double _imgui_drawlist_add_bezier_cubic(double id) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);

	ext_buffer->seek(0);
	ImVec2 p1(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 p2(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 p3(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 p4(ext_buffer->read_float(), ext_buffer->read_float());
	ImU32 col = ext_buffer->read_float();
	float thickness = ext_buffer->read_float();
	int num_segments = ext_buffer->read_float();
	drawlist->AddBezierCubic(p1, p2, p3, p4, col, thickness, num_segments);

	return 0.0;
}

fn_export double _imgui_drawlist_add_bezier_quadratic(double id) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);

	ext_buffer->seek(0);
	ImVec2 p1(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 p2(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 p3(ext_buffer->read_float(), ext_buffer->read_float());
	ImU32 col = ext_buffer->read_float();
	float thickness = ext_buffer->read_float();
	int num_segments = ext_buffer->read_float();
	drawlist->AddBezierQuadratic(p1, p2, p3, col, thickness, num_segments);

	return 0.0;
}


// ImDrawList: Image Primitives
fn_export double _imgui_drawlist_add_image(double id, const char* tex_name) {

	if (!_imgui_is_image_loaded(tex_name)) return -1.0;

	ImTextureID tex_id = ext_loaded_image_map[tex_name];

	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);

	ext_buffer->seek(0);
	ImVec2 p_min(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 p_max(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 uv_min(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 uv_max(ext_buffer->read_float(), ext_buffer->read_float());
	ImU32 col = ext_buffer->read_float();
	drawlist->AddImage(tex_id, p_min, p_max, uv_min, uv_max, col);

	return 0.0;
}

fn_export double _imgui_drawlist_add_image_quad(double id, const char* tex_name) {

	if (!_imgui_is_image_loaded(tex_name)) return -1.0;

	ImTextureID tex_id = ext_loaded_image_map[tex_name];

	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);

	ext_buffer->seek(0);
	ImVec2 p1(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 p2(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 p3(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 p4(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 uv1(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 uv2(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 uv3(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 uv4(ext_buffer->read_float(), ext_buffer->read_float());
	ImU32 col = ext_buffer->read_float();
	drawlist->AddImageQuad(tex_id, p1, p2, p3, p4, uv1, uv2, uv3, uv4, col);

	return 0.0;
}

fn_export double _imgui_drawlist_add_image_rounded(double id, const char* tex_name) {

	if (!_imgui_is_image_loaded(tex_name)) return -1.0;

	ImTextureID tex_id = ext_loaded_image_map[tex_name];

	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);

	ext_buffer->seek(0);
	ImVec2 p_min(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 p_max(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 uv_min(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 uv_max(ext_buffer->read_float(), ext_buffer->read_float());
	ImU32 col = ext_buffer->read_float();
	float rounding = ext_buffer->read_float();
	ImDrawFlags flags = ext_buffer->read_float();
	drawlist->AddImageRounded(tex_id, p_min, p_max, uv_min, uv_max, col, rounding, flags);

	return 0.0;
}


// ImDrawList: Stateful path API
fn_export double imgui_drawlist_path_clear(double id) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);

	drawlist->PathClear();

	return 0.0;
}

fn_export double _imgui_drawlist_path_line_to(double id) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);

	ext_buffer->seek(0);
	ImVec2 pos(ext_buffer->read_float(), ext_buffer->read_float());

	drawlist->PathLineTo(pos);

	return 0.0;
}

fn_export double _imgui_drawlist_path_line_to_merge_duplicate(double id) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);

	ext_buffer->seek(0);
	ImVec2 pos(ext_buffer->read_float(), ext_buffer->read_float());

	drawlist->PathLineToMergeDuplicate(pos);

	return 0.0;
}

fn_export double _imgui_drawlist_path_fill_convex(double id) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);

	ext_buffer->seek(0);
	ImU32 col = ext_buffer->read_float();

	drawlist->PathFillConvex(col);

	return 0.0;
}

fn_export double _imgui_drawlist_path_stroke(double id) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);

	ext_buffer->seek(0);
	ImU32 col = ext_buffer->read_float();
	ImDrawFlags flags = ext_buffer->read_float();
	float thickness = ext_buffer->read_float();

	drawlist->PathStroke(col, flags, thickness);

	return 0.0;
}

fn_export double _imgui_drawlist_path_arc_to(double id) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);

	ext_buffer->seek(0);
	ImVec2 center(ext_buffer->read_float(), ext_buffer->read_float());
	float radius = ext_buffer->read_float();
	float a_min = ext_buffer->read_float();
	float a_max = ext_buffer->read_float();
	int num_segments = ext_buffer->read_float();

	drawlist->PathArcTo(center, radius, a_min, a_max, num_segments);

	return 0.0;
}

fn_export double _imgui_drawlist_path_arc_to_fast(double id) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);

	ext_buffer->seek(0);
	ImVec2 center(ext_buffer->read_float(), ext_buffer->read_float());
	float radius = ext_buffer->read_float();
	float a_min_of_12 = ext_buffer->read_float();
	float a_max_of_12 = ext_buffer->read_float();

	drawlist->PathArcToFast(center, radius, a_min_of_12, a_max_of_12);

	return 0.0;
}

fn_export double _imgui_drawlist_path_bezier_cubic_curve_to(double id) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);

	ext_buffer->seek(0);
	ImVec2 p2(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 p3(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 p4(ext_buffer->read_float(), ext_buffer->read_float());
	int num_segments = ext_buffer->read_float();

	drawlist->PathBezierCubicCurveTo(p2, p3, p4, num_segments);

	return 0.0;
}

fn_export double _imgui_drawlist_path_bezier_quadratic_curve_to(double id) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);

	ext_buffer->seek(0);
	ImVec2 p2(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 p3(ext_buffer->read_float(), ext_buffer->read_float());
	int num_segments = ext_buffer->read_float();

	drawlist->PathBezierQuadraticCurveTo(p2, p3, num_segments);

	return 0.0;
}

fn_export double _imgui_drawlist_path_rect(double id) {
	ImDrawList* drawlist = reinterpret_cast<ImDrawList*>((int64)id);

	ext_buffer->seek(0);
	ImVec2 rect_min(ext_buffer->read_float(), ext_buffer->read_float());
	ImVec2 rect_max(ext_buffer->read_float(), ext_buffer->read_float());
	float rounding = ext_buffer->read_float();
	ImDrawFlags flags = ext_buffer->read_float();

	drawlist->PathRect(rect_min,rect_max,rounding,flags);

	return 0.0;
}


// ImFontAtlas functions

fn_export double imgui_fonts_add_font_default(double id) {
	ImFontAtlas* fonts = reinterpret_cast<ImFontAtlas*>((int64)id);
	ImFont* font = fonts->AddFontDefault();
	return reinterpret_cast<int64>(font);
}

fn_export double _imgui_fonts_add_font_from_file_ttf(double id, const char* filename) {
	ext_buffer->seek(0);
	ImFontAtlas* fonts = reinterpret_cast<ImFontAtlas*>((int64)id);
	float size_pixels = ext_buffer->read_float();
	ImWchar* glyph_ranges = reinterpret_cast<ImWchar*>((int64)ext_buffer->read_float());
	ImFont* font = fonts->AddFontFromFileTTF(filename, size_pixels, NULL, glyph_ranges);
	return reinterpret_cast<int64>(font);
}

fn_export double imgui_fonts_build(double id) {
	ImFontAtlas* fonts = reinterpret_cast<ImFontAtlas*>((int64)id);
	return fonts->Build();
}

fn_export double imgui_fonts_get_glyph_range_default(double id) {
	ImFontAtlas* fonts = reinterpret_cast<ImFontAtlas*>((int64)id);
	const ImWchar* glyph_range = fonts->GetGlyphRangesDefault();
	return reinterpret_cast<int64>(glyph_range);
}

fn_export double imgui_fonts_get_glyph_range_korean(double id) {
	ImFontAtlas* fonts = reinterpret_cast<ImFontAtlas*>((int64)id);
	const ImWchar* glyph_range = fonts->GetGlyphRangesKorean();
	return reinterpret_cast<int64>(glyph_range);
}

fn_export double imgui_fonts_get_glyph_range_japanese(double id) {
	ImFontAtlas* fonts = reinterpret_cast<ImFontAtlas*>((int64)id);
	const ImWchar* glyph_range = fonts->GetGlyphRangesJapanese();
	return reinterpret_cast<int64>(glyph_range);
}

fn_export double imgui_fonts_get_glyph_range_chinese_full(double id) {
	ImFontAtlas* fonts = reinterpret_cast<ImFontAtlas*>((int64)id);
	const ImWchar* glyph_range = fonts->GetGlyphRangesChineseFull();
	return reinterpret_cast<int64>(glyph_range);
}

fn_export double imgui_fonts_get_glyph_range_chinese_simplified_common(double id) {
	ImFontAtlas* fonts = reinterpret_cast<ImFontAtlas*>((int64)id);
	const ImWchar* glyph_range = fonts->GetGlyphRangesChineseSimplifiedCommon();
	return reinterpret_cast<int64>(glyph_range);
}

fn_export double imgui_fonts_get_glyph_range_cyrillic(double id) {
	ImFontAtlas* fonts = reinterpret_cast<ImFontAtlas*>((int64)id);
	const ImWchar* glyph_range = fonts->GetGlyphRangesCyrillic();
	return reinterpret_cast<int64>(glyph_range);
}

fn_export double imgui_fonts_get_glyph_range_thai(double id) {
	ImFontAtlas* fonts = reinterpret_cast<ImFontAtlas*>((int64)id);
	const ImWchar* glyph_range = fonts->GetGlyphRangesThai();
	return reinterpret_cast<int64>(glyph_range);
}

fn_export double imgui_fonts_get_glyph_range_vietnamese(double id) {
	ImFontAtlas* fonts = reinterpret_cast<ImFontAtlas*>((int64)id);
	const ImWchar* glyph_range = fonts->GetGlyphRangesVietnamese();
	return reinterpret_cast<int64>(glyph_range);
}



//-----------------------------------------------------------------------------
// [SECTION] ImGuiTableSortSpecs/ImGuiTableColumnSortSpecs access
//-----------------------------------------------------------------------------
// do I even need this? 





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

fn_export double _imgui_style_get_window_min_size(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ImVec2 min_size = style_ptr->WindowMinSize;
	ext_buffer->seek(0);
	ext_buffer->write(min_size.x);
	ext_buffer->write(min_size.y);
	return 0.0;
}

fn_export double _imgui_style_get_window_title_align(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ImVec2 title_align = style_ptr->WindowTitleAlign;
	ext_buffer->seek(0);
	ext_buffer->write(title_align.x);
	ext_buffer->write(title_align.y);
	return 0.0;
}

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

fn_export double _imgui_style_get_item_spacing(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ImVec2 spacing = style_ptr->ItemSpacing;
	ext_buffer->seek(0);
	ext_buffer->write(spacing.x);
	ext_buffer->write(spacing.y);
	return 0.0;
}

fn_export double _imgui_style_get_item_inner_spacing(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ImVec2 spacing = style_ptr->ItemInnerSpacing;
	ext_buffer->seek(0);
	ext_buffer->write(spacing.x);
	ext_buffer->write(spacing.y);
	return 0.0;
}

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

fn_export double imgui_style_get_color_button_position(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	return style_ptr->ColorButtonPosition;
}

fn_export double _imgui_style_get_button_text_align(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ImVec2 text_align = style_ptr->ButtonTextAlign;
	ext_buffer->seek(0);
	ext_buffer->write(text_align.x);
	ext_buffer->write(text_align.y);
	return 0.0;
}

fn_export double _imgui_style_get_selectable_text_align(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ImVec2 text_align = style_ptr->SelectableTextAlign;
	ext_buffer->seek(0);
	ext_buffer->write(text_align.x);
	ext_buffer->write(text_align.y);
	return 0.0;
}

fn_export double _imgui_style_get_display_window_padding(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ImVec2 padding = style_ptr->DisplayWindowPadding;
	ext_buffer->seek(0);
	ext_buffer->write(padding.x);
	ext_buffer->write(padding.y);
	return 0.0;
}

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

fn_export double _imgui_style_get_color(double style, double index) {
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

fn_export double _imgui_style_set_window_padding(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ext_buffer->seek(0);
	ImVec2 padding(ext_buffer->read_float(), ext_buffer->read_float());
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

fn_export double _imgui_style_set_window_min_size(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ext_buffer->seek(0);
	ImVec2 size(ext_buffer->read_float(), ext_buffer->read_float());
	style_ptr->WindowMinSize = size;
	return 0.0;
}

fn_export double _imgui_style_set_window_title_align(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ext_buffer->seek(0);
	ImVec2 align(ext_buffer->read_float(), ext_buffer->read_float());
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

fn_export double _imgui_style_set_frame_padding(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ext_buffer->seek(0);
	ImVec2 padding(ext_buffer->read_float(), ext_buffer->read_float());
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

fn_export double _imgui_style_set_item_spacing(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ext_buffer->seek(0);
	ImVec2 spacing(ext_buffer->read_float(), ext_buffer->read_float());
	style_ptr->ItemSpacing = spacing;
	return 0.0;
}

fn_export double _imgui_style_set_item_inner_spacing(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ext_buffer->seek(0);
	ImVec2 spacing(ext_buffer->read_float(), ext_buffer->read_float());
	style_ptr->ItemInnerSpacing = spacing;
	return 0.0;
}

fn_export double _imgui_style_set_cell_padding(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ext_buffer->seek(0);
	ImVec2 padding(ext_buffer->read_float(), ext_buffer->read_float());
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

fn_export double _imgui_style_set_button_text_align(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ext_buffer->seek(0);
	ImVec2 align(ext_buffer->read_float(), ext_buffer->read_float());
	style_ptr->ButtonTextAlign = align;
	return 0.0;
}

fn_export double _imgui_style_set_selectable_text_align(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ext_buffer->seek(0);
	ImVec2 align(ext_buffer->read_float(), ext_buffer->read_float());
	style_ptr->SelectableTextAlign = align;
	return 0.0;
}

fn_export double _imgui_style_set_display_window_padding(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ext_buffer->seek(0);
	ImVec2 padding(ext_buffer->read_float(), ext_buffer->read_float());
	style_ptr->DisplayWindowPadding = padding;
	return 0.0;
}

fn_export double _imgui_style_set_display_safe_area_padding(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ext_buffer->seek(0);
	ImVec2 padding(ext_buffer->read_float(), ext_buffer->read_float());
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

fn_export double _imgui_style_set_color(double style) {
	ImGuiStyle* style_ptr = reinterpret_cast<ImGuiStyle*>((int64)style);
	ext_buffer->seek(0);
	ImGuiCol index = ext_buffer->read_float();
	ImVec4 color(ext_buffer->read_float(), ext_buffer->read_float(), ext_buffer->read_float(), ext_buffer->read_float());
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

fn_export double imgui_io_get_fonts(double io) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	ImFontAtlas* fonts = io_ptr->Fonts;
	return reinterpret_cast<int64>(fonts);
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

fn_export double imgui_io_get_key_ctrl(double io) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	return io_ptr->KeyCtrl;
}

fn_export double imgui_io_get_key_shift(double io) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	return io_ptr->KeyShift;
}

fn_export double imgui_io_get_key_alt(double io) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	return io_ptr->KeyAlt;
}

fn_export double imgui_io_get_key_super(double io) {
	ImGuiIO* io_ptr = reinterpret_cast<ImGuiIO*>((int64)io);
	return io_ptr->KeySuper;
}