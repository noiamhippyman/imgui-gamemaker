imgui_setup();

//var filename = @"C:\Users\brand\Downloads\Source_Code_Pro\SourceCodePro-Regular.ttf";
//font_1 = imgui_fonts_add_font_from_file_ttf(filename,24,0,0);
font0 = imgui_fonts_add_font_default();
//font1 = imgui_fonts_add_font_from_file_ttf(@"C:\Users\brand\Downloads\TestFonts\OpenSans-Regular.ttf",12,0,0);
font3 = imgui_fonts_add_font_from_file_ttf(@"C:\Users\brand\Downloads\TestFonts\NotoSansJP-Regular.otf",20,0,imgui_fonts_get_glyph_range_japanese());
imgui_fonts_build();

imgui_load_image(Spr_Test);