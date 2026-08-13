// generated from rosidl_typesupport_microxrcedds_c/resource/idl__type_support_c.c.em
// with input from rosgraph_msgs:msg/QoSProfile.idl
// generated code does not contain a copyright notice
#include "rosgraph_msgs/msg/detail/qo_s_profile__rosidl_typesupport_microxrcedds_c.h"


#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "rosidl_typesupport_microxrcedds_c/identifier.h"
#include "rosidl_typesupport_microxrcedds_c/message_type_support.h"
#include "rosgraph_msgs/msg/rosidl_typesupport_microxrcedds_c__visibility_control.h"
#include "rosgraph_msgs/msg/detail/qo_s_profile__struct.h"
#include "rosgraph_msgs/msg/detail/qo_s_profile__functions.h"

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

#include "builtin_interfaces/msg/detail/duration__functions.h"  // deadline, lifespan, liveliness_lease_duration

// forward declare type support functions
ROSIDL_TYPESUPPORT_MICROXRCEDDS_C_IMPORT_rosgraph_msgs
size_t get_serialized_size_builtin_interfaces__msg__Duration(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_MICROXRCEDDS_C_IMPORT_rosgraph_msgs
size_t max_serialized_size_builtin_interfaces__msg__Duration(
  bool * full_bounded,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_MICROXRCEDDS_C_IMPORT_rosgraph_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, builtin_interfaces, msg, Duration)();


typedef rosgraph_msgs__msg__QoSProfile _QoSProfile__ros_msg_type;

static bool _QoSProfile__cdr_serialize(
  const void * untyped_ros_message,
  ucdrBuffer * cdr)
{
  (void) untyped_ros_message;
  (void) cdr;

  bool rv = false;

  if (!untyped_ros_message) {
    return false;
  }

  _QoSProfile__ros_msg_type * ros_message = (_QoSProfile__ros_msg_type *)(untyped_ros_message);
  (void)ros_message;

  // Member: depth
  rv = ucdr_serialize_uint32_t(cdr, ros_message->depth);
  // Member: deadline
  rv = ((const message_type_support_callbacks_t *)(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, builtin_interfaces, msg, Duration
      )()->data))->cdr_serialize(&ros_message->deadline, cdr);
  // Member: lifespan
  rv = ((const message_type_support_callbacks_t *)(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, builtin_interfaces, msg, Duration
      )()->data))->cdr_serialize(&ros_message->lifespan, cdr);
  // Member: history
  rv = ucdr_serialize_uint8_t(cdr, ros_message->history);
  // Member: reliability
  rv = ucdr_serialize_uint8_t(cdr, ros_message->reliability);
  // Member: durability
  rv = ucdr_serialize_uint8_t(cdr, ros_message->durability);
  // Member: liveliness
  rv = ucdr_serialize_uint8_t(cdr, ros_message->liveliness);
  // Member: liveliness_lease_duration
  rv = ((const message_type_support_callbacks_t *)(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, builtin_interfaces, msg, Duration
      )()->data))->cdr_serialize(&ros_message->liveliness_lease_duration, cdr);

  return rv;
}

static bool _QoSProfile__cdr_deserialize(
  ucdrBuffer * cdr,
  void * untyped_ros_message)
{
  (void) cdr;

  bool rv = false;

  if (!untyped_ros_message) {
    return false;
  }
  _QoSProfile__ros_msg_type * ros_message = (_QoSProfile__ros_msg_type *)(untyped_ros_message);
  (void)ros_message;

  // Field name: depth
  rv = ucdr_deserialize_uint32_t(cdr, &ros_message->depth);
  // Field name: deadline
  rv = ((const message_type_support_callbacks_t *)(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, builtin_interfaces, msg, Duration
      )()->data))->cdr_deserialize(cdr, &ros_message->deadline);
  // Field name: lifespan
  rv = ((const message_type_support_callbacks_t *)(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, builtin_interfaces, msg, Duration
      )()->data))->cdr_deserialize(cdr, &ros_message->lifespan);
  // Field name: history
  rv = ucdr_deserialize_uint8_t(cdr, &ros_message->history);
  // Field name: reliability
  rv = ucdr_deserialize_uint8_t(cdr, &ros_message->reliability);
  // Field name: durability
  rv = ucdr_deserialize_uint8_t(cdr, &ros_message->durability);
  // Field name: liveliness
  rv = ucdr_deserialize_uint8_t(cdr, &ros_message->liveliness);
  // Field name: liveliness_lease_duration
  rv = ((const message_type_support_callbacks_t *)(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, builtin_interfaces, msg, Duration
      )()->data))->cdr_deserialize(cdr, &ros_message->liveliness_lease_duration);
  return rv;
}

