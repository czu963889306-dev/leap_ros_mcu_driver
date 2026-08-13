// generated from rosidl_typesupport_microxrcedds_c/resource/idl__type_support_c.c.em
// with input from rosgraph_msgs:msg/Service.idl
// generated code does not contain a copyright notice
#include "rosgraph_msgs/msg/detail/service__rosidl_typesupport_microxrcedds_c.h"


#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "rosidl_typesupport_microxrcedds_c/identifier.h"
#include "rosidl_typesupport_microxrcedds_c/message_type_support.h"
#include "rosgraph_msgs/msg/rosidl_typesupport_microxrcedds_c__visibility_control.h"
#include "rosgraph_msgs/msg/detail/service__struct.h"
#include "rosgraph_msgs/msg/detail/service__functions.h"

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

#include "rosgraph_msgs/msg/detail/interface_type__functions.h"  // request_type, response_type
#include "rosgraph_msgs/msg/detail/qo_s_profile__functions.h"  // request_qos, response_qos
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


typedef rosgraph_msgs__msg__Service _Service__ros_msg_type;

static bool _Service__cdr_serialize(
  const void * untyped_ros_message,
  ucdrBuffer * cdr)
{
  (void) untyped_ros_message;
  (void) cdr;

  bool rv = false;

  if (!untyped_ros_message) {
    return false;
  }

  _Service__ros_msg_type * ros_message = (_Service__ros_msg_type *)(untyped_ros_message);
  (void)ros_message;

  // Member: name
 {
    uint32_t string_len = (ros_message->name.data == NULL) ? 0 : (uint32_t)strlen(ros_message->name.data) + 1;
    ros_message->name.size = (ros_message->name.data == NULL) ? 0 : string_len - 1 ;
    rv = ucdr_serialize_sequence_char(cdr, ros_message->name.data, string_len);
  }
  // Member: request_type
  rv = ((const message_type_support_callbacks_t *)(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, InterfaceType
      )()->data))->cdr_serialize(&ros_message->request_type, cdr);
  // Member: request_qos
  rv = ((const message_type_support_callbacks_t *)(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, QoSProfile
      )()->data))->cdr_serialize(&ros_message->request_qos, cdr);
  // Member: response_type
  rv = ((const message_type_support_callbacks_t *)(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, InterfaceType
      )()->data))->cdr_serialize(&ros_message->response_type, cdr);
  // Member: response_qos
  rv = ((const message_type_support_callbacks_t *)(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, QoSProfile
      )()->data))->cdr_serialize(&ros_message->response_qos, cdr);

  return rv;
}

static bool _Service__cdr_deserialize(
  ucdrBuffer * cdr,
  void * untyped_ros_message)
{
  (void) cdr;

  bool rv = false;

  if (!untyped_ros_message) {
    return false;
  }
  _Service__ros_msg_type * ros_message = (_Service__ros_msg_type *)(untyped_ros_message);
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
  // Field name: request_type
  rv = ((const message_type_support_callbacks_t *)(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, InterfaceType
      )()->data))->cdr_deserialize(cdr, &ros_message->request_type);
  // Field name: request_qos
  rv = ((const message_type_support_callbacks_t *)(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, QoSProfile
      )()->data))->cdr_deserialize(cdr, &ros_message->request_qos);
  // Field name: response_type
  rv = ((const message_type_support_callbacks_t *)(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, InterfaceType
      )()->data))->cdr_deserialize(cdr, &ros_message->response_type);
  // Field name: response_qos
  rv = ((const message_type_support_callbacks_t *)(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, QoSProfile
      )()->data))->cdr_deserialize(cdr, &ros_message->response_qos);
  return rv;
}

ROSIDL_TYPESUPPORT_MICROXRCEDDS_C_PUBLIC_rosgraph_msgs
size_t get_serialized_size_rosgraph_msgs__msg__Service(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  if (!untyped_ros_message) {
    return 0;
  }

  const _Service__ros_msg_type * ros_message = (const _Service__ros_msg_type *)(untyped_ros_message);
  (void)ros_message;

  const size_t initial_alignment = current_alignment;

  // Member: name
  current_alignment += ucdr_alignment(current_alignment, MICROXRCEDDS_PADDING) + MICROXRCEDDS_PADDING;
  current_alignment += ros_message->name.size + 1;
  // Member: request_type
  current_alignment +=
    get_serialized_size_rosgraph_msgs__msg__InterfaceType(&ros_message->request_type, current_alignment);
  // Member: request_qos
  current_alignment +=
    get_serialized_size_rosgraph_msgs__msg__QoSProfile(&ros_message->request_qos, current_alignment);
  // Member: response_type
  current_alignment +=
    get_serialized_size_rosgraph_msgs__msg__InterfaceType(&ros_message->response_type, current_alignment);
  // Member: response_qos
  current_alignment +=
    get_serialized_size_rosgraph_msgs__msg__QoSProfile(&ros_message->response_qos, current_alignment);

  return current_alignment - initial_alignment;
}

static uint32_t _Service__get_serialized_size(const void * untyped_ros_message)
{
  return (uint32_t)(
    get_serialized_size_rosgraph_msgs__msg__Service(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_MICROXRCEDDS_C_PUBLIC_rosgraph_msgs
size_t max_serialized_size_rosgraph_msgs__msg__Service(
  bool * full_bounded,
  size_t current_alignment)
{
  (void) current_alignment;
  *full_bounded = true;

  const size_t initial_alignment = current_alignment;

  // Member: name
  *full_bounded = false;
  // Member: request_type
  current_alignment +=
    max_serialized_size_rosgraph_msgs__msg__InterfaceType(full_bounded, current_alignment);
  // Member: request_qos
  current_alignment +=
    max_serialized_size_rosgraph_msgs__msg__QoSProfile(full_bounded, current_alignment);
  // Member: response_type
  current_alignment +=
    max_serialized_size_rosgraph_msgs__msg__InterfaceType(full_bounded, current_alignment);
  // Member: response_qos
  current_alignment +=
    max_serialized_size_rosgraph_msgs__msg__QoSProfile(full_bounded, current_alignment);

  return current_alignment - initial_alignment;
}

static size_t _Service__max_serialized_size()
{
  bool full_bounded;
  return max_serialized_size_rosgraph_msgs__msg__Service(&full_bounded, 0);
}

static message_type_support_callbacks_t __callbacks_Service = {
  "rosgraph_msgs::msg",
  "Service",
  _Service__cdr_serialize,
  _Service__cdr_deserialize,
  _Service__get_serialized_size,
  get_serialized_size_rosgraph_msgs__msg__Service,
  _Service__max_serialized_size
};

static rosidl_message_type_support_t _Service__type_support = {
  ROSIDL_TYPESUPPORT_MICROXRCEDDS_C__IDENTIFIER_VALUE,
  &__callbacks_Service,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Service)() {
  return &_Service__type_support;
}

#if defined(__cplusplus)
}
#endif
