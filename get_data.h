/**
 * @file get_data.h
 * @brief Read the data and check for the input errors
 */
#ifndef GET_DATA_H
#define GET_DATA_H

#include <stdio.h>

#include "buffer_clean.h"
#include "define_consts.h"

/**
* @brief Read the data and write it into the structure
* @param[in] quadr_coeff Poiner to the structure type Coeff with coefficients of equation
* @return NO_INPUT_ERRORS if data was successfully written in coefficients structure
*         INPUT_ERROR if data was not written
*/
int GetData(struct Coeff *quadr_coeff);

#endif /* GET_DATA_H */
