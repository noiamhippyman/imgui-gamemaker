imgui_setup();

//var filename = @"C:\Users\brand\Downloads\Source_Code_Pro\SourceCodePro-Regular.ttf";
//font_1 = imgui_fonts_add_font_from_file_ttf(filename,24,0,0);
font0 = imgui_fonts_add_font_default();
font1 = imgui_fonts_add_font_from_file_ttf(@"C:\Users\brand\Downloads\Source_Code_Pro\SourceCodePro-Regular.ttf",24,0,0);
font2 = imgui_fonts_add_font_from_file_ttf(@"C:\Users\brand\Downloads\Major_Mono_Display\MajorMonoDisplay-Regular.ttf",16,0,0);
imgui_fonts_build();