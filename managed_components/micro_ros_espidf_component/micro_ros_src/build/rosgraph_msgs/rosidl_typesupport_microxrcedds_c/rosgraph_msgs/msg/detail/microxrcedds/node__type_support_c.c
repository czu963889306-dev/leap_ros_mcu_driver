// generated from rosidl_typesupport_microxrcedds_c/resource/idl__type_support_c.c.em
// with input from rosgraph_msgs:msg/Node.idl
// generated code does not contain a copyright notice
#include "rosgraph_msgs/msg/detail/node__rosidl_typesupport_microxrcedds_c.h"


#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "rosidl_typesupport_microxrcedds_c/identifier.h"
#include "rosidl_typesupport_microxrcedds_c/message_type_support.h"
#include "rosgraph_msgs/msg/rosidl_typesupport_microxrcedds_c__visibility_control.h"
#include "rosgraph_msgs/msg/detail/node__struct.h"
#include "rosgraph_msgs/msg/detail/node__functions.h"

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

#include "rcl_interfaces/msg/detail/parameter_descriptor__functions.h"  // parameters
#include "rcl_interfaces/msg/detail/parameter_value__functions.h"  // parameter_values
#include "rosgraph_msgs/msg/detail/action__functions.h"  // action_clients, action_servers
#include "rosgraph_msgs/msg/detail/service__functions.h"  // service_clients, service_servers
#include "rosgraph_msgs/msg/detail/topic__functions.h"  // publishers, subscriptions
#include "rosidl_runtime_c/string.h"  // name
#include "rosidl_runtime_c/string_functions.h"  // name

