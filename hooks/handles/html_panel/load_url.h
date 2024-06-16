void __fastcall hooks::handles::html_panel_load_url(void* html_panel, const char* url)
{
    if (settings::menu::custom_loading_screen::enable && !strstr(url, xorstr("asset://garrysmod/html/menu.html")))
        url = settings::menu::custom_loading_screen::url;

    originals::html_panel_load_url(html_panel, url);
}