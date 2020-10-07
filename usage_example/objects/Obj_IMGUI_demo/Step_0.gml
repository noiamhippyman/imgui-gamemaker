
if (keyboard_check_pressed(vk_f1)) {
	imgui_set_font(font0);
}

if (keyboard_check_pressed(vk_f2)) {
	imgui_set_font(font1);
}

if (keyboard_check_pressed(vk_f3)) {
	imgui_set_font(font2);
}

imgui_newframe();

//imgui_show_user_guide_gml();

imgui_set_next_window_size(550,400,0);
imgui_begin("Test",noone,0);
//imgui_show_demo_window_widgets_gml();

imgui_text("What font am I?!");

imgui_end();


//imgui_show_demo_window(noone)
imgui_show_style_editor();