#pragma once

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

    bool check();

private:
    bool toggle_state = false;
};