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
		if (is_array(val)) {
			var val_count = array_length(val);
			for (var j = 0; j < val_count; ++j) {
				var v = val[j];
				buffer_poke(buffer,offset,type,v);
				switch (type) {
					case buffer_f32:
						offset += buffer_sizeof(type);
						break;
					case buffer_string:
						offset += string_byte_length(v)+1;
						break;
				}
			}
		} else {
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
	if (!buffer_exists(global.imgui_buffer)) global.imgui_buffer = buffer_create(IMGUI_BUFFER_SIZE,buffer_fixed,1);
	
	
	var hwnd = window_handle();
	var os = os_get_info();
	var device = os[? "video_d3d11_device" ];
	var context = os[? "video_d3d11_context" ];
	_imgui_setup(hwnd,device,context);
	_extension_setup(buffer_get_address(global.imgui_buffer), buffer_get_size(global.imgui_buffer));
}

function imgui_cleanup() {
	_imgui_cleanup(window_handle());
	_extension_cleanup();
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

function imgui_combo(label,current_item,items,item_count,popup_max_height_in_items) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, popup_max_height_in_items,
		buffer_f32, current_item,
		buffer_f32, item_count,
		buffer_string, items
	]);
	_imgui_combo(label);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32 // Current Item
	]);
}

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
		buffer_f32, varray,
		//buffer_f32, varray[0],
		//buffer_f32, varray[1],
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
		buffer_f32, varray,
		//buffer_f32, varray[0],
		//buffer_f32, varray[1],
		//buffer_f32, varray[2],
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
		buffer_f32, varray,
		//buffer_f32, varray[0],
		//buffer_f32, varray[1],
		//buffer_f32, varray[2],
		//buffer_f32, varray[3],
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
		buffer_f32, varray,
		//buffer_f32, varray[0],
		//buffer_f32, varray[1],
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
		buffer_f32, varray,
		//buffer_f32, varray[0],
		//buffer_f32, varray[1],
		//buffer_f32, varray[2],
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
		buffer_f32, varray,
		//buffer_f32, varray[0],
		//buffer_f32, varray[1],
		//buffer_f32, varray[2],
		//buffer_f32, varray[3],
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
		buffer_f32, varray,
		//buffer_f32, varray[0],
		//buffer_f32, varray[1],
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
		buffer_f32, varray,
		//buffer_f32, varray[0],
		//buffer_f32, varray[1],
		//buffer_f32, varray[2],
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
		buffer_f32, varray,
		//buffer_f32, varray[0],
		//buffer_f32, varray[1],
		//buffer_f32, varray[2],
		//buffer_f32, varray[3],
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
		buffer_f32, varray,
		//buffer_f32, varray[0],
		//buffer_f32, varray[1],
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
		buffer_f32, varray,
		//buffer_f32, varray[0],
		//buffer_f32, varray[1],
		//buffer_f32, varray[2],
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
		buffer_f32, varray,
		//buffer_f32, varray[0],
		//buffer_f32, varray[1],
		//buffer_f32, varray[2],
		//buffer_f32, varray[3],
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

function imgui_input_float(label,value,step,step_fast,format,flags) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, value,
		buffer_f32, step,
		buffer_f32, step_fast
	]);
	
	_imgui_input_float(label,format,flags);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32 // Current Value
	]);
}

function imgui_input_float2(label,varray,format,flags) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, varray
		//buffer_f32, varray[0],
		//buffer_f32, varray[1]
	]);
	
	_imgui_input_float2(label,format,flags);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32, // Current X
		buffer_f32 // Current Y
	]);
}

function imgui_input_float3(label,varray,format,flags) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, varray
		//buffer_f32, varray[0],
		//buffer_f32, varray[1],
		//buffer_f32, varray[2]
	]);
	
	_imgui_input_float3(label,format,flags);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32, // Current X
		buffer_f32, // Current Y
		buffer_f32 // Current Z
	]);
}

function imgui_input_float4(label,varray,format,flags) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, varray
		//buffer_f32, varray[0],
		//buffer_f32, varray[1],
		//buffer_f32, varray[2],
		//buffer_f32, varray[3]
	]);
	
	_imgui_input_float4(label,format,flags);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32, // Current X
		buffer_f32, // Current Y
		buffer_f32, // Current Z
		buffer_f32 // Current W
	]);
}

