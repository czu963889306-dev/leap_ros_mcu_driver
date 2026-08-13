// generated from rosidl_typesupport_microxrcedds_c/resource/idl__type_support_c.c.em
// with input from rosgraph_msgs:msg/Topic.idl
// generated code does not contain a copyright notice
#include "rosgraph_msgs/msg/detail/topic__rosidl_typesupport_microxrcedds_c.h"


#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "rosidl_typesupport_microxrcedds_c/identifier.h"
#include "rosidl_typesupport_microxrcedds_c/message_type_support.h"
#include "rosgraph_msgs/msg/rosidl_typesupport_microxrcedds_c__visibility_control.h"
#include "rosgraph_msgs/msg/detail/topic__struct.h"
#include "rosgraph_msgs/msg/detail/topic__functions.h"

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

#include "rosgraph_msgs/msg/detail/interface_type__functions.h"  // type
#include "rosgraph_msgs/msg/detail/qo_s_profile__functions.h"  // qos
#include "rosidl_runtime_c/string.h"  // name
#include "rosidl_runtime_c/string_functions.h"  // name

// forward declare type support functions
size_t get_serialized_size_rosgraph_msgs__msg__InterfaceType(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_rosgraph_msgs__msg__InterfaceType(
  bool * full_bounded,
  size_t current_alignment);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, InterfaceType)();
size_t get_serialized_size_rosgraph_msgs__msg__QoSProfile(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_rosgraph_msgs__msg__QoSProfile(
  bool * full_bounded,
  size_t current_alignment);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, QoSProfile)();


typedef rosgraph_msgs__msg__Topic _Topic__ros_msg_type;

static bool _Topic__cdr_serialize(
  const void * untyped_ros_message,
  ucdrBuffer * cdr)
{
  (void) untyped_ros_message;
  (void) cdr;

  bool rv = false;

  if (!untyped_ros_message) {
    return false;
  }

  _Topic__ros_msg_type * ros_message = (_Topic__ros_msg_type *)(untyped_ros_message);
  (void)ros_message;

  // Member: name
 {
    uint32_t string_len = (ros_message->name.data == NULL) ? 0 : (uint32_t)strlen(ros_message->name.data) + 1;
    ros_message->name.size = (ros_message->name.data == NULL) ? 0 : string_len - 1 ;
    rv = ucdr_serialize_sequence_char(cdr, ros_message->name.data, string_len);
  }
  // Member: type
  rv = ((const message_type_support_callbacks_t *)(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, InterfaceType
      )()->data))->cdr_serialize(&ros_message->type, cdr);
  // Member: qos
  rv = ((const message_type_support_callbacks_t *)(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, QoSProfile
      )()->data))->cdr_serialize(&ros_message->qos, cdr);

  return rv;
}

static bool _Topic__cdr_deserialize(
  ucdrBuffer * cdr,
  void * untyped_ros_message)
{
  (void) cdr;

  bool rv = false;

  if (!untyped_ros_message) {
    return false;
  }
  _Topic__ros_msg_type * ros_message = (_Topic__ros_msg_type *)(untyped_ros_message);
  (void)ros_message;

  // Field name: name
  {
    size_t capacity = ros_message->name.capacity;
    uint32_t string_size;
    rv = ucdr_deserialize_sequence_char(cdr, ros_message->name.data, capacity, &string_size);
    if (rv) {
      ros_message->name.size = (string_size == 0) ? 0 : string_size - 1;
    } else if(string_size > capacity){
      cdr->error = false;
      cdr->last_data_size = 1;
      ros_message->name.size = 0;
      ucdr_align_to(cdr, sizeof(char));
      ucdr_advance_buffer(cdr, string_size);
    }
  }
  // Field name: type
  rv = ((const message_type_support_callbacks_t *)(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, InterfaceType
      )()->data))->cdr_deserialize(cdr, &ros_message->type);
  // Field name: qos
  rv = ((const message_type_support_callbacks_t *)(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, QoSProfile
      )()->data))->cdr_deserialize(cdr, &ros_message->qos);
  return rv;
}

ROSIDL_TYPESUPPORT_MICROXRCEDDS_C_PUBLIC_rosgraph_msgs
size_t get_serialized_size_rosgraph_msgs__msg__Topic(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  if (!untyped_ros_message) {
    return 0;
  }

  const _Topic__ros_msg_type * ros_message = (const _Topic__ros_msg_type *)(untyped_ros_message);
  (void)ros_message;

  const size_t initial_alignment = current_alignment;

  // Member: name
  current_alignment += ucdr_alignment(current_alignment, MICROXRCEDDS_PADDING) + MICROXRCEDDS_PADDING;
  current_alignment += ros_message->name.size + 1;
  // Member: type
  current_alignment +=
    get_serialized_size_rosgraph_msgs__msg__InterfaceType(&ros_message->type, current_alignment);
  // Member: qos
  current_alignment +=
    get_serialized_size_rosgraph_msgs__msg__QoSProfile(&ros_message->qos, current_alignment);

  return current_alignment - initial_alignment;
}

static uint32_t _Topic__get_serialized_size(const void * untyped_ros_message)
{
  return (uint32_t)(
    get_serialized_size_rosgraph_msgs__msg__Topic(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_MICROXRCEDDS_C_PUBLIC_rosgraph_msgs
size_t max_serialized_size_rosgraph_msgs__msg__Topic(
  bool * full_bounded,
  size_t current_alignment)
{
  (void) current_alignment;
  *full_bounded = true;

  const size_t initial_alignment = current_alignment;

  // Member: name
  *full_bounded = false;
  // Member: type
  current_alignment +=
    max_serialized_size_rosgraph_msgs__msg__InterfaceType(full_bounded, current_alignment);
  // Member: qos
  current_alignment +=
    max_serialized_size_rosgraph_msgs__msg__QoSProfile(full_bounded, current_alignment);

  return current_alignment - initial_alignment;
}

static size_t _Topic__max_serialized_size()
{
  bool full_bounded;
  return max_serialized_size_rosgraph_msgs__msg__Topic(&full_bounded, 0);
}

static message_type_support_callbacks_t __callbacks_Topic = {
  "rosgraph_msgs::msg",
  "Topic",
  _Topic__cdr_serialize,
  _Topic__cdr_deserialize,
  _Topic__get_serialized_size,
  get_serialized_size_rosgraph_msgs__msg__Topic,
  _Topic__max_serialized_size
};

static rosidl_message_type_support_t _Topic__type_support = {
  ROSIDL_TYPESUPPORT_MICROXRCEDDS_C__IDENTIFIER_VALUE,
  &__callbacks_Topic,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Topic)() {
  return &_Topic__type_support;
}

#if defined(__cplusplus)
}
#endif
