// generated from rosidl_typesupport_microxrcedds_c/resource/idl__type_support_c.c.em
// with input from leap_interfaces:srv/SetSpeedPid.idl
// generated code does not contain a copyright notice
#include "leap_interfaces/srv/detail/set_speed_pid__rosidl_typesupport_microxrcedds_c.h"


#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "rosidl_typesupport_microxrcedds_c/identifier.h"
#include "rosidl_typesupport_microxrcedds_c/message_type_support.h"
#include "leap_interfaces/msg/rosidl_typesupport_microxrcedds_c__visibility_control.h"
#include "leap_interfaces/srv/detail/set_speed_pid__struct.h"
#include "leap_interfaces/srv/detail/set_speed_pid__functions.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#define MICROXRCEDDS_PADDING sizeof(uint32_t)

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif


// forward declare type support functions


typedef leap_interfaces__srv__SetSpeedPid_Request _SetSpeedPid_Request__ros_msg_type;

static bool _SetSpeedPid_Request__cdr_serialize(
  const void * untyped_ros_message,
  ucdrBuffer * cdr)
{
  (void) untyped_ros_message;
  (void) cdr;

  bool rv = false;

  if (!untyped_ros_message) {
    return false;
  }

  _SetSpeedPid_Request__ros_msg_type * ros_message = (_SetSpeedPid_Request__ros_msg_type *)(untyped_ros_message);
  (void)ros_message;

  // Member: kp
  rv = ucdr_serialize_float(cdr, ros_message->kp);
  // Member: ki
  rv = ucdr_serialize_float(cdr, ros_message->ki);
  // Member: kd
  rv = ucdr_serialize_float(cdr, ros_message->kd);

  return rv;
}

static bool _SetSpeedPid_Request__cdr_deserialize(
  ucdrBuffer * cdr,
  void * untyped_ros_message)
{
  (void) cdr;

  bool rv = false;

  if (!untyped_ros_message) {
    return false;
  }
  _SetSpeedPid_Request__ros_msg_type * ros_message = (_SetSpeedPid_Request__ros_msg_type *)(untyped_ros_message);
  (void)ros_message;

  // Field name: kp
  rv = ucdr_deserialize_float(cdr, &ros_message->kp);
  // Field name: ki
  rv = ucdr_deserialize_float(cdr, &ros_message->ki);
  // Field name: kd
  rv = ucdr_deserialize_float(cdr, &ros_message->kd);
  return rv;
}

ROSIDL_TYPESUPPORT_MICROXRCEDDS_C_PUBLIC_leap_interfaces
size_t get_serialized_size_leap_interfaces__srv__SetSpeedPid_Request(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  if (!untyped_ros_message) {
    return 0;
  }

  const _SetSpeedPid_Request__ros_msg_type * ros_message = (const _SetSpeedPid_Request__ros_msg_type *)(untyped_ros_message);
  (void)ros_message;

  const size_t initial_alignment = current_alignment;

  // Member: kp
  {
    const size_t item_size = sizeof(ros_message->kp);
    current_alignment += ucdr_alignment(current_alignment, item_size) + item_size;
  }
  // Member: ki
  {
    const size_t item_size = sizeof(ros_message->ki);
    current_alignment += ucdr_alignment(current_alignment, item_size) + item_size;
  }
  // Member: kd
  {
    const size_t item_size = sizeof(ros_message->kd);
    current_alignment += ucdr_alignment(current_alignment, item_size) + item_size;
  }

  return current_alignment - initial_alignment;
}

