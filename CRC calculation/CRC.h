#pragma once

/**
 *  \brief Cyclic Redundancy Check or CRC is used to detect error in data
 *  @param bytes Integer array which contains payload
 *  @param len of the payload
 *  @return unsigned 32 bit integer is returned which is the computed CRC
 */
uint32_t Compute_CRC32(uint8_t *bytes, int len);
