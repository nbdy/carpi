# Workflow
0. Application start
   1. Config Loading (no parameters / -c / --config)
   2. Parameter parsing (if any)
1. Create ModuleManager instance
   1. Load all modules from specified config
2. Get drawable Modules into a vector
3. Enter render loop
   1. Check if a new drawable module has been selected
      1. Get pointer of selected module
   2. Call draw function on currently selected module
4. Destroy stuff if needed
5. Exit