static uint32_t _SetSpeedPid_Request__get_serialized_size(const void * untyped_ros_message)
{
  return (uint32_t)(
    get_serialized_size_leap_interfaces__srv__SetSpeedPid_Request(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_MICROXRCEDDS_C_PUBLIC_leap_interfaces
size_t max_serialized_size_leap_interfaces__srv__SetSpeedPid_Request(
  bool * full_bounded,
  size_t current_alignment)
{
  (void) current_alignment;
  *full_bounded = true;

  const size_t initial_alignment = current_alignment;

  // Member: kp
  current_alignment += ucdr_alignment(current_alignment, sizeof(float)) + sizeof(float);
  // Member: ki
  current_alignment += ucdr_alignment(current_alignment, sizeof(float)) + sizeof(float);
  // Member: kd
  current_alignment += ucdr_alignment(current_alignment, sizeof(float)) + sizeof(float);

  return current_alignment - initial_alignment;
}

static size_t _SetSpeedPid_Request__max_serialized_size()
{
  bool full_bounded;
  return max_serialized_size_leap_interfaces__srv__SetSpeedPid_Request(&full_bounded, 0);
}

static message_type_support_callbacks_t __callbacks_SetSpeedPid_Request = {
  "leap_interfaces::srv",
  "SetSpeedPid_Request",
  _SetSpeedPid_Request__cdr_serialize,
  _SetSpeedPid_Request__cdr_deserialize,
  _SetSpeedPid_Request__get_serialized_size,
  get_serialized_size_leap_interfaces__srv__SetSpeedPid_Request,
  _SetSpeedPid_Request__max_serialized_size
};

static rosidl_message_type_support_t _SetSpeedPid_Request__type_support = {
  ROSIDL_TYPESUPPORT_MICROXRCEDDS_C__IDENTIFIER_VALUE,
  &__callbacks_SetSpeedPid_Request,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, leap_interfaces, srv, SetSpeedPid_Request)() {
  return &_SetSpeedPid_Request__type_support;
}

#if defined(__cplusplus)
}
#endif

// already included above
// #include <stdint.h>
// already included above
// #include <stdio.h>
// already included above
// #include <string.h>
// already included above
// #include "rosidl_typesupport_microxrcedds_c/identifier.h"
// already included above
// #include "rosidl_typesupport_microxrcedds_c/message_type_support.h"
// already included above
// #include "leap_interfaces/msg/rosidl_typesupport_microxrcedds_c__visibility_control.h"
// already included above
// #include "leap_interfaces/srv/detail/set_speed_pid__struct.h"
// already included above
// #include "leap_interfaces/srv/detail/set_speed_pid__functions.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#define MICROXRCEDDS_PADDING sizeof(uint32_t)

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif


// forward declare type support functions


typedef leap_interfaces__srv__SetSpeedPid_Response _SetSpeedPid_Response__ros_msg_type;

static bool _SetSpeedPid_Response__cdr_serialize(
  const void * untyped_ros_message,
  ucdrBuffer * cdr)
{
  (void) untyped_ros_message;
  (void) cdr;

  bool rv = false;

  if (!untyped_ros_message) {
    return false;
  }

  _SetSpeedPid_Response__ros_msg_type * ros_message = (_SetSpeedPid_Response__ros_msg_type *)(untyped_ros_message);
  (void)ros_message;

  // Member: success
  rv = ucdr_serialize_bool(cdr, (ros_message->success) ? 0x01 : 0x00);
  // Member: kp
  rv = ucdr_serialize_float(cdr, ros_message->kp);
  // Member: ki
  rv = ucdr_serialize_float(cdr, ros_message->ki);
  // Member: kd
  rv = ucdr_serialize_float(cdr, ros_message->kd);

  return rv;
}

static bool _SetSpeedPid_Response__cdr_deserialize(
  ucdrBuffer * cdr,
  void * untyped_ros_message)
{
  (void) cdr;

  bool rv = false;

  if (!untyped_ros_message) {
    return false;
  }
  _SetSpeedPid_Response__ros_msg_type * ros_message = (_SetSpeedPid_Response__ros_msg_type *)(untyped_ros_message);
  (void)ros_message;

  // Field name: success
  rv = ucdr_deserialize_bool(cdr, &ros_message->success);
  // Field name: kp
  rv = ucdr_deserialize_float(cdr, &ros_message->kp);
  // Field name: ki
  rv = ucdr_deserialize_float(cdr, &ros_message->ki);
  // Field name: kd
  rv = ucdr_deserialize_float(cdr, &ros_message->kd);
  return rv;
}

ROSIDL_TYPESUPPORT_MICROXRCEDDS_C_PUBLIC_leap_interfaces
size_t get_serialized_size_leap_interfaces__srv__SetSpeedPid_Response(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  if (!untyped_ros_message) {
    return 0;
  }

  const _SetSpeedPid_Response__ros_msg_type * ros_message = (const _SetSpeedPid_Response__ros_msg_type *)(untyped_ros_message);
  (void)ros_message;

  const size_t initial_alignment = current_alignment;

  // Member: success
  {
    const size_t item_size = sizeof(ros_message->success);
    current_alignment += ucdr_alignment(current_alignment, item_size) + item_size;
  }
  // Member: kp
  {
    const size_t item_size = sizeof(ros_message->kp);
    current_alignment += ucdr_alignment(current_alignment, item_size) + item_size;
  }
  // Member: ki
  {
    const size_t item_size = sizeof(ros_message->ki);
    current_alignment += ucdr_alignment(current_alignment, item_size) + item_size;
  }
  // Member: kd
  {
    const size_t item_size = sizeof(ros_message->kd);
    current_alignment += ucdr_alignment(current_alignment, item_size) + item_size;
  }

  return current_alignment - initial_alignment;
}

static uint32_t _SetSpeedPid_Response__get_serialized_size(const void * untyped_ros_message)
{
  return (uint32_t)(
    get_serialized_size_leap_interfaces__srv__SetSpeedPid_Response(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_MICROXRCEDDS_C_PUBLIC_leap_interfaces
size_t max_serialized_size_leap_interfaces__srv__SetSpeedPid_Response(
  bool * full_bounded,
  size_t current_alignment)
{
  (void) current_alignment;
  *full_bounded = true;

  const size_t initial_alignment = current_alignment;

  // Member: success
  current_alignment += ucdr_alignment(current_alignment, sizeof(bool)) + sizeof(bool);
  // Member: kp
  current_alignment += ucdr_alignment(current_alignment, sizeof(float)) + sizeof(float);
  // Member: ki
  current_alignment += ucdr_alignment(current_alignment, sizeof(float)) + sizeof(float);
  // Member: kd
  current_alignment += ucdr_alignment(current_alignment, sizeof(float)) + sizeof(float);

  return current_alignment - initial_alignment;
}

static size_t _SetSpeedPid_Response__max_serialized_size()
{
  bool full_bounded;
  return max_serialized_size_leap_interfaces__srv__SetSpeedPid_Response(&full_bounded, 0);
}

static message_type_support_callbacks_t __callbacks_SetSpeedPid_Response = {
  "leap_interfaces::srv",
  "SetSpeedPid_Response",
  _SetSpeedPid_Response__cdr_serialize,
  _SetSpeedPid_Response__cdr_deserialize,
  _SetSpeedPid_Response__get_serialized_size,
  get_serialized_size_leap_interfaces__srv__SetSpeedPid_Response,
  _SetSpeedPid_Response__max_serialized_size
};

static rosidl_message_type_support_t _SetSpeedPid_Response__type_support = {
  ROSIDL_TYPESUPPORT_MICROXRCEDDS_C__IDENTIFIER_VALUE,
  &__callbacks_SetSpeedPid_Response,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, leap_interfaces, srv, SetSpeedPid_Response)() {
  return &_SetSpeedPid_Response__type_support;
}

#if defined(__cplusplus)
}
#endif

#include "rosidl_typesupport_microxrcedds_c/service_type_support.h"
// already included above
// #include "rosidl_typesupport_microxrcedds_c/identifier.h"
// already included above
// #include "leap_interfaces/msg/rosidl_typesupport_microxrcedds_c__visibility_control.h"
#include "leap_interfaces/srv/set_speed_pid.h"

#if defined(__cplusplus)
extern "C"
{
#endif

static service_type_support_callbacks_t SetSpeedPid__callbacks = {
  "leap_interfaces::srv",
  "SetSpeedPid",
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, leap_interfaces, srv, SetSpeedPid_Request),
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, leap_interfaces, srv, SetSpeedPid_Response),
};

static rosidl_service_type_support_t SetSpeedPid__handle = {
  ROSIDL_TYPESUPPORT_MICROXRCEDDS_C__IDENTIFIER_VALUE,
  &SetSpeedPid__callbacks,
  get_service_typesupport_handle_function,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, leap_interfaces, srv, SetSpeedPid)() {
  return &SetSpeedPid__handle;
}

#if defined(__cplusplus)
}
#endif