// forward declare type support functions
ROSIDL_TYPESUPPORT_MICROXRCEDDS_C_IMPORT_rosgraph_msgs
size_t get_serialized_size_rcl_interfaces__msg__ParameterDescriptor(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_MICROXRCEDDS_C_IMPORT_rosgraph_msgs
size_t max_serialized_size_rcl_interfaces__msg__ParameterDescriptor(
  bool * full_bounded,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_MICROXRCEDDS_C_IMPORT_rosgraph_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rcl_interfaces, msg, ParameterDescriptor)();
ROSIDL_TYPESUPPORT_MICROXRCEDDS_C_IMPORT_rosgraph_msgs
size_t get_serialized_size_rcl_interfaces__msg__ParameterValue(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_MICROXRCEDDS_C_IMPORT_rosgraph_msgs
size_t max_serialized_size_rcl_interfaces__msg__ParameterValue(
  bool * full_bounded,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_MICROXRCEDDS_C_IMPORT_rosgraph_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rcl_interfaces, msg, ParameterValue)();
size_t get_serialized_size_rosgraph_msgs__msg__Action(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_rosgraph_msgs__msg__Action(
  bool * full_bounded,
  size_t current_alignment);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Action)();
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


typedef rosgraph_msgs__msg__Node _Node__ros_msg_type;

static bool _Node__cdr_serialize(
  const void * untyped_ros_message,
  ucdrBuffer * cdr)
{
  (void) untyped_ros_message;
  (void) cdr;

  bool rv = false;

  if (!untyped_ros_message) {
    return false;
  }

  _Node__ros_msg_type * ros_message = (_Node__ros_msg_type *)(untyped_ros_message);
  (void)ros_message;

  // Member: name
 {
    uint32_t string_len = (ros_message->name.data == NULL) ? 0 : (uint32_t)strlen(ros_message->name.data) + 1;
    ros_message->name.size = (ros_message->name.data == NULL) ? 0 : string_len - 1 ;
    rv = ucdr_serialize_sequence_char(cdr, ros_message->name.data, string_len);
  }
  // Member: parameters
  {
    const size_t size = ros_message->parameters.size;
    rv = ucdr_serialize_uint32_t(cdr, size);

    if(rv == true){
      for(size_t i = 0; i < size; i++){
        rv = ((const message_type_support_callbacks_t *)(
          ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rcl_interfaces, msg, ParameterDescriptor
          )()->data))->cdr_serialize(&ros_message->parameters.data[i], cdr);
        if(rv == false){
          break;
        }
      }
    }
  }
  // Member: parameter_values
  {
    const size_t size = ros_message->parameter_values.size;
    rv = ucdr_serialize_uint32_t(cdr, size);

    if(rv == true){
      for(size_t i = 0; i < size; i++){
        rv = ((const message_type_support_callbacks_t *)(
          ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rcl_interfaces, msg, ParameterValue
          )()->data))->cdr_serialize(&ros_message->parameter_values.data[i], cdr);
        if(rv == false){
          break;
        }
      }
    }
  }
  // Member: publishers
  {
    const size_t size = ros_message->publishers.size;
    rv = ucdr_serialize_uint32_t(cdr, size);

    if(rv == true){
      for(size_t i = 0; i < size; i++){
        rv = ((const message_type_support_callbacks_t *)(
          ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Topic
          )()->data))->cdr_serialize(&ros_message->publishers.data[i], cdr);
        if(rv == false){
          break;
        }
      }
    }
  }
  // Member: subscriptions
  {
    const size_t size = ros_message->subscriptions.size;
    rv = ucdr_serialize_uint32_t(cdr, size);

    if(rv == true){
      for(size_t i = 0; i < size; i++){
        rv = ((const message_type_support_callbacks_t *)(
          ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Topic
          )()->data))->cdr_serialize(&ros_message->subscriptions.data[i], cdr);
        if(rv == false){
          break;
        }
      }
    }
  }
  // Member: service_clients
  {
    const size_t size = ros_message->service_clients.size;
    rv = ucdr_serialize_uint32_t(cdr, size);

    if(rv == true){
      for(size_t i = 0; i < size; i++){
        rv = ((const message_type_support_callbacks_t *)(
          ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Service
          )()->data))->cdr_serialize(&ros_message->service_clients.data[i], cdr);
        if(rv == false){
          break;
        }
      }
    }
  }
  // Member: service_servers
  {
    const size_t size = ros_message->service_servers.size;
    rv = ucdr_serialize_uint32_t(cdr, size);

    if(rv == true){
      for(size_t i = 0; i < size; i++){
        rv = ((const message_type_support_callbacks_t *)(
          ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Service
          )()->data))->cdr_serialize(&ros_message->service_servers.data[i], cdr);
        if(rv == false){
          break;
        }
      }
    }
  }
  // Member: action_clients
  {
    const size_t size = ros_message->action_clients.size;
    rv = ucdr_serialize_uint32_t(cdr, size);

    if(rv == true){
      for(size_t i = 0; i < size; i++){
        rv = ((const message_type_support_callbacks_t *)(
          ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Action
          )()->data))->cdr_serialize(&ros_message->action_clients.data[i], cdr);
        if(rv == false){
          break;
        }
      }
    }
  }
  // Member: action_servers
  {
    const size_t size = ros_message->action_servers.size;
    rv = ucdr_serialize_uint32_t(cdr, size);

    if(rv == true){
      for(size_t i = 0; i < size; i++){
        rv = ((const message_type_support_callbacks_t *)(
          ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Action
          )()->data))->cdr_serialize(&ros_message->action_servers.data[i], cdr);
        if(rv == false){
          break;
        }
      }
    }
  }

  return rv;
}

