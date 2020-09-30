imgui_newframe();

if (keyboard_check_pressed(vk_space)) {
	open = !open;
}

if (open) {
	var ret = imgui_begin("Test",open,0);
	if (ret[0]) {
		open = ret[1];
		
		
		
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
		
		imgui_color_button("Color Button",color,0,100,100)
		//if (imgui_color_button("Color Button",color,0,0,0)) {
		//	color[0] = random(1);
		//	color[1] = random(1);
		//	color[2] = random(1);
		//}
		
	}
	imgui_end();
}

imgui_show_demo_window(true);