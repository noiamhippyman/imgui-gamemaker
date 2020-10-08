//if (keyboard_check(ord("1"))) { imgui_set_font(font0); }
//if (keyboard_check(ord("2"))) { imgui_set_font(font1); }
//if (keyboard_check(ord("3"))) { imgui_set_font(font2); }
//if (keyboard_check(ord("4"))) { imgui_set_font(font3); }

imgui_newframe();

//imgui_show_user_guide_gml();

imgui_set_next_window_size(550,400,0);
imgui_begin("Test",noone,0);

imgui_show_demo_window_widgets_gml();

//imgui_text("Default text");

//imgui_push_font(font1);
//imgui_text("Font 1");
//imgui_pop_font();

//imgui_push_font(font2);
//imgui_text("Font 2");
//imgui_pop_font();

//imgui_push_font(font3);
//imgui_text("Font 3 /w Japanese Glyph Range こんにちは世界");
//imgui_pop_font();

imgui_end();

imgui_show_demo_window(noone);