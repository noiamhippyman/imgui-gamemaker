#macro IMGUI_BUFFER_SIZE 4096			// how many floats can this buffer hold. Size in bytes is { buffer_sizeof(IMGUI_BUFFER_TYPE) * IMGUI_BUFFER_SIZE }.
//#macro IMGUI_BUFFER_TYPE buffer_f32

// Flags for imgui_begin
enum ImGuiWindowFlags {
    None                   = 0,
    NoTitleBar             = 1 << 0,   // Disable title-bar
    NoResize               = 1 << 1,   // Disable user resizing with the lower-right grip
    NoMove                 = 1 << 2,   // Disable user moving the window
    NoScrollbar            = 1 << 3,   // Disable scrollbars (window can still scroll with mouse or programmatically)
    NoScrollWithMouse      = 1 << 4,   // Disable user vertically scrolling with mouse wheel. On child window, mouse wheel will be forwarded to the parent unless NoScrollbar is also set.
    NoCollapse             = 1 << 5,   // Disable user collapsing window by double-clicking on it. Also referred to as "window menu button" within a docking node.
    AlwaysAutoResize       = 1 << 6,   // Resize every window to its content every frame
    NoBackground           = 1 << 7,   // Disable drawing background color (WindowBg, etc.) and outside border. Similar as using SetNextWindowBgAlpha(0.0f).
    NoSavedSettings        = 1 << 8,   // Never load/save settings in .ini file
    NoMouseInputs          = 1 << 9,   // Disable catching mouse, hovering test with pass through.
    MenuBar                = 1 << 10,  // Has a menu-bar
    HorizontalScrollbar    = 1 << 11,  // Allow horizontal scrollbar to appear (off by default). You may use SetNextWindowContentSize(ImVec2(width,0.0f)) prior to calling Begin() to specify width. Read code in imgui_demo in the "Horizontal Scrolling" section.
    NoFocusOnAppearing     = 1 << 12,  // Disable taking focus when transitioning from hidden to visible state
    NoBringToFrontOnFocus  = 1 << 13,  // Disable bringing window to front when taking focus (e.g. clicking on it or programmatically giving it focus)
    AlwaysVerticalScrollbar= 1 << 14,  // Always show vertical scrollbar (even if ContentSize.y < Size.y)
    AlwaysHorizontalScrollbar=1<< 15,  // Always show horizontal scrollbar (even if ContentSize.x < Size.x)
    AlwaysUseWindowPadding = 1 << 16,  // Ensure child windows without border uses style.WindowPadding (ignored by default for non-bordered child windows, because more convenient)
    NoNavInputs            = 1 << 18,  // No gamepad/keyboard navigation within the window
    NoNavFocus             = 1 << 19,  // No focusing toward this window with gamepad/keyboard navigation (e.g. skipped by CTRL+TAB)
    UnsavedDocument        = 1 << 20,  // Append '*' to title without affecting the ID, as a convenience to avoid using the ### operator. When used in a tab/docking context, tab is selected on closure and closure is deferred by one frame to allow code to cancel the closure (with a confirmation popup, etc.) without flicker.
    NoDocking              = 1 << 21,  // Disable docking of this window

    NoNav                  = ImGuiWindowFlags.NoNavInputs | ImGuiWindowFlags.NoNavFocus,
    NoDecoration           = ImGuiWindowFlags.NoTitleBar | ImGuiWindowFlags.NoResize | ImGuiWindowFlags.NoScrollbar | ImGuiWindowFlags.NoCollapse,
    NoInputs               = ImGuiWindowFlags.NoMouseInputs | ImGuiWindowFlags.NoNavInputs | ImGuiWindowFlags.NoNavFocus
}

// Flags for imgui_is_window_focused
enum ImGuiFocusedFlags
{
    None                          = 0,
    ChildWindows                  = 1 << 0,   // IsWindowFocused(): Return true if any children of the window is focused
    RootWindow                    = 1 << 1,   // IsWindowFocused(): Test from root window (top most parent of the current hierarchy)
    AnyWindow                     = 1 << 2,   // IsWindowFocused(): Return true if any window is focused. Important: If you are trying to tell how to dispatch your low-level inputs, do NOT use this. Use 'io.WantCaptureMouse' instead! Please read the FAQ!
    RootAndChildWindows           = ImGuiFocusedFlags.RootWindow | ImGuiFocusedFlags.ChildWindows
}

