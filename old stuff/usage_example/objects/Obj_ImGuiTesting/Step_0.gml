imgui_newframe();

if (keyboard_check_pressed(vk_space)) {
	open = !open;
}

if (open) {
	
	var ret = imgui_begin("Test",open,ImGuiWindowFlags.MenuBar);
	if (ret[0]) {
		open = ret[1];
#region Combo/Selectable Functions
		if (imgui_begin_combo("Selectables##Combo",current_item,0)) {
			for (var i = 0; i < array_length(items); ++i) {
				
				var is_selected = imgui_selectable(items[i],current_item == items[i],0,0,0);
				if (is_selected) current_item = items[i];
			}
			imgui_end_combo();
		}
		
		ret = imgui_combo("Combo",current_index,items,array_length(items),-1);
		if (ret[0]) current_index = ret[1];
		
#endregion

#region Drag Functions
		ret = imgui_collapsing_header("Drag Functions",noone,0);
		if (ret[0]) {
			ret = imgui_drag_float("Drag Float",float_v[0],0.1,0,0,"%.3f",0);
			if (ret[0]) float_v[0] = ret[1];
		
			ret = imgui_drag_float2("Drag Float2",[float_v[0],float_v[1]],0.1,0,0,"%.3f",0);
			if (ret[0]) { 
				float_v[0] = ret[1]; 
				float_v[1] = ret[2];
			}
		
			ret = imgui_drag_float3("Drag Float3",[float_v[0],float_v[1],float_v[2]],0.1,0,0,"%.3f",0);
			if (ret[0]) { 
				float_v[0] = ret[1]; 
				float_v[1] = ret[2]; 
				float_v[2] = ret[3];
			}
		
			ret = imgui_drag_float4("Drag Float4",[float_v[0],float_v[1],float_v[2],float_v[3]],0.1,0,0,"%.3f",0);
			if (ret[0]) { 
				float_v[0] = ret[1]; 
				float_v[1] = ret[2]; 
				float_v[2] = ret[3];
				float_v[3] = ret[4];
			}
		
			ret = imgui_drag_float_range2("Drag Float Range2",float_v_current_min,float_v_current_max,0.1,0,0,"%.3f",0,0);
			if (ret[0]) {
				float_v_current_min = ret[1];
				float_v_current_max = ret[2];
			}
		
			ret = imgui_drag_int("Drag Int",int_v[0],2,0,0,"%d",0);
			if (ret[0]) int_v[0] = ret[1];
		
			ret = imgui_drag_int2("Drag Int2",[int_v[0],int_v[1]],2,0,0,"%d",0);
			if (ret[0]) { 
				int_v[0] = ret[1]; 
				int_v[1] = ret[2];
			}
		
			ret = imgui_drag_int3("Drag Int3",[int_v[0],int_v[1],int_v[2]],2,0,0,"%d",0);
			if (ret[0]) { 
				int_v[0] = ret[1]; 
				int_v[1] = ret[2]; 
				int_v[2] = ret[3];
			}
		
			ret = imgui_drag_int4("Drag Int4",[int_v[0],int_v[1],int_v[2],int_v[3]],2,0,0,"%d",0);
			if (ret[0]) { 
				int_v[0] = ret[1]; 
				int_v[1] = ret[2]; 
				int_v[2] = ret[3];
				int_v[3] = ret[4];
			}
		
			ret = imgui_drag_int_range2("Drag Int Range2",int_v_current_min,int_v_current_max,2,0,0,"%d",0,0);
			if (ret[0]) {
				int_v_current_min = ret[1];
				int_v_current_max = ret[2];
			}
		}
		imgui_separator();
#endregion
		
#region Slider Functions
		ret = imgui_collapsing_header("Slider Functions",noone,0);
		if (ret[0]) {
			ret = imgui_slider_float("Slider Float",float_v[0],-1,1,"%.3f",0);
			if (ret[0]) {
				float_v[0] = ret[1];
			}
		
			ret = imgui_slider_float2("Slider Float2",float_v,-1,1,"%.3f",0);
			if (ret[0]) {
				float_v[0] = ret[1];
				float_v[1] = ret[2];
			}
		
			ret = imgui_slider_float3("Slider Float3",float_v,-1,1,"%.3f",0);
			if (ret[0]) {
				float_v[0] = ret[1];
				float_v[1] = ret[2];
				float_v[2] = ret[3];
			}
		
			ret = imgui_slider_float4("Slider Float4",float_v,-1,1,"%.3f",0);
			if (ret[0]) {
				float_v[0] = ret[1];
				float_v[1] = ret[2];
				float_v[2] = ret[3];
				float_v[3] = ret[4];
			}
		
			ret = imgui_slider_angle("Slider Angle",slider_angle,-360,360,"%.0f deg",0);
			if (ret[0]) {
				slider_angle = ret[1];
			}
		
			ret = imgui_slider_int("Slider Int",int_v[0],-1,1,"%d",0);
			if (ret[0]) {
				int_v[0] = ret[1];
			}
		
			ret = imgui_slider_int2("Slider Int2",int_v,-1,1,"%d",0);
			if (ret[0]) {
				int_v[0] = ret[1];
				int_v[1] = ret[2];
			}
		
			ret = imgui_slider_int3("Slider Int3",int_v,-1,1,"%d",0);
			if (ret[0]) {
				int_v[0] = ret[1];
				int_v[1] = ret[2];
				int_v[2] = ret[3];
			}
		
			ret = imgui_slider_int4("Slider Int4",int_v,-1,1,"%d",0);
			if (ret[0]) {
				int_v[0] = ret[1];
				int_v[1] = ret[2];
				int_v[2] = ret[3];
				int_v[3] = ret[4];
			}
		
			ret = imgui_vslider_float("##vf",24,64,float_v[0],-1,1,"%.3f",0);
			if (ret[0]) {
				float_v[0] = ret[1];
			}
		
			imgui_same_line(0,0);
		
			ret = imgui_vslider_int("##vi",24,64,int_v[0],-1,1,"%d",0);
			if (ret[0]) {
				int_v[0] = ret[1];
			}
		}
		imgui_separator();
#endregion
		
#region Keyboard Input Functions
		ret = imgui_collapsing_header("Keyboard Input Functions",noone,0);
		if (ret[0]) {
			ret = imgui_input_text("Input Text",input_text,0)
			if (ret[0]) {
				input_text = ret[1];
			}
		
			ret = imgui_input_text_multiline("Multiline Input Text",multiline_input_text,400,200,0);
			if (ret[0]) {
				multiline_input_text = ret[1];
			}
		
			ret = imgui_input_text_with_hint("Hint Input Text","Hinty Hint",input_text_with_hint,0);
			if (ret[0]) {
				input_text_with_hint = ret[1];
			}
		
			ret = imgui_input_float("Input Float",float_v[0],0.1,0.5,"%.3f",0);
			if (ret[0]) float_v[0] = ret[1];
		
			ret = imgui_input_float2("Input Float2",float_v,"%.3f",0);
			if (ret[0]) {
				float_v[0] = ret[1];
				float_v[1] = ret[2];
			}
		
			ret = imgui_input_float3("Input Float3",float_v,"%.3f",0);
			if (ret[0]) {
				float_v[0] = ret[1];
				float_v[1] = ret[2];
				float_v[2] = ret[3];
			}
		
			ret = imgui_input_float4("Input Float4",float_v,"%.3f",0);
			if (ret[0]) {
				float_v[0] = ret[1];
				float_v[1] = ret[2];
				float_v[2] = ret[3];
				float_v[3] = ret[4];
			}
		
			ret = imgui_input_int("Input Int",int_v[0],10,100,0);
			if (ret[0]) int_v[0] = ret[1];
		
			ret = imgui_input_int2("Input Int2",int_v,0);
			if (ret[0]) {
				int_v[0] = ret[1];
				int_v[1] = ret[2];
			}
		
			ret = imgui_input_int3("Input Int3",int_v,0);
			if (ret[0]) {
				int_v[0] = ret[1];
				int_v[1] = ret[2];
				int_v[2] = ret[3];
			}
		
			ret = imgui_input_int4("Input Int4",int_v,0);
			if (ret[0]) {
				int_v[0] = ret[1];
				int_v[1] = ret[2];
				int_v[2] = ret[3];
				int_v[3] = ret[4];
			}
		}
		imgui_separator();
#endregion
		
#region ColorEdit/ColorPicker/ColorButton
		ret = imgui_collapsing_header("ColorEdit/ColorPicker/ColorButton Functions",noone,0);
		if (ret[0]) {
			ret = imgui_color_edit3("Color Edit3",color,0);
			if (ret[0]) {
				color[0] = ret[1];
				color[1] = ret[2];
				color[2] = ret[3];
			}
		
			ret = imgui_color_edit4("Color Edit4",color,0);
			if (ret[0]) {
				color[0] = ret[1];
				color[1] = ret[2];
				color[2] = ret[3];
				color[3] = ret[4];
			}
		
			ret = imgui_color_picker3("Color Picker3",color,0);
			if (ret[0]) {
				color[0] = ret[1];
				color[1] = ret[2];
				color[2] = ret[3];
			}
		
			ret = imgui_color_picker4("Color Picker4",color,0);
			if (ret[0]) {
				color[0] = ret[1];
				color[1] = ret[2];
				color[2] = ret[3];
				color[3] = ret[4];
			}
		
			if (imgui_color_button("Color Button",color,0,0,0)) {
				color[0] = random(1);
				color[1] = random(1);
				color[2] = random(1);
			}
		}
		imgui_separator();
#endregion

#region Tree Functions
		if (collapsing_header_open) {
			ret = imgui_collapsing_header("Closing Collapsing Header",collapsing_header_open,0);
			if (ret[0]) {
				imgui_text("Text inside collapsing header that you can close.");
				if (imgui_tree_node("Tree Node")) {
					imgui_text("Text inside tree node inside collapsing header that you can close.");
					if (imgui_tree_node_ex("Tree Node Ex",0)) {
						imgui_text("Text inside inner tree node inside tree node inside collapsing header that you can close.");
						imgui_tree_pop();// always remember to pop out of every tree you start
					}
					imgui_tree_pop();// you have to pop out of tree or else it will crash
				}
			}
			collapsing_header_open = ret[1];	
		}
#endregion

#region List Box Functions
		ret = imgui_collapsing_header("List Box Functions",noone,0);
		if (ret[0]) {
			ret = imgui_list_box("List Box",current_index,items,array_length(items),-1);
			if (ret[0]) current_index = ret[1];
		
			if (imgui_list_box_header("List Box Header",0,64)) {
				imgui_text("Text1 in LBH");
				imgui_text("Text2 in LBH");
				imgui_text("Text3 in LBH");
				imgui_text("Text4 in LBH");
				imgui_list_box_footer();
			}
		}
#endregion
		
#region Plotting Functions
		ret = imgui_collapsing_header("Plotting Functions",noone,0);
		if (ret[0]) {
			imgui_plot_lines("Plot Lines",[0,1,2,3,4,5,6,7,8,9],2,0,noone,noone,200,50);
			imgui_plot_histogram("Plot Histogram",[0,1,2,3,4,5,6,7,8,9],5,"Overlay",noone,noone,500,500);
		}
#endregion
		
#region Tooltips
		imgui_text("Press F1 to see normal tooltip");
		if (keyboard_check(vk_f1)) {
			imgui_set_tooltip("Tooltip");
		}
		
		imgui_text("Press F2 to see custom tooltip");
		if (keyboard_check(vk_f2)) {
			imgui_begin_tooltip();
			imgui_button("Button in a tooltip. But why?",0,0);
			imgui_set_next_item_open(true,0);
			if (imgui_tree_node("Tree in a tooltip")) {
				imgui_label_text("Labeled", "Some text in a tree in a tooltip.");
				imgui_tree_pop();
			}
			imgui_end_tooltip();
		}
#endregion
	
#region Popups, Modals

		if (imgui_button("How about a popup?",0,0)) {
			imgui_open_popup("Popup",0);
		}
		if (imgui_begin_popup("Popup",0)) {
			imgui_text("I'm in a popup");
			imgui_end_popup();
		}
	
		if (imgui_button("How about a modal popup?",0,0)) {
			imgui_open_popup("Modal Popup",0);
		}
		ret = imgui_begin_popup_modal("Modal Popup",modal_open,0);
		if (ret[0]) {
			modal_open = ret[1];
			imgui_text("Im in a modal popup");
			if (imgui_button("Close",0,0)) {
				imgui_close_current_popup();
			}
			imgui_end_popup();
		}
	
		// It's really annoying when the comment-block below is active.
		// Uncomment to see them popup helper functions working.
		/*
		if (imgui_begin_child(1,0,0,true,0)) {
			imgui_text("Howdy");
			imgui_end_child();
		}
		if (imgui_begin_popup_context_item("0",0)) {
			imgui_text("Text in a context item popup");
			imgui_end_popup();
		}
	
		if (imgui_begin_popup_context_window("Test",0)) {
			imgui_text("Text in a context window popup");
			imgui_end_popup();
		}
	
		if (imgui_begin_popup_context_void("Oi",0)) {
			imgui_text("Text in a context void popup");
			imgui_end_popup();
		}
		*/
	
#endregion

#region Columns

		imgui_columns(4,"columns",true);
		imgui_separator();
		imgui_text("ID"); imgui_next_column();
		imgui_text("Name"); imgui_next_column();
		imgui_text("Path"); imgui_next_column();
		imgui_text("Hovered"); imgui_next_column();
		imgui_separator();
		var names = [ "One", "Two", "Three" ];
		var paths = [ "/path/one", "/path/two", "/path/three" ];
		var selected = -1;
		for (var i = 0; i < 3; ++i) {
			if (imgui_selectable(string_format(i,4,0),selected == i, 0,0,0)) {
				selected = i;
			}
			var hovered = imgui_is_item_hovered();
			imgui_next_column();
			imgui_text(names[i]); imgui_next_column();
			imgui_text(paths[i]); imgui_next_column();
			imgui_text(string(hovered)); imgui_next_column();
		}
		imgui_columns(1,0,false);
		imgui_separator();

#endregion

#region Tab bars, Tabs
		if (imgui_begin_tab_bar("Tab Bar",0)) {
			ret = imgui_begin_tab_item("Avocado",avocado_open,0);
			if (ret[1] == false and avocado_open) avocado_open = ret[1];
			if (ret[0]) {
				avocado_open = ret[1];
				imgui_text("This is the Avocado tab!\nblah blah blah blah blah");
				imgui_end_tab_item();
			}
			ret = imgui_begin_tab_item("Broccoli",noone,0);
			if (ret[0]) {
				//broccoli_open = ret[1];
				imgui_text("This is the Broccoli tab!\nblah blah blah blah blah");
				imgui_end_tab_item();
			}
			ret = imgui_begin_tab_item("Cucumber",cucumber_open,0);
			if (ret[1] == false and cucumber_open) cucumber_open = ret[1];
			if (ret[0]) {
				imgui_text("This is the Cucumber tab!\nblah blah blah blah blah");
				imgui_end_tab_item();
			}
			
			imgui_end_tab_bar();
		}
#endregion

	}
	imgui_end();
}

imgui_show_demo_window(true);