#include "Meeting.h"

/**
 * Allocating (dynamically) new meeting with (at least) the following
 * input data:
 * @param person_1 (struct Person *) pointer to the first person in the meeting.
 * @param person_2 (struct Person *) pointer to the second person in the meeting.
 * @param measure (double) the time of the meeting in minutes.
 * @param distance (double) the distance the two people where in.
 * @return (struct Meeting *) pointer to dynamically allocated meeting.
 * @if_fails returns NULL.
 */
Meeting *MeetingAlloc(Person *person_1, Person *person_2, double measure, double distance)
{
    Meeting *meeting = (Meeting *) malloc(sizeof(Meeting));
    if (meeting == NULL) // check if the mallco work
    {
        return NULL;
    }
    meeting->person_1 = person_1;
    meeting->person_2 = person_2;
    meeting->distance = distance;
    meeting->measure = measure;
    return meeting;
}

/**
 * This function for free the meeting
 * @param p_meeting meeting
 */
void MeetingFree(Meeting **p_meeting)
{
    if (p_meeting == NULL || *p_meeting ==NULL)
    {
        return;
    }
    free(*p_meeting);
    p_meeting = NULL;
}

/**
 *  Returns a pointer to one of the persons in the meeting.
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
 */
Person *MeetingGetPerson(const Meeting *const meeting, size_t person_ind)
{
    if (meeting == NULL)
    {
        return NULL;
    }
    if (person_ind == 1)
    {
        return meeting->person_1;
    }
    else if (person_ind == 2)
    {
        return meeting->person_2;
    }
    else
    {
        return NULL;
    }
}

