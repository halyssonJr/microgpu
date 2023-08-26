#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "alloc.h"
#include "operations.h"
#include "responses.h"

/*
 * The accessible interface to the databus. The microgpu databus is
 * responsible for receiving operations from a controlling device and
 * sending responses back.
 */
typedef struct Mgpu_Databus Mgpu_Databus;

/*
 * Implementation specific structure that provides options for configuration
 * of the databus.
 */
typedef struct Mgpu_DatabusOptions Mgpu_DatabusOptions;

/*
 * Creates a new databus based on the passed in options.
 */
Mgpu_Databus *mgpu_databus_new(Mgpu_DatabusOptions *options, const Mgpu_Allocator *allocator);

/*
 * Uninitializes the databus and frees all memory allocated for it.
 */
void mgpu_databus_free(Mgpu_Databus *databus);

/*
 * Blocks and waits for the next operation to be received over the databus.
 * Returns true if the passed in operation struct was populated, or false if
 * an error occurred and the struct could not be filled in.
 */
bool mgpu_databus_get_next_operation(Mgpu_Databus *databus, Mgpu_Operation *operation);

/*
 * Sends the specified response to the controller over the databus. Almost always
 * triggered in reaction to an operation that requested a response.
 */
void mgpu_databus_send_response(Mgpu_Databus *databus, Mgpu_Response *response);