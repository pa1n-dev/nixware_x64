int __fastcall hooks::handles::html_panel_paint(void* rcx)
{
    static std::once_flag flag;
    std::call_once(flag, [&]() 
    { 
        using run_javascript_t = void(*)(void*, const char*);
        run_javascript_t run_javascript = reinterpret_cast<run_javascript_t>(memory::pattern_scanner(xorstr("menusystem.dll"), xorstr("48 8B 89 ? ? ? ? 48 8B 01 48 FF 60 68")));

        run_javascript(rcx, xorstr("UpdateNewsList([{\"Title\":\"nixware x64\",\"ShortName\":\"mya-update\",\"Tags\":\"Update\",\"Date\":\"2024-01-04T08:16:00\",\"Url\":\"https://www.youtube.com/watch?v=dQw4w9WgXcQ\",\"SummaryHtml\":\"updated to x64 chromium\",\"HeaderImage\":\"http://somestuff.tech.xsph.ru/img/lenin_mini.png\"}], false)"));
        run_javascript(rcx, xorstr("function UpdateBackground() { $('body').css({ 'background-image': scope.InGame ? 'none' : 'url(\"http://somestuff.tech.xsph.ru/img/kami.gif\")', 'background-size' : scope.InGame ? 'auto' : 'cover', 'background-repeat' : scope.InGame ? 'repeat' : 'no-repeat' }); } setInterval(UpdateBackground, 1);"));
    });


    return originals::html_panel_paint(rcx);
}