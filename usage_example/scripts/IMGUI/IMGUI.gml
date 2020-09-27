// Helper functions
function buffer_array_create(count,type) {
	var sizeoftype = buffer_sizeof(type);
	return buffer_create(count * sizeoftype, buffer_fixed, sizeoftype);
}

function buffer_write_args(buffer,args) {
	buffer_seek(buffer,buffer_seek_start,0);
	var count = array_length(args);
	for (var i = 0; i < count; ++i) {
		buffer_write(buffer,IMGUI_BUFFER_TYPE,args[i]);
	}
}

function buffer_return(buffer,expected_num) {
	var ret = array_create(expected_num);
	buffer_seek(buffer,buffer_seek_start,0);
	for (var i = 0; i < expected_num; ++i) {
		ret[i] = buffer_read(buffer,IMGUI_BUFFER_TYPE);
	}
	return ret;
}


// IMGUI Functions
function imgui_setup() {
	
	if (!variable_global_exists("imgui_buffer")) global.imgui_buffer = noone;
	if (!buffer_exists(global.imgui_buffer)) global.imgui_buffer = buffer_array_create(IMGUI_BUFFER_SIZE,IMGUI_BUFFER_TYPE);
	
	
	var hwnd = window_handle();
	var os = os_get_info();
	var device = os[? "video_d3d11_device" ];
	var context = os[? "video_d3d11_context" ];
	_imgui_setup(hwnd,device,context);
	_extension_assign_buffer(buffer_get_address(global.imgui_buffer));
}

function imgui_cleanup() {
	_imgui_cleanup(window_handle());
	buffer_delete(global.imgui_buffer);
}

function imgui_begin(label, open, flags) {
	_imgui_begin(label,open,flags);
	
	return buffer_return(global.imgui_buffer,2); // returns [ Collapsed, Open ]
}

function imgui_get_window_pos() {
	_imgui_get_window_pos();
	
	return buffer_return(global.imgui_buffer,2); // returns [ X, Y ]
}

function imgui_get_window_size() {
	_imgui_get_window_size();
	
	return buffer_return(global.imgui_buffer,2); // returns [ Width, Height ]
}

function imgui_get_content_region_max() {
	_imgui_get_content_region_max();
	
	return buffer_return(global.imgui_buffer,2); // returns [ Width, Height ]
}

function imgui_get_content_region_avail() {
	_imgui_get_content_region_avail();
	
	return buffer_return(global.imgui_buffer,2); // returns [ Width, Height ]
}

function imgui_get_window_content_region_min() {
	_imgui_get_window_content_region_min();
	
	return buffer_return(global.imgui_buffer,2); // returns [ Width, Height ]
}

function imgui_get_window_content_region_max() {
	_imgui_get_window_content_region_max();
	
	return buffer_return(global.imgui_buffer,2); // returns [ Width, Height ]
}

function imgui_get_style_color_vec4(imguicol) {
	_imgui_get_style_color_vec4(imguicol);
	
	return buffer_return(global.imgui_buffer,4); // returns [ R,G,B,A ]
}

function imgui_get_font_tex_uv_white_pixel() {
	_imgui_get_font_tex_uv_white_pixel();
	
	return buffer_return(global.imgui_buffer,2); // returns [ U, V ]
}

function imgui_get_cursor_pos() {
	_imgui_get_cursor_pos();
	
	return buffer_return(global.imgui_buffer,2); // returns [ X, Y ]
}

function imgui_get_cursor_start_pos() {
	_imgui_get_cursor_start_pos();
	
	return buffer_return(global.imgui_buffer,2); // returns [ X, Y ]
}

function imgui_get_cursor_screen_pos() {
	_imgui_get_cursor_screen_pos();
	
	return buffer_return(global.imgui_buffer,2); // returns [ X, Y ]
}

function imgui_text_colored(r,g,b,a,text) {
	var color = imgui_get_color_u32_f4(r,g,b,a);
	_imgui_text_colored(color,text);
}

function imgui_checkbox(label,checked) {
	_imgui_checkbox(label,checked);
	
	return buffer_return(global.imgui_buffer,2); // returns [ Changed, Current Value ]
}

function imgui_checkbox_flags(label,flags,flags_value) {
	_imgui_checkbox_flags(label,flags,flags_value);
	
	return buffer_return(global.imgui_buffer,2); // returns [ Changed, Current Value ]
}

