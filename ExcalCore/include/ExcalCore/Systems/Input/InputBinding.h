//
// Created by arch-excalixy on 3/2/26.
//

#pragma once

#include "KeyCode.h"

struct InputBindingCore {
    virtual ~InputBindingCore() = default;
};

struct InputBindingButton : InputBindingCore {
    explicit InputBindingButton(KeyCode key)
        : key(key) {}

    KeyCode key;
};

struct InputBindingAxis : InputBindingCore {
    explicit InputBindingAxis(KeyCode positive, KeyCode negative)
        : positive(positive), negative(negative) {}

    KeyCode positive;
    KeyCode negative;
};

struct InputBinding2D : InputBindingCore {
    explicit InputBinding2D(KeyCode up, KeyCode down, KeyCode left, KeyCode right)
        : up(up), down(down), left(left), right(right) {}

    KeyCode up;
    KeyCode down;
    KeyCode left;
    KeyCode right;
};

struct InputBinding3D : InputBindingCore {
    explicit InputBinding3D(KeyCode up, KeyCode down, KeyCode left, KeyCode right, KeyCode front, KeyCode back)
        : up(up), down(down), left(left), right(right), front(front), back(back) {}

    KeyCode up;
    KeyCode down;
    KeyCode left;
    KeyCode right;
    KeyCode front;
    KeyCode back;
};
