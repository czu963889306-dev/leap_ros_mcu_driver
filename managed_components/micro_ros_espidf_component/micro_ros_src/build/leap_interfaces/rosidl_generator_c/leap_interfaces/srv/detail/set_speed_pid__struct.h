// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from leap_interfaces:srv/SetSpeedPid.idl
// generated code does not contain a copyright notice

#ifndef LEAP_INTERFACES__SRV__DETAIL__SET_SPEED_PID__STRUCT_H_
#define LEAP_INTERFACES__SRV__DETAIL__SET_SPEED_PID__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/SetSpeedPid in the package leap_interfaces.
typedef struct leap_interfaces__srv__SetSpeedPid_Request
{
  float kp;
  float ki;
  float kd;
} leap_interfaces__srv__SetSpeedPid_Request;

// Struct for a sequence of leap_interfaces__srv__SetSpeedPid_Request.
typedef struct leap_interfaces__srv__SetSpeedPid_Request__Sequence
{
  leap_interfaces__srv__SetSpeedPid_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} leap_interfaces__srv__SetSpeedPid_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/SetSpeedPid in the package leap_interfaces.
typedef struct leap_interfaces__srv__SetSpeedPid_Response
{
  bool success;
  float kp;
  float ki;
  float kd;
} leap_interfaces__srv__SetSpeedPid_Response;

// Struct for a sequence of leap_interfaces__srv__SetSpeedPid_Response.
typedef struct leap_interfaces__srv__SetSpeedPid_Response__Sequence
{
  leap_interfaces__srv__SetSpeedPid_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} leap_interfaces__srv__SetSpeedPid_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // LEAP_INTERFACES__SRV__DETAIL__SET_SPEED_PID__STRUCT_H_
