// Copyright 2019 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

import 'dart:async';

import 'package:fidl/fidl.dart';
import 'package:fidl_fuchsia_services_examples/fidl_async.dart';

/// The [MindReaderImpl] extends the MindReader class and provides
/// concrete implementations for fidl defined methods.
class ResourceMonitorServerImpl extends ResourceMonitor {
  /// The discoverable name for this service
  static const String serviceName = ResourceMonitor.$serviceName;

  final _binding = ResourceMonitorBinding();

  void bind(InterfaceRequest<ResourceMonitor> request) =>
      _binding.bind(this, request);

  @override
  Future<String> monitorTime(int selectedResource) async {
    final response = retrieveDateTime(selectedResource);

    return response;
  }

  String retrieveDateTime(int selectedResource) {
    if (selectedResource == 1) {
      return DateTime.now().day.toString();
    } else if (selectedResource == 2) {
      return DateTime.now().month.toString();
    } else if (selectedResource == 3) {
      return DateTime.now().year.toString();
    } else if (selectedResource == 4) {
      return DateTime.now().hour.toString();
    } else if (selectedResource == 5) {
      return DateTime.now().minute.toString();
    } else if (selectedResource == 6) {
      return DateTime.now().second.toString();
    } else {
      return 'Invalid Input';
    }
  }
}
