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
				var v = val[(val_count-1)-j];
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


// ImGui functions with default arguments

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

// using ImGuiWindowFlags
function imgui_begin(name, open=-1, flags=0) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, open,
		buffer_f32, flags
	]);
	
	_imgui_begin(name);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // expanded
		buffer_f32 // open
	]);
}

// using ImGuiWindowFlags
function imgui_begin_child(name,size=[0,0],border=false,flags=0) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, size,
		buffer_f32, border,
		buffer_f32, flags
	]);
	
	return _imgui_begin_child(name);
}

// using ImGuiFocusedFlags
function imgui_is_window_focused(flags=0) {
	return _imgui_is_window_focused(flags);
}

// using ImGuiHoveredFlags
function imgui_is_window_hovered(flags=0) {
	return _imgui_is_window_hovered(flags);
}

function imgui_get_window_pos() {
	_imgui_get_window_pos();
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // window x 
		buffer_f32 // window y
	]);
}

function imgui_get_window_size() {
	_imgui_get_window_size();
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // window width 
		buffer_f32 // window height
	]);
}

// using ImGuiCond
function imgui_set_next_window_pos(pos,cond=0,pivot=[0,0]) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32,pos,
		buffer_f32,cond,
		buffer_f32,pivot
	]);
	
	_imgui_set_next_window_pos();
}

// using ImGuiCond
function imgui_set_next_window_size(size,cond=0) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32,size,
		buffer_f32,cond
	]);
	
	_imgui_set_next_window_size();
}

function imgui_set_next_window_size_constraints(size_min,size_max) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, size_min,
		buffer_f32, size_max
	]);
	
	_imgui_set_next_window_size_constraints();
}

function imgui_set_next_window_content_size(size) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, size
	]);
	
	_imgui_set_next_window_content_size();
}

// using ImGuiCond
function imgui_set_next_window_collapsed(collapsed,cond=0) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, collapsed,
		buffer_f32, cond
	]);
	
	_imgui_set_next_window_collapsed();
}

// using ImGuiCond
function imgui_set_window_pos(pos,cond=0) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, pos,
		buffer_f32, cond
	]);
	
	_imgui_set_window_pos();
}

// using ImGuiCond
function imgui_set_window_size(size,cond=0) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, size,
		buffer_f32, cond
	]);
	
	_imgui_set_window_size();
}

// using ImGuiCond
function imgui_set_window_collapsed(collapsed,cond=0) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, collapsed,
		buffer_f32, cond
	]);
	
	_imgui_set_window_collapsed();
}

function imgui_get_content_region_avail() {
	_imgui_get_content_region_avail();
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // region x
		buffer_f32, // region y
	]);
}

function imgui_get_content_region_max() {
	_imgui_get_content_region_max();
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // region x
		buffer_f32, // region y
	]);
}

function imgui_get_window_content_region_min() {
	_imgui_get_window_content_region_min();
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // region x
		buffer_f32, // region y
	]);
}

function imgui_get_window_content_region_max() {
	_imgui_get_window_content_region_max();
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // region x
		buffer_f32, // region y
	]);
}

function imgui_set_scroll_here_x(center_x_ratio=0.5) {
	_imgui_set_scroll_here_x(center_x_ratio);
}

function imgui_set_scroll_here_y(center_y_ratio=0.5) {
	_imgui_set_scroll_here_y(center_y_ratio);
}

function imgui_set_scroll_from_pos_x(center_x_ratio=0.5) {
	_imgui_set_scroll_from_pos_x(center_x_ratio);
}

function imgui_set_scroll_from_pos_y(center_y_ratio=0.5) {
	_imgui_set_scroll_from_pos_y(center_y_ratio);
}

function imgui_push_style_color(idx,col) {
	buffer_write_args(global.imgui_buffer, [
		buffer_f32, idx,
		buffer_f32, col
	]);
	
	_imgui_push_style_color();
}

function imgui_pop_style_color(count=1) {
	_imgui_pop_style_color(count);
}

function imgui_push_style_var_f2(idx,val) {
	buffer_write_args(global.imgui_buffer, [
		buffer_f32, idx,
		buffer_f32, val 
	]);
	_imgui_push_style_var_f2();
}

function imgui_pop_style_var(count=1) {
	_imgui_pop_style_var(count);
}

