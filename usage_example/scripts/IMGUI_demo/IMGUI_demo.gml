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
	static input_i0 = 123;
	static input_f0 = 0.001;
	static input_f1 = 1;
	static vec4a = [ 0.1,0.2,0.3,0.44 ];
	static drag_i1 = 50;
	static drag_i2 = 42;
	static drag_f1 = 1;
	static drag_f2 = 0.0067;
	static slider_i1 = 0;
	static slider_f1 = 0.123;
	static slider_f2 = 0;
	static angle = 0;
	enum Element { Fire, Earth, Air, Water, COUNT }
	static elem = Element.Fire;
	static col1 = [ 1, 0, 0.2 ];
	static col2 = [ 0.4, 0.7, 0.0, 0.5 ];
	static list_item_current = 1;
	static base_flags = ImGuiTreeNodeFlags.OpenOnArrow | ImGuiTreeNodeFlags.OpenOnDoubleClick | ImGuiTreeNodeFlags.SpanAvailWidth;
	static align_label_with_current_x_position = false;
	static test_drag_and_drop = false;
	static selection_mask = (1 << 2);
	static closable_group = true;
	static wrap_width = 200;
	static buf = "日本語";
	
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
			
			//static input_i0 = 123;
			ret = imgui_input_int("input int",input_i0,1,100,0);
			if (ret[0]) input_i0 = ret[1];
			imgui_same_line(0,0);
			imgui_help_marker(
				"You can apply arithmetic operators +,*,/ on numerical values.\n" +
                "  e.g. [ 100 ], input \'*2\', result becomes [ 200 ]\n" +
                "Use +- to subtract."
			);
			
			//static input_f0 = 0.001;
			ret = imgui_input_float("input float",input_f0,0.01,1,"%.3f",0);
			if (ret[0]) input_f0 = ret[1];
			
			//static f1 = 1;
			ret = imgui_input_float("input scientific",input_f1,0.0,0.0,"%.0e",0);
			if (ret[0]) input_f1 = ret[1];
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
			
			//static i1 = 50;
			//static i2 = 42;
			ret = imgui_drag_int("drag int",drag_i1,1,0,0,"%.3f",0);
			if (ret[0]) drag_i1 = ret[1];
			imgui_same_line(0,0);
			imgui_help_marker(
				"Click and drag to edit value.\n" +
                "Hold SHIFT/ALT for faster/slower edit.\n" +
                "Double-click or CTRL+click to input value."
			);
			
			ret = imgui_drag_int("drag int 0..100", drag_i2,1,0,100,"%d%%",ImGuiSliderFlags.ClampOnInput);
			if (ret[0]) drag_i2 = ret[1];
			
			//static f1 = 1;
			//static f2 = 0.0067;
			ret = imgui_drag_float("drag float",drag_f1,0.005,0,0,"%.3f",0);
			if (ret[0]) drag_f1 = ret[1];
			ret = imgui_drag_float("drag small float",drag_f2,0.00001,0,0,"%.06f ns",0);
			if (ret[0]) drag_f2 = ret[1];
			
		}
		
		{
			//static slider_i1 = 0;
			ret = imgui_slider_int("slider int", slider_i1, -1,3,"%d",0);
			if (ret[0]) slider_i1 = ret[1];
			imgui_same_line(0,0);
			imgui_help_marker("CTRL+click to input value.");
			
			//static slider_f1 = 0.123;
			//static slider_f2 = 0;
			ret = imgui_slider_float("slider float", slider_f1, 0.0,1.0,"ratio = %.3f",0);
			if (ret[0]) slider_f1 = ret[1];
			ret = imgui_slider_float("slider float (log)", slider_f2, -10.0,10.0,"%.4f",ImGuiSliderFlags.Logarithmic);
			if (ret[0]) slider_f2 = ret[1];
			
			//static angle = 0;
			ret = imgui_slider_angle("slider angle",angle,-360,360,"%.0f deg",0);
			if (ret[0]) angle = ret[1];
			
			// Using the format string to display a name instead of an integer.
            // Here we completely omit '%d' from the format string, so it'll only display a name.
            // This technique can also be used with DragInt().
			//enum Element { Fire, Earth, Air, Water, COUNT }
			//static elem = Element.Fire;
			var elems_names = [ "Fire", "Earth", "Air", "Water" ];
			var elem_name = (elem >= 0 and elem < Element.COUNT) ? elems_names[elem] : "Unknown";
			ret = imgui_slider_int("slider enum",elem,0,Element.COUNT - 1, elem_name, 0);
			if (ret[0]) elem = ret[1];
			imgui_same_line(0,0);
			imgui_help_marker("Using the format string parameter to display a name instead of the underlying integer.");
		}
		
		{
			//static col1 = [ 1, 0, 0.2 ];
			//static col2 = [ 0.4, 0.7, 0.0, 0.5 ];
			ret = imgui_color_edit3("color 1", col1, 0);
			if (ret[0]) {
				col1[0] = ret[1];
				col1[1] = ret[2];
				col1[2] = ret[3];
			}
			imgui_same_line(0,0);
			imgui_help_marker(
				"Click on the colored square to open a color picker.\n" +
                "Click and hold to use drag and drop.\n" +
                "Right-click on the colored square to show options.\n" +
                "CTRL+click on individual component to input value.\n"
			);
			
			ret = imgui_color_edit4("color 2", col2, 0);
			if (ret[0]) {
				col2[0] = ret[1];
				col2[1] = ret[2];
				col2[2] = ret[3];
				col2[3] = ret[4];
			}
		}
		
		{
			//List box
			var list_items = [ "Apple", "Banana", "Cherry", "Kiwi", "Mango", "Orange", "Pineapple", "Strawberry", "Watermelon" ];
			//static list_item_current = 1;
			ret = imgui_list_box("listbox\n(single select)",list_item_current,list_items,array_length(list_items),4);
			if (ret[0]) list_item_current = ret[1];
		}
		
		imgui_tree_pop();
	}
	
	if (imgui_tree_node("Trees")) {
		
		if (imgui_tree_node("Basic Trees")) {
			for (var i = 0; i < 5; ++i) {
				// Use imgui_set_next_item_open() so set the default state of a node to be open. We could
                // also use imgui_tree_node_ex() with the ImGuiTreeNodeFlags.DefaultOpen flag to achieve the same thing!
				if (i == 0) imgui_set_next_item_open(true,ImGuiCond.Once);
				
				if (imgui_tree_node("Child " + string(i))) {
					imgui_text("blah blah");
					imgui_same_line(0,0);
					if (imgui_small_button("button")) {}
					imgui_tree_pop();
				}
			}
			imgui_tree_pop();
		}
		
		if (imgui_tree_node("Advanced, with Selectable nodes")) {
			
			imgui_help_marker(
				"This is a more typical looking tree with selectable nodes.\n" +
                "Click to select, CTRL+Click to toggle, click on arrows or double-click to open."
			);
			
			//static base_flags = ImGuiTreeNodeFlags.OpenOnArrow | ImGuiTreeNodeFlags.OpenOnDoubleClick | ImGuiTreeNodeFlags.SpanAvailWidth;
			//static align_label_with_current_x_position = false;
			//static test_drag_and_drop = false;
			
			ret = imgui_checkbox_flags("ImGuiTreeNodeFlags.OpenOnArrow", base_flags, ImGuiTreeNodeFlags.OpenOnArrow);
			if (ret[0]) base_flags = ret[1];
			ret = imgui_checkbox_flags("ImGuiTreeNodeFlags.OpenOnDoubleClick", base_flags, ImGuiTreeNodeFlags.OpenOnDoubleClick);
			if (ret[0]) base_flags = ret[1];
			ret = imgui_checkbox_flags("ImGuiTreeNodeFlags.SpanAvailWidth", base_flags, ImGuiTreeNodeFlags.SpanAvailWidth);
			if (ret[0]) base_flags = ret[1];
			ret = imgui_checkbox_flags("ImGuiTreeNodeFlags.SpanFullWidth", base_flags, ImGuiTreeNodeFlags.SpanFullWidth);
			if (ret[0]) base_flags = ret[1];
			ret = imgui_checkbox("Align label with current x position",align_label_with_current_x_position);
			if (ret[0]) align_label_with_current_x_position = ret[1];
			ret = imgui_checkbox("Test tree node as drag source",test_drag_and_drop);
			if (ret[0]) test_drag_and_drop = ret[1];
			imgui_text("Hello!");
			if (align_label_with_current_x_position) {
				imgui_unindent(imgui_get_tree_node_to_label_spacing());
			}
			
			// 'selection_mask' is dumb representation of what may be user-side selection state.
            //  You may retain selection state inside or outside your objects in whatever format you see fit.
            // 'node_clicked' is temporary storage of what node we have clicked to process selection at the end
            /// of the loop. May be a pointer to your own node type, etc.
			//static selection_mask = (1 << 2);
			var node_clicked = -1;
			for (var i = 0; i < 6; ++i) {
				// Disable the default "open on single-click behavior" + set Selected flag according to our selection.
				var node_flags = base_flags;
				var is_selected = (selection_mask & (1 << i)) != 0;
				if (is_selected) {
					node_flags |= ImGuiTreeNodeFlags.Selected;
				}
				
				if (i < 3) {
					// Items 0..2 are Tree Node
					var node_open = imgui_tree_node_ex("Selectable node " + string(i),node_flags);
					if (imgui_is_item_clicked(0)) node_clicked = i;
					
					if (test_drag_and_drop and imgui_begin_drag_drop_source(0)) {
						imgui_set_drag_drop_payload("_TREENODE",0);
						imgui_text("This is a drag and drop source");
						imgui_end_drag_drop_source();
					}
					if (node_open) {
						imgui_bullet_text("Blah blah\nBlah Blah");
						imgui_tree_pop();
					}
				} else {
					// Items 3..5 are Tree Leaves
                    // The only reason we use TreeNode at all is to allow selection of the leaf. Otherwise we can
                    // use imgui_bullet_text() or advance the cursor by imgui_get_tree_node_to_label_spacing() and call imgui_text().
                    node_flags |= ImGuiTreeNodeFlags.Leaf | ImGuiTreeNodeFlags.NoTreePushOnOpen; // ImGuiTreeNodeFlags.Bullet
					imgui_tree_node_ex("Selectable leaf " + string(i),node_flags);
					if (imgui_is_item_clicked(0)) {
						node_clicked = i;
					}
					if (test_drag_and_drop and imgui_begin_drag_drop_source(0)) {
						imgui_set_drag_drop_payload("_TREENODE",0);
						imgui_text("This is a drag and drop source");
						imgui_end_drag_drop_source();
					}
				}
			}
			
			if (node_clicked != -1) {
				// Update selection state
                // (process outside of tree loop to avoid visual inconsistencies during the clicking frame)
				if (imgui_io_get_key_ctrl()) {
					selection_mask ^= (1 << node_clicked);				// CTRL+click to toggle
				} else {//if (!(selection_mask & (1 << node_clicked)))	// Depending on selection behavior you want, may want to preserve selection when clicking on item that is part of the selection
					selection_mask = (1 << node_clicked);				// Click to single-select
				}
			}
			
			if (align_label_with_current_x_position) {
				imgui_indent(imgui_get_tree_node_to_label_spacing());
			}
			imgui_tree_pop();
		}
		
		imgui_tree_pop();
	}
	
	if (imgui_tree_node("Collapsing Headers")) {
		
		//static closable_group = true;
		ret = imgui_checkbox("Show 2nd header",closable_group);
		if (ret[0]) closable_group = ret[1];
		ret = imgui_collapsing_header("Header",noone,ImGuiTreeNodeFlags.None);
		if (ret[0]) {
			imgui_text("Is Item Hovered: " + string(imgui_is_item_hovered()));
			for (var i = 0; i < 5; ++i) {
				imgui_text("Some content " + string(i));
			}
		}
		
		ret = imgui_collapsing_header("Header 2",closable_group,0);
		if (ret[0]) {
			imgui_text("Is Item Hovered: " + string(imgui_is_item_hovered()));
			for (var i = 0; i < 5; ++i) {
				imgui_text("More content " + string(i));
			}
		}
		closable_group = ret[1];
		
		imgui_tree_pop();
	}
	
	if (imgui_tree_node("Bullets")) {
		
		imgui_bullet_text("Bullet point 1");
		imgui_bullet_text("Bullet point 2\nOn multiple lines");
		if (imgui_tree_node("Tree node")) {
			imgui_bullet_text("Another bullet point");
			imgui_tree_pop();
		}
		imgui_bullet(); imgui_text("Bullet point 3 (two calls)");
		imgui_bullet(); imgui_small_button("Button");
		
		imgui_tree_pop();
	}
	
	if (imgui_tree_node("Text")) {
		
		if (imgui_tree_node("Colored Text")) {
			// Using shortcut. You can use imgui_push_style_color()/imgui_pop_style_color() for more flexibility.
			imgui_text_colored(1,0,1,1,"Pink");
			imgui_text_colored(1,1,0,1,"Yellow");
			imgui_text_disabled("Disabled");
			imgui_same_line(0,0); imgui_help_marker("The TextDisabled color is stored in ImGuiStyle");
			imgui_tree_pop();
		}
		
		if (imgui_tree_node("Word Wrapping")) {
			imgui_text_wrapped(
				"This text should automatically wrap on the edge of the window. The current implementation " +
                "for text wrapping follows simple rules suitable for English and possibly other languages."
			);
			imgui_spacing();
			
			//static wrap_width = 200;
			ret = imgui_slider_float("Wrap width",wrap_width,-20,600,"%.0f",0);
			if (ret[0]) wrap_width = ret[1];
			
			for (var n = 0; n < 2; ++n) {
				imgui_text("Test paragraph " + string(n));
				var pos = imgui_get_cursor_screen_pos();
				var marker_min = [ pos[0] + wrap_width, pos[1] ];
				var marker_max = [ pos[0] + wrap_width + 10, pos[1] + imgui_get_text_line_height() ];
				imgui_push_text_wrap_pos(imgui_get_cursor_pos()[0] + wrap_width);
				if (n == 0) {
					imgui_text("The lazy dog is a good dog. This paragraph should fit within " + string(wrap_width) + " pixels. Testing a 1 character word. The quick brown fox jumps over the lazy dog.");
				} else {
					imgui_text("aaaaaaaa bbbbbbbb, c cccccccc,dddddddd. d eeeeeeee   ffffffff. gggggggg!hhhhhhhh");
				}
				
				var rmin = imgui_get_item_rect_min();
				var rmax = imgui_get_item_rect_max();
				imgui_drawlist_add_rect(rmin[0],rmin[1],rmax[0],rmax[1],imgui_color_convert_float4_to_u32(1,1,0,1),0,15,1);
				imgui_drawlist_add_rect_filled(marker_min[0],marker_min[1],marker_max[0],marker_max[1],imgui_color_convert_float4_to_u32(1,0,1,1),0,15);
				imgui_pop_text_wrap_pos();
			}
			
			imgui_tree_pop();
		}
		
		if (imgui_tree_node("UTF-8 Text")) {
            // UTF-8 test with Japanese characters
            // (Needs a suitable font? Try "Google Noto" or "Arial Unicode". See docs/FONTS.md for details.)
            // - From C++11 you can use the u8"my text" syntax to encode literal strings as UTF-8
            // - For earlier compiler, you may be able to encode your sources as UTF-8 (e.g. in Visual Studio, you
            //   can save your source files as 'UTF-8 without signature').
            // - FOR THIS DEMO FILE ONLY, BECAUSE WE WANT TO SUPPORT OLD COMPILERS, WE ARE *NOT* INCLUDING RAW UTF-8
            //   CHARACTERS IN THIS SOURCE FILE. Instead we are encoding a few strings with hexadecimal constants.
            //   Don't do this in your application! Please use u8"text in any language" in your application!
            // Note that characters values are preserved even by imgui_input_text() if the font cannot be displayed,
            // so you can safely copy & paste garbled characters into another application.
            imgui_text_wrapped(
                "CJK text will only appears if the font was loaded with the appropriate CJK character ranges. " +
                "Call imgui_fonts_add_font_from_file_ttf() manually to load extra character ranges. " +
                "Read docs/FONTS.md for details."
			);
			
			imgui_push_font(font3);
            
			imgui_text("Hiragana: カキクケコ (kakikukeko)"); // idk if this is right. 
			imgui_text("Kanjis: 日本語 (nihongo)");
			imgui_text("I used Google translate. I have no idea if these are correct\nI just wanted to show you can use fonts with different languages.");
			
            imgui_input_text("UTF-8 input", buf, 0);
			
			imgui_pop_font();
            imgui_tree_pop();
        }
		
		imgui_tree_pop();
	}
	
	if (imgui_tree_node("Images")) {
		
		imgui_text_wrapped(
			"Images work a bit differently in GameMaker. You need to preload the images first with imgui_load_image. This only needs to be called one time at the start of your game. Then use the name you loaded it with to render it. Hover the texture for a zoomed view!"
		);
		
		var tex_size = [sprite_get_width(Spr_Test),sprite_get_height(Spr_Test)];
		
		var pos = imgui_get_cursor_screen_pos();
		var uv_min = [0,0];
		var uv_max = [1,1];
		var tint_col = [1,1,1,1];
		var border_col = [1,1,1,0.5];
		
		imgui_text(string(tex_size[0]) + " x " + string(tex_size[1]));
		
		imgui_image("Spr_Test",tex_size,uv_min,uv_max,tint_col,border_col);
		
		if (imgui_is_item_hovered()) {
			imgui_begin_tooltip();
			var region_sz = 32;
			var mpos = imgui_get_mouse_pos();
			var region_x = mpos[0] - pos[0] - (region_sz * 0.5);
			var region_y = mpos[1] - pos[1] - (region_sz * 0.5);
			var zoom = 4;
			region_x = clamp(region_x,0,tex_size[0]-region_sz);
			region_y = clamp(region_y,0,tex_size[1]-region_sz);
			imgui_text("Mouse: " + string(mpos));
			imgui_text("Screen cursor: " + string(pos));
			imgui_text("Min: " + string(region_x) + ", " + string(region_y));
			imgui_text("Max: " + string(region_x + region_sz) + ", " + string(region_y + region_sz));
			
			var uv0 = [ region_x / tex_size[0], region_y / tex_size[1] ];
			var uv1 = [ (region_x + region_sz) / tex_size[0], (region_y + region_sz) / tex_size[1] ];
			imgui_text("UV0: " + +string(uv0));
			imgui_text("UV1: " + +string(uv1));
			imgui_image("Spr_Test",[region_sz * zoom, region_sz * zoom],uv0,uv1,tint_col,border_col);
			imgui_end_tooltip();
		}
		
		imgui_text_wrapped("And now some textured buttons..");
		static image_button_pressed_count = 0;
		for (var i = 0; i < 8; ++i) {
			imgui_push_id(i);
			var frame_padding = -1 + i;
			var size = [ 32, 32 ];
			var uv0 = [ 0, 0 ];
			var uv1 = [ 32 / tex_size[0], 32 / tex_size[1] ];
			var bg_col = [0,0,0,1];
			var tint_col = [1,1,1,1];
			if (imgui_image_button("Spr_Test",size,uv0,uv1,frame_padding,bg_col,tint_col)) {
				image_button_pressed_count += 1;
			}
			imgui_pop_id();
			imgui_same_line(0,-1);
		}
		
		imgui_new_line();
		imgui_text("Pressed " + string(image_button_pressed_count) + " times.");
		imgui_tree_pop();
	}
	
	if (imgui_tree_node("Combo"))
    {
        // Expose flags as checkbox for the demo
        static combo_flags = 0;
        ret = imgui_checkbox_flags("ImGuiComboFlags.PopupAlignLeft", combo_flags, ImGuiComboFlags.PopupAlignLeft);
		if (ret[0]) combo_flags = ret[1];
        imgui_same_line(0,-1); imgui_help_marker("Only makes a difference if the popup is larger than the combo");
		ret = imgui_checkbox_flags("ImGuiComboFlags.NoArrowButton", combo_flags, ImGuiComboFlags.NoArrowButton); 
        if (ret[0]) {
			combo_flags = ret[1];
            combo_flags &= ~ImGuiComboFlags.NoPreview;     // Clear the other flag, as we cannot combine both
		}
		ret = imgui_checkbox_flags("ImGuiComboFlags.NoPreview", combo_flags, ImGuiComboFlags.NoPreview);
        if (ret[0]) {
			combo_flags = ret[1];
            combo_flags &= ~ImGuiComboFlags.NoArrowButton; // Clear the other flag, as we cannot combine both
		}

        // Using the generic BeginCombo() API, you have full control over how to display the combo contents.
        // (your selection data could be an index, a pointer to the object, an id for the object, a flag intrusively
        // stored in the object itself, etc.)
        var items = [ "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK", "LLLLLLL", "MMMM", "OO BIG OLD GIANT ENTRY TO TEST OUT LEFT ALIGNMENT FLAG OOOOOLALALALALALALALALALLAOOOOO" ];
        static combo_item_current_idx = 0; // Here we store our selection data as an index.
        var combo_preview_value = items[combo_item_current_idx];  // Pass in the preview value visible before opening the combo (it could be anything)
        if (imgui_begin_combo("combo 1", combo_preview_value, combo_flags))
        {
            for (var n = 0; n < array_length(items); n++)
            {
                var is_selected = (combo_item_current_idx == n);
                if (imgui_selectable(items[n], is_selected))
                    combo_item_current_idx = n;

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    imgui_set_item_default_focus();
            }
            imgui_end_combo();
        }

		// There's too much shit for just me. This is the only one-liner combo you get. 
		// maybe if you beg enough I'll jump through more hoops. nobody will beg for this though. lol
        // Simplified one-liner Combo() using an array of const char*
        // This is not very useful (may obsolete): prefer using BeginCombo()/EndCombo() for full control.
        static combo_item_current_oneliner = -1; // If the selection isn't within 0..count, Combo won't display a preview
        ret = imgui_combo("combo 3 (array)", combo_item_current_oneliner, items, array_length(items),-1);
		if (ret[0]) combo_item_current_oneliner = ret[1];

       imgui_tree_pop();
    }
	
	if (imgui_tree_node("List boxes"))
    {
        // Using the generic BeginListBox() API, you have full control over how to display the combo contents.
        // (your selection data could be an index, a pointer to the object, an id for the object, a flag intrusively
        // stored in the object itself, etc.)
        var items = [ "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK", "LLLLLLL", "MMMM", "OOOOOOO" ];
        static listbox_item_current_idx = 0; // Here we store our selection data as an index.
        if (imgui_begin_list_box("listbox 1",0,0))
        {
            for (var n = 0; n < array_length(items); n++)
            {
                var is_selected = (listbox_item_current_idx == n);
                if (imgui_selectable(items[n], is_selected))
                    listbox_item_current_idx = n;

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
					imgui_set_item_default_focus()
            }
            imgui_end_list_box();
        }

        // Custom size: use all width, 5 items tall. any width value less than 0 seems to work. any value greater than zero will set the exact width
        imgui_text("Full-width:");
        if (imgui_begin_list_box("##listbox 2", -1, 5 * imgui_get_text_line_height_with_spacing()))
        {
            for (var n = 0; n < array_length(items); n++)
            {
                var is_selected = (listbox_item_current_idx == n);
                if (imgui_selectable(items[n], is_selected))
                    listbox_item_current_idx = n;

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
					imgui_set_item_default_focus();
            }
            imgui_end_list_box();
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