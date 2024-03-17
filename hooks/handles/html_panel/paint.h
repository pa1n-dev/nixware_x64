int __fastcall hooks::handles::html_panel_paint(void* html_panel)
{
    static std::once_flag once;
    std::call_once(once, [&]() 
    { 
        using run_javascript_fn = void(*)(void*, const char*);
        static run_javascript_fn run_javascript = (run_javascript_fn)memory::pattern_scanner(xorstr("menusystem.dll"), xorstr("48 8B 89 ? ? ? ? 48 8B 01 48 FF 60 68"));

        run_javascript(html_panel, xorstr("UpdateNewsList([{\"Title\":\"backtrack update\",\"ShortName\":\"nixware-march-update\",\"Tags\":\"Update\",\"Date\":\"2024-03-01T12:00:00\",\"Url\":\"https://github.com/pa1n-dev/nixware_x64\",\"SummaryHtml\":\"add backtrack without fake ping\",\"HeaderImage\":\"https://cdn.discordapp.com/attachments/1194221664339234816/1218902861258166312/news1.gif?ex=66095ac0&is=65f6e5c0&hm=52eb103dd94a59f1e2cb7780056453e8a2d987cdff9ade5ed39f18299d475adf&\"},{\"Title\":\"nixware x64\",\"ShortName\":\"nixware-update\",\"Tags\":\"Update\",\"Date\":\"2024-01-04T12:00:00\",\"Url\":\"https://www.youtube.com/watch?v=dQw4w9WgXcQ\",\"SummaryHtml\":\"updated to x64 chromium\",\"HeaderImage\":\"https://cdn.discordapp.com/attachments/1194221664339234816/1218904227842101288/news2.gif?ex=66095c06&is=65f6e706&hm=717bab81973716760c103da0bf7e565c20a298561322042a1a9bbfe021a27524&\"}], false)"));
        //run_javascript(html_panel, xorstr("function UpdateBackground() { $('body').css({ 'background-image': scope.InGame ? 'none' : 'url(\"http://somestuff.tech.xsph.ru/img/kami.gif\")', 'background-size' : scope.InGame ? 'auto' : 'cover', 'background-repeat' : scope.InGame ? 'repeat' : 'no-repeat' }); } setInterval(UpdateBackground, 1);"));
    });

    return originals::html_panel_paint(html_panel);
}