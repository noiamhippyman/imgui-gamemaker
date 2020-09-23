imgui_newframe();

imgui_begin("IMGUI " + imgui_get_version(),true,ImGuiWindowFlags.NoCollapse);
if (imgui_button("Demo Window",0,0)) show_demo_window = !show_demo_window;
if (imgui_button("About Window",0,0)) show_about_window = !show_about_window;
if (imgui_button("Metrics Window",0,0)) show_metrics_window = !show_metrics_window;
if (imgui_button("Style Editor",0,0)) show_style_editor = !show_style_editor;
if (imgui_button("User Guide",0,0)) show_user_guide = !show_user_guide;
imgui_end();

if (show_demo_window) 
	show_demo_window = imgui_show_demo_window(show_demo_window);

if (show_about_window)
	show_about_window = imgui_show_about_window(show_about_window);

if (show_metrics_window)
	show_metrics_window = imgui_show_metrics_window(show_metrics_window);

if (show_user_guide) {
	var ret = imgui_begin("User Guide",true,0);
	if (ret[0]) imgui_show_user_guide();
	show_user_guide = ret[1];
	imgui_end();
}

if (show_style_editor) {
	var ret = imgui_begin("Style Editor",true,0);
	if (ret[0]) {
		imgui_show_style_editor();
		imgui_show_style_selector("Style Selector");
		imgui_show_font_selector("Font Selector");
	}
	show_style_editor = ret[1];
	imgui_end();
}

//imgui_begin("Test",true,0);
//var winappear = imgui_is_window_appearing();
//var wincollapse = imgui_is_window_collapsed();
//var winfocus = imgui_is_window_focused(0);
//var winhover = imgui_is_window_hovered(0);
//var windpiscale = imgui_get_window_dpi_scale();
//var winpos = imgui_get_window_pos();
//var winsize = imgui_get_window_size();
//var winwidth = imgui_get_window_width();
//var winheight = imgui_get_window_height();

//imgui_end();

//imgui_begin("Monitor",true,0);

//imgui_text("imgui_is_window_appearing: " + string(winappear));
//imgui_text("imgui_is_window_collapsed: " + string(wincollapse));
//imgui_text("imgui_is_window_focused: " + string(winfocus));
//imgui_text("imgui_is_window_hovered: " + string(winhover));
//imgui_text("imgui_get_window_dpi_scale: " + string(windpiscale));
//imgui_text("imgui_get_window_pos: " + string(winpos));
//imgui_text("imgui_get_window_size: " + string(winsize));
//imgui_text("imgui_get_window_width: " + string(winwidth));
//imgui_text("imgui_get_window_height: " + string(winheight));

//imgui_end();