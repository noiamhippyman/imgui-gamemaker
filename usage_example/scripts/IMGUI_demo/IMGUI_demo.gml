/*

Index of this file:

// [SECTION] Forward Declarations, Helpers
// [SECTION] Demo Window / imgui_show_demo_window_gml()
// [SECTION] About Window / imgui_show_about_window_gml()
// [SECTION] Style Editor / imgui_show_style_editor_gml()
// [SECTION] Example App: Main Menu Bar / imgui_show_example_app_main_menu_bar_gml()
// [SECTION] Example App: Debug Console / imgui_show_example_app_console_gml()
// [SECTION] Example App: Debug Log / imgui_show_example_app_log_gml()
// [SECTION] Example App: Simple Layout / imgui_show_example_app_layout_gml()
// [SECTION] Example App: Property Editor / imgui_show_example_app_property_editor_gml()
// [SECTION] Example App: Long Text / imgui_show_example_app_long_text_gml()
// [SECTION] Example App: Auto Resize / imgui_show_example_app_auto_resize_gml()
// [SECTION] Example App: Constrained Resize / imgui_show_example_app_constrained_resize_gml()
// [SECTION] Example App: Simple Overlay / imgui_show_example_app_simple_overlay_gml()
// [SECTION] Example App: Manipulating Window Titles / imgui_show_example_app_window_titles_gml()
// [SECTION] Example App: Custom Rendering using ImDrawList API / imgui_show_example_app_custom_rendering_gml()
// [SECTION] Example App: Docking, DockSpace / imgui_show_example_app_dockspace_gml()
// [SECTION] Example App: Documents Handling / imgui_show_example_app_documents_gml()

*/

// Helper to display a little (?) mark which shows a tooltip when hovered.
function imgui_help_marker(desc) {
	imgui_text_disabled("(?)");
	if (imgui_is_item_hovered()) {
		imgui_begin_tooltip();
		imgui_push_text_wrap_pos(imgui_get_font_size() * 35);
		imgui_text_unformatted(desc);
		imgui_pop_text_wrap_pos();
		imgui_end_tooltip();
	}
}

function imgui_show_docking_disabled_message() {
	imgui_text("ERROR: Docking is not enabled! See Demo > Configuration.");
	if (imgui_small_button("Enable Docking")) {
		var flags = imgui_io_get_config_flags();
		flags |= ImGuiConfigFlags.DockingEnable;
		imgui_io_set_config_flags(flags);
	}
}

// Helper to display basic user controls.
function imgui_show_user_guide_gml() {
	imgui_bullet_text("Double-click on title bar to collapse window.");
    imgui_bullet_text("Click and drag on lower corner to resize window\n (double-click to auto fit window to its contents).");
    imgui_bullet_text("CTRL+Click on a slider or drag box to input value as text.");
    imgui_bullet_text("TAB/SHIFT+TAB to cycle through keyboard editable fields.");
    if (imgui_io_get_font_allow_user_scaling())
        imgui_bullet_text("CTRL+Mouse Wheel to zoom window contents.");
    imgui_bullet_text("While inputing text:\n");
    imgui_indent(0);
    imgui_bullet_text("CTRL+Left/Right to word jump.");
    imgui_bullet_text("CTRL+A or double-click to select all.");
    imgui_bullet_text("CTRL+X/C/V to use clipboard cut/copy/paste.");
    imgui_bullet_text("CTRL+Z,CTRL+Y to undo/redo.");
    imgui_bullet_text("ESCAPE to revert.");
    imgui_bullet_text("You can apply arithmetic operators +,*,/ on numerical values.\nUse +- to subtract.");
    imgui_unindent(0);
    imgui_bullet_text("With keyboard navigation enabled:");
    imgui_indent(0);
    imgui_bullet_text("Arrow keys to navigate.");
    imgui_bullet_text("Space to activate a widget.");
    imgui_bullet_text("Return to input text into a widget.");
    imgui_bullet_text("Escape to deactivate a widget, close popup, exit child window.");
    imgui_bullet_text("Alt to jump to the menu layer of a window.");
    imgui_bullet_text("CTRL+Tab to select a window.");
    imgui_unindent(0);
}

//-----------------------------------------------------------------------------
// [SECTION] Demo Window / imgui_show_demo_window_gml()
//-----------------------------------------------------------------------------
// - imgui_show_demo_window_widgets_gml()
// - imgui_show_demo_window_layout_gml()
// - imgui_show_demo_window_popups_gml()
// - imgui_show_demo_window_columns_gml()
// - imgui_show_demo_window_misc_gml()
//-----------------------------------------------------------------------------

function imgui_show_demo_window_widgets_gml() {}
function imgui_show_demo_window_layout_gml() {}
function imgui_show_demo_window_popups_gml() {}
function imgui_show_demo_window_columns_gml() {}
function imgui_show_demo_window_misc_gml() {}

// Demonstrate most Dear ImGui features (this is big function!)
// You may execute this function to experiment with the UI and understand what it does.
// You may then search for keywords in the code when you are interested by a specific feature.
function imgui_show_demo_window_gml(open) {}

//-----------------------------------------------------------------------------
// [SECTION] About Window / imgui_show_about_window_gml()
// Access from Dear ImGui Demo -> Tools -> About
//-----------------------------------------------------------------------------

