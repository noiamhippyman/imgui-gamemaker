function buffer_array_create(count,type) {
	var sizeoftype = buffer_sizeof(type);
	return buffer_create(count * sizeoftype, buffer_fixed, sizeoftype);
}

function imgui_setup() {
	if (!variable_global_exists("imgui_vec_buffer")) {
		global.imgui_vec_buffer = noone;
	}
	
	if (!variable_global_exists("imgui_bool_buffer")) {
		global.imgui_bool_buffer = noone;
	}
	
	if (!buffer_exists(global.imgui_vec_buffer)) {
		global.imgui_vec_buffer = buffer_array_create(4,buffer_f32);
	}
	
	if (!buffer_exists(global.imgui_bool_buffer)) {
		global.imgui_bool_buffer = buffer_array_create(2,buffer_u8);
	}
	
	
	var hwnd = window_handle();
	var os = os_get_info();
	var device = os[? "video_d3d11_device" ];
	var context = os[? "video_d3d11_context" ];
	_imgui_setup(hwnd,device,context);
	_imgui_send_buffers(
		buffer_get_address(global.imgui_vec_buffer),
		buffer_get_address(global.imgui_bool_buffer)
	);
}

function imgui_cleanup() {
	_imgui_cleanup(window_handle());
	buffer_delete(global.imgui_vec_buffer);
	buffer_delete(global.imgui_bool_buffer);
}

function imgui_begin(label, open) {
	_imgui_begin(label,open);
		
	var ret_array = [
		buffer_peek(global.imgui_bool_buffer,0,buffer_u8),
		buffer_peek(global.imgui_bool_buffer,1,buffer_u8)
	];
	
	return ret_array;
}