static bool _Node__cdr_deserialize(
  ucdrBuffer * cdr,
  void * untyped_ros_message)
{
  (void) cdr;

  bool rv = false;

  if (!untyped_ros_message) {
    return false;
  }
  _Node__ros_msg_type * ros_message = (_Node__ros_msg_type *)(untyped_ros_message);
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
  // Field name: parameters
  {
    uint32_t size;
    rv = ucdr_deserialize_uint32_t(cdr, &size);

    if(size > ros_message->parameters.capacity){
      return 0;
    }

    ros_message->parameters.size = size;
    for(size_t i = 0; i < size; i++){
      rv = ((const message_type_support_callbacks_t *)(
        ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rcl_interfaces, msg, ParameterDescriptor
        )()->data))->cdr_deserialize(cdr, &ros_message->parameters.data[i]);
      if(rv == false){
        break;
      }
    }
  }
  // Field name: parameter_values
  {
    uint32_t size;
    rv = ucdr_deserialize_uint32_t(cdr, &size);

    if(size > ros_message->parameter_values.capacity){
      return 0;
    }

    ros_message->parameter_values.size = size;
    for(size_t i = 0; i < size; i++){
      rv = ((const message_type_support_callbacks_t *)(
        ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rcl_interfaces, msg, ParameterValue
        )()->data))->cdr_deserialize(cdr, &ros_message->parameter_values.data[i]);
      if(rv == false){
        break;
      }
    }
  }
  // Field name: publishers
  {
    uint32_t size;
    rv = ucdr_deserialize_uint32_t(cdr, &size);

    if(size > ros_message->publishers.capacity){
      return 0;
    }

    ros_message->publishers.size = size;
    for(size_t i = 0; i < size; i++){
      rv = ((const message_type_support_callbacks_t *)(
        ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Topic
        )()->data))->cdr_deserialize(cdr, &ros_message->publishers.data[i]);
      if(rv == false){
        break;
      }
    }
  }
  // Field name: subscriptions
  {
    uint32_t size;
    rv = ucdr_deserialize_uint32_t(cdr, &size);

    if(size > ros_message->subscriptions.capacity){
      return 0;
    }

    ros_message->subscriptions.size = size;
    for(size_t i = 0; i < size; i++){
      rv = ((const message_type_support_callbacks_t *)(
        ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Topic
        )()->data))->cdr_deserialize(cdr, &ros_message->subscriptions.data[i]);
      if(rv == false){
        break;
      }
    }
  }
  // Field name: service_clients
  {
    uint32_t size;
    rv = ucdr_deserialize_uint32_t(cdr, &size);

    if(size > ros_message->service_clients.capacity){
      return 0;
    }

    ros_message->service_clients.size = size;
    for(size_t i = 0; i < size; i++){
      rv = ((const message_type_support_callbacks_t *)(
        ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Service
        )()->data))->cdr_deserialize(cdr, &ros_message->service_clients.data[i]);
      if(rv == false){
        break;
      }
    }
  }
  // Field name: service_servers
  {
    uint32_t size;
    rv = ucdr_deserialize_uint32_t(cdr, &size);

    if(size > ros_message->service_servers.capacity){
      return 0;
    }

    ros_message->service_servers.size = size;
    for(size_t i = 0; i < size; i++){
      rv = ((const message_type_support_callbacks_t *)(
        ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Service
        )()->data))->cdr_deserialize(cdr, &ros_message->service_servers.data[i]);
      if(rv == false){
        break;
      }
    }
  }
  // Field name: action_clients
  {
    uint32_t size;
    rv = ucdr_deserialize_uint32_t(cdr, &size);

    if(size > ros_message->action_clients.capacity){
      return 0;
    }

    ros_message->action_clients.size = size;
    for(size_t i = 0; i < size; i++){
      rv = ((const message_type_support_callbacks_t *)(
        ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Action
        )()->data))->cdr_deserialize(cdr, &ros_message->action_clients.data[i]);
      if(rv == false){
        break;
      }
    }
  }
  // Field name: action_servers
  {
    uint32_t size;
    rv = ucdr_deserialize_uint32_t(cdr, &size);

    if(size > ros_message->action_servers.capacity){
      return 0;
    }

    ros_message->action_servers.size = size;
    for(size_t i = 0; i < size; i++){
      rv = ((const message_type_support_callbacks_t *)(
        ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Action
        )()->data))->cdr_deserialize(cdr, &ros_message->action_servers.data[i]);
      if(rv == false){
        break;
      }
    }
  }
  return rv;
}

