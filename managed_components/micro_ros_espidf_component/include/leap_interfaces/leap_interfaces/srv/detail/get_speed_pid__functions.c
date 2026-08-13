// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from leap_interfaces:srv/GetSpeedPid.idl
// generated code does not contain a copyright notice
#include "leap_interfaces/srv/detail/get_speed_pid__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
leap_interfaces__srv__GetSpeedPid_Request__init(leap_interfaces__srv__GetSpeedPid_Request * msg)
{
  if (!msg) {
    return false;
  }
  // structure_needs_at_least_one_member
  return true;
}

void
leap_interfaces__srv__GetSpeedPid_Request__fini(leap_interfaces__srv__GetSpeedPid_Request * msg)
{
  if (!msg) {
    return;
  }
  // structure_needs_at_least_one_member
}

bool
leap_interfaces__srv__GetSpeedPid_Request__are_equal(const leap_interfaces__srv__GetSpeedPid_Request * lhs, const leap_interfaces__srv__GetSpeedPid_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // structure_needs_at_least_one_member
  if (lhs->structure_needs_at_least_one_member != rhs->structure_needs_at_least_one_member) {
    return false;
  }
  return true;
}

bool
leap_interfaces__srv__GetSpeedPid_Request__copy(
  const leap_interfaces__srv__GetSpeedPid_Request * input,
  leap_interfaces__srv__GetSpeedPid_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // structure_needs_at_least_one_member
  output->structure_needs_at_least_one_member = input->structure_needs_at_least_one_member;
  return true;
}

