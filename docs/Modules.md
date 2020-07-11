## Modules
Module creation is quiet simple.<br>
Use any Module from ['modules/'](https://github.com/smthnspcl/carpi/tree/qt/modules/) as a reference.<br>
<br>
Or just use the python script 'modules/add.py'.
```shell script
usage: add.py [-h] -n NAME

optional arguments:
  -h, --help            show this help message and exit
  -n NAME, --name NAME  module name

ex.:
./add.py -n WiFi
> module 'WiFi' already exists

./add.py -n Bluetooth
creating directory 'Bluetooth'
creating 'Bluetooth/CMakeLists.txt'
creating 'Bluetooth/Bluetooth.cpp'
creating 'Bluetooth/Bluetooth.h'
creating 'Bluetooth/Bluetooth_global.h'
creating 'Bluetooth/bluetooth.ui'
```
After you created a module, just add it to the root CMakeLists.txt via 'add_submodule(modules/{YOUR_MODULE})'<br>
Then just add your code to your new module.