function imgui_show_about_window_gml(open) {}

//-----------------------------------------------------------------------------
// [SECTION] Style Editor / imgui_show_style_editor_gml()
//-----------------------------------------------------------------------------
// - imgui_show_style_selector_gml()
// - imgui_show_font_selector_gml()
// - imgui_show_style_editor_gml()
//-----------------------------------------------------------------------------

// Demo helper function to select among default colors. See imgui_show_style_editor_gml() for more advanced options.
// Here we use the simplified imgui_combo() api that packs items into a single literal string.
// Useful for quick combo boxes where the choices are known locally.
function imgui_show_style_selector_gml(label) {}

// Demo helper function to select among loaded fonts.
// Here we use the regular imgui_begin_combo()/imgui_end_combo() api which is more the more flexible one.
function imgui_show_font_selector_gml(label) {}

function imgui_show_style_editor_gml() {}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Main Menu Bar / imgui_show_example_app_main_menu_bar_gml()
//-----------------------------------------------------------------------------
// - imgui_show_example_app_main_menu_bar_gml()
// - imgui_show_example_menu_file_gml()
//-----------------------------------------------------------------------------

// Demonstrate creating a "main" fullscreen menu bar and populating it.
// Note the difference between imgui_begin_main_menu_bar() and imgui_begin_menu_bar():
// - imgui_begin_menu_bar() = menu-bar inside current window (which needs the ImGuiWindowFlags_MenuBar flag!)
// - imgui_begin_main_menu_bar() = helper to create menu-bar-sized window at the top of the main viewport + call imgui_begin_menu_bar() into it.
function imgui_show_example_app_main_menu_bar_gml() {}

// Note that shortcuts are currently provided for display only
// (future version will add explicit flags to BeginMenu() to request processing shortcuts)
function imgui_show_example_menu_file_gml() {}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Debug Console / imgui_show_example_app_console_gml()
//-----------------------------------------------------------------------------

// Demonstrate creating a simple console window, with scrolling, filtering, completion and history.
// For the console example, we are using a more C++ like approach of declaring a class to hold both data and functions.
function imgui_show_example_app_console_gml(open) {}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Debug Log / imgui_show_example_app_log_gml()
//-----------------------------------------------------------------------------

// Demonstrate creating a simple log window with basic filtering.
function imgui_show_example_app_log_gml(open) {}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Simple Layout / imgui_show_example_app_layout_gml()
//-----------------------------------------------------------------------------

// Demonstrate create a window with multiple child windows.
function imgui_show_example_app_layout_gml(open) {}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Property Editor / imgui_show_example_app_property_editor_gml()
//-----------------------------------------------------------------------------

function imgui_show_placeholder_object_gml(prefix,uid) {}

// Demonstrate create a simple property editor.
function imgui_show_example_app_property_editor_gml(open) {}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Long Text / imgui_show_example_app_long_text_gml()
//-----------------------------------------------------------------------------

// Demonstrate/test rendering huge amount of text, and the incidence of clipping.
function imgui_show_example_app_long_text_gml(open) {}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Auto Resize / imgui_show_example_app_auto_resize_gml()
//-----------------------------------------------------------------------------

// Demonstrate creating a window which gets auto-resized according to its content.
function imgui_show_example_app_auto_resize_gml(open) {}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Constrained Resize / imgui_show_example_app_constrained_resize_gml()
//-----------------------------------------------------------------------------

// Demonstrate creating a window with custom resize constraints.
function imgui_show_example_app_constrained_resize_gml(open) {}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Simple Overlay / imgui_show_example_app_simple_overlay_gml()
//-----------------------------------------------------------------------------

// Demonstrate creating a simple static window with no decoration
// + a context-menu to choose which corner of the screen to use.
function imgui_show_example_app_simple_overlay_gml(open) {}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Manipulating Window Titles / imgui_show_example_app_window_titles_gml()
//-----------------------------------------------------------------------------

// Demonstrate using "##" and "###" in identifiers to manipulate ID generation.
// This apply to all regular items as well.
// Read FAQ section "How can I have multiple widgets with the same label?" for details.
function imgui_show_example_app_window_titles_gml(open) {}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Custom Rendering using ImDrawList API / imgui_show_example_app_custom_rendering_gml()
//-----------------------------------------------------------------------------

// Demonstrate using the low-level ImDrawList to draw custom shapes.
function imgui_show_example_app_custom_rendering_gml(open) {} // TODO: Need to wrap functions to draw with ImDrawList.

//-----------------------------------------------------------------------------
// [SECTION] Example App: Docking, DockSpace / imgui_show_example_app_dockspace_gml()
//-----------------------------------------------------------------------------

// Demonstrate using imgui_dockspace() to create an explicit docking node within an existing window.
// Note that you already dock windows into each others _without_ a imgui_dockspace() by just moving windows
// from their title bar (or by holding SHIFT if imgui_set_config_docking_with_shift() is set).
// imgui_dockspace() is only useful to construct to a central location for your application.
function imgui_show_example_app_dockspace_gml(open) {} // TODO: Need to wrap functions for this too.

//-----------------------------------------------------------------------------
// [SECTION] Example App: Documents Handling / imgui_show_example_app_documents_gml()
//-----------------------------------------------------------------------------

function imgui_show_example_app_documents_gml(open) {}