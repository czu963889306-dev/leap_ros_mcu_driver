// generated from rosidl_typesupport_microxrcedds_c/resource/idl__type_support_c.c.em
// with input from geometry_msgs:msg/PolygonInstance.idl
// generated code does not contain a copyright notice
#include "geometry_msgs/msg/detail/polygon_instance__rosidl_typesupport_microxrcedds_c.h"


#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "rosidl_typesupport_microxrcedds_c/identifier.h"
#include "rosidl_typesupport_microxrcedds_c/message_type_support.h"
#include "geometry_msgs/msg/rosidl_typesupport_microxrcedds_c__visibility_control.h"
#include "geometry_msgs/msg/detail/polygon_instance__struct.h"
#include "geometry_msgs/msg/detail/polygon_instance__functions.h"

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

#include "geometry_msgs/msg/detail/polygon__functions.h"  // polygon

// forward declare type support functions
size_t get_serialized_size_geometry_msgs__msg__Polygon(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_geometry_msgs__msg__Polygon(
  bool * full_bounded,
  size_t current_alignment);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, geometry_msgs, msg, Polygon)();


typedef geometry_msgs__msg__PolygonInstance _PolygonInstance__ros_msg_type;

static bool _PolygonInstance__cdr_serialize(
  const void * untyped_ros_message,
  ucdrBuffer * cdr)
{
  (void) untyped_ros_message;
  (void) cdr;

  bool rv = false;

  if (!untyped_ros_message) {
    return false;
  }

  _PolygonInstance__ros_msg_type * ros_message = (_PolygonInstance__ros_msg_type *)(untyped_ros_message);
  (void)ros_message;

  // Member: polygon
  rv = ((const message_type_support_callbacks_t *)(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, geometry_msgs, msg, Polygon
      )()->data))->cdr_serialize(&ros_message->polygon, cdr);
  // Member: id
  rv = ucdr_serialize_int64_t(cdr, ros_message->id);

  return rv;
}

static bool _PolygonInstance__cdr_deserialize(
  ucdrBuffer * cdr,
  void * untyped_ros_message)
{
  (void) cdr;

  bool rv = false;

  if (!untyped_ros_message) {
    return false;
  }
  _PolygonInstance__ros_msg_type * ros_message = (_PolygonInstance__ros_msg_type *)(untyped_ros_message);
  (void)ros_message;

  // Field name: polygon
  rv = ((const message_type_support_callbacks_t *)(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, geometry_msgs, msg, Polygon
      )()->data))->cdr_deserialize(cdr, &ros_message->polygon);
  // Field name: id
  rv = ucdr_deserialize_int64_t(cdr, &ros_message->id);
  return rv;
}

ROSIDL_TYPESUPPORT_MICROXRCEDDS_C_PUBLIC_geometry_msgs
size_t get_serialized_size_geometry_msgs__msg__PolygonInstance(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  if (!untyped_ros_message) {
    return 0;
  }

  const _PolygonInstance__ros_msg_type * ros_message = (const _PolygonInstance__ros_msg_type *)(untyped_ros_message);
  (void)ros_message;

  const size_t initial_alignment = current_alignment;

  // Member: polygon
  current_alignment +=
    get_serialized_size_geometry_msgs__msg__Polygon(&ros_message->polygon, current_alignment);
  // Member: id
  {
    const size_t item_size = sizeof(ros_message->id);
    current_alignment += ucdr_alignment(current_alignment, item_size) + item_size;
  }

  return current_alignment - initial_alignment;
}

static uint32_t _PolygonInstance__get_serialized_size(const void * untyped_ros_message)
{
  return (uint32_t)(
    get_serialized_size_geometry_msgs__msg__PolygonInstance(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_MICROXRCEDDS_C_PUBLIC_geometry_msgs
size_t max_serialized_size_geometry_msgs__msg__PolygonInstance(
  bool * full_bounded,
  size_t current_alignment)
{
  (void) current_alignment;
  *full_bounded = true;

  const size_t initial_alignment = current_alignment;

  // Member: polygon
  current_alignment +=
    max_serialized_size_geometry_msgs__msg__Polygon(full_bounded, current_alignment);
  // Member: id
  current_alignment += ucdr_alignment(current_alignment, sizeof(int64_t)) + sizeof(int64_t);

  return current_alignment - initial_alignment;
}

static size_t _PolygonInstance__max_serialized_size()
{
  bool full_bounded;
  return max_serialized_size_geometry_msgs__msg__PolygonInstance(&full_bounded, 0);
}

static message_type_support_callbacks_t __callbacks_PolygonInstance = {
  "geometry_msgs::msg",
  "PolygonInstance",
  _PolygonInstance__cdr_serialize,
  _PolygonInstance__cdr_deserialize,
  _PolygonInstance__get_serialized_size,
  get_serialized_size_geometry_msgs__msg__PolygonInstance,
  _PolygonInstance__max_serialized_size
};

static rosidl_message_type_support_t _PolygonInstance__type_support = {
  ROSIDL_TYPESUPPORT_MICROXRCEDDS_C__IDENTIFIER_VALUE,
  &__callbacks_PolygonInstance,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, geometry_msgs, msg, PolygonInstance)() {
  return &_PolygonInstance__type_support;
}

#if defined(__cplusplus)
}
#endif
