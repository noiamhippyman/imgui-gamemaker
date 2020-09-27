// Helper functions
//function buffer_array_create(count,type) {
//	var sizeoftype = buffer_sizeof(type);
//	return buffer_create(count * sizeoftype, buffer_fixed, sizeoftype);
//}
/*
	args format
	[type,val,type,val]
*/
function buffer_write_args(buffer,args) {
	var count = array_length(args);
	var offset = 0;
	for (var i = 0; i < count; i+=2) {
		var type = args[i];
		var val = args[i+1];
		buffer_poke(buffer,offset,type,val);
		switch (type) {
			case buffer_f32:
				offset += buffer_sizeof(type);
				break;
			case buffer_string:
				offset += string_byte_length(val)+1;
				break;
		}
		
	}
}

/*
	expected_return_types format
	[type,type,...]
*/
function buffer_return(buffer,expected_return_types) {
	var count = array_length(expected_return_types);
	var ret = array_create(count);
	var offset = 0;
	for (var i = 0; i < count; ++i) {
		var type = expected_return_types[i];
		var val = buffer_peek(buffer,offset,type);
		switch (type) {
			case buffer_f32:
				offset += buffer_sizeof(type);
				break;
			case buffer_string:
				offset += string_byte_length(val)+1;
				break;
		}
		ret[i] = val;
	}
	return ret;
}


// IMGUI Functions
function imgui_setup() {
	
	if (!variable_global_exists("imgui_buffer")) global.imgui_buffer = noone;
	if (!buffer_exists(global.imgui_buffer)) global.imgui_buffer = buffer_create(IMGUI_BUFFER_SIZE,buffer_fixed,1);//buffer_array_create(IMGUI_BUFFER_SIZE,IMGUI_BUFFER_TYPE);
	
	
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
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // Collapsed
		buffer_f32 // Open
	]);
	
}

function imgui_get_window_pos() {
	
	_imgui_get_window_pos();
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // X
		buffer_f32 // Y
	]);
	
}

function imgui_get_window_size() {
	
	_imgui_get_window_size();
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // Width
		buffer_f32 // Height
	]);
	
}

function imgui_get_content_region_max() {
	
	_imgui_get_content_region_max();
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // Width
		buffer_f32 // Height
	]);
	
}

function imgui_get_content_region_avail() {
	
	_imgui_get_content_region_avail();
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // Width
		buffer_f32 // Height
	]);
	
}

function imgui_get_window_content_region_min() {
	
	_imgui_get_window_content_region_min();
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // Width
		buffer_f32 // Height
	]);
	
}

function imgui_get_window_content_region_max() {
	
	_imgui_get_window_content_region_max();
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // Width
		buffer_f32 // Height
	]);
	
}

function imgui_get_style_color_vec4(imguicol) {
	
	_imgui_get_style_color_vec4(imguicol);
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // R
		buffer_f32, // G
		buffer_f32, // B
		buffer_f32 // A
	]);
	
}

function imgui_get_font_tex_uv_white_pixel() {
	
	_imgui_get_font_tex_uv_white_pixel();
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // U
		buffer_f32 // V
	]);
	
}

function imgui_get_cursor_pos() {
	
	_imgui_get_cursor_pos();
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // X
		buffer_f32 // Y
	]);
	
}

function imgui_get_cursor_start_pos() {
	
	_imgui_get_cursor_start_pos();
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // X
		buffer_f32 // Y
	]);
	
}

function imgui_get_cursor_screen_pos() {
	
	_imgui_get_cursor_screen_pos();
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // X
		buffer_f32 // Y
	]);
	
}

function imgui_text_colored(r,g,b,a,text) {
	
	var color = imgui_get_color_u32_f4(r,g,b,a);
	_imgui_text_colored(color,text);
	
}

function imgui_checkbox(label,checked) {
	
	_imgui_checkbox(label,checked);
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // Changed
		buffer_f32 // Current Value
	]);
	
}

function imgui_checkbox_flags(label,flags,flags_value) {
	
	_imgui_checkbox_flags(label,flags,flags_value);
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // Changed
		buffer_f32 // Current Value
	]);
	
}

function imgui_radio_button_int(label,v,v_button) {
	
	_imgui_radio_button_int(label,v,v_button);
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32,  // Changed
		buffer_f32 // Current Value
	]);
	
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
	
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, value,
		buffer_f32, v_speed,
		buffer_f32, v_min,
		buffer_f32, v_max
	]);
	
	_imgui_drag_float(label,format,flags);
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // Changed
		buffer_f32 // Current Value
	]);
	
}

