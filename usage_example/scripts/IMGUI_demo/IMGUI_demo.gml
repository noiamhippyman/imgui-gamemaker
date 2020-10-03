function imgui_help_marker(desc) {
	imgui_text_disabled("(?)");
	if (imgui_is_item_hovered()) {
		imgui_begin_tooltip();
		imgui_push_text_wrap_pos(imgui_get_font_size() * 35);
		imgui_text_unformatted(desc);
		imgui_pop_text_wrap_pos();
		imgui_end_tooltip();
	}
}

function imgui_show_docking_disabled_message() {
	imgui_text("ERROR: Docking is not enabled! See Demo > Configuration.");
}

function imgui_show_user_guide_gml() {
	
}