leap_interfaces__srv__GetSpeedPid_Request *
leap_interfaces__srv__GetSpeedPid_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  leap_interfaces__srv__GetSpeedPid_Request * msg = (leap_interfaces__srv__GetSpeedPid_Request *)allocator.allocate(sizeof(leap_interfaces__srv__GetSpeedPid_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(leap_interfaces__srv__GetSpeedPid_Request));
  bool success = leap_interfaces__srv__GetSpeedPid_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
leap_interfaces__srv__GetSpeedPid_Request__destroy(leap_interfaces__srv__GetSpeedPid_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    leap_interfaces__srv__GetSpeedPid_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
leap_interfaces__srv__GetSpeedPid_Request__Sequence__init(leap_interfaces__srv__GetSpeedPid_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  leap_interfaces__srv__GetSpeedPid_Request * data = NULL;

  if (size) {
    data = (leap_interfaces__srv__GetSpeedPid_Request *)allocator.zero_allocate(size, sizeof(leap_interfaces__srv__GetSpeedPid_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = leap_interfaces__srv__GetSpeedPid_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        leap_interfaces__srv__GetSpeedPid_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
leap_interfaces__srv__GetSpeedPid_Request__Sequence__fini(leap_interfaces__srv__GetSpeedPid_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      leap_interfaces__srv__GetSpeedPid_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

leap_interfaces__srv__GetSpeedPid_Request__Sequence *
leap_interfaces__srv__GetSpeedPid_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  leap_interfaces__srv__GetSpeedPid_Request__Sequence * array = (leap_interfaces__srv__GetSpeedPid_Request__Sequence *)allocator.allocate(sizeof(leap_interfaces__srv__GetSpeedPid_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = leap_interfaces__srv__GetSpeedPid_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
leap_interfaces__srv__GetSpeedPid_Request__Sequence__destroy(leap_interfaces__srv__GetSpeedPid_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    leap_interfaces__srv__GetSpeedPid_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
leap_interfaces__srv__GetSpeedPid_Request__Sequence__are_equal(const leap_interfaces__srv__GetSpeedPid_Request__Sequence * lhs, const leap_interfaces__srv__GetSpeedPid_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!leap_interfaces__srv__GetSpeedPid_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
leap_interfaces__srv__GetSpeedPid_Request__Sequence__copy(
  const leap_interfaces__srv__GetSpeedPid_Request__Sequence * input,
  leap_interfaces__srv__GetSpeedPid_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(leap_interfaces__srv__GetSpeedPid_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    leap_interfaces__srv__GetSpeedPid_Request * data =
      (leap_interfaces__srv__GetSpeedPid_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!leap_interfaces__srv__GetSpeedPid_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          leap_interfaces__srv__GetSpeedPid_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!leap_interfaces__srv__GetSpeedPid_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
leap_interfaces__srv__GetSpeedPid_Response__init(leap_interfaces__srv__GetSpeedPid_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // kp
  // ki
  // kd
  return true;
}

void
leap_interfaces__srv__GetSpeedPid_Response__fini(leap_interfaces__srv__GetSpeedPid_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
  // kp
  // ki
  // kd
}

bool
leap_interfaces__srv__GetSpeedPid_Response__are_equal(const leap_interfaces__srv__GetSpeedPid_Response * lhs, const leap_interfaces__srv__GetSpeedPid_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  // kp
  if (lhs->kp != rhs->kp) {
    return false;
  }
  // ki
  if (lhs->ki != rhs->ki) {
    return false;
  }
  // kd
  if (lhs->kd != rhs->kd) {
    return false;
  }
  return true;
}

bool
leap_interfaces__srv__GetSpeedPid_Response__copy(
  const leap_interfaces__srv__GetSpeedPid_Response * input,
  leap_interfaces__srv__GetSpeedPid_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  // kp
  output->kp = input->kp;
  // ki
  output->ki = input->ki;
  // kd
  output->kd = input->kd;
  return true;
}

leap_interfaces__srv__GetSpeedPid_Response *
leap_interfaces__srv__GetSpeedPid_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  leap_interfaces__srv__GetSpeedPid_Response * msg = (leap_interfaces__srv__GetSpeedPid_Response *)allocator.allocate(sizeof(leap_interfaces__srv__GetSpeedPid_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(leap_interfaces__srv__GetSpeedPid_Response));
  bool success = leap_interfaces__srv__GetSpeedPid_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
leap_interfaces__srv__GetSpeedPid_Response__destroy(leap_interfaces__srv__GetSpeedPid_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    leap_interfaces__srv__GetSpeedPid_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
leap_interfaces__srv__GetSpeedPid_Response__Sequence__init(leap_interfaces__srv__GetSpeedPid_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  leap_interfaces__srv__GetSpeedPid_Response * data = NULL;

  if (size) {
    data = (leap_interfaces__srv__GetSpeedPid_Response *)allocator.zero_allocate(size, sizeof(leap_interfaces__srv__GetSpeedPid_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = leap_interfaces__srv__GetSpeedPid_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        leap_interfaces__srv__GetSpeedPid_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
leap_interfaces__srv__GetSpeedPid_Response__Sequence__fini(leap_interfaces__srv__GetSpeedPid_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      leap_interfaces__srv__GetSpeedPid_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

leap_interfaces__srv__GetSpeedPid_Response__Sequence *
leap_interfaces__srv__GetSpeedPid_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  leap_interfaces__srv__GetSpeedPid_Response__Sequence * array = (leap_interfaces__srv__GetSpeedPid_Response__Sequence *)allocator.allocate(sizeof(leap_interfaces__srv__GetSpeedPid_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = leap_interfaces__srv__GetSpeedPid_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
leap_interfaces__srv__GetSpeedPid_Response__Sequence__destroy(leap_interfaces__srv__GetSpeedPid_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    leap_interfaces__srv__GetSpeedPid_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
leap_interfaces__srv__GetSpeedPid_Response__Sequence__are_equal(const leap_interfaces__srv__GetSpeedPid_Response__Sequence * lhs, const leap_interfaces__srv__GetSpeedPid_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!leap_interfaces__srv__GetSpeedPid_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
leap_interfaces__srv__GetSpeedPid_Response__Sequence__copy(
  const leap_interfaces__srv__GetSpeedPid_Response__Sequence * input,
  leap_interfaces__srv__GetSpeedPid_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(leap_interfaces__srv__GetSpeedPid_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    leap_interfaces__srv__GetSpeedPid_Response * data =
      (leap_interfaces__srv__GetSpeedPid_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!leap_interfaces__srv__GetSpeedPid_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          leap_interfaces__srv__GetSpeedPid_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!leap_interfaces__srv__GetSpeedPid_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