function imgui_radio_button_int(label,v,v_button) {
	_imgui_radio_button_int(label,v,v_button);
	
	return buffer_return(global.imgui_buffer,2); // returns [ Changed, Current Value ]
}

//function imgui_combo(label,current_item,items_separated_by_zeros,popup_max_height_in_items) {
//	_imgui_combo(label,current_item,items_separated_by_zeros,popup_max_height_in_items);
	
//	var ret_array = [
//		buffer_peek(global.imgui_buffer,0,IMGUI_BUFFER_TYPE), // Combo changed
//		buffer_peek(global.imgui_buffer,4,IMGUI_BUFFER_TYPE) // Current combo index
//	];
	
//	return ret_array;
//}

function imgui_drag_float(label,value,v_speed,v_min,v_max,format,flags) {
	buffer_write_args(global.imgui_buffer,[ value, v_speed, v_min, v_max ]);
	
	_imgui_drag_float(label,format,flags);
	
	return buffer_return(global.imgui_buffer,2); // returns [ Changed, Current Value ];
}

function imgui_drag_float2(label,varray,v_speed,v_min,v_max,format,flags) {
	buffer_write_args(global.imgui_buffer,[ varray[0], varray[1], v_speed, v_min, v_max ]);
	
	_imgui_drag_float2(label,format,flags);
	
	return buffer_return(global.imgui_buffer,3); // returns [ Changed, Current X Value, Current Y Value ];
}

function imgui_drag_float3(label,varray,v_speed,v_min,v_max,format,flags) {
	buffer_write_args(global.imgui_buffer,[ varray[0], varray[1], varray[2], v_speed, v_min, v_max ]);
	
	_imgui_drag_float3(label,format,flags);
	
	return buffer_return(global.imgui_buffer,4); // returns [ Changed, Current X Value, Current Y Value, Current Z Value ];
}

function imgui_drag_float4(label,varray,v_speed,v_min,v_max,format,flags) {
	buffer_write_args(global.imgui_buffer,[ varray[0], varray[1], varray[2], varray[3], v_speed, v_min, v_max ]);
	
	_imgui_drag_float4(label,format,flags);
	
	return buffer_return(global.imgui_buffer,5); // returns [ Changed, Current X Value, Current Y Value, Current Z Value, Current W Value ];
}

function imgui_drag_float_range2(label,v_current_min,v_current_max,v_speed,v_min,v_max,format,format_end,flags) {
	buffer_write_args(global.imgui_buffer,[ v_current_min, v_current_max, v_speed, v_min, v_max ]);
	_imgui_drag_float_range2(label,format,format_end,flags);
	return buffer_return(global.imgui_buffer,3); // returns [ Changed, Current Min Value, Current Max Value ]
}

function imgui_drag_int(label,value,v_speed,v_min,v_max,format,flags) {
	buffer_write_args(global.imgui_buffer,[ value, v_speed, v_min, v_max ]);
	
	_imgui_drag_int(label,format,flags);
	
	return buffer_return(global.imgui_buffer,2); // returns [ Changed, Current Value ];
}

function imgui_drag_int2(label,varray,v_speed,v_min,v_max,format,flags) {
	buffer_write_args(global.imgui_buffer,[ varray[0], varray[1], v_speed, v_min, v_max ]);
	
	_imgui_drag_int2(label,format,flags);
	
	return buffer_return(global.imgui_buffer,3); // returns [ Changed, Current X Value, Current Y Value ];
}

function imgui_drag_int3(label,varray,v_speed,v_min,v_max,format,flags) {
	buffer_write_args(global.imgui_buffer,[ varray[0], varray[1], varray[2], v_speed, v_min, v_max ]);
	
	_imgui_drag_int3(label,format,flags);
	
	return buffer_return(global.imgui_buffer,4); // returns [ Changed, Current X Value, Current Y Value, Current Z Value ];
}

function imgui_drag_int4(label,varray,v_speed,v_min,v_max,format,flags) {
	buffer_write_args(global.imgui_buffer,[ varray[0], varray[1], varray[2], varray[3], v_speed, v_min, v_max ]);
	
	_imgui_drag_int4(label,format,flags);
	
	return buffer_return(global.imgui_buffer,5); // returns [ Changed, Current X Value, Current Y Value, Current Z Value, Current W Value ];
}