function imgui_push_text_wrap_pos(wrap_local_pos_x=0) {
	_imgui_push_text_wrap_pos(wrap_local_pos_x);
}

function imgui_get_font_tex_uv_white_pixel() {
	_imgui_get_font_tex_uv_white_pixel()
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // U
		buffer_f32  // V
	]);
}

function imgui_get_style_color_u32(idx,alpha=1) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, idx,
		buffer_f32, alpha
	]);
	
	return _imgui_get_style_color_u32();
}

function imgui_get_color_u32(col) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, col
	]);
	
	return _imgui_get_color_u32();
}

function imgui_get_style_color_vec4(idx) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, idx
	]);
	
	_imgui_get_style_color_vec4();
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // r
		buffer_f32, // g
		buffer_f32, // b
		buffer_f32  // a
	]);
}

function imgui_same_line(offset_from_start_x=0,spacing=-1) {
	_imgui_same_line(offset_from_start_x,spacing);
}

function imgui_dummy(size) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, size
	]);
	_imgui_dummy();
}

function imgui_indent(indent_w=0) {
	_imgui_indent(indent_w);
}

function imgui_unindent(indent_w=0) {
	_imgui_unindent(indent_w);
}

function imgui_get_cursor_pos() {
	_imgui_get_cursor_pos();
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // cursor x
		buffer_f32  // cursor y
	]);
}

function imgui_set_cursor_pos(pos) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, pos
	]);
	_imgui_set_cursor_pos();
}

function imgui_get_cursor_start_pos() {
	_imgui_get_cursor_start_pos();
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // cursor x
		buffer_f32  // cursor y
	]);
}

function imgui_get_cursor_screen_pos() {
	_imgui_get_cursor_screen_pos();
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // cursor x
		buffer_f32  // cursor y
	]);
}

function imgui_set_cursor_screen_pos(pos) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, pos
	]);
	_imgui_set_cursor_screen_pos();
}

function imgui_text_unformatted(text,text_end=imgui_null()) {
	_imgui_text_unformatted(text,text_end);
}

function imgui_text_colored(col,text) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32,col
	]);
	_imgui_text_colored(text);
}

function imgui_button(label,size=[0,0]) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32,size
	]);
	return _imgui_button(label);
}

function imgui_invisible_button(str_id,size,flags=0) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32,size,
		buffer_f32,flags
	]);
	return _imgui_invisible_button(str_id);
}

function imgui_image(name,size,uv0=[0,0],uv1=[1,1],tint_col=[1,1,1,1],border_col=[0,0,0,0]) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, size,
		buffer_f32, uv0,
		buffer_f32, uv1,
		buffer_f32, tint_col,
		buffer_f32, border_col
	]);
	
	_imgui_image(name);
}

function imgui_image_button(name,size,uv0=[0,0],uv1=[1,1],frame_padding=-1,bg_col=[0,0,0,0],tint_col=[1,1,1,1]) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, size,
		buffer_f32, uv0,
		buffer_f32, uv1,
		buffer_f32, frame_padding,
		buffer_f32, bg_col,
		buffer_f32, tint_col
	]);
	
	return _imgui_image_button(name);
}

function imgui_checkbox(label,value) {
	_imgui_checkbox(label,value);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32  // Is Checked
	]);
}

function imgui_checkbox_flags(label,flags,flags_value) {
	_imgui_checkbox_flags(label,flags,flags_value);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32  // Flags
	]);
}

function imgui_radio_button_int(label,v,v_button) {
	_imgui_radio_button_int(label,v,v_button);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32  // Value
	]);
}

function imgui_progress_bar(fraction,size=[-1,0],overlay=imgui_null()) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, fraction,
		buffer_f32, size
	]);
	
	_imgui_progress_bar(overlay);
}

function imgui_begin_combo(label,preview_value,flags=0) {
	return _imgui_begin_combo(label,preview_value,flags);
}

function imgui_combo(label,current_item,items,item_count,popup_max_height_in_items=-1) {
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

function imgui_drag_float(label,v,v_speed=1,v_min=0,v_max=0,format="%.3f",flags=0) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, v,
		buffer_f32, v_speed,
		buffer_f32, v_min,
		buffer_f32, v_max,
		buffer_f32, flags
	]);
	
	_imgui_drag_float(label,format);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32  // V
	]);
}

