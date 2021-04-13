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
