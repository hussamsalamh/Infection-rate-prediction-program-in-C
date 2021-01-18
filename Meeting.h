#ifndef MEETING_H
#define MEETING_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * ======================= required ========================
 * Declaration of the Person struct.
 * No need the implement it here or at Meeting.c file.
 * It is required for compilation (because the meeting
 * struct uses person, and the person struct uses meetings).
 * */
#include "Person.h"
typedef struct Person Person;
// ==========================================================

/**
 * @struct Meeting
 * Declaration for Meeting struct.
 * @param person_1 the first person in the meeting.
 * @param person_2 the second person in the meeting.
 * @param measure the time of the meeting (in minutes).
 * @param distance the distance they were in (in distance).
 */
typedef struct Meeting {
    Person *person_1;
    Person *person_2;
    double measure;
    double distance;
} Meeting ;



/**
 * Allocating (dynamically) new meeting with (at least) the following
 * input data:
 * @param person_1 (struct Person *) pointer to the first person in the meeting.
 * @param person_2 (struct Person *) pointer to the second person in the meeting.
 * @param measure (double) the time of the meeting in minutes.
 * @param distance (double) the distance the two people where in.
 * @return (struct Meeting *) pointer to dynamically allocated meeting.
 * @if_fails returns NULL.
 * @assumption the inputs would be valid.
 */
Meeting *MeetingAlloc(Person *person_1, Person *person_2, double measure, double distance);

/**
 * Frees everything the meeting has allocated and the pointer itself.
 * @param p_meeting (struct Meeting **) pointer to dynamically allocated meeting.
 * @assumption you can not assume anything.
 */
void MeetingFree(Meeting **p_meeting);

/**
 * Returns a pointer to one of the persons in the meeting.
 * @param meeting (struct Meeting *) the meeting we would like to
 * get its person.
 * @param person_ind (size_t) the index of the person we
 * want (can be either 1 or 2).
 * @return (struct Person *) pointer to the person we want.
 * person_ind == 1 ==> return person_1 (according the person_1 given in
 * MeetingAlloc).
 * person_ind == 2 ==> return person_2 (according to the person_2 given in
 * MeetingAlloc).
 * @if_failds return NULL
 * @assumption you can not assume anything.
 */
Person *MeetingGetPerson(const Meeting * const meeting, size_t person_ind);


#endif //MEETING_H