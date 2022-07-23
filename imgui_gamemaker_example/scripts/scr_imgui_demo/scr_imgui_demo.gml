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
			
			static basic_input_i0 = 123;
			ret = imgui_input_int("input int", basic_input_i0);
			if (ret[0]) basic_input_i0 = ret[1];
			
			static basic_input_f0 = 0.001;
			ret = imgui_input_float("input float", basic_input_f0,0.01,1,"%.3f");
			if (ret[0]) basic_input_f0 = ret[1];
			
			static basic_input_d0 = 999999.00000001;
			ret = imgui_input_double("input double", basic_input_d0,0.01,1,"%.8f");
			if (ret[0]) basic_input_d0 = ret[1];
			
			static basic_input_f1 = 10000000000;
			ret = imgui_input_float("input scientific", basic_input_f1,0,0,"%e");
			if (ret[0]) basic_input_f1 = ret[1];
			imgui_same_line();
			imgui_help_marker("You can input value using the scientific notation.\n e.g. \"1e+8\" becomes \"100000000\"");
			
			static basic_input_vec4a = [0.1,0.2,0.3,0.44];
			ret = imgui_input_float3("input float3", basic_input_vec4a);
			if (ret[0]) array_copy(basic_input_vec4a,0,ret,1,3);
		
		}
		
		{
		
			static basic_drag_i1 = 50;
			static basic_drag_i2 = 42;
			ret = imgui_drag_int("drag int",basic_drag_i1,1);
			if (ret[0]) basic_drag_i1 = ret[1];
			imgui_same_line();
			imgui_help_marker("Click and drag to edit value.\nHold SHIFT/ALT for faster/slower edit.\nDouble-click or CTRL+Click to input value.");
			
			ret = imgui_drag_int("drag int 0..100", basic_drag_i2, 1, 0, 100, "%d%%", ImGuiSliderFlags.AlwaysClamp);
			if (ret[0]) basic_drag_i2 = ret[1];
			
			static basic_drag_float_f1 = 1;
			static basic_drag_float_f2 = 0.0067;
			ret = imgui_drag_float("drag float", basic_drag_float_f1, 0.005);
			if (ret[0]) basic_drag_float_f1 = ret[1];
			ret = imgui_drag_float("drag small float", basic_drag_float_f2, 0.0001,0,0,"%.06fns");
			if (ret[0]) basic_drag_float_f2 = ret[1];
			
		}
		
		{
			
			static basic_slider_i1 = 0;
			ret = imgui_slider_int("slider int",basic_slider_i1,-1,3);
			if (ret[0]) basic_slider_i1 = ret[1];
			imgui_same_line();
			imgui_help_marker("CTRL+Click to input value.");
			
			static basic_slider_f1 = 0.123;
			static basic_slider_f2 = 0;
			ret = imgui_slider_float("slider float",basic_slider_f1,0.0,1.0,"ratio = %.3f");
			if (ret[0]) basic_slider_f1 = ret[1];
			ret = imgui_slider_float("slider float (log)",basic_slider_f2,-10.0,10.0,"%.4f",ImGuiSliderFlags.Logarithmic);
			if (ret[0]) basic_slider_f2 = ret[1];
			
			static basic_slider_angle = 0;
			ret = imgui_slider_angle("slider angle",basic_slider_angle);
			if (ret[0]) basic_slider_angle = ret[1];
			
			enum Element { Fire, Earth, Air, Water, COUNT }
			static basic_slider_elem = Element.Fire;
			var elem_names = ["Fire","Earth","Air","Water"];
			var elem_name = (basic_slider_elem >= 0 && basic_slider_elem < Element.COUNT) ? elem_names[basic_slider_elem] : "Unknown";
			ret = imgui_slider_int("slider enum",basic_slider_elem,0,Element.COUNT-1,elem_name);
			if (ret[0]) basic_slider_elem = ret[1];
			imgui_same_line();
			imgui_help_marker("Using the format string parameter to display a name instead of the underlying integer.");
			
		}
		
		{
			
			static basic_coloredit_col1 = [ 1.0, 0.0, 0.2 ];
			static basic_coloredit_col2 = [ 0.4, 0.7, 0.0, 0.5 ];
			
			ret = imgui_color_edit3("color 1", basic_coloredit_col1);
			if (ret[0]) array_copy(basic_coloredit_col1,0,ret,1,3);
			imgui_same_line();
			imgui_help_marker("Click on the color square to open a color picker.\nClick and hold to use drag and drop.\nRight-click on the color square to show options.\nCTRL+Click on individual component to input value.\n");
			ret = imgui_color_edit4("color 2", basic_coloredit_col2);
			if (ret[0]) array_copy(basic_coloredit_col2,0,ret,1,4);
			
		}
		
		{
			
			var basic_listbox_items = ["Apple", "Banana", "Cherry", "Kiwi", "Mango", "Orange", "Pineapple", "Strawberry", "Watermelon"];
			static basic_listbox_item_current = 1;
			ret = imgui_list_box("listbox",basic_listbox_item_current,basic_listbox_items,array_length(basic_listbox_items),4);
			if (ret[0]) basic_listbox_item_current = ret[1];
			
		}
		
		imgui_tree_pop();
	}
	
	if (imgui_tree_node("Trees")) {
		
		if (imgui_tree_node("Basic trees")) {
			for (var i = 0; i < 5; ++i) {
				if (i == 0) imgui_set_next_item_open(true,ImGuiCond.Once);
				if (imgui_tree_node("Child " + string(i))) {
					imgui_text("blah blah");
					imgui_same_line();
					if (imgui_small_button("button")) {}
					imgui_tree_pop();
				}
			}
			imgui_tree_pop();
		}
		
		if (imgui_tree_node("Advanced, with Selectable nodes")) {
			imgui_help_marker("This is a more typical looking tree with selectable nodes.\nClick to select, CTRL+Click to toggle, click on arrows or double-click to open.");
			static trees_adv_base_flags = ImGuiTreeNodeFlags.OpenOnArrow | ImGuiTreeNodeFlags.OpenOnDoubleClick | ImGuiTreeNodeFlags.SpanAvailWidth;
			static tree_adv_align_label_with_current_x_position = false;
			static tree_adv_test_drag_and_drop = false;
			
			ret = imgui_checkbox_flags("ImGuiTreeNodesFlags.OpenOnArrow", trees_adv_base_flags, ImGuiTreeNodeFlags.OpenOnArrow);
			if (ret[0]) trees_adv_base_flags = ret[1];
			ret = imgui_checkbox_flags("ImGuiTreeNodesFlags.OpenOnDoubleClick", trees_adv_base_flags, ImGuiTreeNodeFlags.OpenOnDoubleClick);
			if (ret[0]) trees_adv_base_flags = ret[1];
			ret = imgui_checkbox_flags("ImGuiTreeNodesFlags.SpanAvailWidth", trees_adv_base_flags, ImGuiTreeNodeFlags.SpanAvailWidth); imgui_same_line(); imgui_help_marker("Extend hit area to all available width instead of allowing more items to be laid out after the node.");
			if (ret[0]) trees_adv_base_flags = ret[1];
			ret = imgui_checkbox_flags("ImGuiTreeNodesFlags.SpanFullWidth", trees_adv_base_flags, ImGuiTreeNodeFlags.SpanFullWidth);
			if (ret[0]) trees_adv_base_flags = ret[1];
			
			ret = imgui_checkbox("Align label with current X position",tree_adv_align_label_with_current_x_position);
			if (ret[0]) tree_adv_align_label_with_current_x_position = ret[1];
			ret = imgui_checkbox("Test tree node as a drag source",tree_adv_test_drag_and_drop);
			if (ret[0]) tree_adv_test_drag_and_drop = ret[1];
			imgui_text("Hello!");
			if (tree_adv_align_label_with_current_x_position) imgui_unindent(imgui_get_tree_node_to_label_spacing());
			
			static trees_adv_selection_mask = 1<<2;
			var node_clicked = -1;
			for (var i = 0; i < 6; ++i) {
				var node_flags = trees_adv_base_flags;
				var is_selected = (trees_adv_selection_mask & (1<<i)) != 0
				if (is_selected) node_flags |= ImGuiTreeNodeFlags.Selected;
				if (i < 3) {
					var node_open = imgui_tree_node_ex("Selectable Node " + string(i),node_flags);
					if (imgui_is_item_clicked() && !imgui_is_item_toggled_open()) node_clicked = i;
					
					if (tree_adv_test_drag_and_drop && imgui_begin_drag_drop_source()) {
						imgui_set_drag_drop_payload("_TREENODE");
						imgui_text("This is a drag and drop source");
						imgui_end_drag_drop_source();
					}
					
					if (node_open) {
						imgui_bullet_text("Blah blah\nBlah Blah");
						imgui_tree_pop();
					}
				} else {
					node_flags |= ImGuiTreeNodeFlags.Leaf | ImGuiTreeNodeFlags.NoTreePushOnOpen;
					imgui_tree_node_ex("Selectable Leaf " + string(i),node_flags);
					if (imgui_is_item_clicked() && !imgui_is_item_toggled_open()) node_clicked = i;
					if (tree_adv_test_drag_and_drop && imgui_begin_drag_drop_source()) {
						imgui_set_drag_drop_payload("_TREENODE");
						imgui_text("This is a drag and drop source");
						imgui_end_drag_drop_source();
					}
				}
			}
			
			if (node_clicked != -1) {
				var io = imgui_get_io();
				if (imgui_io_get_key_ctrl(io)) {
					trees_adv_selection_mask ^= (1 << node_clicked);
				} else {
					trees_adv_selection_mask = (1 << node_clicked);
				}
			}
			
			if (tree_adv_align_label_with_current_x_position) imgui_indent(imgui_get_tree_node_to_label_spacing());
			
			imgui_tree_pop();
		}
		
		
		
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