hwnd = window_handle();

var osinfo = os_get_info();
device = osinfo[? "video_d3d11_device" ];
context = osinfo[? "video_d3d11_context" ];
ds_map_destroy(osinfo);


imgui_setup(hwnd,device,context);