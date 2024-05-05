//https://s9.gifyu.com/images/SVJCx.png https://s12.gifyu.com/images/SVJC6.png
int __fastcall hooks::handles::html_panel_paint(void* html_panel)
{
    static std::once_flag once;
    std::call_once(once, [&]() 
    {     
        globals::menu_panel = html_panel;

        const char* script = xorstr(R"(
        UpdateNewsList(
            [           
                {
                    "Title":"visuals update",
                    "ShortName":"nixware-may-update",
                    "Tags":"Update",
                    "Date":"2024-03-13T04:00:00",
                    "Url":"https://github.com/pa1n-dev/nixware_x64/releases",
                    "SummaryHtml":"add more visuals & mcore support",
                    "HeaderImage":"https://s12.gifyu.com/images/Sa7w5.gif"
                },
                {
                    "Title":"backtrack update",
                    "ShortName":"nixware-march-update",
                    "Tags":"Update",
                    "Date":"2024-03-01T12:00:00",
                    "Url":"https://github.com/pa1n-dev/nixware_x64",
                    "SummaryHtml":"add backtrack without fake ping",
                    "HeaderImage":"https://s9.gifyu.com/images/SVR6S.gif"
                },
                {
                    "Title":"nixware x64",
                    "ShortName":"nixware-update",
                    "Tags":"Update",
                    "Date":"2024-01-04T12:00:00",
                    "Url":"https://www.youtube.com/watch?v=dQw4w9WgXcQ",
                    "SummaryHtml":"updated to x64 chromium",
                    "HeaderImage":"https://s12.gifyu.com/images/SVR6b.gif"
                }
            ], false); 
        )");

        const char* background_script = xorstr(R"(
        function UpdateBackground() { 
            $('body').css({ 
                'background-image': scope.InGame ? 'none' : 'url("http://somestuff.tech.xsph.ru/img/kami.gif")', 
                'background-size': scope.InGame ? 'auto' : 'cover', 
                'background-repeat': scope.InGame ? 'repeat' : 'no-repeat' 
            }); 
        } 
        setInterval(UpdateBackground, 1);
        )");

        utilities::run_javascript(html_panel, script);
        //utilities::run_javascript(html_panel, background_script);
    });

    return originals::html_panel_paint(html_panel);
}