function imgui_drag_float2(label,varray,v_speed,v_min,v_max,format,flags) {
	
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, varray[0],
		buffer_f32, varray[1],
		buffer_f32, v_speed,
		buffer_f32, v_min,
		buffer_f32, v_max
	]);
	
	_imgui_drag_float2(label,format,flags);
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // Changed
		buffer_f32, // Current X
		buffer_f32 // Current Y
	]);
	
}

function imgui_drag_float3(label,varray,v_speed,v_min,v_max,format,flags) {
	
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, varray[0],
		buffer_f32, varray[1],
		buffer_f32, varray[2],
		buffer_f32, v_speed,
		buffer_f32, v_min,
		buffer_f32, v_max
	]);
	
	_imgui_drag_float3(label,format,flags);
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // Changed
		buffer_f32, // Current X
		buffer_f32, // Current Y
		buffer_f32 // Current Z
	]);
	
}

function imgui_drag_float4(label,varray,v_speed,v_min,v_max,format,flags) {
	
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, varray[0],
		buffer_f32, varray[1],
		buffer_f32, varray[2],
		buffer_f32, varray[3],
		buffer_f32, v_speed,
		buffer_f32, v_min,
		buffer_f32, v_max
	]);
	
	_imgui_drag_float4(label,format,flags);
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // Changed
		buffer_f32, // Current X
		buffer_f32, // Current Y
		buffer_f32, // Current Z
		buffer_f32 // Current W
	]);
	
}

function imgui_drag_float_range2(label,v_current_min,v_current_max,v_speed,v_min,v_max,format,format_end,flags) {
	
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, v_current_min,
		buffer_f32, v_current_max,
		buffer_f32, v_speed,
		buffer_f32, v_min,
		buffer_f32, v_max
	]);
	
	_imgui_drag_float_range2(label,format,format_end,flags);
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // Changed
		buffer_f32, // Current Min
		buffer_f32 // Current Max
	]);
	
}

function imgui_drag_int(label,value,v_speed,v_min,v_max,format,flags) {
	
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, value,
		buffer_f32, v_speed,
		buffer_f32, v_min,
		buffer_f32, v_max
	]);
	
	_imgui_drag_int(label,format,flags);
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // Changed
		buffer_f32 // Current Value
	]);
	
}

function imgui_drag_int2(label,varray,v_speed,v_min,v_max,format,flags) {
	
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, varray[0],
		buffer_f32, varray[1],
		buffer_f32, v_speed,
		buffer_f32, v_min,
		buffer_f32, v_max
	]);
	
	_imgui_drag_int2(label,format,flags);
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // Changed
		buffer_f32, // Current X
		buffer_f32 // Current Y
	]);
	
}

function imgui_drag_int3(label,varray,v_speed,v_min,v_max,format,flags) {
	
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, varray[0],
		buffer_f32, varray[1],
		buffer_f32, varray[2],
		buffer_f32, v_speed,
		buffer_f32, v_min,
		buffer_f32, v_max
	]);
	
	_imgui_drag_int3(label,format,flags);
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // Changed
		buffer_f32, // Current X
		buffer_f32, // Current Y
		buffer_f32 // Current Z
	]);
	
}

function imgui_drag_int4(label,varray,v_speed,v_min,v_max,format,flags) {
	
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, varray[0],
		buffer_f32, varray[1],
		buffer_f32, varray[2],
		buffer_f32, varray[3],
		buffer_f32, v_speed,
		buffer_f32, v_min,
		buffer_f32, v_max
	]);
	
	_imgui_drag_int4(label,format,flags);
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // Changed 
		buffer_f32, // Current X
		buffer_f32, // Current Y
		buffer_f32, // Current Z
		buffer_f32 // Current W
	]);
	
}

function imgui_drag_int_range2(label,v_current_min,v_current_max,v_speed,v_min,v_max,format,format_end,flags) {
	
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, v_current_min,
		buffer_f32, v_current_max,
		buffer_f32, v_speed,
		buffer_f32, v_min,
		buffer_f32, v_max
	]);
	
	_imgui_drag_int_range2(label,format,format_end,flags);
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32,  // Changed
		buffer_f32, // Current Min
		buffer_f32 // Current Max
	]);
	
}

function imgui_slider_float(label,value,v_min,v_max,format,flags) {
	
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, value,
		buffer_f32, v_min,
		buffer_f32, v_max
	]);
	
	_imgui_slider_float(label,format,flags);
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // Changed
		buffer_f32 // Current Value
	]);
	
}

