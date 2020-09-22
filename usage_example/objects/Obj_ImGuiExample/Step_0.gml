imgui_newframe();


if (open) {
	var ret = imgui_begin("Test",open);

	var expanded = ret[0];
	open = ret[1];
	if (expanded) {
		imgui_text("Expanded: " + string(expanded));
		imgui_text("Opened: " + string(open));
	}
	
	imgui_end();
}


if (!open and keyboard_check_pressed(vk_f1)) {
	open = true;
}