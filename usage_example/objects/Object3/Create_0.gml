buffer = buffer_create(1024,buffer_fixed,1);
test_buffer_setup(buffer_get_address(buffer), buffer_get_size(buffer));

test_buffer_funcs();

buffer_seek(buffer,buffer_seek_start,0);
show_debug_message("Read Float: " + string(buffer_read(buffer,buffer_f32)));
show_debug_message("Read String: " + string(buffer_read(buffer,buffer_string)));

show_debug_message("Peek Float: " + string(buffer_peek(buffer,0,buffer_f32)));
show_debug_message("Peek String: " + string(buffer_peek(buffer,4,buffer_string)));

test_buffer_cleanup();

buffer_delete(buffer);

game_end();