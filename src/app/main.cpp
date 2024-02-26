// SPDX-License-Identifier: GPL-3.0-or-later

#include "app.h"
#include "globalmodule.h"
#include "keyboard/keyboardmodule.h"

using namespace scratchcpp;

int main(int argc, char *argv[])
{
    App app;
    app.addModule(new GlobalModule);
    app.addModule(new keyboard::KeyboardModule);

    return app.run(argc, argv);
}