ROSIDL_TYPESUPPORT_MICROXRCEDDS_C_PUBLIC_rosgraph_msgs
size_t get_serialized_size_rosgraph_msgs__msg__Node(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  if (!untyped_ros_message) {
    return 0;
  }

  const _Node__ros_msg_type * ros_message = (const _Node__ros_msg_type *)(untyped_ros_message);
  (void)ros_message;

  const size_t initial_alignment = current_alignment;

  // Member: name
  current_alignment += ucdr_alignment(current_alignment, MICROXRCEDDS_PADDING) + MICROXRCEDDS_PADDING;
  current_alignment += ros_message->name.size + 1;
  // Member: parameters
  {
    const size_t sequence_size = ros_message->parameters.size;

    current_alignment += ucdr_alignment(current_alignment, MICROXRCEDDS_PADDING) + MICROXRCEDDS_PADDING;

    for(size_t i = 0; i < sequence_size; i++){
      size_t element_size = ((const message_type_support_callbacks_t *)(
        ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rcl_interfaces, msg, ParameterDescriptor
        )()->data))->get_serialized_size_with_initial_alignment(&ros_message->parameters.data[i], current_alignment);
      uint8_t alignment_size = (element_size < MICROXRCEDDS_PADDING) ? element_size : MICROXRCEDDS_PADDING;
      current_alignment += ucdr_alignment(current_alignment, alignment_size) + element_size;
    }
  }
  // Member: parameter_values
  {
    const size_t sequence_size = ros_message->parameter_values.size;

    current_alignment += ucdr_alignment(current_alignment, MICROXRCEDDS_PADDING) + MICROXRCEDDS_PADDING;

    for(size_t i = 0; i < sequence_size; i++){
      size_t element_size = ((const message_type_support_callbacks_t *)(
        ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rcl_interfaces, msg, ParameterValue
        )()->data))->get_serialized_size_with_initial_alignment(&ros_message->parameter_values.data[i], current_alignment);
      uint8_t alignment_size = (element_size < MICROXRCEDDS_PADDING) ? element_size : MICROXRCEDDS_PADDING;
      current_alignment += ucdr_alignment(current_alignment, alignment_size) + element_size;
    }
  }
  // Member: publishers
  {
    const size_t sequence_size = ros_message->publishers.size;

    current_alignment += ucdr_alignment(current_alignment, MICROXRCEDDS_PADDING) + MICROXRCEDDS_PADDING;

    for(size_t i = 0; i < sequence_size; i++){
      size_t element_size = ((const message_type_support_callbacks_t *)(
        ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Topic
        )()->data))->get_serialized_size_with_initial_alignment(&ros_message->publishers.data[i], current_alignment);
      uint8_t alignment_size = (element_size < MICROXRCEDDS_PADDING) ? element_size : MICROXRCEDDS_PADDING;
      current_alignment += ucdr_alignment(current_alignment, alignment_size) + element_size;
    }
  }
  // Member: subscriptions
  {
    const size_t sequence_size = ros_message->subscriptions.size;

    current_alignment += ucdr_alignment(current_alignment, MICROXRCEDDS_PADDING) + MICROXRCEDDS_PADDING;

    for(size_t i = 0; i < sequence_size; i++){
      size_t element_size = ((const message_type_support_callbacks_t *)(
        ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Topic
        )()->data))->get_serialized_size_with_initial_alignment(&ros_message->subscriptions.data[i], current_alignment);
      uint8_t alignment_size = (element_size < MICROXRCEDDS_PADDING) ? element_size : MICROXRCEDDS_PADDING;
      current_alignment += ucdr_alignment(current_alignment, alignment_size) + element_size;
    }
  }
  // Member: service_clients
  {
    const size_t sequence_size = ros_message->service_clients.size;

    current_alignment += ucdr_alignment(current_alignment, MICROXRCEDDS_PADDING) + MICROXRCEDDS_PADDING;

    for(size_t i = 0; i < sequence_size; i++){
      size_t element_size = ((const message_type_support_callbacks_t *)(
        ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Service
        )()->data))->get_serialized_size_with_initial_alignment(&ros_message->service_clients.data[i], current_alignment);
      uint8_t alignment_size = (element_size < MICROXRCEDDS_PADDING) ? element_size : MICROXRCEDDS_PADDING;
      current_alignment += ucdr_alignment(current_alignment, alignment_size) + element_size;
    }
  }
  // Member: service_servers
  {
    const size_t sequence_size = ros_message->service_servers.size;

    current_alignment += ucdr_alignment(current_alignment, MICROXRCEDDS_PADDING) + MICROXRCEDDS_PADDING;

    for(size_t i = 0; i < sequence_size; i++){
      size_t element_size = ((const message_type_support_callbacks_t *)(
        ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Service
        )()->data))->get_serialized_size_with_initial_alignment(&ros_message->service_servers.data[i], current_alignment);
      uint8_t alignment_size = (element_size < MICROXRCEDDS_PADDING) ? element_size : MICROXRCEDDS_PADDING;
      current_alignment += ucdr_alignment(current_alignment, alignment_size) + element_size;
    }
  }
  // Member: action_clients
  {
    const size_t sequence_size = ros_message->action_clients.size;

    current_alignment += ucdr_alignment(current_alignment, MICROXRCEDDS_PADDING) + MICROXRCEDDS_PADDING;

    for(size_t i = 0; i < sequence_size; i++){
      size_t element_size = ((const message_type_support_callbacks_t *)(
        ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Action
        )()->data))->get_serialized_size_with_initial_alignment(&ros_message->action_clients.data[i], current_alignment);
      uint8_t alignment_size = (element_size < MICROXRCEDDS_PADDING) ? element_size : MICROXRCEDDS_PADDING;
      current_alignment += ucdr_alignment(current_alignment, alignment_size) + element_size;
    }
  }
  // Member: action_servers
  {
    const size_t sequence_size = ros_message->action_servers.size;

    current_alignment += ucdr_alignment(current_alignment, MICROXRCEDDS_PADDING) + MICROXRCEDDS_PADDING;

    for(size_t i = 0; i < sequence_size; i++){
      size_t element_size = ((const message_type_support_callbacks_t *)(
        ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Action
        )()->data))->get_serialized_size_with_initial_alignment(&ros_message->action_servers.data[i], current_alignment);
      uint8_t alignment_size = (element_size < MICROXRCEDDS_PADDING) ? element_size : MICROXRCEDDS_PADDING;
      current_alignment += ucdr_alignment(current_alignment, alignment_size) + element_size;
    }
  }

  return current_alignment - initial_alignment;
}

