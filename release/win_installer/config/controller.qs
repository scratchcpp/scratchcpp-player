function Controller() {
    installer.setMessageBoxAutomaticAnswer("installationErrorWithRetry", QMessageBox.Ignore);
    installer.setMessageBoxAutomaticAnswer("installationError", QMessageBox.Ignore);
}

Controller.prototype.IntroductionPageCallback = function() {
    if(installer.isUpdater())
        gui.clickButton(buttons.NextButton);
}

Controller.prototype.ComponentSelectionPageCallback = function() {
    if(installer.isUpdater())
        gui.clickButton(buttons.NextButton);
}

Controller.prototype.ReadyForInstallationPageCallback = function() {
    if(installer.isUpdater()) {
        gui.clickButton(buttons.NextButton);
        installer.setDefaultPageVisible(QInstaller.Introduction, false);
        installer.setDefaultPageVisible(QInstaller.TargetDirectory, false);
        installer.setDefaultPageVisible(QInstaller.ReadyForInstallation, false);
        installer.setDefaultPageVisible(QInstaller.ComponentSelection, false);
        installer.setDefaultPageVisible(QInstaller.StartMenuSelection, false);
        installer.setDefaultPageVisible(QInstaller.LicenseCheck, false);
    }
}

Controller.prototype.FinishedPageCallback = function() {
    if(installer.isUpdater()) {
        var execName = installer.value("updateSource");
        if(execName != "") {
            installer.executeDetached(execName);
            gui.clickButton(buttons.FinishButton);
            gui.clickButton(buttons.QuitButton);
        }
    }
}
