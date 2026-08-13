// generated from rosidl_typesupport_microxrcedds_c/resource/idl__type_support_c.c.em
// with input from rosgraph_msgs:msg/Action.idl
// generated code does not contain a copyright notice
#include "rosgraph_msgs/msg/detail/action__rosidl_typesupport_microxrcedds_c.h"


#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "rosidl_typesupport_microxrcedds_c/identifier.h"
#include "rosidl_typesupport_microxrcedds_c/message_type_support.h"
#include "rosgraph_msgs/msg/rosidl_typesupport_microxrcedds_c__visibility_control.h"
#include "rosgraph_msgs/msg/detail/action__struct.h"
#include "rosgraph_msgs/msg/detail/action__functions.h"

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

#include "rosgraph_msgs/msg/detail/service__functions.h"  // cancel_goal, get_result, send_goal
#include "rosgraph_msgs/msg/detail/topic__functions.h"  // feedback, status
#include "rosidl_runtime_c/string.h"  // name
#include "rosidl_runtime_c/string_functions.h"  // name

// forward declare type support functions
size_t get_serialized_size_rosgraph_msgs__msg__Service(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_rosgraph_msgs__msg__Service(
  bool * full_bounded,
  size_t current_alignment);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Service)();
size_t get_serialized_size_rosgraph_msgs__msg__Topic(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_rosgraph_msgs__msg__Topic(
  bool * full_bounded,
  size_t current_alignment);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Topic)();


typedef rosgraph_msgs__msg__Action _Action__ros_msg_type;

static bool _Action__cdr_serialize(
  const void * untyped_ros_message,
  ucdrBuffer * cdr)
{
  (void) untyped_ros_message;
  (void) cdr;

  bool rv = false;

  if (!untyped_ros_message) {
    return false;
  }

  _Action__ros_msg_type * ros_message = (_Action__ros_msg_type *)(untyped_ros_message);
  (void)ros_message;

  // Member: name
 {
    uint32_t string_len = (ros_message->name.data == NULL) ? 0 : (uint32_t)strlen(ros_message->name.data) + 1;
    ros_message->name.size = (ros_message->name.data == NULL) ? 0 : string_len - 1 ;
    rv = ucdr_serialize_sequence_char(cdr, ros_message->name.data, string_len);
  }
  // Member: send_goal
  rv = ((const message_type_support_callbacks_t *)(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Service
      )()->data))->cdr_serialize(&ros_message->send_goal, cdr);
  // Member: get_result
  rv = ((const message_type_support_callbacks_t *)(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Service
      )()->data))->cdr_serialize(&ros_message->get_result, cdr);
  // Member: cancel_goal
  rv = ((const message_type_support_callbacks_t *)(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Service
      )()->data))->cdr_serialize(&ros_message->cancel_goal, cdr);
  // Member: feedback
  rv = ((const message_type_support_callbacks_t *)(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Topic
      )()->data))->cdr_serialize(&ros_message->feedback, cdr);
  // Member: status
  rv = ((const message_type_support_callbacks_t *)(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Topic
      )()->data))->cdr_serialize(&ros_message->status, cdr);

  return rv;
}

static bool _Action__cdr_deserialize(
  ucdrBuffer * cdr,
  void * untyped_ros_message)
{
  (void) cdr;

  bool rv = false;

  if (!untyped_ros_message) {
    return false;
  }
  _Action__ros_msg_type * ros_message = (_Action__ros_msg_type *)(untyped_ros_message);
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
  // Field name: send_goal
  rv = ((const message_type_support_callbacks_t *)(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Service
      )()->data))->cdr_deserialize(cdr, &ros_message->send_goal);
  // Field name: get_result
  rv = ((const message_type_support_callbacks_t *)(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Service
      )()->data))->cdr_deserialize(cdr, &ros_message->get_result);
  // Field name: cancel_goal
  rv = ((const message_type_support_callbacks_t *)(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Service
      )()->data))->cdr_deserialize(cdr, &ros_message->cancel_goal);
  // Field name: feedback
  rv = ((const message_type_support_callbacks_t *)(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Topic
      )()->data))->cdr_deserialize(cdr, &ros_message->feedback);
  // Field name: status
  rv = ((const message_type_support_callbacks_t *)(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Topic
      )()->data))->cdr_deserialize(cdr, &ros_message->status);
  return rv;
}

