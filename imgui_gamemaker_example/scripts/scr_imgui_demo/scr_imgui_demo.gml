function imgui_help_marker(desc) {
	imgui_text_disabled("(?)");
	if (imgui_is_item_hovered()) {
		imgui_begin_tooltip();
		imgui_push_text_wrap_pos(imgui_get_font_size() * 35);
		imgui_text_unformatted(desc)
		imgui_pop_text_wrap_pos();
		imgui_end_tooltip();
	}
}

function imgui_demo_show_docking_disabled_message() {
	var io = imgui_get_io();
	imgui_text("ERROR: Docking is not enabled! See Demo > Configuration.");
	imgui_text("Set config_flags |= ImGuiConfigFlags.DockingEnable in your code, or ");
	imgui_same_line(0,0);
	if (imgui_small_button("click here")) {
		var config_flags = imgui_io_get_config_flags(io);
		config_flags |= ImGuiConfigFlags.DockingEnable;
		imgui_io_set_config_flags(io,config_flags);
	}
}

// Helper to display basic user controls.
function imgui_demo_show_user_guide() {
    var io = imgui_get_io();
    imgui_bullet_text("Double-click on title bar to collapse window.");
    imgui_bullet_text("Click and drag on lower corner to resize window\n (double-click to auto fit window to its contents).");
    imgui_bullet_text("CTRL+Click on a slider or drag box to input value as text.");
    imgui_bullet_text("TAB/SHIFT+TAB to cycle through keyboard editable fields.");
	imgui_bullet_text("CTRL+Tab to select a window.");
	if (imgui_io_get_font_allow_user_scaling(io))
        imgui_bullet_text("CTRL+Mouse Wheel to zoom window contents.");
    imgui_bullet_text("While inputing text:\n");
    imgui_indent();
    imgui_bullet_text("CTRL+Left/Right to word jump.");
    imgui_bullet_text("CTRL+A or double-click to select all.");
    imgui_bullet_text("CTRL+X/C/V to use clipboard cut/copy/paste.");
    imgui_bullet_text("CTRL+Z,CTRL+Y to undo/redo.");
    imgui_bullet_text("ESCAPE to revert.");
    imgui_unindent();
    imgui_bullet_text("With keyboard navigation enabled:");
    imgui_indent();
    imgui_bullet_text("Arrow keys to navigate.");
    imgui_bullet_text("Space to activate a widget.");
    imgui_bullet_text("Return to input text into a widget.");
    imgui_bullet_text("Escape to deactivate a widget, close popup, exit child window.");
    imgui_bullet_text("Alt to jump to the menu layer of a window.");
    imgui_unindent();
}