static uint32_t _Node__get_serialized_size(const void * untyped_ros_message)
{
  return (uint32_t)(
    get_serialized_size_rosgraph_msgs__msg__Node(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_MICROXRCEDDS_C_PUBLIC_rosgraph_msgs
size_t max_serialized_size_rosgraph_msgs__msg__Node(
  bool * full_bounded,
  size_t current_alignment)
{
  (void) current_alignment;
  *full_bounded = true;

  const size_t initial_alignment = current_alignment;

  // Member: name
  *full_bounded = false;
  // Member: parameters
  {
    *full_bounded = false;
  }
  // Member: parameter_values
  {
    *full_bounded = false;
  }
  // Member: publishers
  {
    *full_bounded = false;
  }
  // Member: subscriptions
  {
    *full_bounded = false;
  }
  // Member: service_clients
  {
    *full_bounded = false;
  }
  // Member: service_servers
  {
    *full_bounded = false;
  }
  // Member: action_clients
  {
    *full_bounded = false;
  }
  // Member: action_servers
  {
    *full_bounded = false;
  }

  return current_alignment - initial_alignment;
}

static size_t _Node__max_serialized_size()
{
  bool full_bounded;
  return max_serialized_size_rosgraph_msgs__msg__Node(&full_bounded, 0);
}

static message_type_support_callbacks_t __callbacks_Node = {
  "rosgraph_msgs::msg",
  "Node",
  _Node__cdr_serialize,
  _Node__cdr_deserialize,
  _Node__get_serialized_size,
  get_serialized_size_rosgraph_msgs__msg__Node,
  _Node__max_serialized_size
};

static rosidl_message_type_support_t _Node__type_support = {
  ROSIDL_TYPESUPPORT_MICROXRCEDDS_C__IDENTIFIER_VALUE,
  &__callbacks_Node,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_microxrcedds_c, rosgraph_msgs, msg, Node)() {
  return &_Node__type_support;
}

#if defined(__cplusplus)
}
#endif
