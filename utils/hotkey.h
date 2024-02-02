#pragma once
#include <winuser.h>

struct hotkey_t
{
    int key;

    enum type
    {
        always_on,
        hold,
        toggle,
        force_disable
    } type = hold;

    inline bool check()
    {
        switch (type)
        {
        case always_on:
            return true;

        case hold:
            return (key != 0 && GetAsyncKeyState(key) & 0x8000);

        case toggle:
        {
            static bool toggle = false;

            if (key != 0 && is_key_pressed(key))
                toggle = !toggle;

            return toggle;
        }

        case force_disable:
            return (key != 0 && !(GetAsyncKeyState(key) & 0x8001));

        }

        return false;
    }

private:
    bool is_key_pressed(int key)
    {
        static bool key_press[256];

        if (GetAsyncKeyState(key) & 0x8000)
        {
            if (!key_press[key])
            {
                key_press[key] = true;
                return true;
            }
        }
        else
            key_press[key] = false;

        return false;
    }
};