function imgui_input_int(label,value,step,step_fast,flags) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, value,
		buffer_f32, step,
		buffer_f32, step_fast
	]);
	
	_imgui_input_int(label,flags);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32 // Current Value
	]);
}

function imgui_input_int2(label,varray,flags) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, varray
		//buffer_f32, varray[0],
		//buffer_f32, varray[1]
	]);
	
	_imgui_input_int2(label,flags);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32, // Current X
		buffer_f32 // Current Y
	]);
}

function imgui_input_int3(label,varray,flags) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, varray
		//buffer_f32, varray[0],
		//buffer_f32, varray[1],
		//buffer_f32, varray[2]
	]);
	
	_imgui_input_int3(label,flags);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32, // Current X
		buffer_f32, // Current Y
		buffer_f32 // Current Z
	]);
}

function imgui_input_int4(label,varray,flags) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, varray
		//buffer_f32, varray[0],
		//buffer_f32, varray[1],
		//buffer_f32, varray[2],
		//buffer_f32, varray[3]
	]);
	
	_imgui_input_int4(label,flags);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32, // Current X
		buffer_f32, // Current Y
		buffer_f32, // Current Z
		buffer_f32 // Current W
	]);
}

function imgui_color_edit3(label,color,flags) {
	buffer_write_args(global.imgui_buffer, [
		buffer_f32, color
		//buffer_f32, color[0],
		//buffer_f32, color[1],
		//buffer_f32, color[2]
	]);
	_imgui_color_edit3(label,flags);
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32, // R
		buffer_f32, // G
		buffer_f32 // B
	]);
}

function imgui_color_edit4(label,color,flags) {
	buffer_write_args(global.imgui_buffer, [
		buffer_f32, color
		//buffer_f32, color[0],
		//buffer_f32, color[1],
		//buffer_f32, color[2],
		//buffer_f32, color[3]
	]);
	_imgui_color_edit4(label,flags);
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32, // R
		buffer_f32, // G
		buffer_f32, // B
		buffer_f32 // A
	]);
}

function imgui_color_picker3(label,color,flags) {
	buffer_write_args(global.imgui_buffer, [
		buffer_f32, color
		//buffer_f32, color[0],
		//buffer_f32, color[1],
		//buffer_f32, color[2]
	]);
	
	_imgui_color_picker3(label,flags);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32, // R
		buffer_f32, // G
		buffer_f32 // B
	]);
}

function imgui_color_picker4(label,color,flags) {
	buffer_write_args(global.imgui_buffer, [
		buffer_f32, color
		//buffer_f32, color[0],
		//buffer_f32, color[1],
		//buffer_f32, color[2],
		//buffer_f32, color[3]
	]);
	_imgui_color_picker4(label,flags);
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32, // R
		buffer_f32, // G
		buffer_f32, // B
		buffer_f32 // A
	]);
}

function imgui_color_button(desc_id,color,flags,width,height) {
	buffer_write_args(global.imgui_buffer, [
		buffer_f32, color,
		buffer_f32, width,
		buffer_f32, height
	]);
	return _imgui_color_button(desc_id,flags);
}

function imgui_collapsing_header(label,open,flags) {
	
	_imgui_collapsing_header(label,open,flags);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Checked
		buffer_f32 // Open
	]);
}

function imgui_selectable(label,selected,flags=0,width=0,height=0) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, width,
		buffer_f32, height,
	]);
	return _imgui_selectable(label,selected,flags);
}

function imgui_list_box(label,current_item,items,item_count,height_in_items) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, height_in_items,
		buffer_f32, current_item,
		buffer_f32, item_count,
		buffer_string, items
	]);
	
	_imgui_list_box(label);
	
	return buffer_return(global.imgui_buffer, [
		buffer_f32, // Changed
		buffer_f32 // Current Item
	]);
}

function imgui_plot_lines(label,values_array,values_offset,overlay,scale_min,scale_max,width,height) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, array_length(values_array),
		buffer_f32, values_array,
		buffer_f32, values_offset,
		buffer_f32, scale_min,
		buffer_f32, scale_max,
		buffer_f32, width,
		buffer_f32, height
	]);
	_imgui_plot_lines(label,overlay);
}

