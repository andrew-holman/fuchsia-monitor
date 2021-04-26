// Copyright 2019 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

import 'package:fuchsia_logger/logger.dart';
import 'package:fuchsia_services/services.dart';

import 'src/_resource_monitor_server_impl.dart';

void main(List<String> args) {
  setupLogger(name: 'resource_monitor_server');

  final resourceMonitor = ResourceMonitorServerImpl();

  // we publish the service in the components /out/public directory.
  // Doing this allows the parent of the process to connect to this service.
  StartupContext.fromStartupInfo().outgoing.addPublicService(
      resourceMonitor.bind, ResourceMonitorServerImpl.serviceName);
}