function imgui_slider_float2(label,varray,v_min,v_max,format,flags) {
	
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, varray[0],
		buffer_f32, varray[1],
		buffer_f32, v_min,
		buffer_f32, v_max
	]);
	
	_imgui_slider_float2(label,format,flags);
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // Changed
		buffer_f32, // Current X
		buffer_f32 // Current Y
	]);
	
}

function imgui_slider_float3(label,varray,v_min,v_max,format,flags) {
	
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, varray[0],
		buffer_f32, varray[1],
		buffer_f32, varray[2],
		buffer_f32, v_min,
		buffer_f32, v_max
	]);
	
	_imgui_slider_float3(label,format,flags);
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // Changed
		buffer_f32, // Current X
		buffer_f32, // Current Y
		buffer_f32 // Current Z
	]);
	
}

function imgui_slider_float4(label,varray,v_min,v_max,format,flags) {
	
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, varray[0],
		buffer_f32, varray[1],
		buffer_f32, varray[2],
		buffer_f32, varray[3],
		buffer_f32, v_min,
		buffer_f32, v_max
	]);
	
	_imgui_slider_float4(label,format,flags);
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // Changed
		buffer_f32, // Current X
		buffer_f32, // Current Y
		buffer_f32, // Current Z
		buffer_f32 // Current W
	]);
	
}

function imgui_slider_angle(label,v_rad,v_degrees_min,v_degrees_max,format,flags) {
	
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, v_rad,
		buffer_f32, v_degrees_min,
		buffer_f32, v_degrees_max
	]);
	
	_imgui_slider_angle(label,format,flags);
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // Changed
		buffer_f32 // Current Radian Angle
	]);
	
}

function imgui_slider_int(label,value,v_min,v_max,format,flags) {
	
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, value,
		buffer_f32, v_min,
		buffer_f32, v_max
	]);
	
	_imgui_slider_int(label,format,flags);
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // Changed
		buffer_f32 // Current Value
	]);
	
}

function imgui_slider_int2(label,varray,v_min,v_max,format,flags) {
	
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, varray[0],
		buffer_f32, varray[1],
		buffer_f32, v_min,
		buffer_f32, v_max
	]);
	
	_imgui_slider_int2(label,format,flags);
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // Changed
		buffer_f32, // Current X
		buffer_f32 // Current Y
	]);
	
}

function imgui_slider_int3(label,varray,v_min,v_max,format,flags) {
	
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, varray[0],
		buffer_f32, varray[1],
		buffer_f32, varray[2],
		buffer_f32, v_min,
		buffer_f32, v_max
	]);
	
	_imgui_slider_int3(label,format,flags);
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32,  // Changed
		buffer_f32, // Current X
		buffer_f32, // Current Y
		buffer_f32 // Current Z
	]);
	
}

function imgui_slider_int4(label,varray,v_min,v_max,format,flags) {
	
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, varray[0],
		buffer_f32, varray[1],
		buffer_f32, varray[2],
		buffer_f32, varray[3],
		buffer_f32, v_min,
		buffer_f32, v_max
	]);
	
	_imgui_slider_int4(label,format,flags);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32, // Current X
		buffer_f32, // Current Y
		buffer_f32, // Current Z
		buffer_f32 // Current W
	]);
	
}

function imgui_vslider_float(label,width,height,value,v_min,v_max,format,flags) {
	
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, width,
		buffer_f32, height,
		buffer_f32, value,
		buffer_f32, v_min,
		buffer_f32, v_max
	]);
	
	_imgui_vslider_float(label,format,flags);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32 // Current Value
	]);
	
}

function imgui_vslider_int(label,width,height,value,v_min,v_max,format,flags) {
	
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, width,
		buffer_f32, height,
		buffer_f32, value,
		buffer_f32, v_min,
		buffer_f32, v_max
	]);
	
	_imgui_vslider_int(label,format,flags);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32 // Current value
	]);
	
}

function imgui_input_text(label,text,flags) {
	
	_imgui_input_text(label,text,flags);
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // Changed
		buffer_string // Current Text
	]);
}

function imgui_input_text_multiline(label,text,width,height,flags) {
	
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, width,
		buffer_f32, height
	]);
	
	_imgui_input_text_multiline(label,text,flags);
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // Changed
		buffer_string // Current Text
	]);
}

function imgui_input_text_with_hint(label,hint,text,flags) {
	
	_imgui_input_text_with_hint(label,hint,text,flags);
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // Changed
		buffer_string // Current Text
	]);
}