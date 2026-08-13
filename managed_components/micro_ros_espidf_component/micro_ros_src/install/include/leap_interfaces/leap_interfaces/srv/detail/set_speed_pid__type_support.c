// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from leap_interfaces:srv/SetSpeedPid.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "leap_interfaces/srv/detail/set_speed_pid__rosidl_typesupport_introspection_c.h"
#include "leap_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "leap_interfaces/srv/detail/set_speed_pid__functions.h"
#include "leap_interfaces/srv/detail/set_speed_pid__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void leap_interfaces__srv__SetSpeedPid_Request__rosidl_typesupport_introspection_c__SetSpeedPid_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  leap_interfaces__srv__SetSpeedPid_Request__init(message_memory);
}

void leap_interfaces__srv__SetSpeedPid_Request__rosidl_typesupport_introspection_c__SetSpeedPid_Request_fini_function(void * message_memory)
{
  leap_interfaces__srv__SetSpeedPid_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember leap_interfaces__srv__SetSpeedPid_Request__rosidl_typesupport_introspection_c__SetSpeedPid_Request_message_member_array[3] = {
  {
    "kp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(leap_interfaces__srv__SetSpeedPid_Request, kp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "ki",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(leap_interfaces__srv__SetSpeedPid_Request, ki),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "kd",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(leap_interfaces__srv__SetSpeedPid_Request, kd),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers leap_interfaces__srv__SetSpeedPid_Request__rosidl_typesupport_introspection_c__SetSpeedPid_Request_message_members = {
  "leap_interfaces__srv",  // message namespace
  "SetSpeedPid_Request",  // message name
  3,  // number of fields
  sizeof(leap_interfaces__srv__SetSpeedPid_Request),
  leap_interfaces__srv__SetSpeedPid_Request__rosidl_typesupport_introspection_c__SetSpeedPid_Request_message_member_array,  // message members
  leap_interfaces__srv__SetSpeedPid_Request__rosidl_typesupport_introspection_c__SetSpeedPid_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  leap_interfaces__srv__SetSpeedPid_Request__rosidl_typesupport_introspection_c__SetSpeedPid_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t leap_interfaces__srv__SetSpeedPid_Request__rosidl_typesupport_introspection_c__SetSpeedPid_Request_message_type_support_handle = {
  0,
  &leap_interfaces__srv__SetSpeedPid_Request__rosidl_typesupport_introspection_c__SetSpeedPid_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_leap_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, leap_interfaces, srv, SetSpeedPid_Request)() {
  if (!leap_interfaces__srv__SetSpeedPid_Request__rosidl_typesupport_introspection_c__SetSpeedPid_Request_message_type_support_handle.typesupport_identifier) {
    leap_interfaces__srv__SetSpeedPid_Request__rosidl_typesupport_introspection_c__SetSpeedPid_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &leap_interfaces__srv__SetSpeedPid_Request__rosidl_typesupport_introspection_c__SetSpeedPid_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "leap_interfaces/srv/detail/set_speed_pid__rosidl_typesupport_introspection_c.h"
// already included above
// #include "leap_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "leap_interfaces/srv/detail/set_speed_pid__functions.h"
// already included above
// #include "leap_interfaces/srv/detail/set_speed_pid__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void leap_interfaces__srv__SetSpeedPid_Response__rosidl_typesupport_introspection_c__SetSpeedPid_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  leap_interfaces__srv__SetSpeedPid_Response__init(message_memory);
}

void leap_interfaces__srv__SetSpeedPid_Response__rosidl_typesupport_introspection_c__SetSpeedPid_Response_fini_function(void * message_memory)
{
  leap_interfaces__srv__SetSpeedPid_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember leap_interfaces__srv__SetSpeedPid_Response__rosidl_typesupport_introspection_c__SetSpeedPid_Response_message_member_array[4] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(leap_interfaces__srv__SetSpeedPid_Response, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "kp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(leap_interfaces__srv__SetSpeedPid_Response, kp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "ki",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(leap_interfaces__srv__SetSpeedPid_Response, ki),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "kd",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(leap_interfaces__srv__SetSpeedPid_Response, kd),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers leap_interfaces__srv__SetSpeedPid_Response__rosidl_typesupport_introspection_c__SetSpeedPid_Response_message_members = {
  "leap_interfaces__srv",  // message namespace
  "SetSpeedPid_Response",  // message name
  4,  // number of fields
  sizeof(leap_interfaces__srv__SetSpeedPid_Response),
  leap_interfaces__srv__SetSpeedPid_Response__rosidl_typesupport_introspection_c__SetSpeedPid_Response_message_member_array,  // message members
  leap_interfaces__srv__SetSpeedPid_Response__rosidl_typesupport_introspection_c__SetSpeedPid_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  leap_interfaces__srv__SetSpeedPid_Response__rosidl_typesupport_introspection_c__SetSpeedPid_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t leap_interfaces__srv__SetSpeedPid_Response__rosidl_typesupport_introspection_c__SetSpeedPid_Response_message_type_support_handle = {
  0,
  &leap_interfaces__srv__SetSpeedPid_Response__rosidl_typesupport_introspection_c__SetSpeedPid_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_leap_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, leap_interfaces, srv, SetSpeedPid_Response)() {
  if (!leap_interfaces__srv__SetSpeedPid_Response__rosidl_typesupport_introspection_c__SetSpeedPid_Response_message_type_support_handle.typesupport_identifier) {
    leap_interfaces__srv__SetSpeedPid_Response__rosidl_typesupport_introspection_c__SetSpeedPid_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &leap_interfaces__srv__SetSpeedPid_Response__rosidl_typesupport_introspection_c__SetSpeedPid_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "leap_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "leap_interfaces/srv/detail/set_speed_pid__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers leap_interfaces__srv__detail__set_speed_pid__rosidl_typesupport_introspection_c__SetSpeedPid_service_members = {
  "leap_interfaces__srv",  // service namespace
  "SetSpeedPid",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // leap_interfaces__srv__detail__set_speed_pid__rosidl_typesupport_introspection_c__SetSpeedPid_Request_message_type_support_handle,
  NULL  // response message
  // leap_interfaces__srv__detail__set_speed_pid__rosidl_typesupport_introspection_c__SetSpeedPid_Response_message_type_support_handle
};

static rosidl_service_type_support_t leap_interfaces__srv__detail__set_speed_pid__rosidl_typesupport_introspection_c__SetSpeedPid_service_type_support_handle = {
  0,
  &leap_interfaces__srv__detail__set_speed_pid__rosidl_typesupport_introspection_c__SetSpeedPid_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, leap_interfaces, srv, SetSpeedPid_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, leap_interfaces, srv, SetSpeedPid_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_leap_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, leap_interfaces, srv, SetSpeedPid)() {
  if (!leap_interfaces__srv__detail__set_speed_pid__rosidl_typesupport_introspection_c__SetSpeedPid_service_type_support_handle.typesupport_identifier) {
    leap_interfaces__srv__detail__set_speed_pid__rosidl_typesupport_introspection_c__SetSpeedPid_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)leap_interfaces__srv__detail__set_speed_pid__rosidl_typesupport_introspection_c__SetSpeedPid_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, leap_interfaces, srv, SetSpeedPid_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, leap_interfaces, srv, SetSpeedPid_Response)()->data;
  }

  return &leap_interfaces__srv__detail__set_speed_pid__rosidl_typesupport_introspection_c__SetSpeedPid_service_type_support_handle;
}