function imgui_demo_show_demo_window_widgets() {
	var ret = imgui_collapsing_header("Widgets");
	if (!ret[0]) return;
	
	static disable_all = false;
	if (disable_all) imgui_begin_disabled();
	
	if (imgui_tree_node("Basic")) {
		
		static basic_button_clicked = 0;
		if (imgui_button("Button")) basic_button_clicked++;
		
		if (basic_button_clicked & 1) {
			imgui_same_line();
			imgui_text("Thanks for clicking me!");
		}
		
		static basic_checkbox_check = true;
		ret = imgui_checkbox("checkbox",basic_checkbox_check);
		basic_checkbox_check = ret[1];
		
		static basic_radio_button_e = 0;
		if (imgui_radio_button("radio a",basic_radio_button_e == 0)) basic_radio_button_e = 0; imgui_same_line();
		if (imgui_radio_button("radio b",basic_radio_button_e == 1)) basic_radio_button_e = 1; imgui_same_line();
		if (imgui_radio_button("radio c",basic_radio_button_e == 2)) basic_radio_button_e = 2;
		
		// Color buttons, demonstrate using imgui_push_id() to add unique identifier in the ID stack, and changing style.
		for (var i = 0; i < 7; ++i) {
			if (i > 0) imgui_same_line();
			imgui_push_id(i);
			var col_btn = imgui_color_convert_hsv_to_rgb([i/7,0.6,0.6]); col_btn[3] = 1;
			var col_btn_hvr = imgui_color_convert_hsv_to_rgb([i/7,0.7,0.7]); col_btn_hvr[3] = 1;
			var col_btn_active = imgui_color_convert_hsv_to_rgb([i/7,0.8,0.8]); col_btn_active[3] = 1;
			imgui_push_style_color(ImGuiCol.Button, col_btn);
			imgui_push_style_color(ImGuiCol.ButtonHovered,col_btn_hvr);
			imgui_push_style_color(ImGuiCol.ButtonActive,col_btn_active);
			imgui_button("Click");
			imgui_pop_style_color(3);
			imgui_pop_id();
		}
		
		// Use imgui_align_text_to_frame_padding() to align text baseline to the baseline of framed widgets elements
        // (otherwise a Text+SameLine+Button sequence will have the text a little too high by default!)
        // See 'Demo->Layout->Text Baseline Alignment' for details.
        imgui_align_text_to_frame_padding();
		imgui_text("Hold to repeat:");
		imgui_same_line();
		
		// Arrow buttons with Repeater
		static basic_repeat_counter = 0;
		var style = imgui_get_style();
		var spacing = imgui_style_get_item_inner_spacing(style)[0];
		imgui_push_button_repeat(true);
		if (imgui_arrow_button("##left",ImGuiDir.Left)) basic_repeat_counter--;
		imgui_same_line(0,spacing);
		if (imgui_arrow_button("##right",ImGuiDir.Right)) basic_repeat_counter++;
		imgui_pop_button_repeat();
		imgui_same_line();
		imgui_text(string(basic_repeat_counter));
		
		imgui_text("Hover over me");
		if (imgui_is_item_hovered()) imgui_set_tooltip("I am a tooltip");
		
		imgui_same_line();
		imgui_text("- or me");
		if (imgui_is_item_hovered()) {
			imgui_begin_tooltip();
			imgui_text("I am a fancy tooltip");
			static basic_fancy_tooltip_arr = [0.6,0.1,1,0.5,0.92,0.1,0.2];
			imgui_plot_lines("Curve",basic_fancy_tooltip_arr,array_length(basic_fancy_tooltip_arr));
			imgui_end_tooltip();
		}
		imgui_separator();
		imgui_label_text("label", "Value");
		
		{
		
			var basic_combo_items = ["AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIIIIII", "JJJJ", "KKKKKKK"];
			static basic_combo_item_current = 0;
			ret = imgui_combo("combo",basic_combo_item_current,basic_combo_items,array_length(basic_combo_items));
			basic_combo_item_current = ret[1];
			imgui_same_line();
			imgui_help_marker("Using the simplified one-liner Combo API here.\nRefer to the \"Combo\" section below for an explanation of how to use the more flexible and general imgui_begin_combo/imgui_end_combo API.");
		
		}
		
		{
		
			static basic_input_text_str0 = "Hello, world!";
			ret = imgui_input_text("input text",basic_input_text_str0);
			if (ret[0]) basic_input_text_str0 = ret[1];
			imgui_same_line();
			imgui_help_marker("USER:\nHold SHIFT or use mouse to select text.\nCTRL+Left/Right to word jump.\nCTRL+A or double-click to select all.\nCTRL+X,CTRL+C,CTRL+V clipboard.\nCTRL+Z,CTRL+Y undo/redo.\nESCAPE to revert.\n\nPROGRAMMER:\n");
			
			static basic_input_text_str1 = "";
			ret = imgui_input_text_with_hint("input text (w/ hint)", "enter text here", basic_input_text_str1);
			if (ret[0]) basic_input_text_str1 = ret[1];
			
			
		
		}
		
		imgui_tree_pop();
	}
	
	if (imgui_tree_node("Trees")) {
		imgui_tree_pop();
	}
	
	if (imgui_tree_node("Collapsing Headers")) {
		imgui_tree_pop();
	}
	
	if (imgui_tree_node("Bullets")) {
		imgui_tree_pop();
	}
	
	if (imgui_tree_node("Text")) {
		imgui_tree_pop();
	}
	
	if (imgui_tree_node("Images")) {
		imgui_tree_pop();
	}
	
	if (imgui_tree_node("Combo")) {
		imgui_tree_pop();
	}
	
	if (imgui_tree_node("List Boxes")) {
		imgui_tree_pop();
	}
	
	if (imgui_tree_node("Selectables")) {
		imgui_tree_pop();
	}
	
	if (imgui_tree_node("Text Input")) {
		imgui_tree_pop();
	}
	
	if (imgui_tree_node("Tabs")) {
		imgui_tree_pop();
	}
	
	if (imgui_tree_node("Plotting")) {
		imgui_tree_pop();
	}
	
	if (imgui_tree_node("Color/Picker Widgets")) {
		imgui_tree_pop();
	}
	
	if (imgui_tree_node("Drag/Slider Flags")) {
		imgui_tree_pop();
	}
	
	if (imgui_tree_node("Range Widgets")) {
		imgui_tree_pop();
	}
	
	if (imgui_tree_node("Data Types")) {
		imgui_tree_pop();
	}
	
	if (imgui_tree_node("Multi-component Widgets")) {
		imgui_tree_pop();
	}
	
	if (imgui_tree_node("Vertical Sliders")) {
		imgui_tree_pop();
	}
	
	if (imgui_tree_node("Drag and Drop")) {
		imgui_tree_pop();
	}
	
	if (imgui_tree_node("Querying Item Status (Edited/Active/Hovered etc.)")) {
		imgui_tree_pop();
	}
	
	if (imgui_tree_node("Querying Window Status (Focused/Hovered etc.)")) {
		imgui_tree_pop();
	}
	
	
	
	
	
	if (disable_all) imgui_end_disabled();
	
	if (imgui_tree_node("Disable Block")) {
		ret = imgui_checkbox("Disable entire section above", disable_all);
		disable_all = ret[1];
		
		imgui_same_line();
		imgui_help_marker("Demonstrate using imgui_begin_disabled()/imgui_end_disabled() across this section.");
		imgui_tree_pop();
	}
}