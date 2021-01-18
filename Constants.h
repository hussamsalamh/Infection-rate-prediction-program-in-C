#ifndef CONSTANTS_H_
#define CONSTANTS_H_

/**
 * @brief The maximal length of line in the input file.
 * Notice: It includes a '\0',
 */
#define MAX_LEN_OF_LINE 257


// === Treatments and Thresholds. ===

/**
 * The threshold which is required to be quarantined,
 * and the message to be printed at the end of it..
 */
#define REGULAR_QUARANTINE_THRESHOLD 0.1
#define REGULAR_QUARANTINE_MSG "Quarantine: %s %lu %lu %lf.\n" // name id age infection_rate

/**
 * The threshold which is required to be hospitalized,
 * and the message to be printed at the end of it..
 */
#define MEDICAL_SUPERVISION_THRESHOLD  0.3
#define MEDICAL_SUPERVISION_THRESHOLD_MSG "Hospitalization: %s %lu %lu %lf.\n" // name id age infection_rate

/**
 * The threshold which is required to be quarantined,
 * and the message to be printed at the end of it..
 */
#define CLEAN_MSG "No-Treatment: %s %lu %lu %lf.\n" // name id age infection_rate

/**
 * Age threshold.
 * Each age above receives INFECTION_RATE_ADDITION_DUE_TO_AGE extra points to the infection rate.
 */
#define AGE_THRESHOLD 55
#define INFECTION_RATE_ADDITION_DUE_TO_AGE 0.08

/**
 * Minimal distance two people can be in.
 */
#define MIN_DISTANCE 1.0

/**
 * The length of the video, also the maximal time
 * two people can be seen together.
 */
#define MAX_MEASURE 45.0

#endif //CONSTANTS_H_