// SPDX-License-Identifier: GPL-3.0-or-later

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QIcon>
#include <cassert>
#include <scratchcpp-render/scratchcpp-render.h>

#include "app.h"
#include "globalmodule.h"
#include "modularity/ioc.h"
#include "ui/internal/uiengine.h"

#ifdef Q_OS_WINDOWS
#include <QOpenGLWidget>
#endif

using namespace scratchcpp;
using namespace scratchcpp::modularity;

App::App()
{
    addModule(new GlobalModule);
}

int App::run(int argc, char **argv)
{
    // Init scratchcpp-render
    scratchcpprender::init();

    // Set up application object
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationDomain("scratchcpp.github.io");
    QCoreApplication::setOrganizationName("ScratchCPP");
    QCoreApplication::setApplicationName("ScratchCPP Player");
    QCoreApplication::setApplicationVersion(BUILD_VERSION);

#ifdef Q_OS_MACOS
    // Disable native menu bar on macOS
    app.setAttribute(Qt::AA_DontUseNativeMenuBar);
#endif
    // Set style and icon theme name
    QQuickStyle::setStyle("Material");
    QIcon::setThemeName("scratchcpp");

    // Register exports
    for (IModuleSetup *module : m_modules)
        module->registerExports();

    // Init settings
    for (IModuleSetup *module : m_modules)
        module->initSettings();

    // Setup modules: onPreInit
    for (IModuleSetup *module : m_modules)
        module->onPreInit();

    /* Splash screen should show now, if any. */

    // Setup modules: onInit
    for (IModuleSetup *module : m_modules)
        module->onInit();

    // Setup modules: onStartApp (on next event loop)
    QMetaObject::invokeMethod(
        qApp,
        [this]() {
            for (IModuleSetup *m : m_modules) {
                m->onStartApp();
            }
        },
        Qt::QueuedConnection);

    // Load main.qml
    QQmlApplicationEngine engine;
    engine.addImportPath(":/");

    const QUrl url(u"qrc:/ScratchCPP/qml/main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    ui::UiEngine::instance()->setQmlEngine(&engine);

#ifdef Q_OS_WINDOWS
    QOpenGLWidget glWidget; // force dependency on OpenGL widgets
#endif

    // Run the event loop
    int exitCode = app.exec();

    // Deinit modules
    for (IModuleSetup *module : m_modules)
        module->onDeinit();

    for (IModuleSetup *module : m_modules)
        module->onDestroy();

    // Remove all modules
    removeModules();

    return exitCode;
}

void App::addModule(IModuleSetup *module)
{
    assert(module);
    assert(std::find_if(m_modules.begin(), m_modules.end(), [module](IModuleSetup *m) { return m->moduleName() == module->moduleName(); }) == m_modules.end());
    m_modules.push_back(module);
}

void App::removeModules()
{
    for (IModuleSetup *module : m_modules)
        delete module;

    m_modules.clear();
    ioc()->reset();
}
