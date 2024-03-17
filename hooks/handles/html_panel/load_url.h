void __fastcall hooks::handles::html_panel_load_url(void* html_panel, const char* url)
{
    if (settings::menu::custom_loading_screen && !strstr(url, xorstr("asset://garrysmod/html/menu.html")))
        url = xorstr("https://pa1n-dev.github.io/nixware/index.html");

    originals::html_panel_load_url(html_panel, url);
}