ROSIDL_TYPESUPPORT_MICROXRCEDDS_C_PUBLIC_rosgraph_msgs
size_t get_serialized_size_rosgraph_msgs__msg__QoSProfile(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  if (!untyped_ros_message) {
    return 0;
  }

  const _QoSProfile__ros_msg_type * ros_message = (const _QoSProfile__ros_msg_type *)(untyped_ros_message);
  (void)ros_message;

  const size_t initial_alignment = current_alignment;

  // Member: depth
  {
    const size_t item_size = sizeof(ros_message->depth);
    current_alignment += ucdr_alignment(current_alignment, item_size) + item_size;
  }
  // Member: deadline
  current_alignment +=
    get_serialized_size_builtin_interfaces__msg__Duration(&ros_message->deadline, current_alignment);
  // Member: lifespan
  current_alignment +=
    get_serialized_size_builtin_interfaces__msg__Duration(&ros_message->lifespan, current_alignment);
  // Member: history
  {
    const size_t item_size = sizeof(ros_message->history);
    current_alignment += ucdr_alignment(current_alignment, item_size) + item_size;
  }
  // Member: reliability
  {
    const size_t item_size = sizeof(ros_message->reliability);
    current_alignment += ucdr_alignment(current_alignment, item_size) + item_size;
  }
  // Member: durability
  {
    const size_t item_size = sizeof(ros_message->durability);
    current_alignment += ucdr_alignment(current_alignment, item_size) + item_size;
  }
  // Member: liveliness
  {
    const size_t item_size = sizeof(ros_message->liveliness);
    current_alignment += ucdr_alignment(current_alignment, item_size) + item_size;
  }
  // Member: liveliness_lease_duration
  current_alignment +=
    get_serialized_size_builtin_interfaces__msg__Duration(&ros_message->liveliness_lease_duration, current_alignment);

  return current_alignment - initial_alignment;
}

static uint32_t _QoSProfile__get_serialized_size(const void * untyped_ros_message)
{
  return (uint32_t)(
    get_serialized_size_rosgraph_msgs__msg__QoSProfile(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_MICROXRCEDDS_C_PUBLIC_rosgraph_msgs
size_t max_serialized_size_rosgraph_msgs__msg__QoSProfile(
  bool * full_bounded,
  size_t current_alignment)
{
  (void) current_alignment;
  *full_bounded = true;

  const size_t initial_alignment = current_alignment;

  // Member: depth
  current_alignment += ucdr_alignment(current_alignment, sizeof(uint32_t)) + sizeof(uint32_t);
  // Member: deadline
  current_alignment +=
    max_serialized_size_builtin_interfaces__msg__Duration(full_bounded, current_alignment);
  // Member: lifespan
  current_alignment +=
    max_serialized_size_builtin_interfaces__msg__Duration(full_bounded, current_alignment);
  // Member: history
  current_alignment += ucdr_alignment(current_alignment, sizeof(uint8_t)) + sizeof(uint8_t);
  // Member: reliability
  current_alignment += ucdr_alignment(current_alignment, sizeof(uint8_t)) + sizeof(uint8_t);
  // Member: durability
  current_alignment += ucdr_alignment(current_alignment, sizeof(uint8_t)) + sizeof(uint8_t);
  // Member: liveliness
  current_alignment += ucdr_alignment(current_alignment, sizeof(uint8_t)) + sizeof(uint8_t);
  // Member: liveliness_lease_duration
  current_alignment +=
    max_serialized_size_builtin_interfaces__msg__Duration(full_bounded, current_alignment);

  return current_alignment - initial_alignment;
}

static size_t _QoSProfile__max_serialized_size()
{
  bool full_bounded;
  return max_serialized_size_rosgraph_msgs__msg__QoSProfile(&full_bounded, 0);
}

static message_type_support_callbacks_t __callbacks_QoSProfile = {
  "rosgraph_msgs::msg",
  "QoSProfile",
  _QoSProfile__cdr_serialize,
  _QoSProfile__cdr_deserialize,
  _QoSProfile__get_serialized_size,
  get_serialized_size_rosgraph_msgs__msg__QoSProfile,
  _QoSProfile__max_serialized_size
};

static rosidl_message_type_support_t _QoSProfile__type_support = {
  ROSIDL_TYPESUPPORT_MICROXRCEDDS_C__IDENTIFIER_VALUE,
  &__callbacks_QoSProfile,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, QoSProfile)() {
  return &_QoSProfile__type_support;
}

#if defined(__cplusplus)
}
#endif
