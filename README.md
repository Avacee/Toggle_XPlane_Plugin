# Toggle_XPlane_Plugin
X-Plane Plugin to Enable/Disable a specified plugin using XPLMCommands

### Build Instructions:
- Change the values in XPluginStart() to something more appropriate.
- Change the signature of the plugin you are wish to enable/disable in DoToggleSkyscapes()
- Create the following enviroment variables (Case sensitive on unix) <br>
  - **XPLANESDK**=The XPlane SDK base folder. Download the SDK from: [X-Plane SDK](https://developer.x-plane.com/sdk/plugin-sdk-downloads/) <br>
  - **XPLANEDIR**=The folder containing x-plane.exe. This will place the debug XPL in the plugin sub folder for debugging.

### Usage
Place the ToggleSkyscapes.xpl in the following folder: 
- Linux: ${XPLANEDIR}/Resources/plugins/ToggleSkyscapes/lin_x64
- Windows: ${XPLANEDIR}/Resources/plugins/ToggleSkyscapes/win_x64
- Mac: ${XPLANEDIR}/Resources/plugins/ToggleSkyscapes/mac_x64

This plugin will create a command within X-Plane that can be bound with a keyboard or joystick button.