ROSIDL_TYPESUPPORT_MICROXRCEDDS_C_PUBLIC_rosgraph_msgs
size_t get_serialized_size_rosgraph_msgs__msg__Action(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  if (!untyped_ros_message) {
    return 0;
  }

  const _Action__ros_msg_type * ros_message = (const _Action__ros_msg_type *)(untyped_ros_message);
  (void)ros_message;

  const size_t initial_alignment = current_alignment;

  // Member: name
  current_alignment += ucdr_alignment(current_alignment, MICROXRCEDDS_PADDING) + MICROXRCEDDS_PADDING;
  current_alignment += ros_message->name.size + 1;
  // Member: send_goal
  current_alignment +=
    get_serialized_size_rosgraph_msgs__msg__Service(&ros_message->send_goal, current_alignment);
  // Member: get_result
  current_alignment +=
    get_serialized_size_rosgraph_msgs__msg__Service(&ros_message->get_result, current_alignment);
  // Member: cancel_goal
  current_alignment +=
    get_serialized_size_rosgraph_msgs__msg__Service(&ros_message->cancel_goal, current_alignment);
  // Member: feedback
  current_alignment +=
    get_serialized_size_rosgraph_msgs__msg__Topic(&ros_message->feedback, current_alignment);
  // Member: status
  current_alignment +=
    get_serialized_size_rosgraph_msgs__msg__Topic(&ros_message->status, current_alignment);

  return current_alignment - initial_alignment;
}

static uint32_t _Action__get_serialized_size(const void * untyped_ros_message)
{
  return (uint32_t)(
    get_serialized_size_rosgraph_msgs__msg__Action(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_MICROXRCEDDS_C_PUBLIC_rosgraph_msgs
size_t max_serialized_size_rosgraph_msgs__msg__Action(
  bool * full_bounded,
  size_t current_alignment)
{
  (void) current_alignment;
  *full_bounded = true;

  const size_t initial_alignment = current_alignment;

  // Member: name
  *full_bounded = false;
  // Member: send_goal
  current_alignment +=
    max_serialized_size_rosgraph_msgs__msg__Service(full_bounded, current_alignment);
  // Member: get_result
  current_alignment +=
    max_serialized_size_rosgraph_msgs__msg__Service(full_bounded, current_alignment);
  // Member: cancel_goal
  current_alignment +=
    max_serialized_size_rosgraph_msgs__msg__Service(full_bounded, current_alignment);
  // Member: feedback
  current_alignment +=
    max_serialized_size_rosgraph_msgs__msg__Topic(full_bounded, current_alignment);
  // Member: status
  current_alignment +=
    max_serialized_size_rosgraph_msgs__msg__Topic(full_bounded, current_alignment);

  return current_alignment - initial_alignment;
}

static size_t _Action__max_serialized_size()
{
  bool full_bounded;
  return max_serialized_size_rosgraph_msgs__msg__Action(&full_bounded, 0);
}

static message_type_support_callbacks_t __callbacks_Action = {
  "rosgraph_msgs::msg",
  "Action",
  _Action__cdr_serialize,
  _Action__cdr_deserialize,
  _Action__get_serialized_size,
  get_serialized_size_rosgraph_msgs__msg__Action,
  _Action__max_serialized_size
};

static rosidl_message_type_support_t _Action__type_support = {
  ROSIDL_TYPESUPPORT_MICROXRCEDDS_C__IDENTIFIER_VALUE,
  &__callbacks_Action,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Action)() {
  return &_Action__type_support;
}

#if defined(__cplusplus)
}
#endif
