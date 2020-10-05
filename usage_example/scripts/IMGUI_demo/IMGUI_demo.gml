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

function imgui_show_demo_window_widgets_gml() {
	static clicked = 0;
	static check = true;
	static e = 0;
	static counter = 0;
	static item_current = 0;
	static str0 = "Hello, world!";
	static str1 = "";
	static i0 = 123;
	static f0 = 0.001;
	static f1 = 1;
	static vec4a = [ 0.1,0.2,0.3,0.44 ];
	
	var ret = imgui_collapsing_header("Widgets",noone,0);
	if (!ret[0])
		return;
	
	if (imgui_tree_node("Basic")) {
		//static clicked = 0;
		if (imgui_button("Button",0,0)) {
			clicked++;
		}
		
		if (clicked & 1) {
			imgui_same_line(0,0);
			imgui_text("Thanks for clicking me!");
		}
		
		//static check = true;
		ret = imgui_checkbox("checkbox",check);
		if (ret[0]) check = ret[1];
		
		//static e = 0;
		if (imgui_radio_button("radio a", e == 0)) e = 0; 
		imgui_same_line(0,0);
		if (imgui_radio_button("radio b", e == 1)) e = 1; 
		imgui_same_line(0,0);
		if (imgui_radio_button("radio c", e == 2)) e = 2;
		
		// Color buttons, demonstrate using imgui_push_id() to add unique identifier in the ID stack, and changing style.
		for (var i = 0; i < 7; ++i) {
			if (i > 0) imgui_same_line(0,0);
			
			imgui_push_id(i);
			var color = imgui_color_convert_hsv_to_rgb(i/7,0.6,0.6);
			imgui_push_style_color(ImGuiCol.Button,color[0],color[1],color[2],1);
			
			color = imgui_color_convert_hsv_to_rgb(i/7,0.7,0.7);
			imgui_push_style_color(ImGuiCol.Button,color[0],color[1],color[2],1);
			
			color = imgui_color_convert_hsv_to_rgb(i/7,0.8,0.8);
			imgui_push_style_color(ImGuiCol.Button,color[0],color[1],color[2],1);
			imgui_button("Click",0,0);
			imgui_pop_style_color(3);
			imgui_pop_id();
		}
		
		// Use imgui_align_text_to_frame_padding() to align text baseline to the baseline of framed widgets elements
        // (otherwise a Text+SameLine+Button sequence will have the text a little too high by default!)
        // See 'Demo->Layout->Text Baseline Alignment' for details.
		imgui_align_text_to_frame_padding();
		imgui_text("Hold to repeat: ");
		imgui_same_line(0,0);
		
		// Arrow buttons with Repeater
		//static counter = 0;
		var spacing = imgui_style_get_item_inner_spacing()[0];
		imgui_push_button_repeat(true);
		if (imgui_arrow_button("##left",ImGuiDir.Left)) counter--;
		imgui_same_line(0,spacing);
		if (imgui_arrow_button("##right",ImGuiDir.Right)) counter++;
		imgui_pop_button_repeat();
		imgui_same_line(0,0);
		imgui_text(string(counter));
		
		imgui_text("Hover over me");
		if (imgui_is_item_hovered()) {
			imgui_set_tooltip("I am a tooltip");
		}
		
		imgui_same_line(0,0);
		imgui_text("- or me");
		if (imgui_is_item_hovered()) {
			imgui_begin_tooltip();
			imgui_text("I am a fancy tooltip");
			var arr = [ 0.6, 0.1, 1, 0.5, 0.92, 0.1, 0.2 ];
			imgui_plot_lines("Curve",arr,0,noone,noone,noone,0,0);
			imgui_end_tooltip();
		}
		
		imgui_separator();
		
		imgui_label_text("label","Value");
		
		{
			// Using the _simplified_ one-liner Combo() api here
	        // See "Combo" section for examples of how to use the more complete imgui_begin_combo()/imgui_end_combo() api.
			var items = [ "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIIIIII", "JJJJ", "KKKKKKK" ];
			//static item_current = 0;
			ret = imgui_combo("combo",item_current,items,array_length(items),-1);
			if (ret[0]) item_current = ret[1];
			imgui_same_line(0,0);
			imgui_help_marker("Refer to the \"Combo\" section below for an explanation of the full imgui_begin_combo/imgui_end_combo API, and demonstration of various flags.\n");
		}
		
		{
			//static str0 = "Hello, world!";
			ret = imgui_input_text("input text",str0,0);
			if (ret[0]) str0 = ret[1];
			imgui_same_line(0,0);
			imgui_help_marker(
				"USER:\n" +
                "Hold SHIFT or use mouse to select text.\n" +
                "CTRL+Left/Right to word jump.\n" +
                "CTRL+A or double-click to select all.\n" +
                "CTRL+X,CTRL+C,CTRL+V clipboard.\n" +
                "CTRL+Z,CTRL+Y undo/redo.\n" +
                "ESCAPE to revert."
			);
			
			//static str1 = "";
			ret = imgui_input_text_with_hint("input text(w/ hint)","enter text here",str1,0);
			if (ret[0]) str1 = ret[1];
			
			//static i0 = 123;
			ret = imgui_input_int("input int",i0,1,100,0);
			if (ret[0]) i0 = ret[1];
			imgui_same_line(0,0);
			imgui_help_marker(
				"You can apply arithmetic operators +,*,/ on numerical values.\n" +
                "  e.g. [ 100 ], input \'*2\', result becomes [ 200 ]\n" +
                "Use +- to subtract."
			);
			
			//static f0 = 0.001;
			ret = imgui_input_float("input float",f0,0.01,1,"%.3f",0);
			if (ret[0]) f0 = ret[1];
			
			//static f1 = 1;
			ret = imgui_input_float("input scientific",f1,0.0,0.0,"%.0e",0);
			if (ret[0]) f1 = ret[1];
			imgui_same_line(0,0);
			imgui_help_marker(
				"You can input value using the scientific notation,\n" +
                "  e.g. \"1e+8\" becomes \"100000000\"."
			);
			
			//static vec4a = [ 0.1,0.2,0.3,0.44 ];
			ret = imgui_input_float3("input float3", vec4a, "%.3f",0);
			if (ret[0]) {
				vec4a[0] = ret[1];
				vec4a[1] = ret[2];
				vec4a[2] = ret[3];
			}
		}
		
		{
			
		}
		
		imgui_tree_pop();
	}
}
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