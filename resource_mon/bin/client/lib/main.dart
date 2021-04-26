import 'dart:async';

import 'package:fidl_fuchsia_services_examples/fidl_async.dart';
import 'package:fidl_fuchsia_sys/fidl_async.dart';
import 'package:fuchsia/fuchsia.dart' show exit;
import 'package:fuchsia_logger/logger.dart';
import 'package:fuchsia_services/services.dart';

import 'src/_resource_monitor_receiver.dart';

//todo I am assuming that we are going to just launch the server from the client to simplify the program

const resourceMonServerURL =
    'fuchsia-pkg://fuchsia.com/resource-monitor#meta/resource_monitor_server.cmx';

void main(List<String> args) {
  setupLogger(name: 'resource_monitor_client');
  // String test = stdin.readLineSync();
  log.info('LOOK HERE DUMMY');

  _run().then((_) => _shutdown());
}

Future<void> _run() async {
  final context = StartupContext.fromStartupInfo();
  // ServiceList serviceList;

  final resourceMonClient = ResourceMonitorRecieverImp();

  final incoming = Incoming();
  ServiceList serviceList = _makeServiceList(resourceMonClient);

  final launchInfo = LaunchInfo(
    url: resourceMonServerURL,
    directoryRequest: incoming.request().passChannel(),
    additionalServices: serviceList,
  );

  final launcherProxy = LauncherProxy();
  context.incoming.connectToService(launcherProxy);

  await launcherProxy.createComponent(
      launchInfo, ComponentControllerProxy().ctrl.request());

  final resourceMonServer = ResourceMonitorProxy();

  incoming.connectToService(resourceMonServer);

  await incoming.close();

  final day = await resourceMonServer.monitorTime(1);
  final month = await resourceMonServer.monitorTime(2);
  final year = await resourceMonServer.monitorTime(3);
  final hour = await resourceMonServer.monitorTime(4);
  final minute = await resourceMonServer.monitorTime(5);
  final sec = await resourceMonServer.monitorTime(6);
  log
    ..info('Current Date: $month/$day/$year')
    ..info('Current Time: $hour:$minute:$sec');
}

ServiceList _makeServiceList(
    ResourceMonitorRecieverImp resourceMonitorRecieverImp) {
  final provider = ServiceProviderImpl()
    ..addServiceForName(resourceMonitorRecieverImp.bind,
        ResourceMonitorRecieverImp.serviceName);
  final serviceProviderBinding = ServiceProviderBinding();
  final serviceList = ServiceList(
      names: [ResourceMonitor.$serviceName],
      provider: serviceProviderBinding.wrap(provider));
  return serviceList;
}

void _shutdown() {
  Future(() => exit(0));
}