function imgui_drag_int_range2(label,v_current_min,v_current_max,v_speed,v_min,v_max,format,format_end,flags) {
	buffer_write_args(global.imgui_buffer,[ v_current_min, v_current_max, v_speed, v_min, v_max ]);
	_imgui_drag_int_range2(label,format,format_end,flags);
	return buffer_return(global.imgui_buffer,3); // returns [ Changed, Current Min Value, Current Max Value ]
}

function imgui_slider_float(label,value,v_min,v_max,format,flags) {
	buffer_write_args(global.imgui_buffer,[ value, v_min, v_max ]);
	_imgui_slider_float(label,format,flags);
	return buffer_return(global.imgui_buffer,2); // returns [ Changed, Current Value ]
}

function imgui_slider_float2(label,varray,v_min,v_max,format,flags) {
	buffer_write_args(global.imgui_buffer,[ varray[0], varray[1], v_min, v_max ]);
	
	_imgui_slider_float2(label,format,flags);
	
	return buffer_return(global.imgui_buffer,3); // returns [ Changed, Current X Value, Current Y Value ];
}

function imgui_slider_float3(label,varray,v_min,v_max,format,flags) {
	buffer_write_args(global.imgui_buffer,[ varray[0], varray[1], varray[2], v_min, v_max ]);
	
	_imgui_slider_float3(label,format,flags);
	
	return buffer_return(global.imgui_buffer,4); // returns [ Changed, Current X Value, Current Y Value, Current Z Value ];
}

function imgui_slider_float4(label,varray,v_min,v_max,format,flags) {
	buffer_write_args(global.imgui_buffer,[ varray[0], varray[1], varray[2], varray[3], v_min, v_max ]);
	
	_imgui_slider_float4(label,format,flags);
	
	return buffer_return(global.imgui_buffer,5); // returns [ Changed, Current X Value, Current Y Value, Current Z Value, Current W Value ];
}

function imgui_slider_angle(label,v_rad,v_degrees_min,v_degrees_max,format,flags) {
	buffer_write_args(global.imgui_buffer,[ v_rad, v_degrees_min, v_degrees_max ]);
	_imgui_slider_angle(label,format,flags);
	return buffer_return(global.imgui_buffer,2); // returns [ Changed, Current Radian Value ];
}

function imgui_slider_int(label,value,v_min,v_max,format,flags) {
	buffer_write_args(global.imgui_buffer,[ value, v_min, v_max ]);
	_imgui_slider_int(label,format,flags);
	return buffer_return(global.imgui_buffer,2); // returns [ Changed, Current Value ]
}

function imgui_slider_int2(label,varray,v_min,v_max,format,flags) {
	buffer_write_args(global.imgui_buffer,[ varray[0], varray[1], v_min, v_max ]);
	
	_imgui_slider_int2(label,format,flags);
	
	return buffer_return(global.imgui_buffer,3); // returns [ Changed, Current X Value, Current Y Value ];
}

function imgui_slider_int3(label,varray,v_min,v_max,format,flags) {
	buffer_write_args(global.imgui_buffer,[ varray[0], varray[1], varray[2], v_min, v_max ]);
	
	_imgui_slider_int3(label,format,flags);
	
	return buffer_return(global.imgui_buffer,4); // returns [ Changed, Current X Value, Current Y Value, Current Z Value ];
}

function imgui_slider_int4(label,varray,v_min,v_max,format,flags) {
	buffer_write_args(global.imgui_buffer,[ varray[0], varray[1], varray[2], varray[3], v_min, v_max ]);
	
	_imgui_slider_int4(label,format,flags);
	
	return buffer_return(global.imgui_buffer,5); // returns [ Changed, Current X Value, Current Y Value, Current Z Value, Current W Value ];
}

function imgui_vslider_float(label,width,height,value,v_min,v_max,format,flags) {
	buffer_write_args(global.imgui_buffer,[ width, height, value, v_min, v_max ]);
	_imgui_vslider_float(label,format,flags);
	return buffer_return(global.imgui_buffer,2); // returns [ Changed, Current Value ]
}

function imgui_vslider_int(label,width,height,value,v_min,v_max,format,flags) {
	buffer_write_args(global.imgui_buffer,[ width, height, value, v_min, v_max ]);
	_imgui_vslider_int(label,format,flags);
	return buffer_return(global.imgui_buffer,2); // returns [ Changed, Current Value ]
}