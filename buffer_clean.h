/**
 * @file buffer_clean.h
 * @brief Function to clear the buffer
 */
#ifndef BUFFER_CLEAN_H
#define BUFFER_CLEAN_H

#include <stdio.h>
#include <ctype.h>

#include "define_consts.h"

/**
 * @brief  Clear the buffer and return the read character information.
 * @return If the last symbol read is EOF return END_OF_FILE.
 *         If there were symbols except space symbols return SYMBOLS_INPUT_ERROR.
 *         If there were only scape symbols and the last one is not EOF return NO_ERRORS.
 */

int BufferClean();

#endif /* BUFFER_CLEAN_H */
