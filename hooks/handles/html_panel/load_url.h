void __fastcall hooks::handles::html_panel_load_url(void* html_panel, const char* url)
{
    if (!strstr(url, xorstr("asset://garrysmod/html/menu.html")))
        url = xorstr("http://somestuff.tech.xsph.ru/");

    originals::html_panel_load_url(html_panel, url);
}