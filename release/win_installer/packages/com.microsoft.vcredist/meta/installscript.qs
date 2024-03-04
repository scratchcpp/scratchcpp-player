function Component(){}

Component.prototype.createOperations = function()
{
	try {
		component.createOperations();
		if (installer.value("os") === "win") {
			component.addElevatedOperation("Execute", "{0,1638}", "@TargetDir@/VC_redist.x64.exe", "/norestart", "/quiet");
		}
	} catch (e) {
		print(e);
	}
}
