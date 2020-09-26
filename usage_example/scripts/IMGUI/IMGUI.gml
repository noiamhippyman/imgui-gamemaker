function buffer_array_create(count,type) {
	var sizeoftype = buffer_sizeof(type);
	return buffer_create(count * sizeoftype, buffer_fixed, sizeoftype);
}

function imgui_setup() {
	
	if (!variable_global_exists("imgui_send_buffer")) global.imgui_send_buffer = noone;
	if (!buffer_exists(global.imgui_send_buffer)) global.imgui_send_buffer = buffer_array_create(IMGUI_SEND_BUFFER_SIZE,IMGUI_SEND_BUFFER_TYPE);
	
	if (!variable_global_exists("imgui_return_buffer")) global.imgui_return_buffer = noone;
	if (!buffer_exists(global.imgui_return_buffer)) global.imgui_return_buffer = buffer_array_create(IMGUI_RETURN_BUFFER_SIZE,IMGUI_RETURN_BUFFER_TYPE);
	
	
	var hwnd = window_handle();
	var os = os_get_info();
	var device = os[? "video_d3d11_device" ];
	var context = os[? "video_d3d11_context" ];
	_imgui_setup(hwnd,device,context);
	_imgui_send_buffers(buffer_get_address(global.imgui_send_buffer),buffer_get_address(global.imgui_return_buffer));
}

function imgui_cleanup() {
	_imgui_cleanup(window_handle());
	buffer_delete(global.imgui_return_buffer);
}

function imgui_begin(label, open, flags) {
	_imgui_begin(label,open,flags);
	
	var ret_array = [
		buffer_peek(global.imgui_return_buffer,0,buffer_f32),
		buffer_peek(global.imgui_return_buffer,4,buffer_f32)
	];
	
	return ret_array;
}

function imgui_get_window_pos() {
	_imgui_get_window_pos();
	
	var ret_array = [
		buffer_peek(global.imgui_return_buffer,0,buffer_f32),
		buffer_peek(global.imgui_return_buffer,4,buffer_f32)
	];
	
	return ret_array;
}

function imgui_get_window_size() {
	_imgui_get_window_size();
	
	var ret_array = [
		buffer_peek(global.imgui_return_buffer,0,buffer_f32),
		buffer_peek(global.imgui_return_buffer,4,buffer_f32)
	];
	
	return ret_array;
}

function imgui_get_content_region_max() {
	_imgui_get_content_region_max();
	
	var ret_array = [
		buffer_peek(global.imgui_return_buffer,0,buffer_f32),
		buffer_peek(global.imgui_return_buffer,4,buffer_f32)
	];
	
	return ret_array;
}

function imgui_get_content_region_avail() {
	_imgui_get_content_region_avail();
	
	var ret_array = [
		buffer_peek(global.imgui_return_buffer,0,buffer_f32),
		buffer_peek(global.imgui_return_buffer,4,buffer_f32)
	];
	
	return ret_array;
}

function imgui_get_window_content_region_min() {
	_imgui_get_window_content_region_min();
	
	var ret_array = [
		buffer_peek(global.imgui_return_buffer,0,buffer_f32),
		buffer_peek(global.imgui_return_buffer,4,buffer_f32)
	];
	
	return ret_array;
}

function imgui_get_window_content_region_max() {
	_imgui_get_window_content_region_max();
	
	var ret_array = [
		buffer_peek(global.imgui_return_buffer,0,buffer_f32),
		buffer_peek(global.imgui_return_buffer,4,buffer_f32)
	];
	
	return ret_array;
}

function imgui_get_style_color_vec4(imguicol) {
	_imgui_get_style_color_vec4(imguicol);
	
	var ret_array = [
		buffer_peek(global.imgui_return_buffer,0,buffer_f32),
		buffer_peek(global.imgui_return_buffer,4,buffer_f32),
		buffer_peek(global.imgui_return_buffer,8,buffer_f32),
		buffer_peek(global.imgui_return_buffer,12,buffer_f32)
	];
	
	return ret_array;
}

function imgui_get_font_tex_uv_white_pixel() {
	_imgui_get_font_tex_uv_white_pixel();
	
	var ret_array = [
		buffer_peek(global.imgui_return_buffer,0,buffer_f32),
		buffer_peek(global.imgui_return_buffer,4,buffer_f32)
	];
	
	return ret_array;
}

function imgui_get_cursor_pos() {
	_imgui_get_cursor_pos();
	
	var ret_array = [
		buffer_peek(global.imgui_return_buffer,0,buffer_f32),
		buffer_peek(global.imgui_return_buffer,4,buffer_f32)
	];
	
	return ret_array;
}

function imgui_get_cursor_start_pos() {
	_imgui_get_cursor_start_pos();
	
	var ret_array = [
		buffer_peek(global.imgui_return_buffer,0,buffer_f32),
		buffer_peek(global.imgui_return_buffer,4,buffer_f32)
	];
	
	return ret_array;
}

function imgui_get_cursor_screen_pos() {
	_imgui_get_cursor_screen_pos();
	
	var ret_array = [
		buffer_peek(global.imgui_return_buffer,0,buffer_f32),
		buffer_peek(global.imgui_return_buffer,4,buffer_f32)
	];
	
	return ret_array;
}

function imgui_text_colored(r,g,b,a,text) {
	var color = imgui_get_color_u32_f4(r,g,b,a);
	_imgui_text_colored(color,text);
}

function imgui_checkbox(label,checked) {
	_imgui_checkbox(label,checked);
		
	var ret_array = [
		buffer_peek(global.imgui_return_buffer,0,buffer_f32),
		buffer_peek(global.imgui_return_buffer,4,buffer_f32)
	];
	
	return ret_array;
}

function imgui_checkbox_flags(label,flags,flags_value) {
	_imgui_checkbox_flags(label,flags,flags_value);
		
	var ret_array = [
		buffer_peek(global.imgui_return_buffer,0,buffer_f32),
		buffer_peek(global.imgui_return_buffer,4,buffer_f32)
	];
	
	return ret_array;
}

function imgui_radio_button_int(label,v,v_button) {
	_imgui_radio_button_int(label,v,v_button);
		
	var ret_array = [
		buffer_peek(global.imgui_return_buffer,0,buffer_f32), 
		buffer_peek(global.imgui_return_buffer,4,buffer_f32) 
	];
	
	return ret_array;
}

function imgui_combo(label,current_item,items_separated_by_zeros,popup_max_height_in_items) {
	_imgui_combo(label,current_item,items_separated_by_zeros,popup_max_height_in_items);
	
	var ret_array = [
		buffer_peek(global.imgui_return_buffer,0,buffer_f32), // Combo changed
		buffer_peek(global.imgui_return_buffer,4,buffer_f32) // Current combo index
	];
	
	return ret_array;
}