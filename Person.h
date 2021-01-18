#ifndef PERSON_H
#define PERSON_H

/**
 * ======================= required ========================
 * Declaration of the Meeting struct.
 * No need the implement it here or at Person.c file.
 * It is required for compilation.
 * */
#include "Meeting.h"
typedef struct Meeting Meeting;
// ==========================================================


/**
 * The type represents the id of a person.
 * - Note - you must use this to describe person id.
 */
typedef size_t IdT;

/**
 * @def PERSON_INITIAL_SIZE
 * the initial size for the dynamic arrays the person owns.
 */
#define PERSON_INITIAL_SIZE 16UL

/**
 * @def PERSON_GROWTH_FACTOR
 * the growth factor in case of extending the dynamic arrays
 * the person owns.
 */
#define PERSON_GROWTH_FACTOR 2UL

#define BASE 10
#define ID_LENGTH 9
/**
 * @struct Person
 * Declaration for Person struct.
 * @param id the id of the person.
 * @param name the name of the person
 * - note - each person owns the memory of his name.
 * @param age the age of the person.
 * @param is_sick boolean value which indicates if
 * the person is sick (1), or not (0).
 * @param infection_rate the infection-rate of the person,
 * calculated with the given score function in the exercise.
 * @param meetings a dynamic array of pointers to meetings.
 * - note - each person owns the dynamic array, but not the
 * meetings themselves.
 * @param num_of_meetings the number of meetings the person owns.
 * @param meetings_capacity the capacity of the meetings array,
 * - the number of seats you allocated for Meeting* elements.
 */
typedef struct Person {
    IdT id;
    char *name;
    size_t age;
    int is_sick;
    double infection_rate;
    Meeting **meetings;
    size_t num_of_meetings;
    size_t meetings_capacity;
} Person;

/**
 * Allocates dynamically new person with (at least) the following
 * input data:
 * @param id (IdT) the id of the person.
 * @param name (char *) the name of the person (received as string) (ex: "Moshe Stam-shem").
 * @param age (size_t) the age of the person.
 * @param is_sick (int) boolean value (0/1) which indicates if the person is sick.
 * @return (struct Person *) pointer to dynamically allocated person,
 * @if_fails returns NULL.
 * @assumption the input would be valid.
 */
Person *PersonAlloc(IdT id, char *name, size_t age, int is_sick);

/**
 * Frees everything the person has allocated and the pointer itself.
 * @param p_person (struct Person **) pointer to dynamically allocated person.
 * @assumption you can not assume anything.
 */
void PersonFree(Person **p_person);

/**
 * Returns a pointer to the meeting with the given person (the person who has the given ID).
 * @param person (struct Person *) the person we would like to get his/her meeting.
 * @par id (IdT) the id of the person she/he met with.
 * @return (Meeting *) a pointer to meeting, returns NULL
 * if no such exists.
 * @if_fails returns NULL.
 * @assumption you can not assume anything.
 */
Meeting *PersonGetMeetingById(const Person *const person, IdT id);

/**
 * The function is used to compare people.
 * @param person_1 (struct Person *) person we would like to compare.
 * @param person_2 (struct Person *) person we would like to compare.
 * @return 0 if the two people are to be considered equal,
 *        -1 if person_1 should be before person_2.
 *         1 if person_1 should be after person_2.
 * @if_fails can not fail.
 * @assumption the input would be valid (pointers to existing people).
 */
int PersonCompareById(const Person *person_1, const Person *person_2);

/**
 * The function is used to compare people.
 * @param person_1 (struct Person *) person we would like to compare.
 * @param person_2 (struct Person *) person we would like to compare.
 * @return 0 if the two people are to be considered equal,
 *        -1 if person_1 should be before person_2.
 *         1 if person_1 should be after person_2.
 * @if_fails can not fail.
 * @assumption the input would be valid (pointers to existing people).
 */
int PersonCompareByName(const Person *person_1, const Person *person_2);

/**
 * The function is used to compare people.
 * @param person_1 (struct Person *) person we would like to compare.
 * @param person_2 (struct Person *) person we would like to compare.
 * @return 0 if the two people are to be considered equal,
 *        -1 if person_1 should be before person_2.
 *         1 if person_1 should be after person_2.
 * @if_fails can not fail.
 * @assumption the input would be valid (pointers to existing people).
 */
int PersonCompareByInfectionRate(const Person *person_1, const Person *person_2);

/**
 * The function is used to compare people.
 * @param person_1 (struct Person *) person we would like to compare.
 * @param person_2 (struct Person *) person we would like to compare.
 * @return 0 if the two people are to be considered equal,
 *        -1 if person_1 should be before person_2.
 *         1 if person_1 should be after person_2.
 * @if_fails can not fail.
 * @assumption the input would be valid (pointers to existing people).
 */
int PersonCompareByAge(const Person *person_1, const Person *person_2);

#endif //PERSON_H