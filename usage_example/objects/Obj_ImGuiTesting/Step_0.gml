imgui_newframe();

if (keyboard_check_pressed(vk_space)) {
	open = !open;
}

if (open) {
	var ret = imgui_begin("Test",open,0);
	if (ret[0]) {
		open = ret[1];
		
		
		
		ret = imgui_drag_float("Drag Float",drag_float_vx,0.1,0,0,"%.3f",0);
		if (ret[0]) drag_float_vx = ret[1];
		
		ret = imgui_drag_float2("Drag Float2",[drag_float_vx,drag_float_vy],0.1,0,0,"%.3f",0);
		if (ret[0]) { 
			drag_float_vx = ret[1]; 
			drag_float_vy = ret[2];
		}
		
		ret = imgui_drag_float3("Drag Float3",[drag_float_vx,drag_float_vy,drag_float_vz],0.1,0,0,"%.3f",0);
		if (ret[0]) { 
			drag_float_vx = ret[1]; 
			drag_float_vy = ret[2]; 
			drag_float_vz = ret[3];
		}
		
		ret = imgui_drag_float4("Drag Float4",[drag_float_vx,drag_float_vy,drag_float_vz,drag_float_vw],0.1,0,0,"%.3f",0);
		if (ret[0]) { 
			drag_float_vx = ret[1]; 
			drag_float_vy = ret[2]; 
			drag_float_vz = ret[3];
			drag_float_vw = ret[4];
		}
		
		ret = imgui_drag_float_range2("Drag Float Range2",drag_float_v_current_min,drag_float_v_current_max,0.1,0,0,"%.3f",0,0);
		if (ret[0]) {
			drag_float_v_current_min = ret[1];
			drag_float_v_current_max = ret[2];
		}
		
		ret = imgui_drag_int("Drag Int",drag_int_vx,2,0,0,"%d",0);
		if (ret[0]) drag_int_vx = ret[1];
		
		ret = imgui_drag_int2("Drag Int2",[drag_int_vx,drag_int_vy],2,0,0,"%d",0);
		if (ret[0]) { 
			drag_int_vx = ret[1]; 
			drag_int_vy = ret[2];
		}
		
		ret = imgui_drag_int3("Drag Int3",[drag_int_vx,drag_int_vy,drag_int_vz],2,0,0,"%d",0);
		if (ret[0]) { 
			drag_int_vx = ret[1]; 
			drag_int_vy = ret[2]; 
			drag_int_vz = ret[3];
		}
		
		ret = imgui_drag_int4("Drag Int4",[drag_int_vx,drag_int_vy,drag_int_vz,drag_int_vw],2,0,0,"%d",0);
		if (ret[0]) { 
			drag_int_vx = ret[1]; 
			drag_int_vy = ret[2]; 
			drag_int_vz = ret[3];
			drag_int_vw = ret[4];
		}
		
		ret = imgui_drag_int_range2("Drag Int Range2",drag_int_v_current_min,drag_int_v_current_max,2,0,0,"%d",0,0);
		if (ret[0]) {
			drag_int_v_current_min = ret[1];
			drag_int_v_current_max = ret[2];
		}
		
		ret = imgui_slider_float("Slider Float",slider_float_vx,-1,1,"%.3f",0);
		if (ret[0]) {
			slider_float_vx = ret[1];
		}
		
		ret = imgui_slider_float2("Slider Float2",[slider_float_vx,slider_float_vy],-1,1,"%.3f",0);
		if (ret[0]) {
			slider_float_vx = ret[1];
			slider_float_vy = ret[2];
		}
		
		ret = imgui_slider_float3("Slider Float3",[slider_float_vx,slider_float_vy,slider_float_vz],-1,1,"%.3f",0);
		if (ret[0]) {
			slider_float_vx = ret[1];
			slider_float_vy = ret[2];
			slider_float_vz = ret[3];
		}
		
		ret = imgui_slider_float4("Slider Float4",[slider_float_vx,slider_float_vy,slider_float_vz,slider_float_vw],-1,1,"%.3f",0);
		if (ret[0]) {
			slider_float_vx = ret[1];
			slider_float_vy = ret[2];
			slider_float_vz = ret[3];
			slider_float_vw = ret[4];
		}
		
		ret = imgui_slider_angle("Slider Angle",slider_angle,-360,360,"%.0f deg",0);
		if (ret[0]) {
			slider_angle = ret[1];
		}
		
		ret = imgui_slider_int("Slider Int",slider_int_vx,-1,1,"%d",0);
		if (ret[0]) {
			slider_int_vx = ret[1];
		}
		
		ret = imgui_slider_int2("Slider Int2",[slider_int_vx,slider_int_vy],-1,1,"%d",0);
		if (ret[0]) {
			slider_int_vx = ret[1];
			slider_int_vy = ret[2];
		}
		
		ret = imgui_slider_int3("Slider Int3",[slider_int_vx,slider_int_vy,slider_int_vz],-1,1,"%d",0);
		if (ret[0]) {
			slider_int_vx = ret[1];
			slider_int_vy = ret[2];
			slider_int_vz = ret[3];
		}
		
		ret = imgui_slider_int4("Slider Int4",[slider_int_vx,slider_int_vy,slider_int_vz,slider_int_vw],-1,1,"%d",0);
		if (ret[0]) {
			slider_int_vx = ret[1];
			slider_int_vy = ret[2];
			slider_int_vz = ret[3];
			slider_int_vw = ret[4];
		}
		
		ret = imgui_vslider_float("##vf",24,64,slider_float_vx,-1,1,"%.3f",0);
		if (ret[0]) {
			slider_float_vx = ret[1];
		}
		
		imgui_same_line(0,0);
		
		ret = imgui_vslider_int("##vi",24,64,slider_int_vx,-1,1,"%d",0);
		if (ret[0]) {
			slider_int_vx = ret[1];
		}
		
	}
	imgui_end();
}

imgui_show_demo_window(true);