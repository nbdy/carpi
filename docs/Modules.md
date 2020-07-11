## Modules
Module creation is quiet simple.<br>
Just not as simple as I'd like to have it (eyeing at python).<br>
We don't really have reflection. There'd be an option to [implement it](https://stackoverflow.com/a/11748131), but it does not seem suitable.
<br>

Use 'modules/SystemInfo' as a reference.<br>
You also need to register your module in the constructor of 'libs/ModuleMaster/ModuleMaster.cpp'.<br>
Since SystemInfo is already registered you'll understand how to once you look at the constructor.<br>