import 'dart:async';
import 'dart:io';

import 'package:fidl_fuchsia_services_examples/fidl_async.dart';
import 'package:fidl_fuchsia_sys/fidl_async.dart';
import 'package:fuchsia/fuchsia.dart' show exit;
import 'package:fuchsia_logger/logger.dart';
import 'package:fuchsia_services/services.dart';

import 'src/_resource_monitor_receiver.dart';

//todo I am assuming that we are going to just launch the server from the client to simplify the program

const resourceMonServerURL = ""


void main(List<String> args) {
  setupLogger(name: 'resource_monitor_client');
  // String test = stdin.readLineSync();

  _run().then((_) => _shutdown());
}

Future<void> _run() async {
  final context = StartupContext.fromStartupInfo();
  ServiceList serviceList;

  final resourceMonClient = ResourceMonitorRecieverImp();

  final incoming = Incoming();
  ServiceList serviceList = _makeServiceList(ResourceMonitorRecieverImp resourceMonClient)

  final launchInfo = LaunchInfo(
    url: resourceMonServerURL,
    additionalServices: serviceList,
  );

  final launcherProxy = LauncherProxy();
  context.incoming.connectToService(launcherProxy);


  await launcherProxy.createComponent(
    launchInfo, ComponentControllerProxy().ctrl.request());

  final resourceMonServer = resourceMonServerProxy();

  incoming.connectToService(resourceMonServer);

  await incoming.close();

  final resposne = await resourceMonServer.collectResources();
  log.info("Recieved response " + resposne + ".");
}


ServiceList _makeServiceList(ResourceMonitorRecieverImp resourceMonitorRecieverImp){

  final provider = ServiceProviderImpl()..addServiceForName(resourceMonitorRecieverImp.bind, ResourceMonitorRecieverImp.serviceName);
  final serviceProviderBinding = ServiceProviderBinding();
  final serviceList = ServiceList (
    names: [ResourceMonitor.$serviceName],
    provider: serviceProviderBinding.wrap(provider)
  );
  return serviceList;
}

void _shutdown(){
  Future(() => exit(0));
}