// Flags for imgui_is_item_hovered, imgui_is_window_hovered functions
// Note: if you are trying to check whether your mouse should be dispatched to Dear ImGui or to your app, you should use 'io.WantCaptureMouse' instead! Please read the FAQ!
// Note: windows with the ImGuiWindowFlags_NoInputs flag are ignored by IsWindowHovered() calls.
enum ImGuiHoveredFlags
{
    None                          = 0,        // Return true if directly over the item/window, not obstructed by another window, not obstructed by an active popup or modal blocking inputs under them.
    ChildWindows                  = 1 << 0,   // IsWindowHovered() only: Return true if any children of the window is hovered
    RootWindow                    = 1 << 1,   // IsWindowHovered() only: Test from root window (top most parent of the current hierarchy)
    AnyWindow                     = 1 << 2,   // IsWindowHovered() only: Return true if any window is hovered
    AllowWhenBlockedByPopup       = 1 << 3,   // Return true even if a popup window is normally blocking access to this item/window
    //AllowWhenBlockedByModal     = 1 << 4,   // Return true even if a modal popup window is normally blocking access to this item/window. FIXME-TODO: Unavailable yet.
    AllowWhenBlockedByActiveItem  = 1 << 5,   // Return true even if an active item is blocking access to this item/window. Useful for Drag and Drop patterns.
    AllowWhenOverlapped           = 1 << 6,   // Return true even if the position is obstructed or overlapped by another window
    AllowWhenDisabled             = 1 << 7,   // Return true even if the item is disabled
    RectOnly                      = ImGuiHoveredFlags.AllowWhenBlockedByPopup | ImGuiHoveredFlags.AllowWhenBlockedByActiveItem | ImGuiHoveredFlags.AllowWhenOverlapped,
    RootAndChildWindows           = ImGuiHoveredFlags.RootWindow | ImGuiHoveredFlags.ChildWindows
}

// Enumeration for imgui_set_window_*, imgui_set_next_window_*, imgui_set_item_* functions
// Represent a condition.
// Important: Treat as a regular enum! Do NOT combine multiple values using binary operators! All the functions above treat 0 as a shortcut to ImGuiCond_Always.
enum ImGuiCond
{
    None          = 0,        // No condition (always set the variable), same as _Always
    Always        = 1 << 0,   // No condition (always set the variable)
    Once          = 1 << 1,   // Set the variable once per runtime session (only the first call will succeed)
    FirstUseEver  = 1 << 2,   // Set the variable if the object/window has no persistently saved data (no entry in .ini file)
    Appearing     = 1 << 3    // Set the variable if the object/window is appearing after being hidden/inactive (or the first time)
}

// Enumeration for PushStyleColor() / PopStyleColor()
enum ImGuiCol
{
    Text,
    TextDisabled,
    WindowBg,              // Background of normal windows
    ChildBg,               // Background of child windows
    PopupBg,               // Background of popups, menus, tooltips windows
    Border,
    BorderShadow,
    FrameBg,               // Background of checkbox, radio button, plot, slider, text input
    FrameBgHovered,
    FrameBgActive,
    TitleBg,
    TitleBgActive,
    TitleBgCollapsed,
    MenuBarBg,
    ScrollbarBg,
    ScrollbarGrab,
    ScrollbarGrabHovered,
    ScrollbarGrabActive,
    CheckMark,
    SliderGrab,
    SliderGrabActive,
    Button,
    ButtonHovered,
    ButtonActive,
    Header,                // Header* colors are used for CollapsingHeader, TreeNode, Selectable, MenuItem
    HeaderHovered,
    HeaderActive,
    Separator,
    SeparatorHovered,
    SeparatorActive,
    ResizeGrip,
    ResizeGripHovered,
    ResizeGripActive,
    Tab,
    TabHovered,
    TabActive,
    TabUnfocused,
    TabUnfocusedActive,
    DockingPreview,        // Preview overlay color when about to docking something
    DockingEmptyBg,        // Background color for empty node (e.g. CentralNode with no window docked into it)
    PlotLines,
    PlotLinesHovered,
    PlotHistogram,
    PlotHistogramHovered,
    TextSelectedBg,
    DragDropTarget,
    NavHighlight,          // Gamepad/keyboard: current highlighted item
    NavWindowingHighlight, // Highlight window when using CTRL+TAB
    NavWindowingDimBg,     // Darken/colorize entire screen behind the CTRL+TAB window list, when active
    ModalWindowDimBg,      // Darken/colorize entire screen behind a modal window, when one is active
    COUNT
}

// Flags for DragFloat(), DragInt(), SliderFloat(), SliderInt() etc.
enum ImGuiSliderFlags
{
    None                   = 0,
    ClampOnInput           = 1 << 4,       // Clamp value to min/max bounds when input manually with CTRL+Click. By default CTRL+Click allows going out of bounds.
    Logarithmic            = 1 << 5,       // Make the widget logarithmic (linear otherwise). Consider using NoRoundToFormat with this if using a format-string with small amount of digits.
    NoRoundToFormat        = 1 << 6,       // Disable rounding underlying value to match precision of the display format string (e.g. %.3f values are rounded to those 3 digits)
    NoInput                = 1 << 7,       // Disable CTRL+Click or Enter key allowing to input text directly into the widget
    InvalidMask_           = 0x7000000F    // [Internal] We treat using those bits as being potentially a 'float power' argument from the previous API that has got miscast to this enum, and will trigger an assert if needed.
}