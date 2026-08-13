// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from leap_interfaces:srv/GetSpeedPid.idl
// generated code does not contain a copyright notice

#ifndef LEAP_INTERFACES__SRV__DETAIL__GET_SPEED_PID__STRUCT_H_
#define LEAP_INTERFACES__SRV__DETAIL__GET_SPEED_PID__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/GetSpeedPid in the package leap_interfaces.
typedef struct leap_interfaces__srv__GetSpeedPid_Request
{
  uint8_t structure_needs_at_least_one_member;
} leap_interfaces__srv__GetSpeedPid_Request;

// Struct for a sequence of leap_interfaces__srv__GetSpeedPid_Request.
typedef struct leap_interfaces__srv__GetSpeedPid_Request__Sequence
{
  leap_interfaces__srv__GetSpeedPid_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} leap_interfaces__srv__GetSpeedPid_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/GetSpeedPid in the package leap_interfaces.
typedef struct leap_interfaces__srv__GetSpeedPid_Response
{
  bool success;
  float kp;
  float ki;
  float kd;
} leap_interfaces__srv__GetSpeedPid_Response;

// Struct for a sequence of leap_interfaces__srv__GetSpeedPid_Response.
typedef struct leap_interfaces__srv__GetSpeedPid_Response__Sequence
{
  leap_interfaces__srv__GetSpeedPid_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} leap_interfaces__srv__GetSpeedPid_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // LEAP_INTERFACES__SRV__DETAIL__GET_SPEED_PID__STRUCT_H_
