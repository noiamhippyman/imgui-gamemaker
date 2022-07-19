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

