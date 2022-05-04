imgui_setup();

//var filename = @"C:\Users\brand\Downloads\Source_Code_Pro\SourceCodePro-Regular.ttf";
//font_1 = imgui_fonts_add_font_from_file_ttf(filename,24,0,0);
font0 = imgui_fonts_add_font_default();
font1 = imgui_fonts_add_font_from_file_ttf(@"C:\Users\brand\Downloads\TestFonts\SourceCodePro-Regular.ttf",24,0,0);
font2 = imgui_fonts_add_font_from_file_ttf(@"C:\Users\brand\Downloads\TestFonts\MajorMonoDisplay-Regular.ttf",16,0,0);
font3 = imgui_fonts_add_font_from_file_ttf(@"C:\Users\brand\Downloads\TestFonts\NotoSansMonoCJKjp-Regular.otf",20,0,imgui_fonts_get_glyph_range_japanese());
imgui_fonts_build();

imgui_load_image(Spr_Test);

//var spr = Spr_Test;
//var spr_w = sprite_get_width(spr);
//var spr_h = sprite_get_height(spr);
//var surf = surface_create(spr_w,spr_h);
//surface_set_target(surf);
//draw_sprite(spr,0,0,0);
//surface_reset_target();
//test_buffer = buffer_create(spr_w*spr_h*4,buffer_fixed,1);
//buffer_get_surface(test_buffer,surf,0);
//surface_free(surf);


//show_message("font0: " + string(font0));
//show_message("font1: " + string(font1));
//show_message("font2: " + string(font2));

//game_end();