void __fastcall hooks::handles::html_panel_load_url(void* rcx, const char* url)
{
    if (!strstr(url, xorstr("asset://garrysmod/html/menu.html")))
        url = xorstr("http://somestuff.tech.xsph.ru/");

    originals::html_panel_load_url(rcx, url);
}