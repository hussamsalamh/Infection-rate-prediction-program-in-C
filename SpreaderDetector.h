#ifndef SPREADERDETECTOR_H
#define SPREADERDETECTOR_H

#include "Meeting.h"
#include "Person.h"
#include "Constants.h"

/**
 * @def SPREADER_DETECTOR_INITIAL_SIZE
 * the initial size for the dynamic arrays the spreader owns.
 */
#define SPREADER_DETECTOR_INITIAL_SIZE 16UL

/**
 * @def SPREADER_DETECTOR_GROWTH_FACTOR
 * the growth factor in case of increasing the dynamic arrays
 * the spreader owns.
 */
#define SPREADER_DETECTOR_GROWTH_FACTOR 2UL

#define BASE 10
#define ID_LENGTH 9
/**
 * @struct SpreaderDetector
 * @param people a dynamic array of pointers to people.
 * - note - each spreader_detector owns the dynamic array, but not the
 * people themselves.
 * @param people_size the size of the people array.
 * @param people_cap the capacity of the people array.
 * @param meetings a dynamic array of pointers to meetings.
 * - note - each spreader_detector owns the dynamic array, but not the
 * meetings themselves.
 * @param meetings_size the size of the meetings array.
 * @param meetings_cap the capacity of the meetings array.
 */
typedef struct SpreaderDetector {
  Person **people;
  size_t people_size;
  size_t people_cap;
  Meeting **meetings;
  size_t meeting_size;
  size_t meeting_cap;
} SpreaderDetector;

/**
 * Allocates (dynamically) a spreader detector with no meetings and
 * no people.
 * @return pointer to dynamically allocated SpreaderDetector struct.
 * @if_fails returns NULL.
 * @assumption you can not assume anything.
 */
SpreaderDetector *SpreaderDetectorAlloc();


/**
 * Frees the given spreader detector.
 * @param p_spreader_detector pointer to spreader detector pointer
 * should be freed.
 * @assumption you can not assume anything.
 */
void SpreaderDetectorFree(SpreaderDetector **p_spreader_detector);

/**
 * Adds the given person to the spreader detector.
 * Important - each person is unique (compare by id).
 * @param spreader_detector the spreader detector we wants to add the person to.
 * @param person the person we wants to add to the spreader detector.
 * @return 1 if the person was added successfully, 0 otherwise.
 * @if_fails returns 0.
 * @assumption you can not assume anything.
 */
int SpreaderDetectorAddPerson(SpreaderDetector *spreader_detector, Person *person);

/**
 * Adds the given meeting to the spreader detector.
 * Important - the people in the meeting should exist in the spreader detector.
 * @param spreader_detector the spreader detector we wants to add the meeting to.
 * @param meeting the meeting we wants to add to the spreader detector.
 * @return 1 if the meeting was added successfully, 0 otherwise.
 * @if_fails returns 0.
 * @assumption you can not assume anything.
 */
int SpreaderDetectorAddMeeting(SpreaderDetector *spreader_detector, Meeting *meeting);

/**
 * This function reads the file of the meeting, parses to file into meetings,
 * and inserts it to the spreader detector.
 * @param spreader_detector the spreader detector we wants to read the meetings into.
 * @param path the path to the meetings file.
 * @assumption you can assume that the path to the file is ok (and anything but that).
 */
void SpreaderDetectorReadMeetingsFile(SpreaderDetector *spreader_detector, const char *path);

/**
 * This function reads the file of the people, parses to file into person objects,
 * and inserts it to the spreader detector.
 * @param spreader_detector the spreader detector we wants to read the people into.
 * @param path the path to the people file.
 * @assumption you can assume that the path to the file is ok (and anything but that).
 */
void SpreaderDetectorReadPeopleFile(SpreaderDetector *spreader_detector, const char *path);

/**
 * Returns the infection rate of the person with the given id.
 * @param spreader_detector the spreader detector contains the person.
 * @param id the id of the person we are looking for.
 * @return the infection rate of the person, if not person exists -
 * returns -1.
 * @if_fails returns -1.
 * @assumption you can assume anything.
 */
double SpreaderDetectorGetInfectionRateById(SpreaderDetector *spreader_detector, IdT id);

/**
 * This function runs the algorithm which calculates the infection rates of the people.
 * When this algorithm ends, the user should be able to use the function
 * SpreaderDetectorGetInfectionRateById and get the infection rate of each person.
 * @param spreader_detector a spreader_detector.
 * @assumption you can not assume anything.
 */
void SpreaderDetectorCalculateInfectionChances(SpreaderDetector *spreader_detector);

/**
 * Gets the recommendation for treatment for all people based on the parameters above,
 * and prints it to the given file path.
 * @param spreader_detector the spreader detector contains the person.
 * @param file_path the path to the output file.
 * @return returns 1 if printed successfully, 0 otherwise.
 * @if_fails return 0.
 * @assumption you can assume that the path to the file is ok (and anything but that).
 */
int SpreaderDetectorPrintRecommendTreatmentToAll(SpreaderDetector *spreader_detector, const char *file_path);

/**
 * Returns the number of people which are in the spreader detector.
 * @param spreader_detector the spreader detector object.
 * @return the number of people.
 * @if_fails return 0.
 * @assumption you can not assume anything.
 * @note 0 might represent spreader with no people, and fail both.
 * make sure you don't trust the output of the function.
 */
size_t SpreaderDetectorGetNumOfPeople(SpreaderDetector *spreader_detector);

/**
 * Returns the number of meetings which are in the spreader detector.
 * @param spreader_detector the spreader detector object.
 * @return the number of meetings.
 * @if_fails return 0.
 * @assumption you can not assume anything.
 * @note 0 might represent spreader with no meetings, and fail both.
 * make sure you don't trust the output of the function.
 */
size_t SpreaderDetectorGetNumOfMeetings(SpreaderDetector *spreader_detector);

#endif //SPREADERDETECTOR_H