function imgui_drag_float2(label,v,v_speed=1,v_min=0,v_max=0,format="%.3f",flags=0) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, v,
		buffer_f32, v_speed,
		buffer_f32, v_min,
		buffer_f32, v_max,
		buffer_f32, flags
	]);
	
	_imgui_drag_float2(label,format);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32, // V[0]
		buffer_f32  // V[1]
	]);
}

function imgui_drag_float3(label,v,v_speed=1,v_min=0,v_max=0,format="%.3f",flags=0) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, v,
		buffer_f32, v_speed,
		buffer_f32, v_min,
		buffer_f32, v_max,
		buffer_f32, flags
	]);
	
	_imgui_drag_float3(label,format);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32, // V[0]
		buffer_f32, // V[1]
		buffer_f32  // V[2]
	]);
}

function imgui_drag_float4(label,v,v_speed=1,v_min=0,v_max=0,format="%.3f",flags=0) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, v,
		buffer_f32, v_speed,
		buffer_f32, v_min,
		buffer_f32, v_max,
		buffer_f32, flags
	]);
	
	_imgui_drag_float4(label,format);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32, // V[0]
		buffer_f32, // V[1]
		buffer_f32, // V[2]
		buffer_f32  // V[3]
	]);
}

function imgui_drag_float_range2(label,v_current_min,v_current_max,v_speed=1,v_min=0,v_max=0,format="%.3f",format_max=imgui_null(),flags=0) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, v_current_min,
		buffer_f32, v_current_max,
		buffer_f32, v_speed,
		buffer_f32, v_min,
		buffer_f32, v_max,
		buffer_f32, flags
	]);
	
	_imgui_drag_float_range2(label,format,format_max);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32, // Current Min
		buffer_f32  // Current Max
	]);
}

function imgui_drag_int(label,v,v_speed=1,v_min=0,v_max=0,format="%d",flags=0) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, v,
		buffer_f32, v_speed,
		buffer_f32, v_min,
		buffer_f32, v_max,
		buffer_f32, flags
	]);
	
	_imgui_drag_int(label,format);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32  // V
	]);
}

function imgui_drag_int2(label,v,v_speed=1,v_min=0,v_max=0,format="%d",flags=0) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, v,
		buffer_f32, v_speed,
		buffer_f32, v_min,
		buffer_f32, v_max,
		buffer_f32, flags
	]);
	
	_imgui_drag_int2(label,format);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32, // V[0]
		buffer_f32  // V[1]
	]);
}

function imgui_drag_int3(label,v,v_speed=1,v_min=0,v_max=0,format="%d",flags=0) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, v,
		buffer_f32, v_speed,
		buffer_f32, v_min,
		buffer_f32, v_max,
		buffer_f32, flags
	]);
	
	_imgui_drag_int3(label,format);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32, // V[0]
		buffer_f32, // V[1]
		buffer_f32  // V[2]
	]);
}

function imgui_drag_int4(label,v,v_speed=1,v_min=0,v_max=0,format="%d",flags=0) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, v,
		buffer_f32, v_speed,
		buffer_f32, v_min,
		buffer_f32, v_max,
		buffer_f32, flags
	]);
	
	_imgui_drag_int4(label,format);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32, // V[0]
		buffer_f32, // V[1]
		buffer_f32, // V[2]
		buffer_f32  // V[3]
	]);
}

function imgui_drag_int_range2(label,v_current_min,v_current_max,v_speed=1,v_min=0,v_max=0,format="%d",format_max=imgui_null(),flags=0) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, v_current_min,
		buffer_f32, v_current_max,
		buffer_f32, v_speed,
		buffer_f32, v_min,
		buffer_f32, v_max,
		buffer_f32, flags
	]);
	
	_imgui_drag_int_range2(label,format,format_max);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32, // Current Min
		buffer_f32  // Current Max
	]);
}

//function imgui_drag_scalar_s8(label,v,v_speed=1,v_min=0,v_max=0,format=imgui_null(),flags=0) {
//	buffer_write_args(global.imgui_buffer,[
//		buffer_f32,v,
//		buffer_f32,v_speed,
//		buffer_f32,v_min,
//		buffer_f32,v_max,
//		buffer_f32,flags
//	]);
	
