imgui_newframe();


imgui_begin("Test");

imgui_text("Hello GameMaker!");

if (imgui_button("Button!")) {
	show_message("HOWDY!");
}

imgui_end();




imgui_begin("Window 2");

imgui_button("BOOBS");
imgui_button("NO BOOBS");
imgui_button("SO MANY BOOBS");

imgui_end();