function imgui_plot_histogram(label,values_array,values_offset,overlay,scale_min,scale_max,width,height) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, array_length(values_array),
		buffer_f32, values_array,
		buffer_f32, values_offset,
		buffer_f32, scale_min,
		buffer_f32, scale_max,
		buffer_f32, width,
		buffer_f32, height
	]);
	_imgui_plot_histogram(label,overlay);
}

function imgui_begin_popup_modal(name,open,flags) {
	_imgui_begin_popup_modal(name,open,flags);
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Opened
		buffer_f32 // Current open? Check to see if these are the same.
	]);
}

function imgui_begin_tab_item(label,open,flags) {
	_imgui_begin_tab_item(label,open,flags);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Selected
		buffer_f32 // Open
	]);
}

function imgui_accept_drag_drop_payload(type,flags) {
	_imgui_accept_drag_drop_payload(type,flags);
	var data_size = buffer_peek(global.imgui_buffer,0,buffer_f32);
	var ret = array_create(data_size);
	var offset = 4;
	for (var i = 0; i < data_size; ++i) {
		ret[i] = buffer_peek(global.imgui_buffer,offset,buffer_f32);
		offset += 4;
	}
	
	return ret;
}

function imgui_get_drag_drop_payload() {
	_imgui_get_drag_drop_payload();
	var data_size = buffer_peek(global.imgui_buffer,0,buffer_f32);
	var ret = array_create(data_size);
	var offset = 4;
	for (var i = 0; i < data_size; ++i) {
		ret[i] = buffer_peek(global.imgui_buffer,offset,buffer_f32);
		offset += 4;
	}
	
	return ret;
}

function imgui_get_item_rect_min() {
	_imgui_get_item_rect_min();
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Rect min x
		buffer_f32 // Rect min y
	]);
}

function imgui_get_item_rect_max() {
	_imgui_get_item_rect_max();
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Rect max x
		buffer_f32 // Rect max y
	]);
}

function imgui_get_item_rect_size() {
	_imgui_get_item_rect_size();
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Rect size x
		buffer_f32 // Rect size y
	]);
}

function imgui_calc_text_size(text,text_end,hide_text_after_double_dash,wrap_width) {
	_imgui_calc_text_size(text,text_end,hide_text_after_double_dash,wrap_width);
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Calculated text size width
		buffer_f32 // Calculated text size height
	]);
}

function imgui_color_convert_u32_to_float4(u32_color) {
	_imgui_color_convert_u32_to_float4(u32_color);
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // R
		buffer_f32, // G
		buffer_f32, // B
		buffer_f32 // A
	]);
}

function imgui_color_convert_rgb_to_hsv(r,g,b) {
	_imgui_color_convert_rgb_to_hsv(r,g,b);
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // H
		buffer_f32, // S
		buffer_f32 // V
	]);
}

function imgui_color_convert_hsv_to_rgb(h,s,v) {
	_imgui_color_convert_hsv_to_rgb(h,s,v);
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // R
		buffer_f32, // G
		buffer_f32 // B
	]);
}

function imgui_get_mouse_pos() {
	_imgui_get_mouse_pos();
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Mouse x
		buffer_f32 // Mouse y
	]);
}

function imgui_get_mouse_pos_on_opening_current_popup() {
	_imgui_get_mouse_pos_on_opening_current_popup();
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Mouse x
		buffer_f32 // Mouse y
	]);
}

function imgui_get_mouse_drag_delta(button,lock_threshold) {
	_imgui_get_mouse_drag_delta(button,lock_threshold);
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Delta x
		buffer_f32 // Delta y
	]);
}

function imgui_style_get_window_padding() {
	_imgui_style_get_window_padding();
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Pad x
		buffer_f32 // Pad y
	]);
}

function imgui_style_get_window_min_size() {
	_imgui_style_get_window_min_size();
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Min size x
		buffer_f32 // Min size y
	]);
}

function imgui_style_get_window_title_align() {
	_imgui_style_get_window_title_align();
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Align x
		buffer_f32 // Align y
	]);
}

