imgui_newframe();

if (keyboard_check_pressed(vk_space)) {
	open = !open;
}

if (open) {
	var ret = imgui_begin("Test",open,0);
	if (ret[0]) {
		open = ret[1];
		
		//if (imgui_begin_combo("Test Combo","Preview",0)) {
		//	for (var i = 0; i < array_length(items); ++i) {
		//		imgui_button(items[i],-1,0);
		//	}
		//	imgui_end_combo();
		//}
		var combo_ret = imgui_combo("Combo Menu##WTF",current_item,"a0b0c00",-1);
		if (combo_ret[0]) current_item = combo_ret[1];
		
		
	}
	imgui_end();
}