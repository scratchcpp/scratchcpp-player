// SPDX-License-Identifier: GPL-3.0-or-later

#include "app.h"
#include "uicomponents/uicomponentsmodule.h"
#include "keyboard/keyboardmodule.h"

using namespace scratchcpp;

int main(int argc, char *argv[])
{
    App app;
    app.addModule(new uicomponents::UiComponentsModule);
    app.addModule(new keyboard::KeyboardModule);

    return app.run(argc, argv);
}