//	_imgui_drag_scalar_s8(label,format);
	
//	return buffer_return(global.imgui_buffer,[
//		buffer_f32, // Changed
//		buffer_f32  // Current Value (v)
//	]);
//}

function imgui_slider_float(label,v,v_speed=1,v_min=0,v_max=0,format="%.3f",flags=0) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, v,
		buffer_f32, v_min,
		buffer_f32, v_max,
		buffer_f32, flags
	]);
	
	_imgui_slider_float(label,format);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32  // V
	]);
}

function imgui_slider_float2(label,v,v_speed=1,v_min=0,v_max=0,format="%.3f",flags=0) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, v,
		buffer_f32, v_min,
		buffer_f32, v_max,
		buffer_f32, flags
	]);
	
	_imgui_slider_float2(label,format);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32, // V[0]
		buffer_f32  // V[1]
	]);
}

function imgui_slider_float3(label,v,v_speed=1,v_min=0,v_max=0,format="%.3f",flags=0) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, v,
		buffer_f32, v_min,
		buffer_f32, v_max,
		buffer_f32, flags
	]);
	
	_imgui_slider_float3(label,format);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32, // V[0]
		buffer_f32, // V[1]
		buffer_f32  // V[2]
	]);
}

function imgui_slider_float4(label,v,v_speed=1,v_min=0,v_max=0,format="%.3f",flags=0) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, v,
		buffer_f32, v_min,
		buffer_f32, v_max,
		buffer_f32, flags
	]);
	
	_imgui_slider_float4(label,format);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32, // V[0]
		buffer_f32, // V[1]
		buffer_f32, // V[2]
		buffer_f32  // V[3]
	]);
}

function imgui_slider_angle(label,v_rad,v_degrees_min=-360,v_degrees_max=360,format="%.0f deg",flags=0) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, v_rad,
		buffer_f32, v_degrees_min,
		buffer_f32, v_degrees_max,
		buffer_f32, flags
	]);
	
	_imgui_slider_angle(label,format);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32, // Radians
	]);
}

function imgui_slider_int(label,v,v_speed=1,v_min=0,v_max=0,format="%d",flags=0) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, v,
		buffer_f32, v_min,
		buffer_f32, v_max,
		buffer_f32, flags
	]);
	
	_imgui_slider_int(label,format);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32  // V
	]);
}

function imgui_slider_int2(label,v,v_speed=1,v_min=0,v_max=0,format="%d",flags=0) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, v,
		buffer_f32, v_min,
		buffer_f32, v_max,
		buffer_f32, flags
	]);
	
	_imgui_slider_int2(label,format);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32, // V[0]
		buffer_f32  // V[1]
	]);
}

function imgui_slider_int3(label,v,v_speed=1,v_min=0,v_max=0,format="%d",flags=0) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, v,
		buffer_f32, v_min,
		buffer_f32, v_max,
		buffer_f32, flags
	]);
	
	_imgui_slider_int3(label,format);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32, // V[0]
		buffer_f32, // V[1]
		buffer_f32  // V[2]
	]);
}

function imgui_slider_int4(label,v,v_speed=1,v_min=0,v_max=0,format="%d",flags=0) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, v,
		buffer_f32, v_min,
		buffer_f32, v_max,
		buffer_f32, flags
	]);
	
	_imgui_slider_int4(label,format);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32, // V[0]
		buffer_f32, // V[1]
		buffer_f32, // V[2]
		buffer_f32  // V[3]
	]);
}

function imgui_vslider_float(label,size,v,v_min,v_max,format="%.3f",flags=0) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, size,
		buffer_f32, v,
		buffer_f32, v_min,
		buffer_f32, v_max,
		buffer_f32, flags
	]);
	
	_imgui_vslider_float(label,format);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32  // Value
	]);
}

function imgui_vslider_int(label,size,v,v_min,v_max,format="%d",flags=0) {
	buffer_write_args(global.imgui_buffer,[
		buffer_f32, size,
		buffer_f32, v,
		buffer_f32, v_min,
		buffer_f32, v_max,
		buffer_f32, flags
	]);
	
	_imgui_vslider_int(label,format);
	
	return buffer_return(global.imgui_buffer,[
		buffer_f32, // Changed
		buffer_f32  // Value
	]);
}






















