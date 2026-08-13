// Copyright 2015 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef AMENT_INDEX_CPP__VERSION_H_
#define AMENT_INDEX_CPP__VERSION_H_

/// \def AMENT_INDEX_CPP_VERSION_MAJOR
/// Defines AMENT_INDEX_CPP major version number
#define AMENT_INDEX_CPP_VERSION_MAJOR (1)

/// \def AMENT_INDEX_CPP_VERSION_MINOR
/// Defines AMENT_INDEX_CPP minor version number
#define AMENT_INDEX_CPP_VERSION_MINOR (4)

/// \def AMENT_INDEX_CPP_VERSION_PATCH
/// Defines AMENT_INDEX_CPP version patch number
#define AMENT_INDEX_CPP_VERSION_PATCH (1)

/// \def AMENT_INDEX_CPP_VERSION_STR
/// Defines AMENT_INDEX_CPP version string
#define AMENT_INDEX_CPP_VERSION_STR "1.4.1"

/// \def AMENT_INDEX_CPP_VERSION_GTE
/// Defines a macro to check whether the version of AMENT_INDEX_CPP is greater than or equal to
/// the given version triple.
#define AMENT_INDEX_CPP_VERSION_GTE(major, minor, patch) ( \
     (major < AMENT_INDEX_CPP_VERSION_MAJOR) ? true \
     : (major > AMENT_INDEX_CPP_VERSION_MAJOR) ? false \
     : (minor < AMENT_INDEX_CPP_VERSION_MINOR) ? true \
     : (minor > AMENT_INDEX_CPP_VERSION_MINOR) ? false \
     : (patch < AMENT_INDEX_CPP_VERSION_PATCH) ? true \
     : (patch > AMENT_INDEX_CPP_VERSION_PATCH) ? false \
     : true)

#endif  // AMENT_INDEX_CPP__VERSION_H_
