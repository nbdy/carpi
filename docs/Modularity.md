## Modularity
Compiled modules will be installed under '/usr/local/lib/carpi/'<br>
So you need to delete them manually if you don't want to have them loaded<br>
There will be the possibility to enable/disable them via a settings tab<br>
<br>
If your modules depend on other modules, you can load them via ModuleLoader::load({moduleNMame}).<br>
Then you can call 
- ModuleLoader::executeReturn<{TYPE}>({libPointer}, {functionName})
- ModuleLoader::getName({libPointer}) -> executeReturn<char*>({libPointer}, "getName")
- ModuleLoader::render({libPointer}) -> executeReturn<QWidget*>({libPointer}, "render")