function imgui_style_get_frame_padding() {
	_imgui_style_get_frame_padding();
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Pad x
		buffer_f32 // Pad y
	]);
}

function imgui_style_get_item_spacing() {
	_imgui_style_get_item_spacing();
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Spacing x
		buffer_f32 // Spacing y
	]);
}

function imgui_style_get_item_inner_spacing() {
	_imgui_style_get_item_inner_spacing();
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Spacing x
		buffer_f32 // Spacing y
	]);
}

function imgui_style_get_selectable_text_align() {
	_imgui_style_get_selectable_text_align();
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Align x
		buffer_f32 // Align y
	]);
}

function imgui_style_get_display_window_padding() {
	_imgui_style_get_display_window_padding();
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Pad x
		buffer_f32 // Pad y
	]);
}

function imgui_style_get_display_safe_area_padding() {
	_imgui_style_get_display_safe_area_padding();
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Pad x
		buffer_f32 // Pad y
	]);
}

function imgui_style_get_color(idx) {
	_imgui_style_get_color(idx);
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // R
		buffer_f32, // G
		buffer_f32, // B
		buffer_f32 // A
	]);
}

function imgui_drawlist_add_text(x,y,color,text_begin,text_end) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, x,
		buffer_f32, y,
		buffer_f32, color
	]);
	_imgui_drawlist_add_text(text_begin,text_end);
}

function imgui_drawlist_add_polyline(points,num_points,color,closed,thickness) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, points
	]);
	_imgui_drawlist_add_polyline(num_points,color,closed,thickness);
}

function imgui_drawlist_add_convex_poly_filled(points,num_points,color) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, points
	]);
	_imgui_drawlist_add_convex_poly_filled(num_points,color);
}

function imgui_load_image(sprite,name = sprite_get_name(sprite)) {
	var d3d_device = os_get_info()[? "video_d3d11_device"];
	var spr_w = sprite_get_width(sprite);
	var spr_h = sprite_get_height(sprite);
	var surf = surface_create(spr_w,spr_h);
	surface_set_target(surf);
	draw_sprite(sprite,0,0,0);
	surface_reset_target();
	var buffer = buffer_create(spr_w*spr_h*4,buffer_fixed,1);
	buffer_get_surface(buffer,surf,0);
	surface_free(surf);
	var buffer_ptr = buffer_get_address(buffer);
	
	buffer_write_args(global.imgui_buffer, [
		buffer_f32, spr_w,
		buffer_f32, spr_h
	]);
	
	_imgui_load_image(name,buffer_ptr,d3d_device);
	
	buffer_delete(buffer);
}

function imgui_image(name,size,uv0=[0,0],uv1=[1,1],tint_col=[1,1,1,1],border_col=[0,0,0,0]) {
		
	buffer_write_args(global.imgui_buffer, [
		buffer_f32,  size[0],
		buffer_f32,  size[1],
		buffer_f32,  uv0[0],
		buffer_f32,  uv0[1],
		buffer_f32,  uv1[0],
		buffer_f32,  uv1[1],
		buffer_f32,  tint_col[0],
		buffer_f32,  tint_col[1],
		buffer_f32,  tint_col[2],
		buffer_f32,  tint_col[3],
		buffer_f32,  border_col[0],
		buffer_f32,  border_col[1],
		buffer_f32,  border_col[2],
		buffer_f32,  border_col[3]
	]);
		
	_imgui_image(name);
}

function imgui_image_button(name,size,uv0=[0,0],uv1=[1,1],frame_padding=-1,bg_col=[0,0,0,0],tint_col=[1,1,1,1]) {
	buffer_write_args(global.imgui_buffer, [
		buffer_f32, size[0],
		buffer_f32, size[1],
		buffer_f32, uv0[0],
		buffer_f32, uv0[1],
		buffer_f32, uv1[0],
		buffer_f32, uv1[1],
		buffer_f32, frame_padding,
		buffer_f32, bg_col[0],
		buffer_f32, bg_col[1],
		buffer_f32, bg_col[2],
		buffer_f32, bg_col[3],
		buffer_f32, tint_col[0],
		buffer_f32, tint_col[1],
		buffer_f32, tint_col[2],
		buffer_f32, tint_col[3]
	]);
	
	return _imgui_image_button(name);
}