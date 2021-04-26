# fuchsia-monitor 
In this project we will create a simple system monitoring application in Google Fuchsia.

## How to setup project
- Clone git project into /fuchsia/examples and name the folder "fuchsia_monitor"
- Include component when setting up configuration with "fx set core.qemu-x64 --with //examples/fuchsia_monitor"
- Run fx build
- Serve project with "fx serve-updates"
- In another terminal run either frontend or backend with:
	- "fx shell run fuchsia-pkg://fuchsia.com/fuchsia-monitor-frontend-cpp#meta/fuchsia-monitor-frontend-cpp.cmx"
	- "fx shell run fuchsia-pkg://fuchsia.com/fuchsia-monitor-backend-cpp#meta/fuchsia-monitor-backend-cpp.cmx"



## How to run the resource_mon directory
- clone the git project
- copy folder "resource_mon" to some fuchsia directory (topaz/examples)
- include the package witht the fx set command (fx set workstation.x64 --with //bundles:kitchen_sink,//topaz/examples/resource_mon/bin:resource-monitor
)
- build Fuchisa via the fx build command
- run the emulator by running fx vdl start -N
- open a new terminal and view the fuchisa logs (fx log)
- run the client by serving the fx shell and running fx shell run "fuchsia-pkg://fuchsia.com/resource-monitor#meta/resource_monitor_client.cmx"
