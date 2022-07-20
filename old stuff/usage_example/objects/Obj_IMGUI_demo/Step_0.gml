//if (keyboard_check(ord("1"))) { imgui_set_font(font0); }
//if (keyboard_check(ord("2"))) { imgui_set_font(font1); }
//if (keyboard_check(ord("3"))) { imgui_set_font(font2); }
//if (keyboard_check(ord("4"))) { imgui_set_font(font3); }

imgui_newframe();

//imgui_show_user_guide_gml();

imgui_set_next_window_size(550,400,0);
imgui_begin("Test",noone,0);

imgui_show_demo_window_widgets_gml();


imgui_end();

imgui_show_demo_window(noone);